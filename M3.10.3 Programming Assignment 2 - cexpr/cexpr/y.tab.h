/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUM = 258,
     VAR = 259,
     SEMICOLON = 260,
     DUMP = 261,
     CLEAR = 262,
     ADD_ASSIGN = 263,
     SUB_ASSIGN = 264,
     MULT_ASSIGN = 265,
     DIVD_ASSIGN = 266,
     REM_ASSIGN = 267,
     LEFT_SHIFT_ASSIGN = 268,
     RIGHT_SHIFT_ASSIGN = 269,
     AND_ASSIGN = 270,
     XOR_ASSIGN = 271,
     OR_ASSIGN = 272,
     BITWISE_OR = 273,
     BITWISE_XOR = 274,
     BITWISE_AND = 275,
     LEFT_SHIFT = 276,
     RIGHT_SHIFT = 277,
     ADD = 278,
     SUB = 279,
     MULT = 280,
     DIVD = 281,
     REM = 282,
     NEGAT = 283,
     BITWISE_NOT = 284,
     OPEN_PAREN = 285,
     CLOSE_PAREN = 286
   };
#endif
/* Tokens.  */
#define NUM 258
#define VAR 259
#define SEMICOLON 260
#define DUMP 261
#define CLEAR 262
#define ADD_ASSIGN 263
#define SUB_ASSIGN 264
#define MULT_ASSIGN 265
#define DIVD_ASSIGN 266
#define REM_ASSIGN 267
#define LEFT_SHIFT_ASSIGN 268
#define RIGHT_SHIFT_ASSIGN 269
#define AND_ASSIGN 270
#define XOR_ASSIGN 271
#define OR_ASSIGN 272
#define BITWISE_OR 273
#define BITWISE_XOR 274
#define BITWISE_AND 275
#define LEFT_SHIFT 276
#define RIGHT_SHIFT 277
#define ADD 278
#define SUB 279
#define MULT 280
#define DIVD 281
#define REM 282
#define NEGAT 283
#define BITWISE_NOT 284
#define OPEN_PAREN 285
#define CLOSE_PAREN 286




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 34 "ex.y"
{
  int num;
  char *string;
}
/* Line 1529 of yacc.c.  */
#line 116 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

