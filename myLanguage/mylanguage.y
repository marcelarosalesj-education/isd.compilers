  // mylanguage
  //  BISON  file
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <iostream>
#include <stack>
using namespace std;

extern "C" int yylex();
extern "C" FILE *yyin;
 
void yyerror(const char *s);

stack<string> operadores;
stack<int> operandos;
stack<int> temporales;

struct Element{
	string varname;
	string vartype;
};

struct Element table[100];
int idx=0;


string trim(string str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}

int getIndex(string var){
  for(int i=0; i < idx; i++){
    if(table[i].varname == var )
      return i;
  }
  return -1;
}

stack<int> printstackInt(stack<int> q){
	stack<int> ret;
	stack<int> ret2;
 	while(!q.empty()){
		int aux;
		aux = q.top();
		q.pop();
		ret.push(aux);
	}
	cout << "------------------------------"<<endl;
	while(!ret.empty()){
		int aux;
		aux = ret.top();
		ret.pop();
		ret2.push(aux);
		cout << aux << " ";
	}
	cout << endl;
	cout << "------------------------------"<<endl;
	return ret2;
}

stack<string> printstackString(stack<string> q){
	stack<string> ret;
	stack<string> ret2;
 	while(!q.empty()){
		string aux;
		aux = q.top();
		q.pop();
		ret.push(aux);
	}
	cout << "------------------------------"<<endl;
	while(!ret.empty()){
		string aux;
		aux = ret.top();
		ret.pop();
		ret2.push(aux);
		cout << aux << " ";
	}
	cout << endl;
	cout << "------------------------------"<<endl;
	return ret2;
}



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
						cout << "    OK ROOT" << endl<<endl;
						int impr;
            cout << "Num of variables: "<<idx<<endl;
						for(impr=0; impr<idx; impr++){
							cout << impr<<"|"<< table[impr].varname << "|"<< table[impr].vartype << endl;

						}

					}
            ;

FUNCTS:	      FUNCT FUNCTS {printf("MANY-FUNCTS \n");}
	    	|  {;}
	    	;

FUNCT:        DEF ID BLOCK        {;}
            ;

M:            MAIN BLOCK          {;}
            ;

BLOCK:        OKEY LIST CKEY      {;}
            | STMT SEMICOLON
            ;

LIST:         STMT SEMICOLON LIST
            |
            ;

STMT:     	
              I       		{;}
            | F       		{;}
            | W       		{;}
            | DW     		{;}
            | DECL
            | ID X3 EQUAL E
            | ID OPAR CPAR
            ;

DECL:		  NUM ID X {
				  string aux = $2;
	              if( std::string::npos != aux.find("=") ){ // It has an =
	                table[idx].varname = trim(aux.substr(0, aux.find("=")));
	              } else if ( std::string::npos != aux.find(";") ){ // It has an ;
	                table[idx].varname = trim(aux.substr(0, aux.find(";")));
	              }
				  table[idx].vartype = "num";
				  idx=idx+1;

			  } 
			| LETT ID Y {							
				  string aux= $2;
	              if( std::string::npos != aux.find("=") ){ // It has an equal
	                table[idx].varname = trim(aux.substr(0, aux.find("=")));
	              } else if ( std::string::npos != aux.find(";") ){ // It has an semicolon
	                table[idx].varname = trim(aux.substr(0, aux.find(";")));
	              }
				  table[idx].vartype = "lett";
				  idx=idx+1;
			  } 
			;
X:            EQUAL INTEGER      		{;}
			| EQUAL FLOATINGPOINT		{;}
            |
            ;
Y:           EQUAL STRING 				{;}
            |
            ;

I:          IF OPAR E CPAR BLOCK IE     {;}
            ;

IE:         ELSE BLOCK                  {;}
            |                           {;}
            ;

F:          FOR OPAR ID EQUAL INTEGER SEMICOLON E SEMICOLON E CPAR BLOCK {;}	;

W:          WHILE OPAR E CPAR BLOCK;

DW:         DO BLOCK WHILE OPAR E CPAR;

E:			  ES
            | ES PRIO1 ES
            ;

PRIO1:		  LT    {operadores.push("<");} 
            | GT    {operadores.push(">");} 
            | LET   {operadores.push("<=");} 
            | GET   {operadores.push(">=");} 
            | EQU   {operadores.push("==");} 
            | NEQ   {operadores.push("!=");} 
            ;

ES: 		  TA
            | ES PRIO2 TA {
            		string opn = operadores.top();  operadores.pop();
                  	int op2 = operandos.top();      operandos.pop();
                  	int op1 = operandos.top();      operandos.pop();
                  	int res = temporales.top();     temporales.pop();
                  	// Generar cuadruplo
                  	cout << "CUADRUPLO:\t";
                  	cout << opn << " " << op1 << " " << op2 << " " << res << endl;
                  	operandos.push(res);                   
              } 

            ;

PRIO2:		  PLUS  {operadores.push("+");} 
            | MINUS {operadores.push("-");} 
            | OR    {operadores.push("OR");}
            ;

TA: 		  FF 
            | TA PRIO3 FF {
                  string opn = operadores.top();  operadores.pop();
                  int op2 = operandos.top();      operandos.pop();
                  int op1 = operandos.top();      operandos.pop();
                  int res = temporales.top();     temporales.pop();
                  // Generar cuadruplo
                  cout <<"CUADRUPLO:\t";
                  cout << opn << " " << op1 << " " << op2 << " " << res << endl;
                  operandos.push(res); 
             } 
            ;

PRIO3: 	  	  MULT    {operadores.push("*");}
            | DIV     {operadores.push("/");}
            | AND     {operadores.push("AND");}
            ;


FF:			  INTEGER 
            | FLOATINGPOINT 
            | X1 OPAR E CPAR
            | X1 ID { 
                      int pos = getIndex( $2 ); 
                      if(pos != -1){ 
                        operandos.push(pos);
                      } else {
                        cout << "VARIABLE NO EXISTE"<<endl;
                        return -1;
                      }
                    } X3 ;

X1:			     NOT | ;
X3: 		     OB E CB X3 | ;


%%

void  yyerror(char const *s) {
	fprintf (stderr, "%s\n", s);
}

int  main(void) {

  temporales.push(101);
  temporales.push(102);
  temporales.push(103);
  temporales.push(104);
  temporales.push(105);
  temporales.push(106);
  temporales.push(107);
  temporales.push(108);
  temporales.push(109);
  temporales.push(110);

  return yyparse ();   //  yyparse  is  defined  for us by flex

  

}

