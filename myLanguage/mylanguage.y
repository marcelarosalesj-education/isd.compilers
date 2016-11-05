  // mylanguage
  //  BISON  file
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <iostream>
#include <stack>
#include<sstream>
using namespace std;

extern "C" int yylex();
extern "C" FILE *yyin;
 
void yyerror(const char *s);

stack<string> operadores;
stack<int> operandos;
stack<int> temporales;
stack<int> saltos;
int idxCuad = 0;

string cuadruplos[100][5];

struct Element{
	string varname;
	string vartype;
};

struct Element table[100];
int idx=0;

std::stringstream ss;

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

            cout << "CUADRUPLO"<<endl;
            for(impr=0; impr<idxCuad; impr++){
              cout << impr << "\t"<< cuadruplos[impr][0] << " " << cuadruplos[impr][1] << " " << cuadruplos[impr][2] << " " << cuadruplos[impr][3] << endl;
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
            | ID {
                  string aux = $1;
                  cout << " >" <<aux<<endl;
                  if( std::string::npos != aux.find("=") ){ // It has an =
                    aux = trim(aux.substr(0, aux.find("=")));
                  } else if ( std::string::npos != aux.find(";") ){ // It has an ;
                    aux = trim(aux.substr(0, aux.find(";")));
                  }
                  cout << " >>"<<aux<<endl;
                  cout << " >>>"<<getIndex(aux)<<endl;
                  operandos.push(getIndex(aux));
              } X3 EQUAL E {
                  int re = operandos.top();      operandos.pop();
                  int id = operandos.top();      operandos.pop();
                  
                  
                  // Generar cuadruplo
                  cout << "CUADRUPLO:\t";
                  cout << "stmt=" << " " << re << " int/float " << id << endl;
                  cuadruplos[idxCuad][0] = "=";
                  ss.str(std::string());
                  ss << re;
                  cuadruplos[idxCuad][1] = ss.str();
                  cuadruplos[idxCuad][2] = "int/float";
                  ss.str(std::string());
                  ss << id;
                  cuadruplos[idxCuad][3] = ss.str();
                  
                  idxCuad++;

              }

            | ID OPAR CPAR
            ;

DECL:		  NUM ID {
                string aux = $2;
                table[idx].varname = aux;
                table[idx].vartype = "num";
                operandos.push(idx);
                idx=idx+1;
        } X 
			| LETT ID {
                string aux = $2;
                table[idx].varname = aux;
                table[idx].vartype = "lett";
                operandos.push(idx);
                idx=idx+1;
        } Y
			;

X:            EQUAL INTEGER  {
                  string aux = $1;
                  string re = trim(aux.substr(aux.find("=")+1, aux.size() ) );
                  int id = operandos.top();      operandos.pop();
                  
                  // Generar cuadruplo
                  cout << "CUADRUPLO:\t";
                  cout << "=" << " " << re <<"i"<< " " << id << endl;
                  cuadruplos[idxCuad][0] = "=";
                  cuadruplos[idxCuad][1] = re;
                  cuadruplos[idxCuad][2] = "int";
                  ss.str(std::string());
                  ss << id;
                  cuadruplos[idxCuad][3] = ss.str();
                  idxCuad++;
              }	
			      | EQUAL FLOATINGPOINT {
                  string aux = $1;
                  string re = trim(aux.substr(aux.find("=")+1, aux.size() ) );
                  int id = operandos.top();      operandos.pop();
                  
                  // Generar cuadruplo
                  cout << "CUADRUPLO:\t";
                  cout << "=" << " " << re <<"f"<< " " << id << endl;
                  cuadruplos[idxCuad][0] = "=";
                  cuadruplos[idxCuad][1] = re;
                  cuadruplos[idxCuad][2] = "float";
                  ss.str(std::string());
                  ss << id;
                  cuadruplos[idxCuad][3] = ss.str();
                  idxCuad++;
              } 
            |
            ;

Y:           EQUAL STRING {
                  string aux = $1;
                  string re = trim(aux.substr(aux.find("=")+1, aux.size() ) );
                  int id = operandos.top();      operandos.pop();
                  
                  // Generar cuadruplo
                  cout << "CUADRUPLO:\t";
                  cout << "=" << " " << re <<"s"<< " " << id << endl;
                  cuadruplos[idxCuad][0] = "=";
                  cuadruplos[idxCuad][1] = re;
                  cuadruplos[idxCuad][2] = "string";
                  ss.str(std::string());
                  ss << id;
                  cuadruplos[idxCuad][3] = ss.str();
                  idxCuad++;
              } 
            |
            ;

I:          IF OPAR E CPAR {
              int re = operandos.top();      operandos.pop();
              // Pendiente validar que el tipo sea bool. Tendria que usar un stack de tipos o algo asi
              // Generar cuadruplo
              cout << "CUADRUPLO:\t";
              cout << "GOTOF" << " " << re << endl;
              cuadruplos[idxCuad][0] = "GOTOF";
              ss.str(std::string());
              ss << re;
              cuadruplos[idxCuad][1] = ss.str();
              idxCuad++;

              saltos.push(idxCuad-1);


            } BLOCK IE     {
              int dir = saltos.top(); saltos.pop();
              // Rellena con idxCuad lo que se obtuvo en dir
              ss.str(std::string());
              ss << idxCuad;
              cuadruplos[dir][2] = ss.str();

            }
            ;

IE:         ELSE {
              int dir = saltos.top(); saltos.pop();

              // Generar cuadruplo
              cout << "CUADRUPLO:\t";
              cout << "GOTO" << endl;
              cuadruplos[idxCuad][0] = "GOTO";
              idxCuad++;

              saltos.push(idxCuad-1);

              // Rellena con idxCuad lo que se obtuvo en dir
              ss.str(std::string());
              ss << idxCuad;
              cuadruplos[dir][2] = ss.str();

            } BLOCK                  {;}
            |                           {;}
            ;

F:          FOR OPAR ID EQUAL INTEGER SEMICOLON E SEMICOLON E CPAR BLOCK {;}	;

W:          WHILE {
              saltos.push(idxCuad);

            } OPAR E CPAR {
              int re = operandos.top(); operandos.pop();
              // Pendiente validar qeu sea bool re

              // Generar cuadruplo
              cout << "CUADRUPLO:\t";
              cout << "GOTOF" << " " << re << endl;
              cuadruplos[idxCuad][0] = "GOTOF";
              ss.str(std::string());
              ss << re;
              cuadruplos[idxCuad][1] = ss.str();
              idxCuad++;

              saltos.push(idxCuad-1);


            } BLOCK {
              int dir1 = saltos.top(); saltos.pop();
              int dir2 = saltos.top(); saltos.pop();
               // Generar cuadruplo
              cout << "CUADRUPLO:\t";
              cout << "GOTO" << " " << dir2 << endl;
              cuadruplos[idxCuad][0] = "GOTO";
              ss.str(std::string());
              ss << dir2;
              cuadruplos[idxCuad][1] = ss.str();
              idxCuad++;

              // Rellena con idxCuad lo que se obtuvo en dir
              ss.str(std::string());
              ss << idxCuad;
              cuadruplos[dir1][2] = ss.str();


            };

DW:         DO {
              saltos.push(idxCuad);

            } BLOCK WHILE OPAR E CPAR {
              int re = operandos.top(); operandos.pop();

              // Pendiente validar qeu sea bool re

              int dir = saltos.top(); saltos.pop();

              // Generar cuadruplo
              cout << "CUADRUPLO:\t";
              cout << "GOTOV" << " " << re << " " << dir << endl;
              cuadruplos[idxCuad][0] = "GOTOV";
              ss.str(std::string());
              ss << re;
              cuadruplos[idxCuad][1] = ss.str();
              ss.str(std::string());
              ss << dir;
              cuadruplos[idxCuad][2] = ss.str();
              idxCuad++;

            }
            ;

E:			  ES
            | ES PRIO1 ES {
                    string opn = operadores.top();  operadores.pop();
                    int op2 = operandos.top();      operandos.pop();
                    int op1 = operandos.top();      operandos.pop();
                    int res = temporales.top();     temporales.pop();
                    // Generar cuadruplo
                    cout << "CUADRUPLO:\t";
                    cout << opn << " " << op1 << " " << op2 << " " << res << endl;
                    cuadruplos[idxCuad][0] = opn;
                    ss.str(std::string());
                    ss << op1;
                    cuadruplos[idxCuad][1] = ss.str();
                    ss.str(std::string());
                    ss << op2;
                    cuadruplos[idxCuad][2] = ss.str();
                    ss.str(std::string());
                    ss << res;
                    cuadruplos[idxCuad][3] = ss.str();
                    idxCuad++;
                    operandos.push(res);
              }
            ;

PRIO1:		    LT    {operadores.push("<");} 
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
                    cuadruplos[idxCuad][0] = opn;
                    ss.str(std::string());
                    ss << op1;
                    cuadruplos[idxCuad][1] = ss.str();
                    ss.str(std::string());
                    ss << op2;
                    cuadruplos[idxCuad][2] = ss.str();
                    ss.str(std::string());
                    ss << res;
                    cuadruplos[idxCuad][3] = ss.str();
                    idxCuad++;
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
                  cuadruplos[idxCuad][0] = opn;
                  ss.str(std::string());
                  ss << op1;
                  cuadruplos[idxCuad][1] = ss.str();
                  ss.str(std::string());
                  ss << op2;
                  cuadruplos[idxCuad][2] = ss.str();
                  ss.str(std::string());
                  ss << res;
                  cuadruplos[idxCuad][3] = ss.str();
                  idxCuad++;
                  operandos.push(res); 
             } 
            ;

PRIO3: 	  	  MULT    {operadores.push("*");}
            | DIV     {operadores.push("/");}
            | AND     {operadores.push("AND");}
            ;


FF:			      INTEGER {
                ;
              }
            | FLOATINGPOINT {
                ;
              }
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
  temporales.push(111);
  temporales.push(112);
  temporales.push(113);
  temporales.push(114);
  temporales.push(115);
  temporales.push(116);
  temporales.push(117);
  temporales.push(118);
  temporales.push(119);
  temporales.push(120);
  temporales.push(121);
  temporales.push(122);
  temporales.push(123);
  temporales.push(124);
  temporales.push(125);
  temporales.push(126);
  temporales.push(127);
  temporales.push(128);
  temporales.push(129);
  temporales.push(130);

  return yyparse ();   //  yyparse  is  defined  for us by flex

  

}

