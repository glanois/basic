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
#include "stringexpression.h"
#include "doubleexpression.h"
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
	double dVal;
   char* sVal;
	Program *progVal;
	Expression *eVal;
   DoubleExpression *dxVal;
	IntegerExpression *ixVal;
	StringExpression *sxVal;
	std::vector<Expression*> *eList;
	std::vector<std::string> *sList;
	std::vector<double> *dList;
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
%token <dVal> DOUBLE
%token <sVal> FVAR
%token <sVal> IVAR
%token <sVal> SVAR
%token <sVal> REMARK

// non-terminal symbols
%type <progVal> program 
%type <eList> exprList
%type <eVal> expr
%type <dxVal> doubleExpr
%type <dxVal> addDoubleExpr
%type <dxVal> mulDoubleExpr
%type <dxVal> expDoubleExpr
%type <dxVal> doubleTerm
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
%type <dList> doubleList

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
	PRINT exprList			{ 
      $$ = new Print($2); 
   }
	| REMARK 				{ $$ = new Rem($1); }
	| LET FVAR EQUAL doubleExpr	{
								$$ = new DoubleLet($2, $4);
								free($2);	// malloced in basic.l
							}
	| LET IVAR EQUAL integerExpr	{
								$$ = new IntegerLet($2, $4);
								free($2);	// malloced in basic.l
							}
   | LET SVAR EQUAL stringExpr	{
								$$ = new StringLet($2, $4);
								free($2);	// malloced in basic.l
                        }
	| GOTO INT				{ $$ = new Goto($2); }
	| END					{ $$ = new End(); }
	| IF doubleExpr  comp doubleExpr  THEN INT { $$ = new DoubleIfThen($2, $4, $3, $6); }
   | IF integerExpr comp integerExpr THEN INT { $$ = new IntegerIfThen($2, $4, $3, $6); }
   /* xxx | IF stringExpr comp stringExpr THEN INT
   { $$ = new StringIfThen($2, $4, $3, $6); } */
	| READ stringList		{ $$ = new Read(*$2); }
	| DATA doubleList		{ $$ = new Data(*$2); }
	| FOR FVAR EQUAL doubleExpr TO doubleExpr {
								$$ = new DoubleFor($4, $6, NULL, $2);
							}
	| FOR FVAR EQUAL doubleExpr TO doubleExpr STEP doubleExpr {
								$$ = new DoubleFor($4, $6, $8, $2);
							}
	| NEXT FVAR				{ $$ = new DoubleNext($2); }
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

doubleList:
	DOUBLE						{ $$ = new std::vector<double>(1, $1); }
	| INT						{ $$ = new std::vector<double>(1, $1); }
	| doubleList COMMA DOUBLE	{
									$1->push_back($3);
									$$ = $1;
								}
	| doubleList COMMA INT		{
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
   doubleExpr
   | integerExpr
   | stringExpr
	
doubleExpr:
	addDoubleExpr
;

addDoubleExpr:
	mulDoubleExpr
	| doubleExpr PLUS mulDoubleExpr 	{ $$ = new DoubleOperatorExpression(*($1), *($3), '+'); }
   | doubleExpr MINUS mulDoubleExpr	{ $$ = new DoubleOperatorExpression(*($1), *($3), '-'); }
   | mulDoubleExpr PLUS doubleExpr 	{ $$ = new DoubleOperatorExpression(*($1), *($3), '+'); }
   | mulDoubleExpr MINUS doubleExpr { $$ = new DoubleOperatorExpression(*($1), *($3), '-'); }
;

mulDoubleExpr:
	expDoubleExpr
	| expDoubleExpr MULT expDoubleExpr	{ $$ = new DoubleOperatorExpression(*($1), *($3), '*'); }
   | expDoubleExpr DIV expDoubleExpr	{ $$ = new DoubleOperatorExpression(*($1), *($3), '/'); }
   | MINUS expDoubleExpr			{ $$ = new DoubleOperatorExpression(*($2), 'n'); }
;

expDoubleExpr:
	doubleTerm
	| doubleTerm EXP doubleTerm			{ $$ = new DoubleOperatorExpression(*($1), *($3), '^'); }
;

doubleTerm:
	DOUBLE			{ 
      $$ = new DoubleExpression($1); }
	| FVAR			{
      $$ = new DoubleVariableExpression(std::string($1));
      free($1); }
	| OPENPAREN addDoubleExpr CLOSEPAREN	{ 
      $$ = new DoubleParenExpression(*($2)); }
;

integerExpr:
	addIntegerExpr
;

addIntegerExpr:
	mulIntegerExpr
	| integerExpr PLUS mulIntegerExpr 	{ $$ = new IntegerOperatorExpression(*($1), *($3), '+'); }
	| integerExpr MINUS mulIntegerExpr	{ $$ = new IntegerOperatorExpression(*($1), *($3), '-'); }
	| mulIntegerExpr PLUS integerExpr 	{ $$ = new IntegerOperatorExpression(*($1), *($3), '+'); }
	| mulIntegerExpr MINUS integerExpr { $$ = new IntegerOperatorExpression(*($1), '-'); }
;

mulIntegerExpr:
	expIntegerExpr
	| expIntegerExpr MULT expIntegerExpr	{ $$ = new IntegerOperatorExpression(*($1), *($3), '*'); }
   | expIntegerExpr DIV expIntegerExpr	{ $$ = new IntegerOperatorExpression(*($1), *($3), '/'); }
   | MINUS expIntegerExpr			{ $$ = new IntegerOperatorExpression(*($2), 'n'); }
;

expIntegerExpr:
	integerTerm
	| integerTerm EXP integerTerm			{ $$ = new IntegerOperatorExpression(*($1), *($3), '^'); }
;

integerTerm:
	INT { 
      $$ = new IntegerExpression($1); }
	| IVAR {
      $$ = new IntegerVariableExpression(std::string($1));
      free($1); }
   | OPENPAREN addIntegerExpr CLOSEPAREN	{ $$ = new IntegerParenExpression(*($2)); }
;

stringExpr:
   stringTerm
   | addStringExpr
;

addStringExpr:
   stringTerm PLUS stringTerm { 
      /* xxx $$ = new StringOperatorExpression($1, $3, '+'); */ 
   }
;

stringTerm:
	STRING { 
      $$ = new StringExpression(std::string($1)); 
      free($1);	// malloced in basic.l
   }
   | SVAR { 
      /* xxx  $$ = new StringVariableExpression($1); free($1); */ 
   }
   | OPENPAREN addStringExpr CLOSEPAREN
   { 
      /* xxx $$ = new StringParenExpression($2); */ 
   }
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
