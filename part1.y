%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int yylex();
int yyerror();
extern int yylineno;
extern char* yytext;
#include "semantic.c"

%}

%union
{
    struct node *node;
    char *string;
}

%token <string> ID NUM STR CHR VAR RNUM RETURN NULLL HEX
%token <string> BOOL CHAR INT REAL STRING PINT PCHAR PREAL VOID P_ID R_ID
%token <string> IF ELSE WHILE FOR DO
%token <string> EQ NEQ BEQ SEQ BIG SMALL AND OR NOT
%token <string> DIVISION EQUAL MINUS PLUS REFERENCE
%token <string> TRUE FALSE
%token <string> MAIN

%left PLUS MINUS RETURN
%left '*' DIVISION
%left EQL NEQ SMALL SEQ BEQ BIG OR AND
%left ';'
%right NOT ')'

%nonassoc IF
%nonassoc ELSE

%type <node> project program s INIT KEYW INIT_ASS ASS ASS1 INIT_STRING STRING_ASS MATH MATH_START MATH_VAR MATH_OPER FORASS FORASS1
%type <node> BOOLEAN KEYACC FUNC_RET FUNC_VOID FUNC_MAIN ACC LOOP_ACC LOOP_ACC2 BLOCK LOOP_B NEXT_BLOCK LOOP_N_B
%type <node> RET FUNC_END CALL_FUNC SEND LOOP_SEND IF_ELSE WHILE_LOOP DO_WHILE FOR_LOOP VOID_BLOCK VOID_LOOP_B EMPTY_BLOCK VOID_EMPTY_BLOCK
%type <node> VOID_NEXT_BLOCK VOID_LOOP_N_B VOID_IF_ELSE VOID_WHILE_LOOP VOID_DO_WHILE VOID_FOR_LOOP STAT COND OPER COND1
%type <node> END_BLOCK START_BLOCK START_BLOCK2
%type <node> MID_COND END_COND RET_I_W_D 
%% 
  
project: program{/*Printtree($1);*/ CheckSemantic($1);};
program:  s{$$=makenode("CODE",$1,NULL,NULL,NULL);}

s:			FUNC_RET s   {$$ = makenode("",$1,$2,NULL,NULL);}
		|	FUNC_VOID s  {$$ = makenode("",$1,$2,NULL,NULL);}
		|	FUNC_MAIN    //{$$ = makenode("",$1,NULL,NULL,NULL);}
;


INIT:			VAR KEYW INIT_ASS ';' {$$ = makenode("VAR",$2,$3,NULL,NULL);}
;

KEYW:			INT {$$ = makenode("INT",NULL,NULL,NULL,NULL);}
		|	CHAR {$$ = makenode("CHAR",NULL,NULL,NULL,NULL);}
		|	BOOL {$$ = makenode("BOOL",NULL,NULL,NULL,NULL);}
		|	REAL {$$ = makenode("REAL",NULL,NULL,NULL,NULL);}
		|	PINT {$$ = makenode("INT",NULL,NULL,NULL,NULL);}
		|	PCHAR {$$ = makenode("CHAR",NULL,NULL,NULL,NULL);}
		|	PREAL {$$ = makenode("REAL",NULL,NULL,NULL,NULL);}
;
	
INIT_ASS:	
			ID {$$ = makenode($1,NULL ,NULL,NULL,NULL);}  
		|	ID EQUAL STR {$$ = makenode("=",makenode($1,NULL,NULL,NULL,NULL),makenode($3,NULL,NULL,NULL,NULL),NULL,NULL);}
		|	ID EQUAL CHR {$$ = makenode("=",makenode($1,NULL,NULL,NULL,NULL),makenode($3,NULL,NULL,NULL,NULL),NULL,NULL);}
		|	ID EQUAL MATH {$$ = makenode("=",makenode($1,NULL,NULL,NULL,NULL),$3,NULL,NULL);}
		|	ID ',' INIT_ASS {$$ = makenode($1,$3,NULL,NULL,NULL);} 
		|	ID EQUAL NULLL {$$ = makenode("=",makenode($1,NULL,NULL,NULL,NULL),makenode("NULL",NULL,NULL,NULL,NULL),NULL,NULL);}
		|	ID EQUAL BOOLEAN {$$ = makenode("=",makenode($1,NULL,NULL,NULL,NULL),$3,NULL,NULL);}
		|	ID EQUAL CALL_FUNC {$$ = makenode("=",makenode($1,NULL,NULL,NULL,NULL),$3,NULL,NULL);}
		|	ID '['MATH']'{$$ = makenode($1,makenode("[",$3,makenode("]",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL,NULL);}
		|	ID '['MATH']' EQUAL ID {$$ = makenode("=",makenode($1,makenode("[",$3,makenode("]",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL,NULL),
						makenode($6,NULL,NULL,NULL,NULL),NULL,NULL);}
		|	ID '['MATH']' EQUAL STR {$$ = makenode("=",makenode($1,makenode("[",$3,makenode("]",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL,NULL),
						makenode($6,NULL,NULL,NULL,NULL),NULL,NULL);}
		|	ID '['MATH']' EQUAL CHR {$$ = makenode("=",makenode($1,makenode("[",$3,makenode("]",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL,NULL),
						makenode($6,NULL,NULL,NULL,NULL),NULL,NULL);}
		|	ID '['MATH']' EQUAL NUM {$$ = makenode("=",makenode($1,makenode("[",$3,makenode("]",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL,NULL),
						makenode($6,NULL,NULL,NULL,NULL),NULL,NULL);}
		|	ID '['MATH']' ',' INIT_ASS {$$ = makenode($1,makenode("[",$3,makenode("]",NULL,NULL,NULL,NULL),NULL,NULL),
										NULL,$6,NULL);}
;
		
		|	ID '['MATH']' EQUAL NULLL {$$ = makenode("=",makenode($1,makenode("[",$3,makenode("]",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL,NULL),
						makenode("NULL",NULL,NULL,NULL,NULL),NULL,NULL);}
		|	ID '['MATH']' EQUAL BOOLEAN {$$ = makenode("=",makenode($1,makenode("[",$3,makenode("]",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL,NULL),$6,NULL,NULL);}
;

FORASS: 		ASS1';' {$$ = makenode("FORASS",$1,NULL,NULL,NULL);}
;

FORASS1: 		ASS1 {$$ = makenode("FORASS1",$1,NULL,NULL,NULL);}
;

ASS: 			ASS1';' {$$ = makenode("ASS",$1,NULL,NULL,NULL);}
;

ASS1:		ID EQUAL NULLL {$$ = makenode("=",makenode($1,NULL,NULL,NULL,NULL),makenode("NULL",NULL,NULL,NULL,NULL),NULL,NULL);}		
		|	ID EQUAL STR  {$$ = makenode("=",makenode($1,NULL,NULL,NULL,NULL),makenode($3,NULL,NULL,NULL,NULL),NULL,NULL);}
		|	ID EQUAL CHR  {$$ = makenode("=",makenode($1,NULL,NULL,NULL,NULL),makenode($3,NULL,NULL,NULL,NULL),NULL,NULL);}
		|	ID EQUAL BOOLEAN {$$ = makenode("=",makenode($1,NULL,NULL,NULL,NULL),$3,NULL,NULL);}

		|	ID EQUAL COND {$$ = makenode("=",makenode($1,NULL,NULL,NULL,NULL),$3,NULL,NULL);}	
		|	ID EQUAL ID '['MATH']' {$$ = makenode("=",makenode($1,NULL,NULL,NULL,NULL),makenode($3,NULL,NULL,NULL,NULL), makenode("[]",$5,NULL,NULL,NULL),NULL);}
		/*|	ID EQUAL R_ID {$$ = makenode("=",makenode($1,NULL,NULL,NULL,NULL),makenode($3,NULL,NULL,NULL,NULL),NULL,NULL);}*/
		/*|	ID EQUAL P_ID {$$ = makenode("=",makenode($1,NULL,NULL,NULL,NULL),makenode($3,NULL,NULL,NULL,NULL),NULL,NULL);}*/
		|	P_ID EQUAL MATH {$$ = makenode("=",makenode($1,NULL,NULL,NULL,NULL),$3,NULL,NULL);}
		|	ID EQUAL MATH {$$ = makenode("=",makenode($1,NULL,NULL,NULL,NULL),$3,NULL,NULL);}
		|	ID EQUAL CALL_FUNC  {$$ = makenode("=",makenode($1,NULL,NULL,NULL,NULL),$3,NULL,NULL);}
		|	ID '['MATH']' {$$ = makenode($1,makenode("[",$3,makenode("]",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL,NULL);}
		|	ID '['MATH']' EQUAL MATH {$$ = makenode("=",makenode($1,makenode("[]",$3,NULL,NULL,NULL),NULL,NULL,NULL),$6,NULL,NULL);}
		|	ID '['MATH']' EQUAL STR {$$ = makenode("=",makenode($1,makenode("[]",$3,NULL,NULL,NULL),NULL,NULL,NULL),
						makenode($6,NULL,NULL,NULL,NULL),NULL,NULL);}
		|	ID '['MATH']' EQUAL CALL_FUNC {$$ = makenode("=",makenode($1,makenode("[]",$3,NULL,NULL,NULL),NULL,NULL,NULL),$6,NULL,NULL);}

		|	ID '['MATH']' EQUAL CHR {$$ = makenode("=",makenode($1,makenode("[",$3,makenode("]",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL,NULL),
						makenode($6,NULL,NULL,NULL,NULL),NULL,NULL);}
		|	ID '['MATH']' EQUAL NULLL {$$ = makenode("=",makenode($1,makenode("[",$3,makenode("]",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL,NULL),
						makenode("NULL",NULL,NULL,NULL,NULL),NULL,NULL);}
		|	ID '['MATH']' EQUAL BOOLEAN {$$ = makenode("=",makenode($1,makenode("[",$3,makenode("]",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL,NULL),$6,NULL,NULL);}
;

INIT_STRING: 		STRING STRING_ASS ';' {$$ = makenode("STRING",$2,NULL,NULL,NULL);}
;

STRING_ASS:		ID {$$ = makenode($1,NULL,NULL,NULL,NULL);}		
		|	ID EQUAL STR {$$ = makenode("=",makenode($1,NULL,NULL,NULL,NULL),makenode($3,NULL,NULL,NULL,NULL),NULL,NULL);}
		|	ID EQUAL NULLL {$$ = makenode("=",makenode($1,NULL,NULL,NULL,NULL),makenode("NULL",NULL,NULL,NULL,NULL),NULL,NULL);}
		|	ID EQUAL CALL_FUNC {$$ = makenode("=",makenode($1,NULL,NULL,NULL,NULL),$3,NULL,NULL);}
		|	ID '['MATH']'  {$$ = makenode($1,makenode("[]",$3,NULL,NULL,NULL),NULL,NULL,NULL);}
		|	ID '['MATH']' EQUAL STR {$$ = makenode("=",makenode($1,makenode("[]",$3,NULL,NULL,NULL),NULL,NULL,NULL),
						makenode($6,NULL,NULL,NULL,NULL),NULL,NULL);}
		|	ID '['MATH']' EQUAL NULLL {$$ = makenode("=",makenode($1,makenode("[]",$3,NULL,NULL,NULL),NULL,NULL,NULL),
						makenode("NULL",NULL,NULL,NULL,NULL),NULL,NULL);}
		|	ID '['MATH']' ',' STRING_ASS {$$ = makenode($1,makenode("[]",$3,NULL,NULL,NULL),$6,NULL,NULL);}
;

MATH: 			MATH_START //{$$ = makenode("",$1,NULL,NULL,NULL);}
		|	'(' MATH_START ')' MATH_OPER MATH {$$ = makenode("()",$2,$4,$5,NULL);}
		| 	'(' MATH_START ')' {$$ = makenode("()",$2,NULL,NULL,NULL);}
;

MATH_START:	MATH_VAR MATH_OPER MATH {$$ = makenode("",$2,$1,$3,NULL);}
		|	MATH_VAR {$$ = makenode("",$1,NULL,NULL,NULL);}
;	

MATH_VAR: 	ID {$$ = makenode($1,NULL,NULL,NULL,NULL);}
		|	NUM {$$ = makenode($1,NULL,NULL,NULL,NULL);}
		|	RNUM {$$ = makenode($1,NULL,NULL,NULL,NULL);}
		|	HEX {$$ = makenode($1,NULL,NULL,NULL,NULL);}
		|	'|' ID '|' {$$=makenode(strcat($2, "||") ,NULL,NULL,NULL,NULL);}
		|	'|' STR '|' {$$=makenode(strcat($2, "||") ,NULL,NULL,NULL,NULL);}
		|	R_ID {$$ = makenode($1,NULL,NULL,NULL,NULL);}
		|	P_ID {$$ = makenode($1,NULL,NULL,NULL,NULL);}
		|	R_ID '[' MATH ']' {$$ = makenode($1,$3,NULL,NULL,NULL);}
	

MATH_OPER: 	PLUS {$$ = makenode("+",NULL,NULL,NULL,NULL);}
		|	MINUS {$$ = makenode("-",NULL,NULL,NULL,NULL);}
		|	'*' {$$ = makenode("*",NULL,NULL,NULL,NULL);}
		|	DIVISION {$$ = makenode("/",NULL,NULL,NULL,NULL);}
;


BOOLEAN:		TRUE {$$ = makenode("true",NULL,NULL,NULL,NULL);}
		|	FALSE {$$ = makenode("false",NULL,NULL,NULL,NULL);}
;

KEYACC: 		KEYW {$$ = makenode("TYPE",$1,NULL,NULL,NULL);}
		|	STRING {$$ = makenode("STRING",NULL,NULL,NULL,NULL);}
;

FUNC_RET:		KEYW ID '(' ACC ')''{' BLOCK RET'}' {$$ = makenode("FUNCTION",$1,makenode(strcat($2,"()"),NULL,NULL,NULL,NULL),
										$4,makenode("BLOCK",$7,makenode("",$8,NULL,NULL,NULL),NULL,NULL));}
		
		|	STRING ID '(' ACC ')''{' BLOCK RET'}'{$$ =makenode("FUNCTION",makenode("STRING",NULL,NULL,NULL,NULL)
											,makenode(strcat($2,"()"),NULL,NULL,NULL,NULL),
										        $4,makenode("BLOCK",$7,$8,NULL,NULL));}
;


FUNC_VOID: 		VOID ID '(' ACC ')''{'VOID_BLOCK'}' {$$ = makenode("FUNCTION",makenode("VOID",NULL,NULL,NULL,NULL),
											makenode(strcat($2,"()"),NULL,NULL,NULL,NULL),
											makenode("ARGS",$4,NULL,NULL,NULL),
											makenode("VOID_BLOCK",$7,NULL,NULL,NULL));}
;


FUNC_MAIN: 		VOID MAIN '('')''{'VOID_BLOCK'}'    {$$ = makenode("FUNCTION",makenode("VOID",NULL,NULL,NULL,NULL),
											makenode("MAIN",NULL,NULL,NULL,NULL),
											makenode("NO ARGS",NULL,NULL,NULL,NULL),
											makenode("VOID_BLOCK",$6,NULL,NULL,NULL));}
		|	INT MAIN '('')''{'BLOCK RET '}'	    {$$ = makenode("FUNCTION",makenode("INT",NULL,NULL,NULL,NULL),
													makenode("MAIN",NULL,NULL,NULL,NULL),
													makenode("NO ARGS",NULL,NULL,NULL,NULL),
													makenode("BLOCK",$6,
													makenode("",$7,NULL,NULL,NULL),NULL,NULL));}
;


ACC: 			KEYACC ID LOOP_ACC {$$ = makenode("",$1,makenode($2,NULL,NULL,NULL,NULL),$3,NULL);}
		|	{$$ = NULL;}
;

LOOP_ACC:	',' KEYACC ID LOOP_ACC {$$ = makenode("",$2,makenode($3,NULL,NULL,NULL,NULL),$4,NULL);}
		|	',' ID LOOP_ACC {$$ = makenode("",makenode($2,NULL,NULL,NULL,NULL),$3,NULL,NULL);}
		|	';' LOOP_ACC2 {$$ = makenode("",$2,NULL,NULL,NULL);}
		|	{$$ = NULL;}
;

LOOP_ACC2:		KEYACC ID LOOP_ACC {$$ = makenode("",$1,makenode($2,NULL,NULL,NULL,NULL),$3,NULL);}
		|	LOOP_ACC
;



BLOCK: START_BLOCK {$$ = makenode("START_BLOCK",$1,NULL,NULL,NULL);}

START_BLOCK:	INIT_STRING LOOP_B {$$ = makenode("",$1,$2,NULL,NULL);} 
		| 	INIT LOOP_B {$$ = makenode("",$1,$2,NULL,NULL);} 
		|	FUNC_RET LOOP_B {$$ = makenode("",$1,$2,NULL,NULL);} 
		|	FUNC_VOID LOOP_B {$$ = makenode("",$1,$2,NULL,NULL);} 
		/*| 	'{' LOOP_B '}' LOOP_B {$$ = makenode("{}",$2,$4,NULL,NULL);}*/
		|	NEXT_BLOCK //{$$ = makenode("",$1,NULL,NULL,NULL,NULL);}
;

LOOP_B:			INIT_STRING LOOP_B {$$ = makenode("",$1,$2,NULL,NULL);} 
		|  	INIT LOOP_B {$$ = makenode("",$1,$2,NULL,NULL);} 
		| 	FUNC_RET LOOP_B {$$ = makenode("",$1,$2,NULL,NULL);}
	/*	| 	'{' LOOP_B '}' LOOP_B {$$ = makenode("{}",$2,$4,NULL,NULL);}*/
		|	FUNC_VOID LOOP_B {$$ = makenode("",$1,$2,NULL,NULL);} 
		|	NEXT_BLOCK //{$$ = makenode("",$1,NULL,NULL,NULL,NULL);}
;



NEXT_BLOCK:		ASS LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);} 
		|  	IF_ELSE LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);} 
		/*|	'{' LOOP_N_B '}' LOOP_N_B {$$ = makenode("{}",$2,$4,NULL,NULL);}*/
		|	WHILE_LOOP LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);} 
		|	DO_WHILE LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);} 
		|	FOR_LOOP LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);} 
		|	EMPTY_BLOCK LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);}
		| 	{$$ = NULL;}
 ;
	
LOOP_N_B:		ASS LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);} 
	/*	|	'{' LOOP_N_B '}' LOOP_N_B {$$ = makenode("{}",$2,$4,NULL,NULL);}*/
		|	EMPTY_BLOCK LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);}
		|	IF_ELSE LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);} 
		|	WHILE_LOOP LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);} 
		|	DO_WHILE LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);} 
		|	FOR_LOOP LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);} 
		| 	{$$ = NULL;} 
;

RET:		RETURN ID ';' {$$ = makenode("return",makenode($2,NULL,NULL,NULL,NULL),
			 makenode("END_BLOCK",NULL,NULL,NULL,NULL),NULL,NULL);}

		|	RETURN CHR ';' {$$ = makenode("return",makenode($2,NULL,NULL,NULL,NULL),
			 makenode("END_BLOCK",NULL,NULL,NULL,NULL),NULL,NULL);}

		|	RETURN NUM ';' {$$ = makenode("return",makenode($2,NULL,NULL,NULL,NULL),
			 makenode("END_BLOCK",NULL,NULL,NULL,NULL),NULL,NULL);}

		|	RETURN STR';'  {$$ = makenode("return",makenode($2,NULL,NULL,NULL,NULL),
			 makenode("END_BLOCK",NULL,NULL,NULL,NULL),NULL,NULL);}

		|	RETURN RNUM';' {$$ = makenode("return",makenode($2,NULL,NULL,NULL,NULL),
			 makenode("END_BLOCK",NULL,NULL,NULL,NULL),NULL,NULL);}

		|	RETURN FUNC_END {$$ = makenode("return",$2, makenode("END_BLOCK",NULL,NULL,NULL,NULL),NULL,NULL);}

		|	RETURN TRUE';' {$$ = makenode("return",makenode("TRUE",NULL,NULL,NULL,NULL),
			 makenode("END_BLOCK",NULL,NULL,NULL,NULL),NULL,NULL);}

		|	RETURN FALSE';'  {$$ = makenode("return",makenode("FALSE",NULL,NULL,NULL,NULL),
			 makenode("END_BLOCK",NULL,NULL,NULL,NULL),NULL,NULL);}
;




FUNC_END: 		CALL_FUNC ';'
;

CALL_FUNC: 		ID '(' SEND ')'{$$ = makenode(strcat($1,"()"),$3,NULL,NULL,NULL);}
;

SEND:		MATH LOOP_SEND {$$ = makenode("",$1,$2,NULL,NULL);}
		|	STR LOOP_SEND {$$ = makenode($1,$2,NULL,NULL,NULL);}
		|	CHR LOOP_SEND {$$ = makenode($1,$2,NULL,NULL,NULL);}
		|	BOOL LOOP_SEND {$$ = makenode($1,$2,NULL,NULL,NULL);} 
		|	CALL_FUNC LOOP_SEND  {$$ = makenode("",$1,$2,NULL,NULL);}
		|	ID '['MATH']' LOOP_SEND  {$$ = makenode($1,makenode("[",$3,makenode("]",NULL,NULL,NULL,NULL),NULL,NULL),$5,NULL,NULL);}
		|	{$$ = NULL;}
;

LOOP_SEND: 	',' MATH LOOP_SEND {$$ = makenode("",$2,$3,NULL,NULL);}
		|	',' STR LOOP_SEND {$$ = makenode("",makenode($2,NULL,NULL,NULL,NULL),$3,NULL,NULL);}		

		|	',' CHR LOOP_SEND {$$ = makenode("",makenode($2,NULL,NULL,NULL,NULL),$3,NULL,NULL);}
		|	',' BOOL LOOP_SEND {$$ = makenode("",makenode($2,NULL,NULL,NULL,NULL),$3,NULL,NULL);}

		|	',' CALL_FUNC LOOP_SEND {$$ = makenode("",$2,$3,NULL,NULL);}
		|	',' ID '['MATH']' LOOP_SEND  {$$ = makenode("",makenode($2,makenode("[",$4,makenode("]",NULL,NULL,NULL,NULL),NULL,NULL),NULL,NULL,NULL),$6,NULL,NULL);}
		| 	{$$ = NULL;} 
;

IF_ELSE:		IF '(' COND ')' '{' BLOCK RET_I_W_D '}' ELSE '{' BLOCK RET_I_W_D '}'{$$ = makenode("IF",$3,makenode("BLOCK",$6,$7,NULL,NULL),
												makenode("ELSE",NULL,NULL,NULL,NULL), makenode("BLOCK",$11,$12,NULL,NULL));}
		
		| 	IF '(' COND ')' '{' BLOCK RET_I_W_D '}'{$$ = makenode("IF",$3,makenode("BLOCK",$6,$7,NULL,NULL),NULL,NULL);}
		|	IF '(' COND ')' STAT {$$ = makenode("IF",$3,$5,NULL,NULL);}
;


EMPTY_BLOCK: '{'BLOCK  RET_I_W_D'}'{$$ = makenode("EMPTY_BLOCK", $2,$3,NULL,NULL);}


WHILE_LOOP:		WHILE '(' COND ')' '{' BLOCK RET_I_W_D '}'{$$ = makenode("WHILE_LOOP",$3,makenode("BLOCK",$6,$7,NULL,NULL),NULL,NULL);}
		|	WHILE '(' COND ')' STAT {$$ = makenode("WHILE_LOOP",$3,$5,NULL,NULL);}

;

DO_WHILE: 		DO '{' BLOCK RET_I_W_D '}' WHILE '(' COND ')'';' {$$ = makenode("DO",makenode("BLOCK",$3,$4,NULL,NULL),makenode("WHILE",$8,NULL,NULL,NULL),NULL,NULL);}
;

FOR_LOOP: 		FOR '(' FORASS COND ';' FORASS1 ')' '{' BLOCK RET_I_W_D '}' {$$ = makenode("FOR",$3,$4,$6,makenode("BLOCK",$9,$10,NULL,NULL));}
		|	FOR '(' FORASS COND ';' FORASS1 ')' ASS {$$ = makenode("FOR",$3,$4,$6,$8);}	
;
//////////////////////////////VOID//////////////////////////////////////

VOID_BLOCK: START_BLOCK2 {$$ = makenode("START_BLOCK",$1,NULL,NULL,NULL);} 

START_BLOCK2:	INIT_STRING VOID_LOOP_B {$$ = makenode("",$1,$2,NULL,NULL);} 
		| 	INIT VOID_LOOP_B {$$ = makenode("",$1,$2,NULL,NULL);}
		|	FUNC_RET VOID_LOOP_B {$$ = makenode("",$1,$2,NULL,NULL);}
		|	FUNC_VOID VOID_LOOP_B {$$ = makenode("",$1,$2,NULL,NULL);}
		|	VOID_NEXT_BLOCK
;

VOID_LOOP_B:	INIT_STRING VOID_LOOP_B {$$ = makenode("",$1,$2,NULL,NULL);}
		|  	INIT VOID_LOOP_B {$$ = makenode("",$1,$2,NULL,NULL);}
		| 	FUNC_RET VOID_LOOP_B {$$ = makenode("",$1,$2,NULL,NULL);}
		|	FUNC_VOID VOID_LOOP_B {$$ = makenode("",$1,$2,NULL,NULL);}
		|	VOID_NEXT_BLOCK //{$$ = makenode("",$1,NULL,NULL,NULL);}
;



VOID_NEXT_BLOCK:	ASS VOID_LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);}
		|  	VOID_IF_ELSE VOID_LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);}
		|	VOID_EMPTY_BLOCK VOID_LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);}
	/*	|	'{' VOID_LOOP_N_B '}' VOID_LOOP_N_B {$$ = makenode("{}",$2,$4,NULL,NULL);}*/
		|	VOID_WHILE_LOOP VOID_LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);}
		|	VOID_DO_WHILE VOID_LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);}
		|	VOID_FOR_LOOP VOID_LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);}
		| 	END_BLOCK {$$ = makenode("END_BLOCK",$1,NULL,NULL,NULL);}
 ;
	
VOID_LOOP_N_B:		ASS VOID_LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);}
	/*	|	'{' VOID_LOOP_N_B '}' VOID_LOOP_N_B {$$ = makenode("{}",$2,$4,NULL,NULL);}*/
		|	VOID_IF_ELSE VOID_LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);}
		|	VOID_WHILE_LOOP VOID_LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);}
		|	VOID_DO_WHILE VOID_LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);}
		|	VOID_FOR_LOOP VOID_LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);}
		|	VOID_EMPTY_BLOCK VOID_LOOP_N_B {$$ = makenode("",$1,$2,NULL,NULL);}
		| 	END_BLOCK {$$ = makenode("END_BLOCK",$1,NULL,NULL,NULL);}
;

END_BLOCK : {$$ = NULL;}

VOID_IF_ELSE:		IF '(' COND ')' '{' VOID_BLOCK '}' ELSE '{' VOID_BLOCK '}' {$$ = makenode("IF",$3,$6,makenode("ELSE",NULL,NULL,NULL,NULL),$10);}
		| 			IF '(' COND ')' '{' VOID_BLOCK '}' {$$ = makenode("IF",$3,$6,NULL,NULL);}
		|			IF '(' COND ')' ASS {$$ = makenode("IF",$3,$5,NULL,NULL);}
;

VOID_WHILE_LOOP:	WHILE '(' COND ')' '{' VOID_BLOCK '}' {$$ = makenode("WHILE_LOOP",$3,$6,NULL,NULL);}
		|			WHILE '(' COND ')' ASS {$$ = makenode("WHILE_LOOP",$3,$5,NULL,NULL);}

;

VOID_EMPTY_BLOCK: '{' VOID_BLOCK '}'{$$ = makenode("VOID_EMPTY_BLOCK", $2,NULL,NULL,NULL);}


VOID_DO_WHILE: 		DO '{' VOID_BLOCK'}' WHILE '(' COND ')'';' {$$ = makenode("DO",$3,makenode("WHILE",$7,NULL,NULL,NULL),NULL,NULL);}
;


VOID_FOR_LOOP: 		FOR '(' FORASS COND ';' FORASS1 ')' '{' VOID_BLOCK'}'{$$ = makenode("FOR",$3,$4,$6,$9);}
		|	FOR '(' FORASS COND ';' FORASS1 ')' ASS {$$ = makenode("FOR",$3,$4,$6,$8);}	
;




/////////////////////////////////////////////////////////////////////
STAT: 			ASS
		|	RET
;


COND:		COND1  //{$$ = makenode("",$2,$1,NULL,NULL);}
		| '('COND1')' END_COND  {$$ = makenode("",$2,$4,NULL,NULL);}


COND1:		MATH OPER {$$ = makenode("",$2,$1,NULL,NULL);}
		|	CALL_FUNC OPER {$$ = makenode("",$2,$1,NULL,NULL);}
		|	STR OPER {$$ = makenode("",$2,makenode($1,NULL,NULL,NULL,NULL),NULL,NULL);}
		|	CHR OPER {$$ = makenode("",$2,makenode($1,NULL,NULL,NULL,NULL),NULL,NULL);}
		|	NULLL OPER {$$ = makenode("",$2,makenode("NULL",NULL,NULL,NULL,NULL),NULL,NULL);}
		|	BOOLEAN OPER {$$ = makenode("",$2,$1,NULL,NULL);}
		|	NOT ID OPER {$$ = makenode("!",makenode($2,NULL,NULL,NULL,NULL),$3,NULL,NULL);}
		|	NOT BOOLEAN OPER {$$ = makenode("!",$2,$3,NULL,NULL);}
		|	NOT CALL_FUNC OPER {$$ = makenode($1,$2,$3,NULL,NULL);}
		|	ID '[' MATH ']' OPER {$$ = makenode($1,$3,$5,NULL,NULL);}
;
	
	
OPER:		SMALL MID_COND {$$ = makenode("<",$2,NULL,NULL,NULL);}
		|	BIG MID_COND {$$ = makenode(">",$2,NULL,NULL,NULL);}
		|	EQ MID_COND {$$ = makenode("==",$2,NULL,NULL,NULL);}
		|	BEQ MID_COND {$$ = makenode(">=",$2,NULL,NULL,NULL);}
		|	SEQ MID_COND {$$ = makenode("<=",$2,NULL,NULL,NULL);}
		|	NEQ MID_COND {$$ = makenode("!=",$2,NULL,NULL,NULL);}
		/*|	END_COND*/
; 

MID_COND:	MATH END_COND {$$ = makenode("",$2,$1,NULL,NULL);}
		|	CALL_FUNC END_COND {$$ = makenode("",$2,$1,NULL,NULL);}
		|	STR END_COND {$$ = makenode("",$2,makenode($1,NULL,NULL,NULL,NULL),NULL,NULL);}
		|	CHR END_COND {$$ = makenode("",$2,makenode($1,NULL,NULL,NULL,NULL),NULL,NULL);}
		|	NULLL END_COND {$$ = makenode("",$2,makenode("NULL",NULL,NULL,NULL,NULL),NULL,NULL);}
		|	BOOLEAN END_COND {$$ = makenode("",$2,$1,NULL,NULL);}
		|	NOT ID END_COND{$$ = makenode("!",makenode($2,NULL,NULL,NULL,NULL),$3,NULL,NULL);}
		|	NOT BOOLEAN END_COND {$$ = makenode("!",$2,$3,NULL,NULL);}
		|	NOT CALL_FUNC END_COND {$$ = makenode($1,$2,$3,NULL,NULL);}
		|	ID '[' MATH ']' END_COND {$$ = makenode($1,$3,$5,NULL,NULL);}
;
		
END_COND:	AND COND {$$ = makenode("&&",$2,NULL,NULL,NULL);}
		|	OR COND {$$ = makenode("||",$2,NULL,NULL,NULL);}
		|	{$$ = NULL;}
;

RET_I_W_D:	RETURN ID ';' {$$ = makenode("return",makenode($2,NULL,NULL,NULL,NULL),NULL,NULL,NULL);}
		|	RETURN CHR ';'{$$ = makenode("return",makenode($2,NULL,NULL,NULL,NULL),NULL,NULL,NULL);}
		|	RETURN NUM';' {$$ = makenode("return",makenode($2,NULL,NULL,NULL,NULL),NULL,NULL,NULL);}
		|	RETURN STR';' {$$ = makenode("return",makenode($2,NULL,NULL,NULL,NULL),NULL,NULL,NULL);}
		|	RETURN RNUM';' {$$ = makenode("return",makenode($2,NULL,NULL,NULL,NULL),NULL,NULL,NULL);}
		|	RETURN FUNC_END {$$ = makenode("return",$2,NULL,NULL,NULL);}
		|	RETURN TRUE';' {$$ = makenode("return",makenode("TRUE",NULL,NULL,NULL,NULL),NULL,NULL,NULL);}
		|	RETURN FALSE';' {$$ = makenode("return",makenode("FALSE",NULL,NULL,NULL,NULL),NULL,NULL,NULL);}
		| 	END_BLOCK {$$ = makenode("END_BLOCK",$1,NULL,NULL,NULL);}
;