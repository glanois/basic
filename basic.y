// A BASIC grammar interpreter

%{
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <variant>

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern "C" int yywrap();

void yyerror(const char *s);

#include "basic.h"
#include "expression.h"
#include "floatexpression.h"
#include "integerexpression.h"
#include "stringexpression.h"
#include "operatorexpression.h"
#include "variableexpression.h"
#include "parenexpression.h"
#include "print.h"
#include "rem.h"
#include "program.h"
#include "multiprogram.h"
#include "let.h"
#include "goto.h"
#include "end.h"
#include "ifthen.h"
#include "read.h"
#include "data.h"
#include "for.h"
#include "next.h"

%}

// token type definition
%union {
   IntValue iVal;
   FloatValue fVal;
   StringValue* sVal;
   Program* progVal;
   Expression* eVal;
   FloatExpression* fxVal;
   StringExpression* sxVal;
   std::vector<Expression*>* eList;
   std::vector<StringValue>* rList;
   std::vector<DataValue>* dList;
   std::vector<Program*>* stmtList;
}

// constant tokens
%token PRINT
%token RUN
%token ENDL
%token LIST
%token COMMA
%token COLON
%token PLUS
%token MINUS
%token MULT
%token DIV
%token EXP
%token SAVE
%token UNSAVE
%token NEW
%token OLD
%token CATALOG
%token SCRATCH
%token RENAME
%token LET
%token GOTO
%token IF
%token THEN
%token END
%token EQUAL
%token LESS
%token GREATER
%token LESSEQUAL
%token GREATEREQUAL
%token NOTEQUAL
%token OPENPAREN
%token CLOSEPAREN
%token DATA
%token READ
%token FOR
%token TO
%token STEP
%token NEXT

// terminal symbols
%token <iVal> INT
%token <sVal> STRING
%token <sVal> DSTRING
%token <fVal> FLOAT
%token <sVal> FVAR
%token <sVal> IVAR
%token <sVal> SVAR
%token <sVal> REMARK

// non-terminal symbols
%type <progVal> program 
%type <eList> exprList
%type <eVal> expr
%type <fxVal> floatExpr
%type <fxVal> addFloatExpr
%type <fxVal> mulFloatExpr
%type <fxVal> expFloatExpr
%type <fxVal> floatTerm
%type <fxVal> integerExpr
%type <fxVal> addIntegerExpr
%type <fxVal> mulIntegerExpr
%type <fxVal> expIntegerExpr
%type <fxVal> integerTerm
%type <sxVal> stringExpr
%type <sxVal> addStringExpr
%type <sxVal> stringTerm
%type <sVal> comp
%type <rList> readList
%type <stmtList> statementList
%type <dList> dataList

%% /* Grammar rules and actions follow */

input:
   /* empty */
   | input line
;

line:
   ENDL
   | stmt ENDL
;

stmt:
   INT { Basic::instance()->remove($1); }
   | INT statementList {
      MultiProgram* mp = new MultiProgram();
      std::vector<Program*>::iterator i;
      for (i = $2->begin(); i != $2->end(); ++i) {
         mp->add((*i));
      }
      Basic::instance()->add($1, mp); }
   | INT program { Basic::instance()->add($1, $2); }
   | RUN         { Basic::instance()->execute(); }
   | LIST        { Basic::instance()->list(std::cout); }
   | NEW         { Basic::instance()->newProgram(); }
   | OLD         { Basic::instance()->oldProgram(); }
   | SAVE        { Basic::instance()->saveProgram(); }
   | UNSAVE      { Basic::instance()->unsaveProgram(); }
   | CATALOG     { Basic::instance()->catalogPrograms(); }
   | SCRATCH     { Basic::instance()->erase(); }
   | RENAME      { Basic::instance()->renameProgram(); }
;

program:
   PRINT exprList { 
      $$ = new Print($2); }
   | REMARK   { 
      $$ = new Rem(*($1)); 
      delete $1; // new()-ed in basic.l
     }
   | LET FVAR EQUAL floatExpr   {
      $$ = new FloatLet(*($2), $4);
      delete $2; // new()-ed in basic.l
   }
   | LET FVAR EQUAL integerExpr   {
      $$ = new FloatLet(
         *($2), 
         new FloatExpression(static_cast<float>($4->value())));
      delete $2; // new()-ed in basic.l
   }
   | LET IVAR EQUAL integerExpr   {
      $$ = new IntegerLet(*($2), $4);
      delete $2; // new()-ed in basic.l
   }
   | LET IVAR EQUAL floatExpr   {
      $$ = new IntegerLet(
         *($2), 
         /* xxx - round() or trunc()? */
         new FloatExpression(static_cast<int>(std::round($4->value())), true));
      delete $2; // new()-ed in basic.l
   }
   | LET SVAR EQUAL stringExpr   {
      $$ = new StringLet(*($2), $4);
      delete $2; // new()-ed in basic.l
   }
   | GOTO INT { $$ = new Goto($2); }
   | END { $$ = new End(); }
   | IF floatExpr comp floatExpr THEN INT { 
      $$ = new FloatIfThen($2, $4, *($3), $6); }
   | IF integerExpr comp floatExpr  THEN INT { 
      $$ = new FloatIfThen(
         new FloatExpression(static_cast<float>($2->value()), true), 
         $4, 
         *($3), 
         $6); }
   | IF floatExpr comp integerExpr  THEN INT { 
      $$ = new FloatIfThen(
         $2, 
         new FloatExpression(static_cast<float>($4->value()), true), 
         *($3), 
         $6); }
   | IF integerExpr comp integerExpr THEN INT { 
      $$ = new FloatIfThen(
         new FloatExpression(static_cast<float>($2->value()), true), 
         new FloatExpression(static_cast<float>($4->value()), true), 
         *($3), 
         $6); }
   | IF stringExpr comp stringExpr THEN INT { 
      $$ = new StringIfThen($2, $4, *($3), $6); }
   | DATA dataList { $$ = new Data(*($2)); }
   | READ readList { $$ = new Read(*($2)); }

   | FOR FVAR EQUAL floatExpr TO floatExpr {
      $$ = new FloatFor($4, $6, NULL, *($2)); }
   | FOR FVAR EQUAL floatExpr TO floatExpr STEP floatExpr {
      $$ = new FloatFor($4, $6, $8, *($2)); }
   | FOR FVAR EQUAL integerExpr TO integerExpr {
      $$ = new FloatFor(
         new FloatExpression(
            static_cast<float>($4->value()), true),
         new FloatExpression(
            static_cast<float>($6->value()), true),
         NULL, 
         *($2)); }
   | FOR FVAR EQUAL integerExpr TO integerExpr STEP integerExpr {
      $$ = new FloatFor(
         new FloatExpression(
            static_cast<float>($4->value()), true),
         new FloatExpression(
            static_cast<float>($6->value()), true),
         new FloatExpression(
            static_cast<float>($8->value()), true),
         *($2)); }
   | NEXT FVAR {
      $$ = new FloatNext(*($2)); }

   | FOR IVAR EQUAL integerExpr TO integerExpr {
      $$ = new IntegerFor(
         new IntegerExpression($4->value()),
         new IntegerExpression($6->value()),
         NULL, 
         *($2)); }
   | FOR IVAR EQUAL integerExpr TO integerExpr STEP integerExpr {
      $$ = new IntegerFor(
         new IntegerExpression($4->value()),
         new IntegerExpression($6->value()), 
         new IntegerExpression($8->value()),
         *($2)); }

   | NEXT IVAR { 
      $$ = new IntegerNext(*($2)); }
;

comp:
   EQUAL          { $$ = new StringValue("=", false); }
   | LESS         { $$ = new StringValue("<", false); }
   | GREATER      { $$ = new StringValue(">", false); }
   | LESSEQUAL    { $$ = new StringValue("<=", false); }
   | GREATEREQUAL { $$ = new StringValue(">=", false); }
   | NOTEQUAL     { $$ = new StringValue("<>", false); }
;

readList:
   FVAR    { $$ = new std::vector<StringValue>(1, *($1)); }
   | IVAR { $$ = new std::vector<StringValue>(1, *($1)); }
   | SVAR { $$ = new std::vector<StringValue>(1, *($1)); }
   | readList COMMA FVAR {
      $1->push_back(*($3));
      $$ = $1; }
   | readList COMMA IVAR {
      $1->push_back(*($3));
      $$ = $1; }
   | readList COMMA SVAR {
      $1->push_back(*($3));
      $$ = $1; }
;

dataList:
   INT { $$ = new std::vector<DataValue>(1, $1); }
   | FLOAT { $$ = new std::vector<DataValue>(1, $1); }
   | STRING { $$ = new std::vector<DataValue>(1, StringValue(*($1))); }
   | DSTRING { $$ = new std::vector<DataValue>(1, StringValue($1->c_str(), false)); }
   | dataList COMMA INT { 
      $1->push_back($3); 
      $$ = $1; }
   | dataList COMMA FLOAT { 
      $1->push_back($3); 
      $$ = $1; }
   | dataList COMMA STRING { // quoted string
      $1->push_back(StringValue(*($3))); 
      $$ = $1; }
   | dataList COMMA DSTRING { // unquoted string
      $1->push_back(StringValue($3->c_str(), false)); 
      $$ = $1; }
;

statementList:
   program { $$ = new std::vector<Program*>(1, $1); }
   | statementList COLON program	{ 
      $1->push_back($3);
      $$ = $1; }
;

exprList:
	expr { 
      $$ = new std::vector<Expression*>(1, $1); }
	| exprList COMMA expr {
      $1->push_back($3);
      $$ = $1; }
;

expr:
   floatExpr
   | integerExpr
   | stringExpr
;
	
floatExpr:
	addFloatExpr
;

addFloatExpr:
	mulFloatExpr
	| floatExpr PLUS mulFloatExpr 	{ 
      $$ = new FloatOperatorExpression($1, $3, '+'); }

   | floatExpr MINUS mulFloatExpr	{ 
      $$ = new FloatOperatorExpression($1, $3, '-'); }

   | mulFloatExpr PLUS floatExpr 	{ 
      $$ = new FloatOperatorExpression($1, $3, '+'); }

   | mulFloatExpr MINUS floatExpr { 
      $$ = new FloatOperatorExpression($1, $3, '-'); }

   | mulFloatExpr PLUS integerExpr 	{ 
      $$ = new FloatOperatorExpression(
         $1, 
         new FloatExpression(static_cast<float>($3->value()), true), 
         '+'); }
;

mulFloatExpr:
	expFloatExpr
	| expFloatExpr MULT expFloatExpr { 
      $$ = new FloatOperatorExpression($1, $3, '*'); }
   | expFloatExpr DIV expFloatExpr { 
      $$ = new FloatOperatorExpression($1, $3, '/'); }
   | MINUS expFloatExpr { 
      $$ = new FloatOperatorExpression($2, 'n'); }
;

expFloatExpr:
   floatTerm
	| floatTerm EXP floatTerm { 
      $$ = new FloatOperatorExpression($1, $3, '^'); }
	| integerTerm EXP floatTerm { 
      $$ = new FloatOperatorExpression(
         new FloatExpression(static_cast<float>($1->value()), true), 
         $3, 
         '^'); }
	| floatTerm EXP integerTerm { 
      $$ = new FloatOperatorExpression(
         $1, 
         new FloatExpression(static_cast<float>($3->value()), true), 
         '^'); }
;

floatTerm:
	FLOAT { 
      $$ = new FloatExpression($1); }
	| FVAR {
      $$ = new FloatVariableExpression(*($1));
      delete $1; }
	| OPENPAREN addFloatExpr CLOSEPAREN	{ 
      $$ = new FloatParenExpression($2); }
;

integerExpr:
	addIntegerExpr
;

addIntegerExpr:
	mulIntegerExpr

	| integerExpr PLUS mulIntegerExpr { 
      $$ = new FloatOperatorExpression(
         new FloatExpression(static_cast<float>($1->value()), true), 
         new FloatExpression(static_cast<float>($3->value()), true), 
         '+'); }

	| integerExpr MINUS mulIntegerExpr { 
      $$ = new FloatOperatorExpression(
         new FloatExpression(static_cast<float>($1->value()), true), 
         new FloatExpression(static_cast<float>($3->value()), true), 
         '-'); }

	| mulIntegerExpr PLUS integerExpr { 
      $$ = new FloatOperatorExpression(
         new FloatExpression(static_cast<float>($1->value()), true), 
         new FloatExpression(static_cast<float>($3->value()), true), 
         '+'); }

	| mulIntegerExpr PLUS floatExpr { 
      $$ = new FloatOperatorExpression(
         new FloatExpression(static_cast<float>($1->value()), true), 
         $3, 
         '+');
   }

	| mulIntegerExpr MINUS integerExpr {
      $$ = new FloatOperatorExpression(
         new FloatExpression(static_cast<float>($1->value()), true), 
         new FloatExpression(static_cast<float>($3->value()), true), 
         '-'); }
;

mulIntegerExpr:
	expIntegerExpr
	| expIntegerExpr MULT expIntegerExpr { 
      $$ = new FloatOperatorExpression(
         new FloatExpression(static_cast<float>($1->value()), true), 
         new FloatExpression(static_cast<float>($3->value()), true),
         '*'); }
   | expIntegerExpr DIV expIntegerExpr { 
      $$ = new FloatOperatorExpression(
         new FloatExpression(static_cast<float>($1->value()), true), 
         new FloatExpression(static_cast<float>($3->value()), true),
         '/'); }
   | MINUS expIntegerExpr { 
      $$ = new FloatOperatorExpression(
         new FloatExpression(static_cast<float>($2->value()), true), 
         'n'); }
;

expIntegerExpr:
	integerTerm
	| integerTerm EXP integerTerm { 
      $$ = new FloatOperatorExpression(
         new FloatExpression(static_cast<float>($1->value()), true), 
         new FloatExpression(static_cast<float>($3->value()), true), 
            '^'); }
;

integerTerm:
	INT { 
      $$ = new FloatExpression(static_cast<float>($1), true); }
	| IVAR {
      $$ = new IntegerVariableExpression(*($1));
      delete $1; }
   | OPENPAREN addIntegerExpr CLOSEPAREN { 
      $$ = new FloatParenExpression(new FloatExpression(static_cast<float>($2->value()), true)); }
;

stringExpr:
   stringTerm
   | addStringExpr
;

addStringExpr:
   stringTerm PLUS stringTerm { $$ = new StringOperatorExpression($1, $3, '+'); }
;

stringTerm:
	STRING { 
      $$ = new StringExpression(*($1)); 
      delete $1; // new()-ed in basic.l
   }
   | SVAR { 
      $$ = new StringVariableExpression(*($1)); 
      delete $1; // new()-ed in basic.l
   }
   | OPENPAREN addStringExpr CLOSEPAREN { $$ = new StringParenExpression($2); }
;

%%

int main(int argc, char **argv){
	std::cout << "Welcome to BASIC!\n";
	Basic::instance()->newProgram();
	std::cout << '>';
	do {
		yyparse();
	} while( !feof(yyin) );
	
	return 0;
}

void yyerror(const char *s){
	std::cout << "Error: " << s << std::endl;
}

int yywrap(){
	if( yyin == stdin )
		return 1;
	fclose(yyin);
	yyin = stdin;
	return 0;
}
