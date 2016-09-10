  // retrieved from http://people.seas.harvard.edu/~bwaggoner/writeups/jumpstart/flexbison/jumpstart_flexbison.pdf
  // FLEX  file  example0.l
  // NOTE: comments  should  be  indented (not at left  margin !)
%{
#include  <stdio.h>
#include "example0.tab.h"   // the  output  of  bison on  example0.y
void  yyerror(char *);   // we need to  forward  declare  these  functions ,
int  yyparse(void);     // don't worry  about  them
%}

%%

  // on  reading  this    do this
";"                        return  SEMICOLON;
"hello-world"            {printf("got  HELLO  token\n");  return  HELLO;}
"quit"                     {printf("got  QUIT  token\n");  return  QUIT;}
[ \t\n]+                  ;   // do  nothing  on  whitespace

%%

void  yyerror(char* str) {printf("ERROR: Could  not  parse !\n");}
int  yywrap(void) { }
int  main(void) {
  // we don't want to do  anything  extra , just  start  the  parser
yyparse ();   //  yyparse  is  defined  for us by flex
}
