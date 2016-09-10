  // hola hola que tal
  // FLEX  file
%{
#include  <stdio.h>
#include "hola.tab.h"   // the  output  of  bison on  example0.y
void  yyerror();   // we need to  forward  declare  these  functions ,
int  yyparse(void);     // don't worry  about  them
%}

%%
  // on  reading  this    do this
"hola"                    {printf("got  HOLA  token\n"); return HOLA;}
"que"                     {printf("got  QUE  token\n"); return QUE;}
"tal"                     {printf("got  TAL  token\n"); return TAL;}
","                       {printf("got  COMA  token\n"); return COMA;}
[ \t\n]+                  ;   // do  nothing  on  whitespace
.                         {ECHO; yyerror();}

%%

void  yyerror() {printf("ERROR: Could  not  parse !\n");}
int  yywrap(void) { }
int  main(void) {
  // we don't want to do  anything  extra , just  start  the  parser
  yyparse ();   //  yyparse  is  defined  for us by flex
}
