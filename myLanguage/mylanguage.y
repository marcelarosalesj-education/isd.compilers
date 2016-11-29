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

string cuadruplos[100][4];
int idxCuad = 0;

bool nodim=true;

struct Element{
	string name;
	string type;
	struct node *dim;
};

struct node{
	int d;
	int m;
	struct node *next;
};

struct Element table[100];
int idx=0;

int f=0;
int L=0;
int dimPos=0;

node *curr = new node;


int MEMORIA[100];
int idxMem = 0;

int baseMem = 0;

string int2string(int var){
  std::stringstream conv;
  conv << var;
  return conv.str();
}

string float2string(float var){
  std::stringstream conv;
  conv << var;
  return conv.str();
}

int string2int(string var){
  int result;
  istringstream convert(var);
  if(!(convert >> result)) result=-1;
  return result;
}

string trim(string str){
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}

string getIndex(string var){
  for(int i=0; i < idx; i++){
    if(table[i].name == var ){
        return int2string(i);
    }
  }
  return "-1";
}

stack<int> printStackInt(stack<int> q){
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

stack<string> printStackString(stack<string> q){
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

void displayLL(struct node *d){
	while( d != NULL ){
		cout << (d)<<":("<<(*d).d << ","<<(*d).m<<")->"<<(*d).next<<endl;
		d=(*d).next;
	}
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
%type <string> ROOT M FUNCTS FUNCT BLOCK X STMT I IE F W DW E PRIO1 ES PRIO2 TA PRIO3 FF X1 X3  DECL ASSIGNDIM FORASSIGN


%%

ROOT:       FUNCTS M {
              cout << "    OK ROOT" << endl<<endl;
			        int impr;
			        cout << "TABLA DE SIMBOLOS"<<endl;
              cout << "Num of variables: "<<idx<<endl;
              for(impr=0; impr<idx; impr++){
                cout << impr<<"|"<< table[impr].name << "|"<< table[impr].type <<"|"<< table[impr].dim << endl;
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

              /*cout << "LAS PILAS QUEDARON :"<<endl;
              cout << "operandos"<<endl;
              printStackString(operandos);
              cout <<endl;
              cout << "operadores"<<endl;
              printStackString(operadores);
              cout <<endl;
              cout << "temporales"<<endl;
              printStackString(temporales);
              cout <<endl;
              cout << "saltos"<<endl;
              printStackInt(saltos);
              cout <<endl;*/
            }
            ;

FUNCTS:     FUNCT FUNCTS 
	    	    | {;}
	    	    ;

FUNCT:      DEF ID BLOCK
            ;

M:          MAIN BLOCK
            ;

BLOCK:      OKEY LIST CKEY
            | STMT SEMICOLON
            ;

LIST:       STMT SEMICOLON LIST
            |
            ;

STMT:     	I
            | F
            | W
            | DW
            | DECL
            | ASSIGN    {;}
            |           {;}
            ;

ASSIGN:     ID {
                string aux = $1;
                if( std::string::npos != aux.find("=") ){           // It has an =
                  aux = trim(aux.substr(0, aux.find("=")));
                } else if ( std::string::npos != aux.find(";") ){   // It has an ;
                  aux = trim(aux.substr(0, aux.find(";")));
                } else if ( std::string::npos != aux.find("[") ){   // It has a [ 
                	aux = trim(aux.substr(0, aux.find("[")));
                }
                operandos.push(getIndex(aux));

                dimPos=0; // Whenever it finds a new ID, its dimension starts in 0

            } ASSIGNDIM {
            	cout <<endl<<"POSDIM:"<<dimPos<<endl;
            	if(dimPos >=1){
					string re = operandos.top(); operandos.pop();
              		re = "["+re+"]";
              		operandos.push(re);
              		cout << "-D-"<<endl;
              	} else if(dimPos == 0){
              		cout << "-ND-"<<endl;
              	}
                
            } EQUAL E {
                string re = operandos.top();      operandos.pop();
                string id = operandos.top();      operandos.pop();
                 
                cuadruplos[idxCuad][0] = "=";
                cuadruplos[idxCuad][1] = re;
                cuadruplos[idxCuad][2] = id;
                
                idxCuad++;  
            }
            | ID OPAR CPAR
            ;

DECL:       NUM ID {
              string aux = $2;
              table[idx].name = aux;
              table[idx].type = "num";
              table[idx].dim     = NULL;
              f=0;
              L=1;
              baseMem++;

              operandos.push( int2string(idx) );
              idx=idx+1;
            } X3 {

              if(f==1){
                curr = table[idx-1].dim;
                curr->m = baseMem-1;
                baseMem = (baseMem-1)+curr->d;
              } else if(f>1) {
                curr = table[idx-1].dim;
                int indice=1;
                (*curr).m = L/(*curr).d;
                while( curr->next != NULL){
                  int mi = (*curr).m; // mi-1, because we haven't moved. Just checked that there's something next 
                  curr = curr->next; // OK, move
                  (*curr).m = mi / (*curr).d; // in i position, do mi = mi-1 / di
                  indice++;
                }
                (*curr).m =  (baseMem-1); // Last current, so, this. Is the last node because its next is null
                baseMem = (baseMem -1) + L;
              }
            } X 
            |LETT ID {
              string aux = $2;
              table[idx].name = aux;
              table[idx].type = "lett";
              table[idx].dim     = NULL;
              f=0;
              L=1;
              baseMem++;

              operandos.push( int2string(idx) );
              idx=idx+1;
            } Y
            ;

X:          EQUAL INTEGER  {
              string aux = $1;
              string re = trim(aux.substr(aux.find("=")+1, aux.size() ) ); // get integer
              string id = operandos.top();      operandos.pop();
              
              cuadruplos[idxCuad][0] = "=";
              cuadruplos[idxCuad][1] = re+" num";
              cuadruplos[idxCuad][2] = id;
              idxCuad++;
            }	
			      |EQUAL FLOATINGPOINT {
              string aux = $1;
              string re = trim(aux.substr(aux.find("=")+1, aux.size() ) );
              string id = operandos.top();      operandos.pop();
              
              cuadruplos[idxCuad][0] = "=";
              cuadruplos[idxCuad][1] = re + " num";
              cuadruplos[idxCuad][2] = id;
              idxCuad++;
            } 
            |{
              // Sacamos lo que hay aqui porque no hay nada en X, para evitar que esta referencia se quede en el stack
              operandos.pop();
            }
            ;

Y:          EQUAL STRING {
              string aux = $1;
              string re = trim(aux.substr(aux.find("=")+1, aux.size() ) );
              string id = operandos.top();      operandos.pop();
              cuadruplos[idxCuad][0] = "=";
              cuadruplos[idxCuad][1] = re;
              cuadruplos[idxCuad][3] = id;
              idxCuad++;
            } 
            |
            ;

I:          IF OPAR E CPAR {
              string re = operandos.top();      operandos.pop();
              // Pendiente validar que el tipo sea bool. Tendria que usar un stack de tipos o algo asi
              
              cuadruplos[idxCuad][0] = "GOTOF";
              cuadruplos[idxCuad][1] = re;
              idxCuad++;
              saltos.push(idxCuad-1);
                            
            } BLOCK IE {
              int dir = saltos.top(); saltos.pop();
              // Rellena con idxCuad lo que se obtuvo en dir
              cuadruplos[dir][2] = int2string(idxCuad);
            }
            ;

IE:         ELSE {
              int dir = saltos.top(); saltos.pop();
              cuadruplos[idxCuad][0] = "GOTO";
              idxCuad++;
              saltos.push(idxCuad-1);
              // Rellena con idxCuad lo que se obtuvo en dir
              cuadruplos[dir][2] = int2string(idxCuad);

            } BLOCK                  {;}
            |                           {;}
            ;

FORASSIGN:  ID {
              operandos.push( getIndex($1) );
            } EQUAL INTEGER { 
              string aux = $3;
              string re = trim(aux.substr(aux.find("=")+1, aux.size() ) );
              string id = operandos.top(); operandos.pop();
              cuadruplos[idxCuad][0] = "=";
              cuadruplos[idxCuad][1] = re + " num";
              cuadruplos[idxCuad][2] = id;
              idxCuad++;
              saltos.push(idxCuad);
            }         

F:          FOR OPAR FORASSIGN SEMICOLON E CPAR {
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
              cuadruplos[idxCuad][1] = int2string(dir2);
              idxCuad++;

              // Rellenar GOTOF
              cuadruplos[dir1][2] = int2string(idxCuad);

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
              cuadruplos[idxCuad][1] = int2string(dir2);
              idxCuad++;

              // Rellena con idxCuad lo que se obtuvo en dir
              cuadruplos[dir1][2] = int2string(idxCuad);


            };

DW:         DO {
              saltos.push(idxCuad);

            } BLOCK WHILE OPAR E CPAR {
              string re = operandos.top(); operandos.pop();

              int dir = saltos.top(); saltos.pop();

              cuadruplos[idxCuad][0] = "GOTOV";
              cuadruplos[idxCuad][1] = re;
              cuadruplos[idxCuad][2] = int2string(dir);
              idxCuad++;
            }
            ;

E:          ES {;}
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

PRIO1:		  LT      {operadores.push("<");} 
            | GT    {operadores.push(">");} 
            | LET   {operadores.push("<=");} 
            | GET   {operadores.push(">=");} 
            | EQU   {operadores.push("==");} 
            | NEQ   {operadores.push("!=");} 
            ;

ES: 		    TA
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

PRIO2:		  PLUS  {operadores.push("+");} 
            | MINUS {operadores.push("-");} 
            | OR    {operadores.push("OR");}
            ;

TA: 		    FF 
            |TA PRIO3 FF {
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

PRIO3: 	  	MULT      {operadores.push("*");}
            | DIV     {operadores.push("/");}
            | AND     {operadores.push("AND");}
            ;


FF:			    INTEGER {
              int aux = $1;
              operandos.push( int2string(aux)+" num");
            }
            |FLOATINGPOINT {
      				float aux = $1;
              operandos.push( float2string(aux)+" num" );  
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
            } X3 
            ;

X1:	    		NOT 
            | {;} 
            ;
X3:         OB {
      				if(f==0){
      					node *n = new node();
      					n->d=0;
      					n->m=0;
      					n->next=NULL;
      					table[idx-1].dim = n;
      					curr = n;
      					f++;
      				} else {
      					node *n = new node();
      					n->d=0;
      					n->m=0;
      					n->next=NULL;
      					curr->next = n;
      					curr = curr->next;
      					f++;
      				}
				    } E {
    					string re = operandos.top(); operandos.pop();
    					L = L * string2int(re);
    					(*curr).d = string2int(re);
    				} CB X3 
            | {;}
            ;

ASSIGNDIM:    { // First positon
				        dimPos++;
        			 	if(dimPos == 1){
        					string id = operandos.top(); operandos.pop();
        					curr = table[ string2int(id) ].dim;
        					cout << "SIDIM"<<nodim<<endl;
        					//cout << "LET'S PRINT THE LL OF THIS VAR"<<endl;
        					//displayLL(curr);
        				}
        			} OB E {
        				// There's a next dimension
        				if( curr->next ) {
        					string re = operandos.top(); operandos.pop();
        					string res = temporales.top(); temporales.pop();

        					// GENERAR CUADRUPLO
        					cuadruplos[idxCuad][0] = "*";
                	cuadruplos[idxCuad][1] = re ;
                	cuadruplos[idxCuad][2] = int2string( (*curr).m ) ;
                	cuadruplos[idxCuad][3] = res;
        					idxCuad++; 

           				int auxx = (string2int(re)*(*curr).m) ;
            			operandos.push( int2string(auxx) );

        				}
        				// There has been two or more dimensions
        				if(dimPos >= 2){
        					string op1 = operandos.top(); operandos.pop();
        					string op2 = operandos.top(); operandos.pop();
        					string res = temporales.top(); temporales.pop();
        					
                  // GENERAR CUADRUPLO
        					cuadruplos[idxCuad][0] = "+";
                	cuadruplos[idxCuad][1] = op1 ;
                	cuadruplos[idxCuad][2] = op2 ;
                	cuadruplos[idxCuad][3] = res;
        					idxCuad++; 					

           				int auxr = string2int(op1) + string2int(op2);
            			operandos.push( int2string(auxr) );
        				}

        				// Last dimension
        				if(curr->next == NULL){
        					string re = operandos.top(); operandos.pop();
        					string res = temporales.top(); temporales.pop();
        					
                  // GENERAR CUADRUPLO
        					cuadruplos[idxCuad][0] = "+";
                  cuadruplos[idxCuad][1] = re ;
                	cuadruplos[idxCuad][2] = int2string( (*curr).m ); // The base
                	cuadruplos[idxCuad][3] = res;
        					idxCuad++; 

           				int auxx = ( string2int(re) + (*curr).m ) ;
            			operandos.push( int2string(auxx) );
        				}
        				curr = curr->next;

        			} CB ASSIGNDIM 
              | {cout << "NO DIM";}
              ;


%%

void  yyerror(char const *s) {
	fprintf (stderr, "%s\n", s);
}

int  main(void) {
  for(int i=60; i>0; i--){
    temporales.push("T"+int2string(i));
  }
  return yyparse ();   //  yyparse  is  defined  for us by flex
}

