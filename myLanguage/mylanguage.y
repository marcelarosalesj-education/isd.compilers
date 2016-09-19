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
  char *string;           /* Ptr to constant string (strings are malloc'd) */
  int integer;            /* Constant integer value */
  float fp;               /* Constant floating point value */
}

%start  ROOT
%token <string> NUM LETT IF THEN ELSEIF ELSE ENDIF WHILE ENDWHILE FOR ENDFOR DO OPARENTHESIS CPARENTHESIS COMMA SEMICOLON QUOTE ID INTEGER FLOATINGPOINT STRING
%type <string> ROOT X Y

%%

ROOT:       X SEMICOLON {printf(" OK \n");}
            ;
X:          NUM ID Y {printf("  ID:%s \n", $2);} /* NUM-$1, ID-$2, Y-$3*/
            | LETT ID Y {;}
            | /* empty string */ {;}
            ;
Y:          COMMA ID Y {;}
            | /* empty string */
            ;
