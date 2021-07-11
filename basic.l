%option case-insensitive

%{
#include <cstdio>
#include <iostream>
#include <vector>

#define YY_DECL extern "C" int yylex()

class Program;
class Expression;
class FloatExpression;
class IntegerExpression;
class StringExpression;

#include "basic.tab.hpp"

%}

ALPHA    [A-Z]	
DIGIT    [0-9]

%%

[ \t]+	;		// skip white space
{DIGIT}+ { 
   yylval.iVal = atoi(yytext);
   return INT; }
(({DIGIT}+"."?)|("."{DIGIT}+)){DIGIT}*(E-?{DIGIT}+)? { 
   yylval.fVal = atof(yytext); 
   return FLOAT; }
\"[^\"\n]*\" {
   // remove the quote marks from either end
   yylval.sVal = strndup(yytext+1, strlen(yytext)-2);
	return STRING; }
PRINT  { return PRINT; }
REM.*  { yylval.sVal = strndup(yytext, 512); return REMARK; }
RUN    { return RUN; }
LIST   { return LIST; }
,      { return COMMA; }
:      { return COLON; }
\n {
   if (yyin == stdin) {
      std::cout << ">";
   }
   return ENDL; }
{ALPHA}{DIGIT}?   { yylval.sVal = strdup(yytext); return FVAR; }
{ALPHA}{DIGIT}?\% { yylval.sVal = strdup(yytext); return IVAR; }
{ALPHA}{DIGIT}?\$ { yylval.sVal = strdup(yytext); return SVAR; }
\+ { return PLUS; }
-  { return MINUS; }
\* { return MULT; }
\/ { return DIV; }
\^ { return EXP; }
SAVE    { return SAVE; }
UNSAVE  { return UNSAVE; }
NEW     { return NEW; }
OLD     { return OLD; }
CATALOG { return CATALOG; }
SCRATCH { return SCRATCH; }
RENAME  { return RENAME; }
LET     { return LET; }
GOTO    { return GOTO; }
END     { return END; }
IF      { return IF; }
THEN    { return THEN; }
DATA    { return DATA; }
READ    { return READ; }
FOR     { return FOR; }
TO      { return TO; }
STEP    { return STEP; }
NEXT    { return NEXT; }
\=      { return EQUAL; }
\<      { return LESS; }
\>      { return GREATER; }
\<\=    { return LESSEQUAL; }
\>\=    { return GREATEREQUAL; }
\<\>    { return NOTEQUAL; }
\(      { return OPENPAREN; }
\)      { return CLOSEPAREN; }
.       ; /* skip any characters that aren't part of a recognized pattern */

%%
