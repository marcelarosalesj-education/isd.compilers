  // hola hola que tal
  //  BISON  file
%{
#include  <stdio.h>
#include  <stdlib.h>
#include <string.h>
extern  int  yylex ();
extern  void  yyerror();
%}


%union {
  char *string;
  int integer;
}
%start  ROOT
%token <string> HOLA
%token <string> QUE
%token <string> TAL
%token <string> COMA
%type <integer> ROOT X Y

%%

ROOT:       X QUE TAL {printf(" OK \n");}
            ;
X:          HOLA Y {;}
            | /* empty string */
            ;
Y:          COMA HOLA Y {;}
            | /* empty string */
            ;
