// A BASIC grammar interpreter

%{
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

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
	float dVal;
   char* sVal;
	Program *progVal;
	Expression *eVal;
   FloatExpression *dxVal;
	IntegerExpression *ixVal;
	StringExpression *sxVal;
	std::vector<Expression*> *eList;
	std::vector<std::string> *sList;
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
%token <dVal> FLOAT
%token <sVal> FVAR
%token <sVal> IVAR
%token <sVal> SVAR
%token <sVal> REMARK

// non-terminal symbols
%type <progVal> program 
%type <eList> exprList
%type <eVal> expr
%type <dxVal> floatExpr
%type <dxVal> addFloatExpr
%type <dxVal> mulFloatExpr
%type <dxVal> expFloatExpr
%type <dxVal> floatTerm
%type <ixVal> integerExpr
%type <ixVal> addIntegerExpr
%type <ixVal> mulIntegerExpr
%type <ixVal> expIntegerExpr
%type <ixVal> integerTerm
%type <sxVal> stringExpr
%type <sxVal> addStringExpr
%type <sxVal> stringTerm
%type <sVal> comp
%type <sList> stringList
%type <stmtList> statementList
%type <dList> floatList

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
	INT					{ Basic::instance()->remove($1); }
	| INT statementList { MultiProgram* mp = new MultiProgram();
                        std::vector<Program*>::iterator i;
                        for (i = $2->begin(); i != $2->end(); ++i)
                        {
                           mp->add((*i));
                        }
								Basic::instance()->add($1, mp); }
	| INT program		{ Basic::instance()->add($1, $2); }
	| RUN				{ Basic::instance()->execute(); }
	| LIST				{ Basic::instance()->list(std::cout); }
	| NEW				{ Basic::instance()->newProgram(); }
	| OLD				{ Basic::instance()->oldProgram(); }
	| SAVE				{ Basic::instance()->saveProgram(); }
	| UNSAVE			{ Basic::instance()->unsaveProgram(); }
	| CATALOG			{ Basic::instance()->catalogPrograms(); }
	| SCRATCH			{ Basic::instance()->erase(); }
	| RENAME			{ Basic::instance()->renameProgram(); }
;

program:
	PRINT exprList { $$ = new Print($2); }
   | REMARK	{ 
      $$ = new Rem(std::string($1)); 
      free($1);	// malloced in basic.l
     }
   | LET FVAR EQUAL floatExpr	{
      $$ = new FloatLet(std::string($2), $4);
      free($2);	// malloced in basic.l
   }
	| LET IVAR EQUAL integerExpr	{
      printf("basic.y program: LET IVAR EQUAL integerExpr IVAR = %s integerExpr = %s\n", $2, $4->list().c_str());
      $$ = new IntegerLet(std::string($2), $4);
      free($2);	// malloced in basic.l
   }
   | LET SVAR EQUAL stringExpr	{
      $$ = new StringLet(std::string($2), $4);
      free($2);	// malloced in basic.l
   }
	| GOTO INT				{ $$ = new Goto($2); }
	| END					{ $$ = new End(); }
	| IF floatExpr  comp floatExpr  THEN INT { $$ = new FloatIfThen($2, $4, $3, $6); }
   | IF integerExpr comp integerExpr THEN INT { $$ = new IntegerIfThen($2, $4, $3, $6); }
   /* xxx | IF stringExpr comp stringExpr THEN INT
   { $$ = new StringIfThen($2, $4, $3, $6); } */
	| DATA floatList		{ $$ = new Data(*$2); }
	| READ stringList		{ $$ = new Read(*$2); }
	| FOR FVAR EQUAL floatExpr TO floatExpr {
								$$ = new FloatFor($4, $6, NULL, $2);
							}
	| FOR FVAR EQUAL floatExpr TO floatExpr STEP floatExpr {
								$$ = new FloatFor($4, $6, $8, $2);
							}
	| NEXT FVAR				{ $$ = new FloatNext($2); }
	| FOR IVAR EQUAL integerExpr TO integerExpr {
								$$ = new IntegerFor($4, $6, NULL, $2);
							}
	| FOR IVAR EQUAL integerExpr TO integerExpr STEP integerExpr {
								$$ = new IntegerFor($4, $6, $8, $2);
							}
	| NEXT IVAR				{ $$ = new IntegerNext($2); }
;

comp:
   EQUAL					{ $$ = "="; }
	| LESS					{ $$ = "<"; }
	| GREATER				{ $$ = ">"; }
	| LESSEQUAL				{ $$ = "<="; }
	| GREATEREQUAL			{ $$ = ">="; }
	| NOTEQUAL				{ $$ = "<>"; }
;

stringList:
	SVAR						{ $$ = new std::vector<std::string>(1, $1); }
	| stringList COMMA FVAR	{
								$1->push_back($3);
								$$ = $1;
							}
	| stringList COMMA IVAR	{
								$1->push_back($3);
								$$ = $1;
							}
	| stringList COMMA SVAR	{
								$1->push_back($3);
								$$ = $1;
							}
;

statementList:
	program								{ $$ = new std::vector<Program*>(1, $1); }
	| statementList COLON program	{ $1->push_back($3);
											$$ = $1;
										}
;

floatList:
	FLOAT						{ $$ = new std::vector<float>(1, $1); }
	| INT						{ $$ = new std::vector<float>(1, $1); }
	| floatList COMMA FLOAT	{
									$1->push_back($3);
									$$ = $1;
								}
	| floatList COMMA INT		{
									$1->push_back($3);
									$$ = $1;
								}
;

exprList:
	expr					{ 
      $$ = new std::vector<Expression*>(1, $1); }
	| exprList COMMA expr	{
								$1->push_back($3);
								$$ = $1;
							}
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
	| floatExpr PLUS mulFloatExpr 	{ $$ = new FloatOperatorExpression($1, $3, '+'); }
   | floatExpr MINUS mulFloatExpr	{ $$ = new FloatOperatorExpression($1, $3, '-'); }
   | mulFloatExpr PLUS floatExpr 	{ $$ = new FloatOperatorExpression($1, $3, '+'); }
   | mulFloatExpr MINUS floatExpr { $$ = new FloatOperatorExpression($1, $3, '-'); }
;

mulFloatExpr:
	expFloatExpr
	| expFloatExpr MULT expFloatExpr { $$ = new FloatOperatorExpression($1, $3, '*'); }
   | expFloatExpr DIV expFloatExpr  { $$ = new FloatOperatorExpression($1, $3, '/'); }
   | MINUS expFloatExpr              { $$ = new FloatOperatorExpression($2, 'n'); }
;

expFloatExpr:
	floatTerm
	| floatTerm EXP floatTerm        { $$ = new FloatOperatorExpression($1, $3, '^'); }
;

floatTerm:
	FLOAT { $$ = new FloatExpression($1); }
	| FVAR {
      $$ = new FloatVariableExpression(std::string($1));
      free($1); 
     }
	| OPENPAREN addFloatExpr CLOSEPAREN	{ 
      $$ = new FloatParenExpression($2); 
   }
;

integerExpr:
	addIntegerExpr
;

addIntegerExpr:
	mulIntegerExpr
	| integerExpr PLUS mulIntegerExpr 	{ $$ = new IntegerOperatorExpression($1, $3, '+'); }
	| integerExpr MINUS mulIntegerExpr	{ $$ = new IntegerOperatorExpression($1, $3, '-'); }
	| mulIntegerExpr PLUS integerExpr 	{ $$ = new IntegerOperatorExpression($1, $3, '+'); }
	| mulIntegerExpr MINUS integerExpr  { $$ = new IntegerOperatorExpression($1, $3, '-'); }
;

mulIntegerExpr:
	expIntegerExpr
	| expIntegerExpr MULT expIntegerExpr	{ $$ = new IntegerOperatorExpression($1, $3, '*'); }
   | expIntegerExpr DIV expIntegerExpr	   { $$ = new IntegerOperatorExpression($1, $3, '/'); }
   | MINUS expIntegerExpr			         { $$ = new IntegerOperatorExpression($2, 'n'); }
;

expIntegerExpr:
	integerTerm
	| integerTerm EXP integerTerm			{ $$ = new IntegerOperatorExpression($1, $3, '^'); }
;

integerTerm:
	INT { $$ = new IntegerExpression($1); }
	| IVAR {
      $$ = new IntegerVariableExpression(std::string($1));
      free($1); }
   | OPENPAREN addIntegerExpr CLOSEPAREN	{ $$ = new IntegerParenExpression($2); }
;

stringExpr:
   stringTerm { printf("DEBUG: basic.y - stringExpr: stringTerm\n"); }
   | addStringExpr
;

addStringExpr:
   stringTerm PLUS stringTerm { $$ = new StringOperatorExpression($1, $3, '+'); }
;

stringTerm:
	STRING { 
      printf("DEBUG: basic.y - stringTerm: STRING = %s\n", $1);
      $$ = new StringExpression(std::string($1)); 
      free($1);	// malloced in basic.l
   }
   | SVAR { 
      printf("DEBUG: basic.y - stringTerm: SVAR = %s\n", $1);
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
