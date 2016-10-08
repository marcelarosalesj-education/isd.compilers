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
"e"                       {printf("got  E  token\n"); return E;}
"if"                      {printf("got  IF  token\n"); return IF;}
"else"                    {printf("got  ELSE  token\n"); return ELSE;}
"for"                     {printf("got  FOR  token\n"); return FOR;}
"do"                      {printf("got  DO  token\n"); return DO;}
"while"                   {printf("got  WHILE  token\n"); return WHILE;}
"("                       {printf("got  OPAR  token\n"); return OPAR;}
")"                       {printf("got  CPAR  token\n"); return CPAR;}
"{"                       {printf("got  OBR  token\n"); return OBR;}
"}"                       {printf("got  CBR  token\n"); return CBR;}
";"                       {printf("got  SEMICOLON  token\n"); return SEMICOLON;}
"="                       {printf("got  EQUAL  token\n"); return EQUAL;}
"\""                      {printf("got  QUOTE  token\n"); return QUOTE;}
{INTEGER}                 {printf( "got INTEGER: %s (%d)\n", yytext, atoi(yytext));
                           yylval.integer = atoi(yytext);
                           return INTEGER;}
{FLOATINGPOINT}           {printf( "got FLOATINGPOINT: %s (%g)\n", yytext, atof(yytext));
                           yylval.fp = atof(yytext);
                           return FLOATINGPOINT;}
{ID}                      {printf( "got ID: %s\n", yytext );
                           yylval.string = yytext;
                           return ID;}
{STRING}                   {printf( "got STRING: %s (%d)\n", yytext, atoi(yytext));
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
