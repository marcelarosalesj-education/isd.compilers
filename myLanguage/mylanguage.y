  // mylanguage
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
%token <string> MAIN DEF NUM LETT E IF ELSE FOR DO WHILE OPAR CPAR OBR CBR SEMICOLON EQUAL QUOTE INTEGER FLOATINGPOINT STRING ID
%type <string> ROOT PROG M FUNCT BLOCK  X  Y  STMT COND I IE F W DW

%%

ROOT:       FUNCT ROOT {printf(" OK ROOT\n");}
            | PROG
            ;

PROG:       M {printf("PROG \n");}
            ;

FUNCT:      DEF ID BLOCK {printf("FUNCT \n");}
            |
            ;

M:          MAIN BLOCK {printf("MAIN \n");}
            |
            ;

BLOCK:      OBR LIST CBR  {printf(" BR Blk \n");}
            | STMT
            |                     {printf(" N Blk \n");}
            ;

LIST:       STMT SEMICOLON LIST
            | STMT
            ;

STMT:         NUM ID X  {printf(" NUMDEF \n");}
            | LETT ID Y    {printf(" LETTDEF \n");}
            | I       {printf(" I\n");}
            | F       {printf(" F\n");}
            | W       {printf(" W\n");}
            | DW      {printf(" DW\n");}
            | COND    {printf(" COND\n");}
            ;

X:          EQUAL INTEGER       {printf(" EN X \n");}
            |
            ;

Y:          EQUAL QUOTE E QUOTE {printf(" EN Y\n");}
            |
            ;

COND:       E                   {printf(" E EN COND \n");}
            ;

I:          IF OPAR COND CPAR BLOCK IE      {printf(" EN IF \n");}
            ;

IE:         ELSE BLOCK                      {printf(" IE ELSE \n");}
            |                                   {printf(" IE NADA \n");}
            ;

F:          FOR OPAR NUM ID EQUAL INTEGER SEMICOLON COND SEMICOLON COND CPAR BLOCK {printf(" TERMINA FOR\n");}
            ;
W:          WHILE OPAR COND CPAR BLOCK
            ;
DW:         DO BLOCK WHILE OPAR COND CPAR SEMICOLON
            ;
