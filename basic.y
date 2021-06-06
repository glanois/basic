// A BASIC grammar interpreter

%{
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

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
	int iVal;
	float fVal;
   char* sVal;
	Program *progVal;
	Expression *eVal;
   FloatExpression *fxVal;
	StringExpression *sxVal;
	std::vector<Expression*> *eList;
	std::vector<std::string> *rList;
   /* xxx - this vector needs to hold float, int, and std::string. */
	std::vector<float> *dList;
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
      std::cout << "basic.y DEBUG: program PRINT exprList" << std::endl;
      $$ = new Print($2); }
   | REMARK	{ 
      $$ = new Rem(std::string($1)); 
      free($1);	// malloced in basic.l
     }
   | LET FVAR EQUAL floatExpr	{
      $$ = new FloatLet(std::string($2), $4);
      free($2);	// malloced in basic.l
   }
   | LET FVAR EQUAL integerExpr	{
      $$ = new FloatLet(
         std::string($2), 
         new FloatExpression(static_cast<float>($4->value())));
      free($2);	// malloced in basic.l
   }
	| LET IVAR EQUAL integerExpr	{
      $$ = new IntegerLet(std::string($2), $4);
      free($2);	// malloced in basic.l
   }
	| LET IVAR EQUAL floatExpr	{
      $$ = new IntegerLet(
         std::string($2), 
         /* xxx - round() or trunc()? */
         new FloatExpression(static_cast<int>(std::round($4->value())), true));
      free($2);	// malloced in basic.l
   }
   | LET SVAR EQUAL stringExpr	{
      $$ = new StringLet(std::string($2), $4);
      free($2);	// malloced in basic.l
   }
	| GOTO INT { $$ = new Goto($2); }
	| END { $$ = new End(); }
	| IF floatExpr comp floatExpr THEN INT { 
      $$ = new FloatIfThen($2, $4, $3, $6); }
   | IF integerExpr comp floatExpr  THEN INT { 
      $$ = new FloatIfThen(
         new FloatExpression(static_cast<float>($2->value()), true), 
         $4, 
         $3, 
         $6); }
   | IF floatExpr comp integerExpr  THEN INT { 
      $$ = new FloatIfThen(
         $2, 
         new FloatExpression(static_cast<float>($4->value()), true), 
         $3, 
         $6); }
   | IF integerExpr comp integerExpr THEN INT { 
      $$ = new FloatIfThen(
         new FloatExpression(static_cast<float>($2->value()), true), 
         new FloatExpression(static_cast<float>($4->value()), true), 
         $3, 
         $6); }
   | IF stringExpr comp stringExpr THEN INT { 
      $$ = new StringIfThen($2, $4, $3, $6); }
	| DATA dataList { $$ = new Data(*$2); }
	| READ readList { $$ = new Read(*$2); }

	| FOR FVAR EQUAL floatExpr TO floatExpr {
      $$ = new FloatFor($4, $6, NULL, $2); }
	| FOR FVAR EQUAL floatExpr TO floatExpr STEP floatExpr {
      $$ = new FloatFor($4, $6, $8, $2); }
	| FOR FVAR EQUAL integerExpr TO integerExpr {
      $$ = new FloatFor(
         new FloatExpression(
            static_cast<float>($4->value()), true),
         new FloatExpression(
            static_cast<float>($6->value()), true),
            NULL, 
            $2); }
	| FOR FVAR EQUAL integerExpr TO integerExpr STEP integerExpr {
      $$ = new FloatFor(
         new FloatExpression(
            static_cast<float>($4->value()), true),
         new FloatExpression(
            static_cast<float>($6->value()), true),
         new FloatExpression(
            static_cast<float>($8->value()), true),
            $2); }
	| NEXT FVAR {
      $$ = new FloatNext($2); }

	| FOR IVAR EQUAL integerExpr TO integerExpr {
      $$ = new IntegerFor(
         new IntegerExpression(
            static_cast<int>(std::round($4->value()))),
         new IntegerExpression(
            static_cast<int>(std::round($6->value()))), 
            NULL, 
            $2); }
	| FOR IVAR EQUAL integerExpr TO integerExpr STEP integerExpr {
      $$ = new IntegerFor(
         new IntegerExpression(
            static_cast<int>(std::round($4->value()))),
         new IntegerExpression(
            static_cast<int>(std::round($6->value()))), 
         new IntegerExpression(
            static_cast<int>(std::round($8->value()))),
            $2); }

	| NEXT IVAR { 
      $$ = new IntegerNext($2); }
;

comp:
   EQUAL					{ $$ = "="; }
	| LESS					{ $$ = "<"; }
	| GREATER				{ $$ = ">"; }
	| LESSEQUAL				{ $$ = "<="; }
	| GREATEREQUAL			{ $$ = ">="; }
	| NOTEQUAL				{ $$ = "<>"; }
;

readList:
	FVAR	 { $$ = new std::vector<std::string>(1, $1); }
	| IVAR { $$ = new std::vector<std::string>(1, $1); }
	| SVAR { $$ = new std::vector<std::string>(1, $1); }
	| readList COMMA FVAR {
      $1->push_back($3);
      $$ = $1; }
	| readList COMMA IVAR {
      $1->push_back($3);
      $$ = $1; }
	| readList COMMA SVAR {
      $1->push_back($3);
      $$ = $1; }
;

/* xxx - that vector has to hold FLOAT, INT, and STRING. */
dataList:
	FLOAT { $$ = new std::vector<float>(1, $1); }
	| dataList COMMA FLOAT { 
      $1->push_back($3); 
      $$ = $1; }
;

statementList:
	program { $$ = new std::vector<Program*>(1, $1); }
	| statementList COLON program	{ 
      $1->push_back($3);
      $$ = $1; }
;

exprList:
	expr					{ 
      std::cout << "basic.y DEBUG: exprList - expr" << std::endl;
      $$ = new std::vector<Expression*>(1, $1); }
	| exprList COMMA expr {
      $1->push_back($3);
      $$ = $1; }
;

expr:
   floatExpr {
      std::cout << "basic.y DEBUG: expr - floatExpr" << std::endl; }
   | integerExpr {
      std::cout << "basic.y DEBUG: expr - integerExpr" << std::endl; }
   | stringExpr {
      std::cout << "basic.y DEBUG: expr - stringExpr" << std::endl; }
;
	
floatExpr:
	addFloatExpr {
      std::cout << "basic.y DEBUG: floatExpr - addFloatExpr" << std::endl; }
;

addFloatExpr:
	mulFloatExpr  {
      std::cout << "basic.y DEBUG: addFloatExpr - mulFloatExpr" << std::endl; }
	| floatExpr PLUS mulFloatExpr 	{ 
      std::cout << "basic.y DEBUG: addFloatExpr - floatExpr PLUS mulFloatExpr " << $1->value() << " + " << $3->value() << std::endl;
      $$ = new FloatOperatorExpression($1, $3, '+'); }

   | floatExpr MINUS mulFloatExpr	{ 
      $$ = new FloatOperatorExpression($1, $3, '-'); }

   | mulFloatExpr PLUS floatExpr 	{ 
      std::cout << "basic.y DEBUG: addFloatExpr - mulFloatExpr PLUS floatExpr " << $1->value() << " + " << $3->value() << std::endl;
      $$ = new FloatOperatorExpression($1, $3, '+'); }

   | mulFloatExpr MINUS floatExpr { 
      std::cout << "basic.y DEBUG: addFloatExpr - mulFloatExpr MINUS floatExpr " << $1->value() << " - " << $3->value() << std::endl;
      $$ = new FloatOperatorExpression($1, $3, '-'); }

   | mulFloatExpr PLUS integerExpr 	{ 
      std::cout << "basic.y DEBUG: addFloatExpr - mulFloatExpr PLUS integerExpr " << $1->value() << " + " << $3->value() << std::endl;
      $$ = new FloatOperatorExpression(
         $1, 
         new FloatExpression(static_cast<float>($3->value()), true), 
         '+'); }
;

mulFloatExpr:
	expFloatExpr {
      std::cout << "basic.y DEBUG: mulFloatExpr - expFloatExpr " << $1->value() << std::endl; }
	| expFloatExpr MULT expFloatExpr { 
      std::cout << "basic.y DEBUG: mulFloatExpr - expFloatExpr MULT expFloatExpr " << $1->value() << " + " << $3->value() << std::endl;
      $$ = new FloatOperatorExpression($1, $3, '*'); }
   | expFloatExpr DIV expFloatExpr { 
      $$ = new FloatOperatorExpression($1, $3, '/'); }
   | MINUS expFloatExpr { 
      $$ = new FloatOperatorExpression($2, 'n'); }
;

expFloatExpr:
   floatTerm {
      std::cout << "basic.y DEBUG: expFloatExpr - floatTerm " << $1->value() << std::endl; }
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
      std::cout << "basic.y DEBUG: floatTerm FLOAT = " << $1 << std::endl;
      $$ = new FloatExpression($1); }
	| FVAR {
      $$ = new FloatVariableExpression(std::string($1));
      free($1); }
	| OPENPAREN addFloatExpr CLOSEPAREN	{ 
      $$ = new FloatParenExpression($2); }
;

integerExpr:
	addIntegerExpr {
      std::cout << "basic.y DEBUG: integerExpr - addIntegerExpr " << std::endl; }
;

addIntegerExpr:
	mulIntegerExpr {
      std::cout << "basic.y DEBUG: addIntegerExpr - mulIntegerExpr " << std::endl; }

	| integerExpr PLUS mulIntegerExpr { 
      std::cout << "basic.y DEBUG: addIntegerExpr - integerExpr PLUS mulIntegerExpr " << std::endl;
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
      std::cout << "basic.y DEBUG: addIntegerExpr - mulIntegerExpr PLUS floatExpr " << std::endl;
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
	expIntegerExpr {
      std::cout << "basic.y DEBUG: mulIntegerExpr - expIntegerExpr " << std::endl; }
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
	integerTerm {
      std::cout << "basic.y DEBUG: expIntegerExpr - integerTerm " << std::endl; }
	| integerTerm EXP integerTerm { 
      $$ = new FloatOperatorExpression(
         new FloatExpression(static_cast<float>($1->value()), true), 
         new FloatExpression(static_cast<float>($3->value()), true), 
            '^'); }
;

integerTerm:
	INT { 
      std::cout << "basic.y DEBUG: integerTerm INT = " << $1 << std::endl;
      $$ = new FloatExpression(static_cast<float>($1), true); }
	| IVAR {
      $$ = new IntegerVariableExpression(std::string($1));
      free($1); }
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
      $$ = new StringExpression(std::string($1)); 
      free($1);	// malloced in basic.l
   }
   | SVAR { 
      $$ = new StringVariableExpression($1); 
      free($1); 	// malloced in basic.l
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
