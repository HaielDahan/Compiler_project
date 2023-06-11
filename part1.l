%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
%}

%option noyywrap
%option yylineno

%%
"bool" return BOOL;
"char" return CHAR;
"int" return INT;
"real" return REAL;
"string" return STRING;
"int*" return PINT;
"char*" return PCHAR;
"real*" return PREAL;

"if" return IF;
"else" return ELSE;
"while" return WHILE;
"for" return FOR;
"var" return VAR;

"return" return RETURN;
"null" return NULLL;
"void" return VOID;
"do" return DO;

"&&" return AND;
"/" return DIVISION;
"=" return EQUAL;
"==" return EQ;
">" return BIG;
">=" return BEQ;
"<" return SMALL;
"<=" return SEQ;
"-" return MINUS;
"!" return NOT;
"!=" return NEQ;
"||" return OR;
"+" return PLUS;
"&" return REFERENCE;
"true" return TRUE;
"false" return FALSE;
"main" return MAIN;

[ \t]
[a-zA-Z]+[a-zA-Z0-9_]* {yylval.string = strdup(yytext);} return ID;
0|[1-9][0-9]* {yylval.string = strdup(yytext);} return NUM;
0[xX][A-F0-9]+ {yylval.string = strdup(yytext);} return HEX;

"*"[a-zA-Z]+[a-zA-Z0-9_]* {yylval.string = strdup(yytext);} return P_ID;
"&"[a-zA-Z]+[a-zA-Z0-9_]* {yylval.string = strdup(yytext);} return R_ID;
\"(\\.|[^"\\])*\" {yylval.string = strdup(yytext);} return STR;
\'(\\.|[^"\\])\' {yylval.string = strdup(yytext);} return CHR;
[0-9]*[\.]?[0-9]+|[-+]?[0-9]*[\.]?[0-9]?+[eE][-+]?[0-9]+ {yylval.string = strdup(yytext);} return RNUM;


"/*"((("*"[^/])?)|[^*])*"*/" ;

[\n] {yylineno++;};
. return yytext[0];
%%