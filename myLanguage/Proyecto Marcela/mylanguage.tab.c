/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 3 "mylanguage.y" /* yacc.c:339  */

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
stack<int> returns;

string cuadruplos[200][4];
int idxCuad = 0;

bool nodim=true;


int MEMSIM[100];
int MEMTEM[60];
int MEMDIM[100];

struct Element {
	string name;
	string type;
	struct node *dim;
	int moduloInicio = -1;
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

void Ejecutor(){

	string auxtemp;
	int idxDim;
	for(int i=0; i<idxCuad; i++){
		string temp0 = cuadruplos[i][0];
		string temp1 = cuadruplos[i][1];
		string temp2 = cuadruplos[i][2];
		string temp3 = cuadruplos[i][3];
		
		if( temp0 == "="){
			if(temp1[0] == 'T'){
				int idxTemp = string2int( temp1.substr(1) ); // Val de temp1

				//cout << " ESTO: "<< temp1 << "  ES: "<<idxTemp<<endl;

				if(temp2[0]=='['){ // ASIGNAR A MEMDIM
					auxtemp = temp2.substr(2);
					idxDim = string2int(auxtemp.erase(auxtemp.size()-1));

					//cout << " ESTO: "<< temp2 << "  ES: "<<idxDim<<endl;

					MEMDIM[ MEMTEM[idxDim] ] = MEMTEM[idxTemp];

				} else { // ASIGNAR A MEMSIM
					MEMSIM[ string2int(temp2) ] = MEMTEM[idxTemp];
				}

			} else if( temp1[0] == '[' ){
				//cout << "a";
				auxtemp = temp1.substr(2);
				//cout << "b";
				idxDim = string2int(auxtemp.erase(auxtemp.size()-1));
				//cout << "c"<<temp2<<endl;
				MEMSIM[ string2int(temp2) ] = MEMDIM[ MEMTEM[ idxDim ] ];
				//cout << "d";
				



			} else {
				int valor = string2int(trim(temp1.substr(0, temp1.find(" "))));
				string num = trim(temp1.substr( temp1.find(" ")+1) );

				if(num == "num"){ 	// De constante a variable
					
					if(temp2[0]=='['){ // ASIGNAR A MEMDIM
						auxtemp = temp2.substr(2);
						idxDim = string2int(auxtemp.erase(auxtemp.size()-1));

						//cout << " ESTO: "<< temp2 << "  ES: "<<idxDim<<endl;

						MEMDIM[ MEMTEM[idxDim] ] = valor;
					} else { // ASIGNAR A MEMSIM
						MEMSIM[ string2int( temp2 ) ] = valor;
						//cout << " valor :" <<valor << " ... "<< MEMSIM[ string2int( temp2 ) ] << endl;
					}
					
				} else {			// De variable a variable
					if(temp2[0]=='['){ // ASIGNAR A MEMDIM
						auxtemp = temp2.substr(2);
						idxDim = string2int(auxtemp.erase(auxtemp.size()-1));

						//cout << " ESTO: "<< temp2 << "  ES: "<<idxDim<<endl;

						MEMDIM[ MEMTEM[idxDim] ] = MEMSIM[ string2int( temp1 ) ];
					} else { // ASIGNAR A MEMSIM
						MEMSIM[ string2int( temp2 ) ] =  MEMSIM[ string2int( temp1 ) ];
					}
					
				}
			}

		} else if(temp0 == "+" || temp0 == "-" || temp0 == "*" || temp0 == "/" ||
				  temp0 == ">" || temp0 == "<" || temp0 == "<=" || temp0 == ">=" ||  
				  temp0 == "==" || temp0 == "!=" || temp0 == "AND" || temp0 == "OR" ) {
			
			int idxTemp3 = string2int( temp3.substr(1) );
			//cout << " ESTO: "<< temp3 << "  ES: "<<idxTemp3<<endl;

			if(temp1[0] == 'T'){ 		// El primero es temporal ...
				int idxTemp1 = string2int( temp1.substr(1) );

				//cout << " ESTO: "<< temp1 << "  ES: "<<idxTemp1<<endl;

				if(temp2[0] == 'T'){ 	// El segundo es temporal
					int idxTemp2 = string2int( temp2.substr(1) );

					//cout << " ESTO: "<< temp2 << "  ES: "<<idxTemp2<<endl;

					// Temporal ? temporal
					if( temp0 == "+" ) {
						MEMTEM[idxTemp3] = MEMTEM[idxTemp1] + MEMTEM[ idxTemp2];
					} else if( temp0 == "-" ) {
						MEMTEM[idxTemp3] = MEMTEM[idxTemp1] - MEMTEM[ idxTemp2];
					} else if( temp0 == "*" ) {
						MEMTEM[idxTemp3] = MEMTEM[idxTemp1] * MEMTEM[ idxTemp2];
					} else if( temp0 == "/" ) {
						MEMTEM[idxTemp3] = MEMTEM[idxTemp1] / MEMTEM[ idxTemp2];
					} else if( temp0 == ">" ) {
						MEMTEM[idxTemp3] = MEMTEM[idxTemp1] > MEMTEM[ idxTemp2];
					} else if( temp0 == "<" ) {
						MEMTEM[idxTemp3] = MEMTEM[idxTemp1] < MEMTEM[ idxTemp2];
					} else if( temp0 == ">=" ) {
						MEMTEM[idxTemp3] = MEMTEM[idxTemp1] >= MEMTEM[ idxTemp2];
					} else if( temp0 == "<=" ) {
						MEMTEM[idxTemp3] = MEMTEM[idxTemp1] <= MEMTEM[ idxTemp2];
					} else if( temp0 == "==" ) {
						MEMTEM[idxTemp3] = MEMTEM[idxTemp1] == MEMTEM[ idxTemp2];
					} else if( temp0 == "!=" ) {
						MEMTEM[idxTemp3] = MEMTEM[idxTemp1] != MEMTEM[ idxTemp2];
					} else if( temp0 == "AND" ) {
						MEMTEM[idxTemp3] = MEMTEM[idxTemp1] && MEMTEM[ idxTemp2];
					} else if( temp0 == "OR" ) {
						MEMTEM[idxTemp3] = MEMTEM[idxTemp1] || MEMTEM[ idxTemp2];
					} 
					

				} else { 				// El segundo es variable o numero ...

					int valor2 = string2int(trim(temp2.substr(0, temp2.find(" "))));
					string num2 = trim(temp2.substr( temp2.find(" ")+1) );

					if(num2 == "num"){ 	// De temporal ? constante
						if( temp0 == "+" ){
							MEMTEM[ idxTemp3 ] = MEMTEM[ idxTemp1 ] + valor2;
						} else if( temp0 == "-" ) {
							MEMTEM[ idxTemp3 ] = MEMTEM[ idxTemp1 ] - valor2;
						} else if( temp0 == "*" ) {
							MEMTEM[ idxTemp3 ] = MEMTEM[ idxTemp1 ] * valor2;
						} else if( temp0 == "/" ) {
							MEMTEM[ idxTemp3 ] = MEMTEM[ idxTemp1 ] / valor2;
						} else if( temp0 == ">" ) {
							MEMTEM[ idxTemp3 ] = MEMTEM[ idxTemp1 ] > valor2;
						} else if( temp0 == "<" ) {
							MEMTEM[ idxTemp3 ] = MEMTEM[ idxTemp1 ] < valor2;
						} else if( temp0 == ">=" ) {
							MEMTEM[ idxTemp3 ] = MEMTEM[ idxTemp1 ] >= valor2;
						} else if( temp0 == "<=" ) {
							MEMTEM[ idxTemp3 ] = MEMTEM[ idxTemp1 ] <= valor2;
						} else if( temp0 == "==" ) {
							MEMTEM[ idxTemp3 ] = MEMTEM[ idxTemp1 ] == valor2;
						} else if( temp0 == "!=" ) {
							MEMTEM[ idxTemp3 ] = MEMTEM[ idxTemp1 ] != valor2;
						} else if( temp0 == "AND" ) {
							MEMTEM[ idxTemp3 ] = MEMTEM[ idxTemp1 ] && valor2;
						} else if( temp0 == "OR" ) {
							MEMTEM[ idxTemp3 ] = MEMTEM[ idxTemp1 ] || valor2;
						} 

					} else {			// De temporal ? variable
						if( temp0 == "+" ){
							MEMTEM[ idxTemp3 ] =  MEMTEM[ idxTemp1 ] + MEMSIM[ string2int(cuadruplos[i][2]) ];
						} else if( temp0 == "-" ) {
							MEMTEM[ idxTemp3 ] =  MEMTEM[ idxTemp1 ] - MEMSIM[ string2int(cuadruplos[i][2]) ];
						} else if( temp0 == "*" ) {
							MEMTEM[ idxTemp3 ] =  MEMTEM[ idxTemp1 ] * MEMSIM[ string2int(cuadruplos[i][2]) ];
						} else if( temp0 == "/" ) {
							MEMTEM[ idxTemp3 ] =  MEMTEM[ idxTemp1 ] / MEMSIM[ string2int(cuadruplos[i][2]) ];
						} else if( temp0 == ">" ) {
							MEMTEM[ idxTemp3 ] =  MEMTEM[ idxTemp1 ] > MEMSIM[ string2int(cuadruplos[i][2]) ];
						} else if( temp0 == "<" ) {
							MEMTEM[ idxTemp3 ] =  MEMTEM[ idxTemp1 ] < MEMSIM[ string2int(cuadruplos[i][2]) ];
						} else if( temp0 == ">=" ) {
							MEMTEM[ idxTemp3 ] =  MEMTEM[ idxTemp1 ] >= MEMSIM[ string2int(cuadruplos[i][2]) ];
						} else if( temp0 == "<=" ) {
							MEMTEM[ idxTemp3 ] =  MEMTEM[ idxTemp1 ] <= MEMSIM[ string2int(cuadruplos[i][2]) ];
						} else if( temp0 == "==" ) {
							MEMTEM[ idxTemp3 ] =  MEMTEM[ idxTemp1 ] == MEMSIM[ string2int(cuadruplos[i][2]) ];
						} else if( temp0 == "!=" ) {
							MEMTEM[ idxTemp3 ] =  MEMTEM[ idxTemp1 ] != MEMSIM[ string2int(cuadruplos[i][2]) ];
						} else if( temp0 == "AND" ) {
							MEMTEM[ idxTemp3 ] =  MEMTEM[ idxTemp1 ] && MEMSIM[ string2int(cuadruplos[i][2]) ];
						} else if( temp0 == "OR" ) {
							MEMTEM[ idxTemp3 ] =  MEMTEM[ idxTemp1 ] || MEMSIM[ string2int(cuadruplos[i][2]) ];
						} 
 

					}
				}

			} else { 		// El primero es variable o numero
				int valor1 = string2int(trim(temp1.substr(0, temp1.find(" "))));
				string num1 = trim(temp1.substr( temp1.find(" ")+1) );

				if(num1 == "num"){ 	// Constante ? ...

					if(temp2[0] == 'T'){ // Constante ? Temporal
						int idxTemp2 = string2int( temp2.substr(1) );
						//cout << " ESTO: "<< temp2 << "  ES: "<<idxTemp2<<endl;

						if( temp0 == "+" ){
							MEMTEM[ idxTemp3 ] = valor1 + MEMTEM[ idxTemp2 ];
						} else if( temp0 == "-" ) {
							MEMTEM[ idxTemp3 ] = valor1 - MEMTEM[ idxTemp2 ];
						} else if( temp0 == "*" ) {
							MEMTEM[ idxTemp3 ] = valor1 * MEMTEM[ idxTemp2 ];
						} else if( temp0 == "/" ) {
							MEMTEM[ idxTemp3 ] = valor1 / MEMTEM[ idxTemp2 ];
						} else if( temp0 == ">" ) {
							MEMTEM[ idxTemp3 ] = valor1 > MEMTEM[ idxTemp2 ];
						} else if( temp0 == "<" ) {
							MEMTEM[ idxTemp3 ] = valor1 < MEMTEM[ idxTemp2 ];
						} else if( temp0 == ">=" ) {
							MEMTEM[ idxTemp3 ] = valor1 >= MEMTEM[ idxTemp2 ];
						} else if( temp0 == "<=" ) {
							MEMTEM[ idxTemp3 ] = valor1 <= MEMTEM[ idxTemp2 ];
						} else if( temp0 == "==" ) {
							MEMTEM[ idxTemp3 ] = valor1 == MEMTEM[ idxTemp2 ];
						} else if( temp0 == "!=" ) {
							MEMTEM[ idxTemp3 ] = valor1 != MEMTEM[ idxTemp2 ];
						} else if( temp0 == "AND" ) {
							MEMTEM[ idxTemp3 ] = valor1 && MEMTEM[ idxTemp2 ];
						} else if( temp0 == "OR" ) {
							MEMTEM[ idxTemp3 ] = valor1 || MEMTEM[ idxTemp2 ];
						} 

					} else {		// Constante + variable o numero 

						int valor2 = string2int(trim(temp2.substr(0, temp2.find(" "))));
						string num2 = trim(temp2.substr( temp2.find(" ")+1) );

						if(num2 == "num"){ 	// Constante ? Constante

							if( temp0 == "+" ){
								MEMTEM[ idxTemp3 ] = valor1 + valor2;
							} else if( temp0 == "-" ) {
								MEMTEM[ idxTemp3 ] = valor1 - valor2;
							} else if( temp0 == "*" ) {
								MEMTEM[ idxTemp3 ] = valor1 * valor2;
							} else if( temp0 == "/" ) {
								MEMTEM[ idxTemp3 ] = valor1 / valor2;
							} else if( temp0 == ">" ) {
								MEMTEM[ idxTemp3 ] = valor1 > valor2;
							} else if( temp0 == "<" ) {
								MEMTEM[ idxTemp3 ] = valor1 < valor2;
							} else if( temp0 == ">=" ) {
								MEMTEM[ idxTemp3 ] = valor1 >= valor2;
							} else if( temp0 == "<=" ) {
								MEMTEM[ idxTemp3 ] = valor1 <= valor2;
							} else if( temp0 == "==" ) {
								MEMTEM[ idxTemp3 ] = valor1 == valor2;
							} else if( temp0 == "!=" ) {
								MEMTEM[ idxTemp3 ] = valor1 != valor2;
							} else if( temp0 == "AND" ) {
								MEMTEM[ idxTemp3 ] = valor1 && valor2;
							} else if( temp0 == "OR" ) {
								MEMTEM[ idxTemp3 ] = valor1 || valor2;
							} 

						} else {			// Constante ? Variable

							if( temp0 == "+" ){
								MEMTEM[ idxTemp3 ] =  valor1 + MEMSIM[ string2int(cuadruplos[i][2]) ];
							} else if( temp0 == "-" ) {
								MEMTEM[ idxTemp3 ] =  valor1 - MEMSIM[ string2int(cuadruplos[i][2]) ];
							} else if( temp0 == "*" ) {
								MEMTEM[ idxTemp3 ] =  valor1 * MEMSIM[ string2int(cuadruplos[i][2]) ];
							} else if( temp0 == "/" ) {
								MEMTEM[ idxTemp3 ] =  valor1 / MEMSIM[ string2int(cuadruplos[i][2]) ];
							} else if( temp0 == ">" ) {
								MEMTEM[ idxTemp3 ] =  valor1 > MEMSIM[ string2int(cuadruplos[i][2]) ];
							} else if( temp0 == "<" ) {
								MEMTEM[ idxTemp3 ] =  valor1 < MEMSIM[ string2int(cuadruplos[i][2]) ];
							} else if( temp0 == ">=" ) {
								MEMTEM[ idxTemp3 ] =  valor1 >= MEMSIM[ string2int(cuadruplos[i][2]) ];
							} else if( temp0 == "<=" ) {
								MEMTEM[ idxTemp3 ] =  valor1 <= MEMSIM[ string2int(cuadruplos[i][2]) ];
							} else if( temp0 == "==" ) {
								MEMTEM[ idxTemp3 ] =  valor1 == MEMSIM[ string2int(cuadruplos[i][2]) ];
							} else if( temp0 == "!=" ) {
								MEMTEM[ idxTemp3 ] =  valor1 != MEMSIM[ string2int(cuadruplos[i][2]) ];
							} else if( temp0 == "AND" ) {
								MEMTEM[ idxTemp3 ] =  valor1 && MEMSIM[ string2int(cuadruplos[i][2]) ];
							} else if( temp0 == "OR" ) {
								MEMTEM[ idxTemp3 ] =  valor1 || MEMSIM[ string2int(cuadruplos[i][2]) ];
							} 

						}
					}
				} else {			// Variable + ...

					if(temp2[0] == 'T'){ // Variable ? Temporal

						int idxTemp2 = string2int( temp2.substr(1) );

						//cout << " ESTO: "<< temp2 << "  ES: "<<idxTemp2<<endl;

						if( temp0 == "+" ){
							MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] + MEMTEM[ idxTemp2 ];
						} else if( temp0 == "-" ) {
							MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] - MEMTEM[ idxTemp2 ];
						} else if( temp0 == "*" ) {
							MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] * MEMTEM[ idxTemp2 ];
						} else if( temp0 == "/" ) {
							MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] / MEMTEM[ idxTemp2 ];
						} else if( temp0 == ">" ) {
							MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] > MEMTEM[ idxTemp2 ];
						} else if( temp0 == "<" ) {
							MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] < MEMTEM[ idxTemp2 ];
						} else if( temp0 == ">=" ) {
							MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] >= MEMTEM[ idxTemp2 ];
						} else if( temp0 == "<=" ) {
							MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] <= MEMTEM[ idxTemp2 ];
						} else if( temp0 == "==" ) {
							MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] == MEMTEM[ idxTemp2 ];
						} else if( temp0 == "!=" ) {
							MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] != MEMTEM[ idxTemp2 ];
						} else if( temp0 == "AND" ) {
							MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] && MEMTEM[ idxTemp2 ];
						} else if( temp0 == "OR" ) {
							MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] || MEMTEM[ idxTemp2 ];
						} 



					} else {		// Variable + variable o numero 
						
						int valor2 = string2int(trim(temp2.substr(0, temp2.find(" "))));
						string num2 = trim(temp2.substr( temp2.find(" ")+1) );

						if(num2 == "num"){ 	// Variable ? Constante

							if( temp0 == "+" ){
								MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] + valor2;
							} else if( temp0 == "-" ) {
								MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] - valor2;
							} else if( temp0 == "*" ) {
								MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] * valor2;
							} else if( temp0 == "/" ) {
								MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] / valor2;
							} else if( temp0 == ">" ) {
								MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] > valor2;
							} else if( temp0 == "<" ) {
								MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] < valor2;
							} else if( temp0 == ">=" ) {
								MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] >= valor2;
							} else if( temp0 == "<=" ) {
								MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] <= valor2;
							} else if( temp0 == "==" ) {
								MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] == valor2;
							} else if( temp0 == "!=" ) {
								MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] != valor2;
							} else if( temp0 == "AND" ) {
								MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] && valor2;
							} else if( temp0 == "OR" ) {
								MEMTEM[ idxTemp3 ] = MEMSIM[ string2int(cuadruplos[i][1]) ] || valor2;
							} 
							
						} else {			// Variable ? Variable

							if( temp0 == "+" ){
								MEMTEM[ idxTemp3 ] =  MEMSIM[ string2int(cuadruplos[i][1]) ] + MEMSIM[ string2int(cuadruplos[i][2]) ];
							} else if( temp0 == "-" ) {
								MEMTEM[ idxTemp3 ] =  MEMSIM[ string2int(cuadruplos[i][1]) ] - MEMSIM[ string2int(cuadruplos[i][2]) ];
							} else if( temp0 == "*" ) {
								MEMTEM[ idxTemp3 ] =  MEMSIM[ string2int(cuadruplos[i][1]) ] * MEMSIM[ string2int(cuadruplos[i][2]) ];
							} else if( temp0 == "/" ) {
								MEMTEM[ idxTemp3 ] =  MEMSIM[ string2int(cuadruplos[i][1]) ] / MEMSIM[ string2int(cuadruplos[i][2]) ];
							} else if( temp0 == ">" ) {
								MEMTEM[ idxTemp3 ] =  MEMSIM[ string2int(cuadruplos[i][1]) ] > MEMSIM[ string2int(cuadruplos[i][2]) ];
							} else if( temp0 == "<" ) {
								MEMTEM[ idxTemp3 ] =  MEMSIM[ string2int(cuadruplos[i][1]) ] < MEMSIM[ string2int(cuadruplos[i][2]) ];
							} else if( temp0 == ">=" ) {
								MEMTEM[ idxTemp3 ] =  MEMSIM[ string2int(cuadruplos[i][1]) ] >= MEMSIM[ string2int(cuadruplos[i][2]) ];
							} else if( temp0 == "<=" ) {
								MEMTEM[ idxTemp3 ] =  MEMSIM[ string2int(cuadruplos[i][1]) ] <= MEMSIM[ string2int(cuadruplos[i][2]) ];
							} else if( temp0 == "==" ) {
								MEMTEM[ idxTemp3 ] =  MEMSIM[ string2int(cuadruplos[i][1]) ] == MEMSIM[ string2int(cuadruplos[i][2]) ];
							} else if( temp0 == "!=" ) {
								MEMTEM[ idxTemp3 ] =  MEMSIM[ string2int(cuadruplos[i][1]) ] != MEMSIM[ string2int(cuadruplos[i][2]) ];
							} else if( temp0 == "AND" ) {
								MEMTEM[ idxTemp3 ] =  MEMSIM[ string2int(cuadruplos[i][1]) ] && MEMSIM[ string2int(cuadruplos[i][2]) ];
							} else if( temp0 == "OR" ) {
								MEMTEM[ idxTemp3 ] =  MEMSIM[ string2int(cuadruplos[i][1]) ] || MEMSIM[ string2int(cuadruplos[i][2]) ];
							} 
 
						}
					}
				}
			}
		
		//FIN operaciones
		} else if (temp0 == "GOTO"){
			i = string2int(temp2)-1;

		} else if (temp0 == "GOTOF") {
			int idxTemp = string2int( temp1.substr(1) );
			if( MEMTEM[idxTemp] == 0){ // Si es 0 es falso y entra
				i = string2int(temp2)-1;
			}
			
		} else if (temp0 == "GOTOV") {
			int idxTemp = string2int( temp1.substr(1) );
			if( MEMTEM[idxTemp] == 1 ){ // Es verdadero, y entra
				i = string2int(temp2)-1;
			}
		} else if (temp0 == "CALL") {
			returns.push(i);
			i = string2int(temp2)-1;

		} else if (temp0 == "RETURN"){
			i = returns.top(); returns.pop();

		} else if (temp0 == "INPUT"){
			//char line[100];
			//string inputVal;
			cout << ">";
			/*while(cin.good()){
				cin.getline(line, sizeof(line)) ;
				inputVal = string(line);
				cout << "HOLA"<<inputVal;			
			}*/
			int inputVal;
			cin >> inputVal;
			//cout << "LEIDO" << inputVal << "|"<<endl;
			//MEMSIM[string2int(temp2)] = string2int(inputVal);
			MEMSIM[string2int(temp2)] = (inputVal);

		}


	}// FIN FOR CUADRUPLOS

	cout << "MEMORIA SIMPLE:"<<endl;
	for(int m=0; m<idx; m++){
		cout << m<<" "<<MEMSIM[m]<<endl;

	}
	cout << endl;
	cout << "MEMORIA DIMENSIONADA:"<<endl;
	  for(int md=0; md<idx; md++){

	    struct node *iter = table[md].dim;
	    if(iter != NULL){
	    	cout << "NAME : " << table[md].name << endl;
	    	int startloop = 0;
	    	int endloop = 1;
	    	// This loop finds the starting and ending mem address
		    while(iter != NULL){		    	
		    	endloop = endloop * iter->d;
		    	if(iter->next == NULL){
		    		startloop = iter->m;
		    	}
		    	iter = iter->next;
		   	}
		   	endloop = endloop+startloop;
		   	// Prints memory
		   	for(int pdim = startloop; pdim < endloop; pdim++){
		   		cout << MEMDIM[pdim]<< endl;
		   	}
		    cout << "------"<<endl;
	    }
	  }
}



#line 668 "mylanguage.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "mylanguage.tab.h".  */
#ifndef YY_YY_MYLANGUAGE_TAB_H_INCLUDED
# define YY_YY_MYLANGUAGE_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    MAIN = 258,
    DEF = 259,
    NUM = 260,
    LETT = 261,
    IF = 262,
    ELSE = 263,
    FOR = 264,
    DO = 265,
    WHILE = 266,
    OPAR = 267,
    CPAR = 268,
    OKEY = 269,
    CKEY = 270,
    SEMICOLON = 271,
    EQUAL = 272,
    QUOTE = 273,
    STRING = 274,
    ID = 275,
    LT = 276,
    GT = 277,
    LET = 278,
    GET = 279,
    EQU = 280,
    NEQ = 281,
    PLUS = 282,
    MINUS = 283,
    MULT = 284,
    DIV = 285,
    AND = 286,
    OR = 287,
    NOT = 288,
    OB = 289,
    CB = 290,
    COMMA = 291,
    CALL = 292,
    INPUT = 293,
    INTEGER = 294,
    FLOATINGPOINT = 295
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 605 "mylanguage.y" /* yacc.c:355  */

  char *string;           /* Ptr to constant string (strings are malloc'd) */
  int integer;            /* Constant integer value */
  float fp;               /* Constant floating point value */

#line 755 "mylanguage.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MYLANGUAGE_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 772 "mylanguage.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   109

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  146

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   295

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   620,   620,   620,   681,   682,   684,   696,   684,   716,
     716,   730,   740,   750,   756,   765,   768,   769,   772,   772,
     782,   782,   789,   790,   793,   794,   797,   798,   799,   800,
     801,   802,   803,   807,   814,   821,   834,   821,   857,   861,
     861,   877,   877,   886,   889,   889,   902,   902,   935,   941,
     944,   941,   966,   966,   981,   982,   998,   999,  1000,  1001,
    1002,  1003,  1006,  1007,  1024,  1025,  1026,  1029,  1030,  1045,
    1046,  1047,  1051,  1055,  1059,  1060,  1060,  1102,  1103,  1105,
    1123,  1105,  1128,  1131,  1141,  1131,  1196
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MAIN", "DEF", "NUM", "LETT", "IF",
  "ELSE", "FOR", "DO", "WHILE", "OPAR", "CPAR", "OKEY", "CKEY",
  "SEMICOLON", "EQUAL", "QUOTE", "STRING", "ID", "LT", "GT", "LET", "GET",
  "EQU", "NEQ", "PLUS", "MINUS", "MULT", "DIV", "AND", "OR", "NOT", "OB",
  "CB", "COMMA", "CALL", "INPUT", "INTEGER", "FLOATINGPOINT", "$accept",
  "ROOT", "$@1", "DECLS", "DECL", "$@2", "$@3", "$@4", "X", "Y", "FUNCTS",
  "FUNCT", "$@5", "M", "$@6", "BLOCK", "LIST", "STMT", "GETINPUT", "C",
  "ASSIGN", "$@7", "$@8", "I", "$@9", "IE", "$@10", "FORASSIGN", "$@11",
  "F", "$@12", "ID2", "W", "$@13", "$@14", "DW", "$@15", "E", "PRIO1",
  "ES", "PRIO2", "TA", "PRIO3", "FF", "$@16", "X1", "X3", "$@17", "$@18",
  "ASSIGNDIM", "$@19", "$@20", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295
};
# endif

#define YYPACT_NINF -92

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-92)))

#define YYTABLE_NINF -87

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      24,     5,    11,     9,   -92,    17,   -92,   -92,   -92,    32,
      24,    13,    26,    25,    46,    32,   -92,   -92,   -92,    31,
     -92,   -92,   -92,   -92,   -92,   -18,    35,   -92,    -3,    -3,
     -92,   -92,   -92,   -92,    39,   -11,   -92,     4,    -1,   -92,
      41,    42,   -92,   -92,     3,    43,    36,    37,   -92,    52,
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,    23,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -18,   -18,
     -92,   -92,   -92,   -18,   -18,   -92,   -92,   -92,   -18,    49,
      -3,    60,    58,    59,    61,    62,   -92,   -92,   -92,    13,
       0,   -11,   -92,    63,    44,    64,   -92,    65,    69,   -18,
     -92,     3,   -92,   -92,    48,   -92,   -92,   -92,   -92,    66,
     -18,    72,    73,   -92,    68,   -18,    -3,    50,    75,   -18,
     -92,   -18,   -92,    82,   -92,   -92,    78,    -3,   -92,    57,
     -92,   -92,    -3,   -92,   -92,    44,    -3,    81,   -92,   -92,
      74,   -92,    79,   -18,    84,   -92
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     0,     0,     0,     2,     0,     6,     9,     1,    17,
       5,    82,    15,     0,     0,    17,     4,    79,     7,     0,
      10,    18,    20,     3,    16,    78,    13,    14,     0,     0,
      77,    72,    73,    80,    54,    62,    67,     0,     0,     8,
       0,     0,    52,    49,    25,    35,     0,     0,    19,     0,
      32,    31,    30,    26,    27,    28,    29,    21,     0,    56,
      57,    58,    59,    60,    61,    64,    65,    66,    78,    78,
      69,    70,    71,    78,    78,    75,    11,    12,    78,     0,
       0,     0,     0,     0,     0,    83,    34,    33,    23,    82,
      55,    63,    68,     0,    86,     0,    44,     0,     0,    78,
      22,    25,    38,    36,     0,    81,    74,    76,    39,     0,
      78,     0,     0,    24,     0,    78,     0,     0,     0,    78,
      50,    78,    84,    43,    45,    46,     0,     0,    37,     0,
      41,    40,     0,    53,    51,    86,     0,     0,    85,    42,
       0,    48,     0,    78,     0,    47
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -92,   -92,   -92,    85,   -92,   -92,   -92,   -92,   -92,   -92,
      86,   -92,   -92,   -92,   -92,   -29,    -2,   -42,   -92,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,   -92,
     -92,   -92,   -92,   -92,   -92,   -92,   -92,   -73,   -92,    34,
     -92,    40,   -92,    27,   -92,   -92,    15,   -92,   -92,   -91,
     -92,   -92
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     9,     4,     5,    11,    26,    12,    39,    20,
      14,    15,    28,    23,    29,    48,    82,    49,    50,    51,
      52,    85,   114,    53,   116,   131,   136,    97,   109,    54,
     132,   142,    55,    81,   127,    56,    80,    33,    68,    34,
      69,    35,    73,    36,    94,    37,    18,    25,    58,   103,
     104,   129
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      57,    93,    83,   107,    40,    95,    41,    42,    43,     8,
      40,    44,    41,    42,    43,    30,    74,    45,    70,    71,
      72,    31,    32,    45,    75,     6,   112,    65,    66,     1,
       2,     7,    67,    10,    46,    47,    13,   118,    76,    77,
      46,    47,   122,    19,   138,    21,   126,    17,   128,    22,
      27,    98,    38,    78,    79,    84,    86,    87,    89,    83,
      59,    60,    61,    62,    63,    64,    65,    66,    88,    96,
     144,    67,    99,   100,   102,   101,   106,   108,   -83,   -86,
     111,   110,   115,   117,   119,   121,   120,   123,   125,   124,
     130,   133,   135,   140,   141,    16,   143,   145,   134,   113,
      92,    24,    90,   137,   105,     0,     0,   139,     0,    91
};

static const yytype_int16 yycheck[] =
{
      29,    74,    44,    94,     7,    78,     9,    10,    11,     0,
       7,    14,     9,    10,    11,    33,    12,    20,    29,    30,
      31,    39,    40,    20,    20,    20,    99,    27,    28,     5,
       6,    20,    32,    16,    37,    38,     4,   110,    39,    40,
      37,    38,   115,    17,   135,    20,   119,    34,   121,     3,
      19,    80,    17,    12,    12,    12,    20,    20,    35,   101,
      21,    22,    23,    24,    25,    26,    27,    28,    16,    20,
     143,    32,    12,    15,    13,    16,    13,    13,    34,    17,
      11,    16,    34,    17,    12,    17,    13,   116,    13,    39,
       8,    13,    35,    12,    20,    10,    17,    13,   127,   101,
      73,    15,    68,   132,    89,    -1,    -1,   136,    -1,    69
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    42,    44,    45,    20,    20,     0,    43,
      16,    46,    48,     4,    51,    52,    44,    34,    87,    17,
      50,    20,     3,    54,    51,    88,    47,    19,    53,    55,
      33,    39,    40,    78,    80,    82,    84,    86,    17,    49,
       7,     9,    10,    11,    14,    20,    37,    38,    56,    58,
      59,    60,    61,    64,    70,    73,    76,    56,    89,    21,
      22,    23,    24,    25,    26,    27,    28,    32,    79,    81,
      29,    30,    31,    83,    12,    20,    39,    40,    12,    12,
      77,    74,    57,    58,    12,    62,    20,    20,    16,    35,
      80,    82,    84,    78,    85,    78,    20,    68,    56,    12,
      15,    16,    13,    90,    91,    87,    13,    90,    13,    69,
      16,    11,    78,    57,    63,    34,    65,    17,    78,    12,
      13,    17,    78,    56,    39,    13,    78,    75,    78,    92,
       8,    66,    71,    13,    56,    35,    67,    56,    90,    56,
      12,    20,    72,    17,    78,    13
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    43,    42,    44,    44,    46,    47,    45,    48,
      45,    49,    49,    49,    50,    50,    51,    51,    53,    52,
      55,    54,    56,    56,    57,    57,    58,    58,    58,    58,
      58,    58,    58,    59,    60,    62,    63,    61,    61,    65,
      64,    67,    66,    66,    69,    68,    71,    70,    72,    74,
      75,    73,    77,    76,    78,    78,    79,    79,    79,    79,
      79,    79,    80,    80,    81,    81,    81,    82,    82,    83,
      83,    83,    84,    84,    84,    85,    84,    86,    86,    88,
      89,    87,    87,    91,    92,    90,    90
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     4,     3,     0,     0,     0,     6,     0,
       4,     2,     2,     0,     2,     0,     2,     0,     0,     4,
       0,     3,     3,     2,     3,     0,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     0,     0,     6,     3,     0,
       7,     0,     3,     0,     0,     4,     0,    13,     1,     0,
       0,     7,     0,     7,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     3,     1,
       1,     1,     1,     1,     4,     0,     4,     1,     0,     0,
       0,     6,     0,     0,     0,     6,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 620 "mylanguage.y" /* yacc.c:1646  */
    {

				cuadruplos[idxCuad][0] = "GOTO";
                idxCuad++;  



			}
#line 1957 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 627 "mylanguage.y" /* yacc.c:1646  */
    {
              cout << "    OK ROOT" << endl<<endl;
			        int impr;
			        cout << "TABLA DE SIMBOLOS"<<endl;
              cout << "Num of variables: "<<idx<<endl;
              for(impr=0; impr<idx; impr++){
                cout << impr<<"|"<< table[impr].name << "|"<< table[impr].type <<"|"<< table[impr].dim;

                struct node *iter = table[impr].dim;
                while(iter != NULL){
                	cout << "|" << iter->d << "|" <<iter->m;
                	iter = iter->next;
                }
                if(table[impr].moduloInicio != -1){
                	cout << "|"<< table[impr].moduloInicio;
                }


                if(table[impr].moduloInicio != -1){
                	cout << ">" << table[impr].moduloInicio<<"<";
                }

                cout << endl;
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

              cout << "EJECUTOR"<<endl;
              Ejecutor();

            }
#line 2014 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 682 "mylanguage.y" /* yacc.c:1646  */
    {;}
#line 2020 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 684 "mylanguage.y" /* yacc.c:1646  */
    {
              string aux = (yyvsp[0].string);
              table[idx].name = aux;
              table[idx].type = "num";
              table[idx].dim     = NULL;
              f=0;
              L=1;

              baseMem++; // Cada que encuentra un id, la baseMem++

              operandos.push( int2string(idx) );
              idx=idx+1;
            }
#line 2038 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 696 "mylanguage.y" /* yacc.c:1646  */
    {

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
            }
#line 2063 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 716 "mylanguage.y" /* yacc.c:1646  */
    {
              string aux = (yyvsp[0].string);
              table[idx].name = aux;
              table[idx].type = "lett";
              table[idx].dim     = NULL;
              f=0;
              L=1;
              baseMem++;

              operandos.push( int2string(idx) );
              idx=idx+1;
            }
#line 2080 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 730 "mylanguage.y" /* yacc.c:1646  */
    {
              string aux = (yyvsp[-1].string);
              string re = trim(aux.substr(aux.find("=")+1, aux.size() ) ); // get integer
              string id = operandos.top();      operandos.pop();
              
              cuadruplos[idxCuad][0] = "=";
              cuadruplos[idxCuad][1] = re+" num";
              cuadruplos[idxCuad][2] = id;
              idxCuad++;
            }
#line 2095 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 740 "mylanguage.y" /* yacc.c:1646  */
    {
              string aux = (yyvsp[-1].string);
              string re = trim(aux.substr(aux.find("=")+1, aux.size() ) );
              string id = operandos.top();      operandos.pop();
              
              cuadruplos[idxCuad][0] = "=";
              cuadruplos[idxCuad][1] = re + " num";
              cuadruplos[idxCuad][2] = id;
              idxCuad++;
            }
#line 2110 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 750 "mylanguage.y" /* yacc.c:1646  */
    {
              // Sacamos lo que hay aqui porque no hay nada en X, para evitar que esta referencia se quede en el stack
              operandos.pop();
            }
#line 2119 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 756 "mylanguage.y" /* yacc.c:1646  */
    {
              string aux = (yyvsp[-1].string);
              string re = trim(aux.substr(aux.find("=")+1, aux.size() ) );
              string id = operandos.top();      operandos.pop();
              cuadruplos[idxCuad][0] = "=";
              cuadruplos[idxCuad][1] = re;
              cuadruplos[idxCuad][3] = id;
              idxCuad++;
            }
#line 2133 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 768 "mylanguage.y" /* yacc.c:1646  */
    {;}
#line 2139 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 769 "mylanguage.y" /* yacc.c:1646  */
    {;}
#line 2145 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 772 "mylanguage.y" /* yacc.c:1646  */
    {
				table[idx].name = (yyvsp[0].string);
				table[idx].moduloInicio = idxCuad;
				idx++;
			}
#line 2155 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 776 "mylanguage.y" /* yacc.c:1646  */
    {
				cuadruplos[idxCuad][0] = "RETURN";
				idxCuad++;
			}
#line 2164 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 782 "mylanguage.y" /* yacc.c:1646  */
    {
				// Rellenas el primer cuadruplo para indicar el inicio del main
				cuadruplos[0][2] = int2string(idxCuad);

				}
#line 2174 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 786 "mylanguage.y" /* yacc.c:1646  */
    {;}
#line 2180 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 801 "mylanguage.y" /* yacc.c:1646  */
    {;}
#line 2186 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 802 "mylanguage.y" /* yacc.c:1646  */
    {;}
#line 2192 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 803 "mylanguage.y" /* yacc.c:1646  */
    {;}
#line 2198 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 807 "mylanguage.y" /* yacc.c:1646  */
    {
				cuadruplos[idxCuad][0] = "INPUT";
				cuadruplos[idxCuad][2] = getIndex((yyvsp[0].string));
				idxCuad++;
			}
#line 2208 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 814 "mylanguage.y" /* yacc.c:1646  */
    {
				cuadruplos[idxCuad][0] = "CALL";
				cuadruplos[idxCuad][2] = int2string(table[string2int(getIndex((yyvsp[0].string)))].moduloInicio);
				idxCuad++;
			}
#line 2218 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 821 "mylanguage.y" /* yacc.c:1646  */
    {
                string aux = (yyvsp[0].string);
                if( std::string::npos != aux.find("=") ){           // It has an =
                  aux = trim(aux.substr(0, aux.find("=")));
                } else if ( std::string::npos != aux.find(";") ){   // It has an ;
                  aux = trim(aux.substr(0, aux.find(";")));
                } else if ( std::string::npos != aux.find("[") ){   // It has a [ 
                	aux = trim(aux.substr(0, aux.find("[")));
                }
                operandos.push(getIndex(aux));

                dimPos=0; // Whenever it finds a new ID, its dimension starts in 0

            }
#line 2237 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 834 "mylanguage.y" /* yacc.c:1646  */
    {
            	//cout <<endl<<"POSDIM:"<<dimPos<<endl;
            	if(dimPos >=1){
					string re = operandos.top(); operandos.pop();
					//cout << "REEEE:" << re << endl;
              		re = "["+re+"]";
              		operandos.push(re);
              		//cout << "-D-"<<endl;
              	} else if(dimPos == 0){
              		//cout << "-ND-"<<endl;
              	}
                
            }
#line 2255 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 846 "mylanguage.y" /* yacc.c:1646  */
    {
                string re = operandos.top();      operandos.pop();
                string id = operandos.top();      operandos.pop();
                 
                cuadruplos[idxCuad][0] = "=";
                cuadruplos[idxCuad][1] = re;
                cuadruplos[idxCuad][2] = id;
                //cout << "ID ES ? "<<id <<endl;
                
                idxCuad++;  
            }
#line 2271 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 861 "mylanguage.y" /* yacc.c:1646  */
    {
              string re = operandos.top();      operandos.pop();
              // Pendiente validar que el tipo sea bool. Tendria que usar un stack de tipos o algo asi
              
              cuadruplos[idxCuad][0] = "GOTOF";
              cuadruplos[idxCuad][1] = re;
              idxCuad++;
              saltos.push(idxCuad-1);
                            
            }
#line 2286 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 870 "mylanguage.y" /* yacc.c:1646  */
    {
              int dir = saltos.top(); saltos.pop();
              // Rellena con idxCuad lo que se obtuvo en dir
              cuadruplos[dir][2] = int2string(idxCuad); // RELLENA UN GOTOF
            }
#line 2296 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 877 "mylanguage.y" /* yacc.c:1646  */
    {
              int dir = saltos.top(); saltos.pop();
              cuadruplos[idxCuad][0] = "GOTO";
              idxCuad++;
              saltos.push(idxCuad-1);
              // Rellena con idxCuad lo que se obtuvo en dir
              cuadruplos[dir][2] = int2string(idxCuad); // LLENA GOTO 

            }
#line 2310 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 885 "mylanguage.y" /* yacc.c:1646  */
    {;}
#line 2316 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 886 "mylanguage.y" /* yacc.c:1646  */
    {;}
#line 2322 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 889 "mylanguage.y" /* yacc.c:1646  */
    {
              operandos.push( getIndex((yyvsp[0].string)) );
            }
#line 2330 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 891 "mylanguage.y" /* yacc.c:1646  */
    { 
              string aux = (yyvsp[-1].string);
              string re = trim(aux.substr(aux.find("=")+1, aux.size() ) );
              string id = operandos.top(); operandos.pop();
              cuadruplos[idxCuad][0] = "=";
              cuadruplos[idxCuad][1] = re + " num";
              cuadruplos[idxCuad][2] = id;
              idxCuad++;
              saltos.push(idxCuad);
            }
#line 2345 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 902 "mylanguage.y" /* yacc.c:1646  */
    {
              string re = operandos.top(); operandos.pop();

              // Cuadruplo
              cuadruplos[idxCuad][0] = "GOTOF";
              cuadruplos[idxCuad][1] = re;
              idxCuad++;

              saltos.push(idxCuad-1);

            }
#line 2361 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 912 "mylanguage.y" /* yacc.c:1646  */
    {
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
              cuadruplos[idxCuad][2] = int2string(dir2);
              idxCuad++;

              // Rellenar GOTOF
              cuadruplos[dir1][2] = int2string(idxCuad);

            }
#line 2387 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 935 "mylanguage.y" /* yacc.c:1646  */
    {
              operandos.push( getIndex((yyvsp[0].string)) );
            }
#line 2395 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 941 "mylanguage.y" /* yacc.c:1646  */
    {
              saltos.push(idxCuad);

            }
#line 2404 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 944 "mylanguage.y" /* yacc.c:1646  */
    {
              string re = operandos.top(); operandos.pop();
              // Pendiente validar qeu sea bool re

              cuadruplos[idxCuad][0] = "GOTOF";
              cuadruplos[idxCuad][1] = re;
              idxCuad++;
              saltos.push(idxCuad-1);
              
            }
#line 2419 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 953 "mylanguage.y" /* yacc.c:1646  */
    {
              int dir1 = saltos.top(); saltos.pop();
              int dir2 = saltos.top(); saltos.pop();
              cuadruplos[idxCuad][0] = "GOTO";
              cuadruplos[idxCuad][2] = int2string(dir2);
              idxCuad++;

              // Rellena con idxCuad lo que se obtuvo en dir
              cuadruplos[dir1][2] = int2string(idxCuad);


            }
#line 2436 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 966 "mylanguage.y" /* yacc.c:1646  */
    {
              saltos.push(idxCuad);

            }
#line 2445 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 969 "mylanguage.y" /* yacc.c:1646  */
    {
              string re = operandos.top(); operandos.pop();

              int dir = saltos.top(); saltos.pop();

              cuadruplos[idxCuad][0] = "GOTOV";
              cuadruplos[idxCuad][1] = re;
              cuadruplos[idxCuad][2] = int2string(dir);
              idxCuad++;
            }
#line 2460 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 981 "mylanguage.y" /* yacc.c:1646  */
    {;}
#line 2466 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 982 "mylanguage.y" /* yacc.c:1646  */
    {
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
#line 2485 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 998 "mylanguage.y" /* yacc.c:1646  */
    {operadores.push("<");}
#line 2491 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 999 "mylanguage.y" /* yacc.c:1646  */
    {operadores.push(">");}
#line 2497 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1000 "mylanguage.y" /* yacc.c:1646  */
    {operadores.push("<=");}
#line 2503 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1001 "mylanguage.y" /* yacc.c:1646  */
    {operadores.push(">=");}
#line 2509 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1002 "mylanguage.y" /* yacc.c:1646  */
    {operadores.push("==");}
#line 2515 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1003 "mylanguage.y" /* yacc.c:1646  */
    {operadores.push("!=");}
#line 2521 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1007 "mylanguage.y" /* yacc.c:1646  */
    {
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
#line 2540 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1024 "mylanguage.y" /* yacc.c:1646  */
    {operadores.push("+");}
#line 2546 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1025 "mylanguage.y" /* yacc.c:1646  */
    {operadores.push("-");}
#line 2552 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1026 "mylanguage.y" /* yacc.c:1646  */
    {operadores.push("OR");}
#line 2558 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1030 "mylanguage.y" /* yacc.c:1646  */
    {
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
#line 2576 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1045 "mylanguage.y" /* yacc.c:1646  */
    {operadores.push("*");}
#line 2582 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1046 "mylanguage.y" /* yacc.c:1646  */
    {operadores.push("/");}
#line 2588 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1047 "mylanguage.y" /* yacc.c:1646  */
    {operadores.push("AND");}
#line 2594 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1051 "mylanguage.y" /* yacc.c:1646  */
    {
              int aux = (yyvsp[0].integer);
              operandos.push( int2string(aux)+" num");
            }
#line 2603 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 1055 "mylanguage.y" /* yacc.c:1646  */
    {
      			float aux = (yyvsp[0].fp);
            	operandos.push( float2string(aux)+" num" );  
            }
#line 2612 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1060 "mylanguage.y" /* yacc.c:1646  */
    { 

              string pos = getIndex( (yyvsp[0].string) );

              if(pos != "-1"){ 
                operandos.push(pos);
                //cout  << " ID ES : "<< $2 << " POS "<< pos <<endl;
              } else {
                cout << "VARIABLE NO EXISTE : "<< (yyvsp[0].string) <<endl;
                return -1;
              }

              //struct node *iter = table[string2int(pos)].dim;
              if( table[string2int(pos)].dim != NULL ){
              	//cout << "  ES DIMENSIONADA   "<<table[string2int(pos)].name<<endl;
              	dimPos=0;

              } else {
              	//cout << " NO ES DIMENSIONADA  "<< table[string2int(pos)].name<<endl;


              }
              //cout << "paso por aqui con : "<<$2<<endl;


            }
#line 2643 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 1085 "mylanguage.y" /* yacc.c:1646  */
    {
           
            	//cout << " OP : "<< operandos.top() << " en pos "<< dimPos<<endl; 
            	// WORKAROUND SUPER MEGA HORRIBLE. PENDIENTE REVISAR
            	// EL PROBLEMA ES QUE DIRECCIONA A VARSIMS Y VARDIMS COMO DIMS, Y NO DEBERIA
            	if(dimPos >=1 && operandos.top()[0] == 'T'){ 
					string re = operandos.top(); operandos.pop();
              		re = "["+re+"]";
              		operandos.push(re);
              		//cout << " RE ES "<< re << " dimPOS : " <<  dimPos<<endl;
              	} else if(dimPos == 0){
              		//cout << "-ND-"<<endl;
              	}
                
            }
#line 2663 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1103 "mylanguage.y" /* yacc.c:1646  */
    {;}
#line 2669 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 1105 "mylanguage.y" /* yacc.c:1646  */
    {
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
		    }
#line 2693 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1123 "mylanguage.y" /* yacc.c:1646  */
    {
				string re = operandos.top(); operandos.pop();
				L = L * string2int(re);
				(*curr).d = string2int(re);
			}
#line 2703 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1128 "mylanguage.y" /* yacc.c:1646  */
    {;}
#line 2709 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1131 "mylanguage.y" /* yacc.c:1646  */
    { 	
					// First positon
			        dimPos++;
				 	if(dimPos == 1){
						string id = operandos.top(); operandos.pop();
						curr = table[ string2int(id) ].dim;
						//cout << "SIDIM"<<nodim<<endl;
						//cout << "LET'S PRINT THE LL OF THIS VAR"<<endl;
						//displayLL(curr);
					}
				}
#line 2725 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1141 "mylanguage.y" /* yacc.c:1646  */
    {
    				// There's a next dimension
    				//cout << " AAAA : ";
    				//cout << operandos.top() << endl;
    				if( curr->next ) {
    					string re = operandos.top(); operandos.pop();
    					string res = temporales.top(); temporales.pop();

    					// GENERAR CUADRUPLO
    					cuadruplos[idxCuad][0] = "*";
	                	cuadruplos[idxCuad][1] = re ;
	                	cuadruplos[idxCuad][2] = int2string( (*curr).m )+" num" ;
	                	cuadruplos[idxCuad][3] = res;
    					idxCuad++; 

	       				//int auxx = (string2int(re)*(*curr).m) ;
	        			//operandos.push( int2string(auxx) );
	        			operandos.push( res );

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

	       				//int auxr = string2int(op1) + string2int(op2);
	        			//operandos.push( int2string(auxr) );
	        			operandos.push( res );
    				}
    				// Last dimension
    				if(curr->next == NULL){
    					string re = operandos.top(); operandos.pop();
    					string res = temporales.top(); temporales.pop();
    					
              			// GENERAR CUADRUPLO
    					cuadruplos[idxCuad][0] = "+";
              			cuadruplos[idxCuad][1] = re ;
            			cuadruplos[idxCuad][2] = int2string( (*curr).m ) + " num"; // The base
            			cuadruplos[idxCuad][3] = res;
    					idxCuad++; 

       					//int auxx = ( string2int(re) + (*curr).m ) ;
        				//operandos.push( int2string(auxx) );
        				operandos.push( res );
    				}
    				curr = curr->next;
        		}
#line 2785 "mylanguage.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1196 "mylanguage.y" /* yacc.c:1646  */
    {
              		//cout << "NO DIM";
              	  }
#line 2793 "mylanguage.tab.c" /* yacc.c:1646  */
    break;


#line 2797 "mylanguage.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1202 "mylanguage.y" /* yacc.c:1906  */


void  yyerror(char const *s) {
	fprintf (stderr, "%s\n", s);
}

int  main(void) {
  for(int i=60; i>=0; i--){
  //for(int i=0; i<=60; i++){
    temporales.push("T"+int2string(i));
  }
  return yyparse ();   //  yyparse  is  defined  for us by flex
}

