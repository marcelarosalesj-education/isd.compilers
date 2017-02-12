/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 605 "mylanguage.y" /* yacc.c:1909  */

  char *string;           /* Ptr to constant string (strings are malloc'd) */
  int integer;            /* Constant integer value */
  float fp;               /* Constant floating point value */

#line 101 "mylanguage.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MYLANGUAGE_TAB_H_INCLUDED  */
