%option case-insensitive

%{
#include <cstdio>
#include <iostream>
#include <vector>
#include <variant>

#define YY_DECL extern "C" int yylex()

class Program;
class Expression;
class FloatExpression;
class IntegerExpression;
class StringExpression;

#include "basic.tab.hpp"

#include "stringutils.h"

%}

ALPHA    [A-Z]	
DIGIT    [0-9]

%x INDATA
%x INDSTRING

%%

[ \t]+	;		// skip white space
{DIGIT}+ { 
   yylval.iVal = atoi(yytext);
   return INT; }
(({DIGIT}+"."?)|("."{DIGIT}+)){DIGIT}*(E-?{DIGIT}+)? { 
   yylval.fVal = atof(yytext); 
   return FLOAT; }
\"[^\"\n]*\" { // Quoted string literal
   // remove the quote marks from either end
   yylval.sVal = strndup(yytext+1, strlen(yytext)-2);
	return STRING; }

   /* DATA statements allow int, float, quoted strings, and unquoted strings.
      Need to use a start state in a DATA statement to suppport the
      unquoted strings.  Otherwise the unquoted string regex would eat 
      program statements. 

      Note that the int/float/quoted strings grab leading/trailing space.
      Otherwise the unquoted string regex treats those as unquoted strings
      when there are any leading/trailing spaces. */
<INDATA>[ \t]*{DIGIT}+[ \t]* { 
   yylval.iVal = atoi(yytext);
   return INT; }
<INDATA>[ \t]*(({DIGIT}+"."?)|("."{DIGIT}+)){DIGIT}*(E-?{DIGIT}+)?[ \t]* { 
   yylval.fVal = atof(yytext); 
   return FLOAT; }
<INDATA>[ \t]*\"[^\"\n]*\"[ \t]* { // Quoted string literal
   std::string s(yytext);
   StringUtils::trim(s, " \t");
   // remove the quote marks from either end
   StringUtils::trim(s, "\"");
   yylval.sVal = strdup(s.c_str());
	return STRING; }
<INDATA>[^,:\n]+ { // Unquoted literal string in DATA statement. (Space is allowed, before, during, and after.)
   std::string s(yytext);
   StringUtils::trim(s, " \t");
   yylval.sVal = strdup(s.c_str());
	return DSTRING; }
<INDATA>, { 
   return COMMA; }
<INDATA>: { 
   BEGIN INITIAL; 
   return COLON; }
<INDATA>\n { 
   BEGIN INITIAL; 
   // Put the newline back so the line can be terminated.
   unput(*yytext); }

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
DATA    { 
   // Use a start state to prevent unquoted strings from
   // being interpreted as program text.
   BEGIN INDATA; 
   return DATA; }
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
