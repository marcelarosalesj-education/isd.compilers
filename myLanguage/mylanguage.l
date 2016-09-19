  // hola hola que tal
  // FLEX  file
%{
#include  <stdio.h>
#include "mylanguage.tab.h"   // the  output  of  bison on  example0.y
void  yyerror();   // we need to  forward  declare  these  functions ,
int  yyparse(void);     // don't worry  about  them
%}




INTEGER         [0-9]+
FLOATINGPOINT   [0-9]+"."[0-9]*
STRING          [a-z][a-zA-Z0-9\-\_]*
ID              [a-z][a-z0-9]*

%%
  // reserved keywords
"num"                     {printf("got  NUM  token\n"); return NUM;}
"lett"                    {printf("got  LETT  token\n"); return LETT;}
"if"                      {printf("got  IF  token\n"); return IF;}
"then"                    {printf("got  THEN  token\n"); return THEN;}
"elseif"                  {printf("got  ELSEIF  token\n"); return ELSEIF;}
"else"                    {printf("got  ELSE  token\n"); return ELSE;}
"endif"                   {printf("got  ENDIF  token\n"); return ENDIF;}
"while"                   {printf("got  WHILE  token\n"); return WHILE;}
"endwhile"                {printf("got  ENDWHILE  token\n"); return ENDWHILE;}
"for"                     {printf("got  FOR  token\n"); return FOR;}
"endfor"                  {printf("got  ENDFOR  token\n"); return ENDFOR;}
"do"                      {printf("got  DO  token\n"); return DO;}
"("                       {printf("got  OPARENTHESIS  token\n"); return OPARENTHESIS;}
")"                       {printf("got  CPARENTHESIS  token\n"); return CPARENTHESIS;}
","                       {printf("got  COMMA  token\n"); return COMMA;}
";"                       {printf("got  SEMICOLON  token\n"); return SEMICOLON;}
"\""                      {printf("got  QUOTE  token\n"); return QUOTE;}
{INTEGER}                 {printf( "got INTEGER: %s (%d)\n", yytext, atoi(yytext));
                           yylval.integer = atoi(yytext);
                           return INTEGER;}
{FLOATINGPOINT}           {printf( "got FLOATINGPOINT: %s (%g)\n", yytext,atof(yytext));
                           yylval.fp = atof(yytext);
                           return FLOATINGPOINT;}
{ID}                      {printf( "got ID: %s\n", yytext );
                           yylval.string = yytext;
                           return ID;}
[ \t\n]+                  ;   // do  nothing  on  whitespace
.                         {ECHO; yyerror();}
%%

void  yyerror() {printf("ERROR: Could  not  parse !\n");}
int  yywrap(void) { }
int  main(void) {
  // we don't want to do  anything  extra , just  start  the  parser
  yyparse ();   //  yyparse  is  defined  for us by flex
}
