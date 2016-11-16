  // mylanguage
  //  BISON  file
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <iostream>
#include <stack>
#include <sstream>
#include <algorithm>
using namespace std;

extern "C" int yylex();
extern "C" FILE *yyin;
 
void yyerror(const char *s);

stack<string> operadores;
stack<string> operandos;
stack<string> temporales;
stack<int> saltos;
stack<string> tipos;

string cuadruplos[100][4];

struct Element{
	string varname;
	string vartype;
};

struct VarDimensionada{
	string id;
	string tipo;
	struct nodo *next;
};

struct nodo{
	int d;
	int m;
	struct nodo *next;	
};

struct Element table[100]; // tabla de variables simples

struct VarDimensionada tablaDimensionada[100];
int f; // para vars dimensionadas 
int L; // para vars


int idx = 0; // index de tabla simple
int idxDim = 0; // index de tabla dimensionada
int idxCuad = 0; // index de cuadruplos


std::stringstream ss;

string trim(string str){
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}

string getIndex(string var){
  for(int i=0; i < idx; i++){
    if(table[i].varname == var ){
        ss.str(std::string());
        ss << i;
        return ss.str();
    }
  }
  return "-1";
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
%token <string> MAIN DEF NUM LETT IF ELSE FOR DO WHILE OPAR CPAR OKEY CKEY SEMICOLON EQUAL QUOTE STRING ID LT GT LET GET EQU NEQ PLUS MINUS MULT DIV AND OR NOT OB CB COMMA 
%token <integer> INTEGER
%token <fp> FLOATINGPOINT
%type <string> ROOT M FUNCTS FUNCT BLOCK  X    STMT I IE F W DW E PRIO1 ES PRIO2 TA PRIO3 FF X1 X3  DECL


%%

ROOT:       FUNCTS M {
				cout << "    OK ROOT" << endl<<endl;
				int impr;
				cout << "TABLA DE SIMBOLOS"<<endl;
    			cout << "Num of variables: "<<idx<<endl;
				for(impr=0; impr<idx; impr++){
					cout << impr<<"|"<< table[impr].varname << "|"<< table[impr].vartype << endl;

				}

	            cout << "CUADRUPLO"<<endl;
	            for(impr=0; impr<idxCuad; impr++){
	              cout << impr << "\t";
	              for(int c=0; c<4; c++){
	              	 cout << cuadruplos[impr][c] << " ";
	              }

	              cout << endl;
	            }
      // Vacias Pilas, operandos, operadores, temporales, saltos

      cout << "LAS PILAS QUEDARON :"<<endl;
      cout << "operandos"<<endl;
      printstackString(operandos);
      cout <<endl;
      cout << "operadores"<<endl;
      printstackString(operadores);
      cout <<endl;
      cout << "temporales"<<endl;
      printstackString(temporales);
      cout <<endl;
      cout << "saltos"<<endl;
      printstackInt(saltos);
      cout <<endl;


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
                  if( std::string::npos != aux.find("=") ){ // It has an =
                    aux = trim(aux.substr(0, aux.find("=")));
                  } else if ( std::string::npos != aux.find(";") ){ // It has an ;
                    aux = trim(aux.substr(0, aux.find(";")));
                  }
                  operandos.push(getIndex(aux));
              } X3 EQUAL E {
                  string re = operandos.top();      operandos.pop();
                  string id = operandos.top();      operandos.pop();
                  
                  cuadruplos[idxCuad][0] = "=";
                  cuadruplos[idxCuad][1] = re;
                  cuadruplos[idxCuad][2] = id;
                  
                  idxCuad++;  
              }

            | ID OPAR CPAR
            ;

DECL:		  NUM ID {
                string aux = $2;
                table[idx].varname = aux;
                table[idx].vartype = "num";
                ss.str(std::string());
                ss << idx;
                operandos.push(ss.str());
                tipos.push("num");
                idx=idx+1;

                f=0;
                L=1;

                
        } X3 X 
			| LETT ID {
                string aux = $2;
                table[idx].varname = aux;
                table[idx].vartype = "lett";
                ss.str(std::string());
                ss << idx;
                operandos.push(ss.str());
                tipos.push("lett");
                idx=idx+1;

                f=0;
                L=1;
        } X3 Y
			;





X:            EQUAL INTEGER  {
                  string aux = $1;
                  string re = trim(aux.substr(aux.find("=")+1, aux.size() ) ); // get integer
                  string id = operandos.top();      operandos.pop();
                  
                  cuadruplos[idxCuad][0] = "=";
                  cuadruplos[idxCuad][1] = re+" num";
                  cuadruplos[idxCuad][2] = id;
                  idxCuad++;
              }	
			      | EQUAL FLOATINGPOINT {
                  string aux = $1;
                  string re = trim(aux.substr(aux.find("=")+1, aux.size() ) );
                  string id = operandos.top();      operandos.pop();
                  
                  cuadruplos[idxCuad][0] = "=";
                  cuadruplos[idxCuad][1] = re + " num";
                  cuadruplos[idxCuad][2] = id;
                  idxCuad++;
              } 
            | {
                // Sacamos lo que hay aqui porque no hay nada en X, para evitar que esta referencia se quede en el stack
                operandos.pop();
              }
            ;

Y:           EQUAL STRING {
                  string aux = $1;
                  string re = trim(aux.substr(aux.find("=")+1, aux.size() ) );
                  string id = operandos.top();      operandos.pop();
                  cuadruplos[idxCuad][0] = "=";
                  cuadruplos[idxCuad][1] = re;
                  cuadruplos[idxCuad][3] = id;
                  idxCuad++;
              } 
            | {
                // Sacamos lo que hay aqui porque no hay nada en Y, para evitar que esta referencia se quede en el stack
                operandos.pop();
              }

            ;

I:          IF OPAR E CPAR {
              string re = operandos.top();      operandos.pop();
              // Pendiente validar que el tipo sea bool. Tendria que usar un stack de tipos o algo asi
              
              cuadruplos[idxCuad][0] = "GOTOF";
              ss.str(std::string());
              ss << re;
              cuadruplos[idxCuad][1] = ss.str();
              idxCuad++;
              saltos.push(idxCuad-1);
                            
            } BLOCK IE {
              int dir = saltos.top(); saltos.pop();
              // Rellena con idxCuad lo que se obtuvo en dir
              ss.str(std::string());
              ss << idxCuad;
              cuadruplos[dir][2] = ss.str();
            }
            ;

IE:         ELSE {
              int dir = saltos.top(); saltos.pop();
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

ASSIGN:     ID {
              operandos.push( getIndex($1) );
              } EQUAL INTEGER  { 
              string aux = $3;
              string re = trim(aux.substr(aux.find("=")+1, aux.size() ) );
              string id = operandos.top(); operandos.pop();
              cuadruplos[idxCuad][0] = "=";
              ss.str(string());
              ss << re + " num";
              cuadruplos[idxCuad][1] = ss.str();
              cuadruplos[idxCuad][2] = id;
              idxCuad++;

              saltos.push(idxCuad);
              
            }         

F:          FOR OPAR ASSIGN SEMICOLON E CPAR {
              string re = operandos.top(); operandos.pop();

              // Cuadruplo
              cuadruplos[idxCuad][0] = "GOTOF";
              cuadruplos[idxCuad][1] = re;
              idxCuad++;

              saltos.push(idxCuad-1);

            } BLOCK OPAR ID2 EQUAL E CPAR{
              int dir1 = saltos.top(); saltos.pop();
              int dir2 = saltos.top(); saltos.pop();

              // Cuadruplo que aumenta el contador
              string re = operandos.top(); operandos.pop();
              string id = operandos.top(); operandos.pop();
              cuadruplos[idxCuad][0] = "=";
              cuadruplos[idxCuad][1] = re;
              cuadruplos[idxCuad][2] = id;
              idxCuad++;

              // Cuadruplo para volver a evaluar la entrada al for
              cuadruplos[idxCuad][0] = "GOTO";
              ss.str(string());
              ss << dir2;
              cuadruplos[idxCuad][1] = ss.str();
              idxCuad++;

              // Rellenar GOTOF
              ss.str(string());
              ss << idxCuad;
              cuadruplos[dir1][2] = ss.str();

            }
            ;

ID2:        ID {
              operandos.push( getIndex($1) );
            }

            ;

W:          WHILE {
              saltos.push(idxCuad);

            } OPAR E CPAR {
              string re = operandos.top(); operandos.pop();
              // Pendiente validar qeu sea bool re

              cuadruplos[idxCuad][0] = "GOTOF";
              cuadruplos[idxCuad][1] = re;
              idxCuad++;
              saltos.push(idxCuad-1);
              
            } BLOCK {
              int dir1 = saltos.top(); saltos.pop();
              int dir2 = saltos.top(); saltos.pop();
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
              string re = operandos.top(); operandos.pop();

              int dir = saltos.top(); saltos.pop();

              cuadruplos[idxCuad][0] = "GOTOV";
              cuadruplos[idxCuad][1] = re;
              ss.str(std::string());
              ss << dir;
              cuadruplos[idxCuad][2] = ss.str();
              idxCuad++;

            }
            ;

E:			  ES {;}
            | ES PRIO1 ES {
              string opn = operadores.top();  operadores.pop();
              string op2 = operandos.top();      operandos.pop();
              string op1 = operandos.top();      operandos.pop();
              string res = temporales.top();     temporales.pop();

              cuadruplos[idxCuad][0] = opn;
              cuadruplos[idxCuad][1] = op1;
              cuadruplos[idxCuad][2] = op2;
              cuadruplos[idxCuad][3] = res;
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
                string op2 = operandos.top();      operandos.pop();
                string op1 = operandos.top();      operandos.pop();

                string res = temporales.top();     temporales.pop();

                cuadruplos[idxCuad][0] = opn;
                cuadruplos[idxCuad][1] = op1;
                cuadruplos[idxCuad][2] = op2;
                cuadruplos[idxCuad][3] = res;
                idxCuad++;
                operandos.push(res);
              }

            ;

PRIO2:		    PLUS  {operadores.push("+");} 
            | MINUS {operadores.push("-");} 
            | OR    {operadores.push("OR");}
            ;

TA: 		  FF 
            | TA PRIO3 FF {
                  string opn = operadores.top();  operadores.pop();
                  string op2 = operandos.top();      operandos.pop();
                  string op1 = operandos.top();      operandos.pop();
                  string res = temporales.top();     temporales.pop();
              
                  cuadruplos[idxCuad][0] = opn;
                  cuadruplos[idxCuad][1] = op1;
                  cuadruplos[idxCuad][2] = op2;
                  cuadruplos[idxCuad][3] = res;
                  idxCuad++;
                  operandos.push(res);
             } 
            ;

PRIO3: 	  	  MULT    {operadores.push("*");}
            | DIV     {operadores.push("/");}
            | AND     {operadores.push("AND");}
            ;


FF:			  INTEGER {
                float aux = ($1)/1.0;
                ss.str(std::string());
                ss << aux << " num " ;
                operandos.push(ss.str());
        }
            | FLOATINGPOINT {
        		float aux = ($1)/1.0;
                ss.str(std::string());
                ss << aux << " num " ;
                operandos.push(ss.str());  
          }
            | X1 OPAR E CPAR
            | X1 ID { 
                      string pos = getIndex( $2 ); 
                      if(pos != "-1"){ 
                        operandos.push(pos);
                      } else {
                        cout << "VARIABLE NO EXISTE : "<< $2 <<endl;
                        return -1;
                      }
                    } X3 ;

X1:			     NOT | ;
X3: 		     OB {
					
					// agregar a tabla dimensionada sin eliminar del stack porque se necesitan para la asinacion en caso de que haya
					tablaDimensionada[idxDim].id = operandos.top();
					tablaDimensionada[idxDim].tipo = tipos.top();

					// Limpiar variable simple que se agrego porque en realidad es dimensionada
					table[idx-1].varname="";
					table[idx-1].vartype="";
					idx--;

					nodo *sig;
					sig = new nodo; 
					if(f==0){
						tablaDimensionada[idxDim].next = sig; 
					}

				} E {
					 tablaDimensionada[idxDim].next->d = atoi( operandos.top() ) * L;
					 operandos.pop();

				} CB X3 | ;


%%

void  yyerror(char const *s) {
	fprintf (stderr, "%s\n", s);
}

int  main(void) {

  for(int i=60; i>0; i--){
    ss.str(string());
    ss << i;
    temporales.push("T"+ss.str());
  }

  return yyparse ();   //  yyparse  is  defined  for us by flex

}

