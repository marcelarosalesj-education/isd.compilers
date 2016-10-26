  // mylanguage
  //  BISON  file
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <iostream>
using namespace std;

//extern  int  yylex ();
extern  void  yyerror();



// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" FILE *yyin;
 
void yyerror(const char *s);




struct Element{
	string varname;
	string vartype;
	int address;
};

struct Element table[100];
int idx=0;

%}


%union {
  char *string;           /* Ptr to constant string (strings are malloc'd) */
  int integer;            /* Constant integer value */
  float fp;               /* Constant floating point value */
}



%start  ROOT
%token <string> MAIN DEF NUM LETT IF ELSE FOR DO WHILE OPAR CPAR OKEY CKEY SEMICOLON EQUAL QUOTE INTEGER FLOATINGPOINT STRING ID LT GT LET GET EQU NEQ PLUS MINUS MULT DIV AND OR NOT OB CB COMMA 
%type <string> ROOT M FUNCTS FUNCT BLOCK  X    STMT I IE F W DW E PRIO1 ES PRIO2 TA PRIO3 FF X1 X3  DECL


%%

ROOT:       FUNCTS M {
						//printf(" OK ROOT   number:%d \n", idx);
						cout << "    OK ROOT num : "<<idx<<endl;
						int impr;
						for(impr=0; impr<idx; impr++){
							//printf("name: %s type:%s \n", table[impr].varname, table[impr].vartype);
							cout << "table : "<< table[impr].varname << "  , "<< table[impr].vartype << endl;

						}

					}
            ;

FUNCTS:	    FUNCT FUNCTS {printf("MANY-FUNCTS \n");}
	    	|  {printf("NO-FUNCTS \n");}
	    	;

FUNCT:      DEF ID BLOCK {printf("FUNCT \n");}
            ;

M:          MAIN BLOCK {printf("MAIN \n");}
            ;

BLOCK:      OKEY LIST CKEY  {printf(" BR Blk \n");}
            | STMT
            ;

LIST:       STMT SEMICOLON LIST
            |
            ;

STMT:     	
              I       		{printf(" I\n");}
            | F       		{printf(" F\n");}
            | W       		{printf(" W\n");}
            | DW     		{printf(" DW\n");}
            | DECL
            | ID X3 EQUAL E
            | ID OPAR CPAR
            ;

DECL:		  NUM ID X 		{
							//printf(" \n\nNUMDEF 2=%s  \n", $2);
							cout << "\n\nNUMDEF  : "<< $2<< endl;
							table[idx].varname = $2;
							table[idx].vartype = "num";
							//printf(" table %s t:%s\n", table[idx].varname, table[idx].vartype );
							cout << "table : "<< table[idx].varname << "  , "<< table[idx].vartype << endl;
							idx=idx+1;

							} 
			| LETT ID Y 	{
							//printf(" \n\nLETTDEF: 2=%s \n", $2);
							cout << "\n\nLETTDEF  : "<< $2<< endl;
							table[idx].varname = $2;
							table[idx].vartype = "lett";
							//printf(" table %s t:%s\n", table[idx].varname, table[idx].vartype);
							cout << "table : "<< table[idx].varname << "  , "<< table[idx].vartype << endl;
							idx=idx+1;

							} 
			;
X:            EQUAL INTEGER      		{printf(" EN X INT\n");}
			| EQUAL FLOATINGPOINT	{printf(" EN X FP\n");}
            |
            ;
Y:           EQUAL QUOTE ID QUOTE 		{printf(" EN Y2\n");}
            |
            ;

I:          IF OPAR E CPAR BLOCK IE     {printf(" EN IF \n");}
            ;

IE:         ELSE BLOCK                  {printf(" IE ELSE \n");}
            |                           {printf(" IE NADA \n");}
            ;
F:          FOR OPAR NUM ID EQUAL INTEGER SEMICOLON E SEMICOLON E CPAR BLOCK {printf(" TERMINA FOR\n");}	;
W:          WHILE OPAR E CPAR BLOCK;
DW:         DO BLOCK WHILE OPAR E CPAR;

E:			ES | ES PRIO1 ES;
PRIO1:		LT | GT | LET | GET | EQU | NEQ;
ES: 		TA | TA PRIO2 ES;
PRIO2:		PLUS | MINUS | OR;
TA: 		FF | FF PRIO3 TA;
PRIO3: 		MULT | DIV | AND;
FF:			INTEGER | FLOATINGPOINT | X1 OPAR E CPAR | X1 ID X3 ;
X1:			NOT | ;
X3: 		OB E CB X3 | ;



