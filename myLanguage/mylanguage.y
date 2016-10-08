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
%type <string> ROOT PROG M FUNCT BLOCK D NUMDEF X LETTDEF Y STMT COND I IE Z F W DW

%%

ROOT:       PROG {printf(" OK ROOT\n");}
            |
            ;
PROG:       FUNCT PROG M {printf(" PROG \n");}
            |
            ;
M:          MAIN OBR BLOCK CBR {printf(" en MAIN \n");}
            |
            ;
FUNCT:      DEF ID OBR BLOCK CBR
            |
            ;
BLOCK:        STMT BLOCK {printf(" D Blk \n");}
            | {printf(" N Blk \n");}
            ;
STMT:         D       {printf(" D\n");}
            | I       {printf(" I\n");}
            | F       {printf(" F\n");}
            | W       {printf(" W\n");}
            | DW      {printf(" DW\n");}
            | COND    {printf(" CONDD\n");}
            |         {printf(" N XX \n");}
            ;
D:            NUMDEF
            | LETTDEF
            ;
NUMDEF:     NUM ID X SEMICOLON  {printf(" NUMDEF \n");}
            ;
X:          EQUAL INTEGER       {printf(" EN X \n");}
            |
            ;
LETTDEF:    LETT ID Y SEMICOLON {printf(" LETTDEF \n");}
            ;
Y:          EQUAL QUOTE E QUOTE {printf(" EN Y\n");}
            |
            ;
COND:       E                   {printf(" E EN COND \n");}
            ;

I:          IF OPAR COND CPAR OBR Z CBR IE      {printf(" EN IF \n");}
            ;
IE:         ELSE OBR Z CBR                      {printf(" IE ELSE \n");}
            |                                   {printf(" IE NADA \n");}
            ;
F:          FOR OPAR NUMDEF SEMICOLON COND SEMICOLON COND CPAR OBR Z CBR
            ;
W:          WHILE OPAR COND CPAR OBR Z CBR
            ;
DW:         DO OBR Z CBR WHILE OPAR COND CPAR SEMICOLON
            ;

Z:          STMT Z              {printf(" Z XX \n");}
            |                   {printf(" Z NADA \n");}
            ;
