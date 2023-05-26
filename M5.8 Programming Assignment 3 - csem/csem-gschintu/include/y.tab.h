/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ID = 258,                      /* ID  */
    CON = 259,                     /* CON  */
    STR = 260,                     /* STR  */
    CHAR = 261,                    /* CHAR  */
    ELSE = 262,                    /* ELSE  */
    FLOAT = 263,                   /* FLOAT  */
    DOUBLE = 264,                  /* DOUBLE  */
    FOR = 265,                     /* FOR  */
    IF = 266,                      /* IF  */
    INT = 267,                     /* INT  */
    RESERVED = 268,                /* RESERVED  */
    RETURN = 269,                  /* RETURN  */
    WHILE = 270,                   /* WHILE  */
    DO = 271,                      /* DO  */
    CONTINUE = 272,                /* CONTINUE  */
    BREAK = 273,                   /* BREAK  */
    GOTO = 274,                    /* GOTO  */
    LVAL = 275,                    /* LVAL  */
    SET = 276,                     /* SET  */
    SETOR = 277,                   /* SETOR  */
    SETXOR = 278,                  /* SETXOR  */
    SETAND = 279,                  /* SETAND  */
    SETLSH = 280,                  /* SETLSH  */
    SETRSH = 281,                  /* SETRSH  */
    SETADD = 282,                  /* SETADD  */
    SETSUB = 283,                  /* SETSUB  */
    SETMUL = 284,                  /* SETMUL  */
    SETDIV = 285,                  /* SETDIV  */
    SETMOD = 286,                  /* SETMOD  */
    OR = 287,                      /* OR  */
    AND = 288,                     /* AND  */
    BITOR = 289,                   /* BITOR  */
    BITXOR = 290,                  /* BITXOR  */
    BITAND = 291,                  /* BITAND  */
    EQ = 292,                      /* EQ  */
    NE = 293,                      /* NE  */
    GT = 294,                      /* GT  */
    GE = 295,                      /* GE  */
    LT = 296,                      /* LT  */
    LE = 297,                      /* LE  */
    LSH = 298,                     /* LSH  */
    RSH = 299,                     /* RSH  */
    ADD = 300,                     /* ADD  */
    SUB = 301,                     /* SUB  */
    MUL = 302,                     /* MUL  */
    DIV = 303,                     /* DIV  */
    MOD = 304,                     /* MOD  */
    UNARY = 305,                   /* UNARY  */
    NOT = 306,                     /* NOT  */
    COM = 307                      /* COM  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ID 258
#define CON 259
#define STR 260
#define CHAR 261
#define ELSE 262
#define FLOAT 263
#define DOUBLE 264
#define FOR 265
#define IF 266
#define INT 267
#define RESERVED 268
#define RETURN 269
#define WHILE 270
#define DO 271
#define CONTINUE 272
#define BREAK 273
#define GOTO 274
#define LVAL 275
#define SET 276
#define SETOR 277
#define SETXOR 278
#define SETAND 279
#define SETLSH 280
#define SETRSH 281
#define SETADD 282
#define SETSUB 283
#define SETMUL 284
#define SETDIV 285
#define SETMOD 286
#define OR 287
#define AND 288
#define BITOR 289
#define BITXOR 290
#define BITAND 291
#define EQ 292
#define NE 293
#define GT 294
#define GE 295
#define LT 296
#define LE 297
#define LSH 298
#define RSH 299
#define ADD 300
#define SUB 301
#define MUL 302
#define DIV 303
#define MOD 304
#define UNARY 305
#define NOT 306
#define COM 307

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 35 "src/cgram.y"

    int inttype;
    void *bb_ptr;
    
    char *str_ptr;
    struct sem_rec *rec_ptr;
    struct id_entry *id_ptr;

#line 180 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
