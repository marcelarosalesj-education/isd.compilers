  // mylanguage
  // FLEX  file
%{
#include  <stdio.h>
#include "mylanguage.tab.h"   // the  output  of  bison on  example0.y
void  yyerror(char const *s);   // we need to  forward  declare  these  functions ,
int  yyparse(void);     // don't worry  about  them
%}

INTEGER         [0-9]+
FLOATINGPOINT   [0-9]+"."[0-9]*
STRING          [a-zA-Z0-9]*
ID              [a-z][a-z0-9]*

%%
"main"                    {printf("got  MAIN  token\n"); return MAIN;}
"def"                     {printf("got  DEF  token\n"); return DEF;}
"num"                     {printf("got  NUM  token\n"); return NUM;}
"lett"                    {printf("got  LETT  token\n"); return LETT;}
"if"                      {printf("got  IF  token\n"); return IF;}
"else"                    {printf("got  ELSE  token\n"); return ELSE;}
"for"                     {printf("got  FOR  token\n"); return FOR;}
"do"                      {printf("got  DO  token\n"); return DO;}
"while"                   {printf("got  WHILE  token\n"); return WHILE;}
"("                       {printf("got  OPAR  token\n"); return OPAR;}
")"                       {printf("got  CPAR  token\n"); return CPAR;}
"["                       {printf("got  OB  token\n"); return OB;}
"]"                       {printf("got  CB  token\n"); return CB;}
"{"                       {printf("got  OKEY  token\n"); return OKEY;}
"}"                       {printf("got  CKEY  token\n"); return CKEY;}
";"                       {printf("got  SEMICOLON  token\n"); return SEMICOLON;}
","                       {printf("got  COMMA  token\n"); return COMMA;}
"="                       {printf("got  EQUAL  token\n"); return EQUAL;}
"\""                      {printf("got  QUOTE  token\n"); return QUOTE;}
"<"                       {printf("got  LT  token\n"); return LT;}
">"                       {printf("got  GT  token\n"); return GT;}
"<="                       {printf("got LET   token\n"); return LET;}
">="                       {printf("got GET   token\n"); return GET;}
"=="                       {printf("got EQU   token\n"); return EQU;}
"!="                       {printf("got NEQ   token\n"); return NEQ;}
"+"                       {printf("got  PLUS  token\n"); return PLUS;}
"-"                       {printf("got  MINUS  token\n"); return MINUS;}
"*"                       {printf("got  MULT  token\n"); return MULT;}
"/"                       {printf("got  DIV  token\n"); return DIV;}
"and"                       {printf("got  AND  token\n"); return AND;}
"or"                       {printf("got  OR  token\n"); return OR;}
"not"                       {printf("got NOT   token\n"); return NOT;}
{INTEGER}                 {printf( "got INTEGER: %s (%d)\n", yytext, atoi(yytext));
                           yylval.integer = atoi(yytext);
                           return INTEGER;}
{FLOATINGPOINT}           {printf( "got FLOATINGPOINT: %s (%g)\n", yytext, atof(yytext));
                           yylval.fp = atof(yytext);
                           return FLOATINGPOINT;}
{ID}                      {printf( "got ID: %s\n", yytext );
                           yylval.string = yytext;
                           return ID;}
{STRING}                   {printf( "got STRING: %s \n", yytext);
                           yylval.string = yytext;
                           return STRING;}
[ \t\n]+                  ;   // do  nothing  on  whitespace
.                         {ECHO; yyerror("error");}

%%

void  yyerror(char const *s) {fprintf (stderr, "%s\n", s);}
int  yywrap(void) { }
int  main(void) {
  // we don't want to do  anything  extra , just  start  the  parser
  yyparse ();   //  yyparse  is  defined  for us by flex
}
