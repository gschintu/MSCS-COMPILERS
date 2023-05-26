/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/cgram.y"

  /* grammar for subset of C. The grammar does not recognize all C syntax:
     For example:
     1. Character literals
     2. Structres
     3. Double constants
     4. Nested paraenthesis of the form "if((x == 1))"
     5. etc.
  */
#include <stdio.h>
#include <stdlib.h>

extern "C" {
    #include "cc.h"
    #include "scan.h"
    #include "semutil.h"
    #include "sem.h"
    #include "sym.h"
}

int yylex();

extern int lineno;
/*
 * yyerror - issue error message
 */
void
yyerror (const char *msg)
{
   fprintf(stderr, " %s.  Line %d\n", msg, lineno);
   exit(1);
}


#line 106 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 272 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_CON = 4,                        /* CON  */
  YYSYMBOL_STR = 5,                        /* STR  */
  YYSYMBOL_CHAR = 6,                       /* CHAR  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_FLOAT = 8,                      /* FLOAT  */
  YYSYMBOL_DOUBLE = 9,                     /* DOUBLE  */
  YYSYMBOL_FOR = 10,                       /* FOR  */
  YYSYMBOL_IF = 11,                        /* IF  */
  YYSYMBOL_INT = 12,                       /* INT  */
  YYSYMBOL_RESERVED = 13,                  /* RESERVED  */
  YYSYMBOL_RETURN = 14,                    /* RETURN  */
  YYSYMBOL_WHILE = 15,                     /* WHILE  */
  YYSYMBOL_DO = 16,                        /* DO  */
  YYSYMBOL_CONTINUE = 17,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 18,                     /* BREAK  */
  YYSYMBOL_GOTO = 19,                      /* GOTO  */
  YYSYMBOL_LVAL = 20,                      /* LVAL  */
  YYSYMBOL_SET = 21,                       /* SET  */
  YYSYMBOL_SETOR = 22,                     /* SETOR  */
  YYSYMBOL_SETXOR = 23,                    /* SETXOR  */
  YYSYMBOL_SETAND = 24,                    /* SETAND  */
  YYSYMBOL_SETLSH = 25,                    /* SETLSH  */
  YYSYMBOL_SETRSH = 26,                    /* SETRSH  */
  YYSYMBOL_SETADD = 27,                    /* SETADD  */
  YYSYMBOL_SETSUB = 28,                    /* SETSUB  */
  YYSYMBOL_SETMUL = 29,                    /* SETMUL  */
  YYSYMBOL_SETDIV = 30,                    /* SETDIV  */
  YYSYMBOL_SETMOD = 31,                    /* SETMOD  */
  YYSYMBOL_OR = 32,                        /* OR  */
  YYSYMBOL_AND = 33,                       /* AND  */
  YYSYMBOL_BITOR = 34,                     /* BITOR  */
  YYSYMBOL_BITXOR = 35,                    /* BITXOR  */
  YYSYMBOL_BITAND = 36,                    /* BITAND  */
  YYSYMBOL_EQ = 37,                        /* EQ  */
  YYSYMBOL_NE = 38,                        /* NE  */
  YYSYMBOL_GT = 39,                        /* GT  */
  YYSYMBOL_GE = 40,                        /* GE  */
  YYSYMBOL_LT = 41,                        /* LT  */
  YYSYMBOL_LE = 42,                        /* LE  */
  YYSYMBOL_LSH = 43,                       /* LSH  */
  YYSYMBOL_RSH = 44,                       /* RSH  */
  YYSYMBOL_ADD = 45,                       /* ADD  */
  YYSYMBOL_SUB = 46,                       /* SUB  */
  YYSYMBOL_MUL = 47,                       /* MUL  */
  YYSYMBOL_DIV = 48,                       /* DIV  */
  YYSYMBOL_MOD = 49,                       /* MOD  */
  YYSYMBOL_UNARY = 50,                     /* UNARY  */
  YYSYMBOL_NOT = 51,                       /* NOT  */
  YYSYMBOL_COM = 52,                       /* COM  */
  YYSYMBOL_53_ = 53,                       /* ';'  */
  YYSYMBOL_54_ = 54,                       /* ','  */
  YYSYMBOL_55_ = 55,                       /* '['  */
  YYSYMBOL_56_ = 56,                       /* ']'  */
  YYSYMBOL_57_ = 57,                       /* '}'  */
  YYSYMBOL_58_ = 58,                       /* '{'  */
  YYSYMBOL_59_ = 59,                       /* '('  */
  YYSYMBOL_60_ = 60,                       /* ')'  */
  YYSYMBOL_61_ = 61,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 62,                  /* $accept  */
  YYSYMBOL_prog = 63,                      /* prog  */
  YYSYMBOL_externs = 64,                   /* externs  */
  YYSYMBOL_extern = 65,                    /* extern  */
  YYSYMBOL_dcls = 66,                      /* dcls  */
  YYSYMBOL_dcl = 67,                       /* dcl  */
  YYSYMBOL_dclr = 68,                      /* dclr  */
  YYSYMBOL_type = 69,                      /* type  */
  YYSYMBOL_func = 70,                      /* func  */
  YYSYMBOL_fhead = 71,                     /* fhead  */
  YYSYMBOL_fname = 72,                     /* fname  */
  YYSYMBOL_fargs = 73,                     /* fargs  */
  YYSYMBOL_args = 74,                      /* args  */
  YYSYMBOL_s = 75,                         /* s  */
  YYSYMBOL_m = 76,                         /* m  */
  YYSYMBOL_n = 77,                         /* n  */
  YYSYMBOL_block = 78,                     /* block  */
  YYSYMBOL_stmts = 79,                     /* stmts  */
  YYSYMBOL_lblstmt = 80,                   /* lblstmt  */
  YYSYMBOL_labels = 81,                    /* labels  */
  YYSYMBOL_b = 82,                         /* b  */
  YYSYMBOL_stmt = 83,                      /* stmt  */
  YYSYMBOL_cexpro = 84,                    /* cexpro  */
  YYSYMBOL_cexpr = 85,                     /* cexpr  */
  YYSYMBOL_exprs = 86,                     /* exprs  */
  YYSYMBOL_expro = 87,                     /* expro  */
  YYSYMBOL_expr = 88,                      /* expr  */
  YYSYMBOL_lval = 89                       /* lval  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   416

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  211

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   307


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      59,    60,     2,     2,    54,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    61,    53,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    55,     2,    56,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    58,     2,    57,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    65,    65,    68,    69,    72,    73,    76,    77,    80,
      81,    84,    85,    86,    89,    90,    91,    92,    95,    98,
     101,   102,   105,   106,   109,   110,   113,   116,   119,   122,
     125,   126,   129,   130,   133,   134,   137,   140,   142,   144,
     146,   148,   150,   152,   154,   156,   158,   160,   162,   164,
     168,   169,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   185,   186,   189,   190,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   225,   226
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "CON", "STR",
  "CHAR", "ELSE", "FLOAT", "DOUBLE", "FOR", "IF", "INT", "RESERVED",
  "RETURN", "WHILE", "DO", "CONTINUE", "BREAK", "GOTO", "LVAL", "SET",
  "SETOR", "SETXOR", "SETAND", "SETLSH", "SETRSH", "SETADD", "SETSUB",
  "SETMUL", "SETDIV", "SETMOD", "OR", "AND", "BITOR", "BITXOR", "BITAND",
  "EQ", "NE", "GT", "GE", "LT", "LE", "LSH", "RSH", "ADD", "SUB", "MUL",
  "DIV", "MOD", "UNARY", "NOT", "COM", "';'", "','", "'['", "']'", "'}'",
  "'{'", "'('", "')'", "':'", "$accept", "prog", "externs", "extern",
  "dcls", "dcl", "dclr", "type", "func", "fhead", "fname", "fargs", "args",
  "s", "m", "n", "block", "stmts", "lblstmt", "labels", "b", "stmt",
  "cexpro", "cexpr", "exprs", "expro", "expr", "lval", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-178)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-21)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -178,     3,   140,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
      51,    10,  -178,  -178,   -53,  -178,    15,   -16,  -178,   -33,
      32,   -25,   -13,  -178,    -3,  -178,  -178,   162,  -178,    15,
     -44,  -178,   -26,  -178,    57,  -178,  -178,    -5,    18,    42,
      27,  -178,    45,    58,    97,   117,   190,   190,  -178,  -178,
     190,  -178,   186,  -178,   268,   378,  -178,   201,  -178,   201,
    -178,   190,    47,  -178,   190,   182,    30,  -178,   284,  -178,
    -178,  -178,  -178,    72,    -7,  -178,  -178,  -178,    70,   234,
      67,  -178,   190,   190,   190,   190,   190,   190,   190,   190,
     190,   190,  -178,   190,   190,   190,   190,   190,   190,   190,
     190,   190,   190,   190,    15,   104,    15,   252,  -178,   -43,
     320,    76,   320,   182,   182,   -28,   304,  -178,   182,  -178,
    -178,  -178,  -178,  -178,   335,   349,   367,    92,    92,   106,
     106,  -178,  -178,  -178,   320,   320,   320,   320,   320,   320,
     320,   320,   320,   320,   320,  -178,  -178,  -178,   190,  -178,
    -178,  -178,   -24,   216,  -178,  -178,  -178,   190,   190,   190,
     190,   190,   190,   -11,   132,   320,   182,  -178,   182,   182,
    -178,   320,   320,   320,   320,   320,   320,  -178,    91,   107,
     137,   130,  -178,   164,  -178,  -178,  -178,  -178,  -178,  -178,
     182,   190,  -178,  -178,    64,  -178,  -178,  -178,   121,   115,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,    21,    14,    15,    16,    17,     4,
       0,     0,     6,    30,     0,     5,     0,    11,     9,    36,
       0,     0,    11,    10,     0,    18,    31,     0,    22,     0,
       0,     7,     0,    12,    97,    95,    96,     0,     0,     0,
       0,    27,     0,     0,     0,     0,     0,     0,    49,    30,
       0,    48,     0,    32,     0,    91,    24,     0,    23,    19,
      13,     0,     0,    34,    65,     0,    97,    46,     0,    27,
      26,    43,    44,     0,    97,    88,    89,    90,    36,     0,
      97,    33,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    37,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    92,     0,
      63,     0,    66,     0,     0,     0,    61,    47,     0,    36,
      45,    29,    94,    35,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    25,     8,    98,     0,    93,
      27,    60,     0,    61,    27,    27,    27,     0,     0,     0,
       0,     0,     0,     0,     0,    64,    50,    62,     0,     0,
      36,    52,    53,    57,    55,    56,    54,    27,     0,     0,
      51,    59,    58,    27,    26,    27,    27,    28,    38,    36,
       0,    65,    27,    28,     0,    28,    36,    27,     0,     0,
      27,    40,    27,    27,    39,    41,    26,    36,    28,    27,
      42
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -178,  -178,  -178,  -178,  -178,   123,   -14,    60,  -178,  -178,
    -178,  -178,  -178,  -177,   -41,   -85,  -178,   134,  -105,  -178,
    -178,   136,  -178,   -87,  -178,     1,   -27,   139
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     9,    59,    10,    18,    11,    12,    13,
      14,    21,    30,   119,    70,   192,    51,    19,    26,    52,
      27,    53,   179,   115,   109,   111,   116,    55
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      54,    32,    23,     3,   154,   155,    20,   189,   154,   155,
      57,   148,    68,    17,   164,    56,    58,   149,    22,    76,
      77,   154,   155,    79,    25,    54,   151,   152,   118,   207,
      60,   163,   156,    31,   107,   110,   167,   112,     5,    24,
       6,     7,    24,   -20,     8,    66,    35,    36,    61,   177,
      66,    35,    36,    33,    64,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   183,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,    65,    45,   180,
      29,   181,   182,    45,   193,    61,    69,   153,    46,    62,
     145,   200,    28,    46,    47,    67,   154,   155,    71,    47,
      73,    50,   208,   194,    15,    16,    50,   108,   197,   166,
     199,    72,    61,   168,   169,   170,    62,   104,    63,   106,
      74,   165,    61,   209,   198,   120,    62,   121,   123,   150,
     171,   172,   173,   174,   175,   176,   184,    87,    88,    89,
      90,    91,   188,     4,   190,   191,     5,   178,     6,     7,
     185,   196,     8,    89,    90,    91,   201,   146,    16,   204,
     186,   205,   206,   155,   112,    34,    35,    36,   210,   154,
     155,   187,    37,    38,   202,   203,    39,    40,    41,    42,
      43,    44,   105,    78,    75,    66,    35,    36,    81,    80,
      35,    36,   195,    66,    35,    36,    37,    38,    45,     0,
      39,    40,    41,    42,    43,    44,     0,     5,    46,     6,
       7,     0,     0,     8,    47,    48,     0,     0,    45,     0,
      49,    50,    45,     0,     0,     0,    45,     0,    46,     0,
       0,     0,    46,   113,    47,     0,    46,     0,    47,    48,
       0,   114,    47,     0,    49,    50,     0,     0,     0,    50,
      82,    83,    84,   157,   158,   159,   160,   161,   162,    85,
      86,    87,    88,    89,    90,    91,     0,     0,    82,    83,
      84,     0,     0,     0,     0,     0,   122,    85,    86,    87,
      88,    89,    90,    91,     0,     0,    82,    83,    84,     0,
       0,     0,     0,     0,   122,    85,    86,    87,    88,    89,
      90,    91,    82,    83,    84,     0,     0,     0,   147,     0,
       0,    85,    86,    87,    88,    89,    90,    91,    82,    83,
      84,    92,     0,     0,     0,     0,     0,    85,    86,    87,
      88,    89,    90,    91,     0,     0,     0,   117,    82,    83,
      84,   157,   158,   159,   160,   161,   162,    85,    86,    87,
      88,    89,    90,    91,    82,    83,    84,     0,     0,     0,
       0,     0,     0,    85,    86,    87,    88,    89,    90,    91,
      83,    84,     0,     0,     0,     0,     0,     0,    85,    86,
      87,    88,    89,    90,    91,    84,     0,     0,     0,     0,
       0,     0,    85,    86,    87,    88,    89,    90,    91,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
      85,    86,    87,    88,    89,    90,    91
};

static const yytype_int16 yycheck[] =
{
      27,     4,    16,     0,    32,    33,    59,   184,    32,    33,
      54,    54,    39,     3,   119,    29,    60,    60,     3,    46,
      47,    32,    33,    50,    57,    52,   113,   114,    69,   206,
      56,   118,    60,    58,    61,    62,    60,    64,     6,    55,
       8,     9,    55,    59,    12,     3,     4,     5,    55,    60,
       3,     4,     5,    56,    59,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,   170,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,    59,    36,   166,
      20,   168,   169,    36,   189,    55,    59,   114,    46,    59,
     104,   196,    60,    46,    52,    53,    32,    33,    53,    52,
       3,    59,   207,   190,    53,    54,    59,    60,   193,   150,
     195,    53,    55,   154,   155,   156,    59,    57,    61,    59,
       3,   148,    55,   208,    60,    53,    59,    57,    61,    53,
     157,   158,   159,   160,   161,   162,   177,    45,    46,    47,
      48,    49,   183,     3,   185,   186,     6,    15,     8,     9,
      59,   192,    12,    47,    48,    49,   197,    53,    54,   200,
      53,   202,   203,    33,   191,     3,     4,     5,   209,    32,
      33,     7,    10,    11,    53,    60,    14,    15,    16,    17,
      18,    19,    59,    49,    45,     3,     4,     5,    52,     3,
       4,     5,   191,     3,     4,     5,    10,    11,    36,    -1,
      14,    15,    16,    17,    18,    19,    -1,     6,    46,     8,
       9,    -1,    -1,    12,    52,    53,    -1,    -1,    36,    -1,
      58,    59,    36,    -1,    -1,    -1,    36,    -1,    46,    -1,
      -1,    -1,    46,    51,    52,    -1,    46,    -1,    52,    53,
      -1,    59,    52,    -1,    58,    59,    -1,    -1,    -1,    59,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    -1,    -1,    34,    35,
      36,    -1,    -1,    -1,    -1,    -1,    60,    43,    44,    45,
      46,    47,    48,    49,    -1,    -1,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    60,    43,    44,    45,    46,    47,
      48,    49,    34,    35,    36,    -1,    -1,    -1,    56,    -1,
      -1,    43,    44,    45,    46,    47,    48,    49,    34,    35,
      36,    53,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,
      46,    47,    48,    49,    -1,    -1,    -1,    53,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    44,    45,    46,    47,    48,    49,
      35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      45,    46,    47,    48,    49,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    46,    47,    48,    49,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      43,    44,    45,    46,    47,    48,    49
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    63,    64,     0,     3,     6,     8,     9,    12,    65,
      67,    69,    70,    71,    72,    53,    54,     3,    68,    79,
      59,    73,     3,    68,    55,    57,    80,    82,    60,    69,
      74,    58,     4,    56,     3,     4,     5,    10,    11,    14,
      15,    16,    17,    18,    19,    36,    46,    52,    53,    58,
      59,    78,    81,    83,    88,    89,    68,    54,    60,    66,
      56,    55,    59,    61,    59,    59,     3,    53,    88,    59,
      76,    53,    53,     3,     3,    89,    88,    88,    79,    88,
       3,    83,    34,    35,    36,    43,    44,    45,    46,    47,
      48,    49,    53,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    69,    67,    69,    88,    60,    86,
      88,    87,    88,    51,    59,    85,    88,    53,    76,    75,
      53,    57,    60,    61,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    68,    53,    56,    54,    60,
      53,    85,    85,    88,    32,    33,    60,    37,    38,    39,
      40,    41,    42,    85,    80,    88,    76,    60,    76,    76,
      76,    88,    88,    88,    88,    88,    88,    60,    15,    84,
      85,    85,    85,    80,    76,    59,    53,     7,    76,    75,
      76,    76,    77,    80,    85,    87,    76,    77,    60,    77,
      80,    76,    53,    60,    76,    76,    76,    75,    80,    77,
      76
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    62,    63,    64,    64,    65,    65,    66,    66,    67,
      67,    68,    68,    68,    69,    69,    69,    69,    70,    71,
      72,    72,    73,    73,    74,    74,    75,    76,    77,    78,
      79,    79,    80,    80,    81,    81,    82,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      84,    84,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    86,    86,    87,    87,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    89,    89
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     1,     0,     3,     2,
       3,     1,     3,     4,     1,     1,     1,     1,     3,     4,
       2,     1,     2,     3,     2,     4,     0,     0,     0,     3,
       0,     2,     2,     3,     2,     3,     0,     2,     7,    11,
      10,    11,    16,     2,     2,     3,     2,     3,     1,     1,
       0,     1,     3,     3,     3,     3,     3,     3,     4,     4,
       2,     1,     3,     1,     3,     0,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     1,     3,     4,     3,     1,     1,     1,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* prog: externs  */
#line 65 "src/cgram.y"
                                {}
#line 1516 "y.tab.c"
    break;

  case 3: /* externs: %empty  */
#line 68 "src/cgram.y"
                                {}
#line 1522 "y.tab.c"
    break;

  case 4: /* externs: externs extern  */
#line 69 "src/cgram.y"
                                {}
#line 1528 "y.tab.c"
    break;

  case 5: /* extern: dcl ';'  */
#line 72 "src/cgram.y"
                                {}
#line 1534 "y.tab.c"
    break;

  case 6: /* extern: func  */
#line 73 "src/cgram.y"
                                {}
#line 1540 "y.tab.c"
    break;

  case 7: /* dcls: %empty  */
#line 76 "src/cgram.y"
                                {}
#line 1546 "y.tab.c"
    break;

  case 8: /* dcls: dcls dcl ';'  */
#line 77 "src/cgram.y"
                                {}
#line 1552 "y.tab.c"
    break;

  case 9: /* dcl: type dclr  */
#line 80 "src/cgram.y"
                                { (yyval.id_ptr) = dcl((yyvsp[0].id_ptr), (yyvsp[-1].inttype), 0); }
#line 1558 "y.tab.c"
    break;

  case 10: /* dcl: dcl ',' dclr  */
#line 81 "src/cgram.y"
                                { (yyval.id_ptr) = dcl((yyvsp[0].id_ptr), (yyvsp[-2].id_ptr)->i_type&~T_ARRAY, 0); }
#line 1564 "y.tab.c"
    break;

  case 11: /* dclr: ID  */
#line 84 "src/cgram.y"
                                { (yyval.id_ptr) = dclr((yyvsp[0].str_ptr), 0, 1); }
#line 1570 "y.tab.c"
    break;

  case 12: /* dclr: ID '[' ']'  */
#line 85 "src/cgram.y"
                                { (yyval.id_ptr) = dclr((yyvsp[-2].str_ptr), T_ARRAY, 1); }
#line 1576 "y.tab.c"
    break;

  case 13: /* dclr: ID '[' CON ']'  */
#line 86 "src/cgram.y"
                                { (yyval.id_ptr) = dclr((yyvsp[-3].str_ptr), T_ARRAY, atoi((yyvsp[-1].str_ptr))); }
#line 1582 "y.tab.c"
    break;

  case 14: /* type: CHAR  */
#line 89 "src/cgram.y"
                                { (yyval.inttype) = T_INT; }
#line 1588 "y.tab.c"
    break;

  case 15: /* type: FLOAT  */
#line 90 "src/cgram.y"
                                { (yyval.inttype) = T_DOUBLE; }
#line 1594 "y.tab.c"
    break;

  case 16: /* type: DOUBLE  */
#line 91 "src/cgram.y"
                                { (yyval.inttype) = T_DOUBLE; }
#line 1600 "y.tab.c"
    break;

  case 17: /* type: INT  */
#line 92 "src/cgram.y"
                                { (yyval.inttype) = T_INT; }
#line 1606 "y.tab.c"
    break;

  case 18: /* func: fhead stmts '}'  */
#line 95 "src/cgram.y"
                                { ftail(); }
#line 1612 "y.tab.c"
    break;

  case 19: /* fhead: fname fargs '{' dcls  */
#line 98 "src/cgram.y"
                                { fhead((yyvsp[-3].id_ptr)); }
#line 1618 "y.tab.c"
    break;

  case 20: /* fname: type ID  */
#line 101 "src/cgram.y"
                                { (yyval.id_ptr) = fname((yyvsp[-1].inttype), (yyvsp[0].str_ptr)); }
#line 1624 "y.tab.c"
    break;

  case 21: /* fname: ID  */
#line 102 "src/cgram.y"
                                { (yyval.id_ptr) = fname(T_INT, (yyvsp[0].str_ptr)); }
#line 1630 "y.tab.c"
    break;

  case 22: /* fargs: '(' ')'  */
#line 105 "src/cgram.y"
                                { enterblock(); }
#line 1636 "y.tab.c"
    break;

  case 23: /* fargs: '(' args ')'  */
#line 106 "src/cgram.y"
                                { enterblock(); }
#line 1642 "y.tab.c"
    break;

  case 24: /* args: type dclr  */
#line 109 "src/cgram.y"
                                { dcl((yyvsp[0].id_ptr), (yyvsp[-1].inttype), PARAM); }
#line 1648 "y.tab.c"
    break;

  case 25: /* args: args ',' type dclr  */
#line 110 "src/cgram.y"
                                { dcl((yyvsp[0].id_ptr), (yyvsp[-1].inttype), PARAM); }
#line 1654 "y.tab.c"
    break;

  case 26: /* s: %empty  */
#line 113 "src/cgram.y"
                                { startloopscope(); }
#line 1660 "y.tab.c"
    break;

  case 27: /* m: %empty  */
#line 116 "src/cgram.y"
                                { (yyval.bb_ptr) = m(); }
#line 1666 "y.tab.c"
    break;

  case 28: /* n: %empty  */
#line 119 "src/cgram.y"
                                { (yyval.rec_ptr) = n(); }
#line 1672 "y.tab.c"
    break;

  case 29: /* block: '{' stmts '}'  */
#line 122 "src/cgram.y"
                                { }
#line 1678 "y.tab.c"
    break;

  case 30: /* stmts: %empty  */
#line 125 "src/cgram.y"
                                { }
#line 1684 "y.tab.c"
    break;

  case 31: /* stmts: stmts lblstmt  */
#line 126 "src/cgram.y"
                                { }
#line 1690 "y.tab.c"
    break;

  case 32: /* lblstmt: b stmt  */
#line 129 "src/cgram.y"
                                { }
#line 1696 "y.tab.c"
    break;

  case 33: /* lblstmt: b labels stmt  */
#line 130 "src/cgram.y"
                                { }
#line 1702 "y.tab.c"
    break;

  case 34: /* labels: ID ':'  */
#line 133 "src/cgram.y"
                                { labeldcl((yyvsp[-1].str_ptr)); }
#line 1708 "y.tab.c"
    break;

  case 35: /* labels: labels ID ':'  */
#line 134 "src/cgram.y"
                                { labeldcl((yyvsp[-1].str_ptr)); }
#line 1714 "y.tab.c"
    break;

  case 36: /* b: %empty  */
#line 137 "src/cgram.y"
                                { }
#line 1720 "y.tab.c"
    break;

  case 37: /* stmt: expr ';'  */
#line 141 "src/cgram.y"
                { }
#line 1726 "y.tab.c"
    break;

  case 38: /* stmt: IF '(' cexpr ')' m lblstmt m  */
#line 143 "src/cgram.y"
                { doif((yyvsp[-4].rec_ptr), (yyvsp[-2].bb_ptr), (yyvsp[0].bb_ptr)); }
#line 1732 "y.tab.c"
    break;

  case 39: /* stmt: IF '(' cexpr ')' m lblstmt ELSE n m lblstmt m  */
#line 145 "src/cgram.y"
                { doifelse((yyvsp[-8].rec_ptr), (yyvsp[-6].bb_ptr), (yyvsp[-3].rec_ptr), (yyvsp[-2].bb_ptr), (yyvsp[0].bb_ptr)); }
#line 1738 "y.tab.c"
    break;

  case 40: /* stmt: WHILE '(' m cexpr ')' m s lblstmt n m  */
#line 147 "src/cgram.y"
                { dowhile((yyvsp[-7].bb_ptr), (yyvsp[-6].rec_ptr), (yyvsp[-4].bb_ptr), (yyvsp[-1].rec_ptr), (yyvsp[0].bb_ptr)); }
#line 1744 "y.tab.c"
    break;

  case 41: /* stmt: DO m s lblstmt WHILE '(' m cexpr ')' ';' m  */
#line 149 "src/cgram.y"
                { dodo((yyvsp[-9].bb_ptr), (yyvsp[-4].bb_ptr), (yyvsp[-3].rec_ptr), (yyvsp[0].bb_ptr)); }
#line 1750 "y.tab.c"
    break;

  case 42: /* stmt: FOR '(' expro ';' m cexpro ';' m expro n ')' m s lblstmt n m  */
#line 151 "src/cgram.y"
                { dofor((yyvsp[-11].bb_ptr), (yyvsp[-10].rec_ptr), (yyvsp[-8].bb_ptr), (yyvsp[-6].rec_ptr), (yyvsp[-4].bb_ptr), (yyvsp[-1].rec_ptr), (yyvsp[0].bb_ptr)); }
#line 1756 "y.tab.c"
    break;

  case 43: /* stmt: CONTINUE ';'  */
#line 153 "src/cgram.y"
                { docontinue(); }
#line 1762 "y.tab.c"
    break;

  case 44: /* stmt: BREAK ';'  */
#line 155 "src/cgram.y"
                { dobreak(); }
#line 1768 "y.tab.c"
    break;

  case 45: /* stmt: GOTO ID ';'  */
#line 157 "src/cgram.y"
                { dogoto((yyvsp[-1].str_ptr)); }
#line 1774 "y.tab.c"
    break;

  case 46: /* stmt: RETURN ';'  */
#line 159 "src/cgram.y"
                { doret((struct sem_rec *) NULL); }
#line 1780 "y.tab.c"
    break;

  case 47: /* stmt: RETURN expr ';'  */
#line 161 "src/cgram.y"
                { doret((yyvsp[-1].rec_ptr)); }
#line 1786 "y.tab.c"
    break;

  case 48: /* stmt: block  */
#line 163 "src/cgram.y"
                { }
#line 1792 "y.tab.c"
    break;

  case 49: /* stmt: ';'  */
#line 165 "src/cgram.y"
                { }
#line 1798 "y.tab.c"
    break;

  case 50: /* cexpro: %empty  */
#line 168 "src/cgram.y"
                                { (yyval.rec_ptr) = node(NULL, NULL, 0, NULL, n(), NULL); }
#line 1804 "y.tab.c"
    break;

  case 51: /* cexpro: cexpr  */
#line 169 "src/cgram.y"
                                {}
#line 1810 "y.tab.c"
    break;

  case 52: /* cexpr: expr EQ expr  */
#line 172 "src/cgram.y"
                                { (yyval.rec_ptr) = rel((const char*) "==", (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1816 "y.tab.c"
    break;

  case 53: /* cexpr: expr NE expr  */
#line 173 "src/cgram.y"
                                { (yyval.rec_ptr) = rel((const char*) "!=", (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1822 "y.tab.c"
    break;

  case 54: /* cexpr: expr LE expr  */
#line 174 "src/cgram.y"
                                { (yyval.rec_ptr) = rel((const char*) "<=", (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1828 "y.tab.c"
    break;

  case 55: /* cexpr: expr GE expr  */
#line 175 "src/cgram.y"
                                { (yyval.rec_ptr) = rel((const char*) ">=", (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1834 "y.tab.c"
    break;

  case 56: /* cexpr: expr LT expr  */
#line 176 "src/cgram.y"
                                { (yyval.rec_ptr) = rel((const char*) "<",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1840 "y.tab.c"
    break;

  case 57: /* cexpr: expr GT expr  */
#line 177 "src/cgram.y"
                                { (yyval.rec_ptr) = rel((const char*) ">",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1846 "y.tab.c"
    break;

  case 58: /* cexpr: cexpr AND m cexpr  */
#line 178 "src/cgram.y"
                                { (yyval.rec_ptr) = ccand((yyvsp[-3].rec_ptr), (yyvsp[-1].bb_ptr), (yyvsp[0].rec_ptr)); }
#line 1852 "y.tab.c"
    break;

  case 59: /* cexpr: cexpr OR m cexpr  */
#line 179 "src/cgram.y"
                                { (yyval.rec_ptr) = ccor((yyvsp[-3].rec_ptr), (yyvsp[-1].bb_ptr), (yyvsp[0].rec_ptr)); }
#line 1858 "y.tab.c"
    break;

  case 60: /* cexpr: NOT cexpr  */
#line 180 "src/cgram.y"
                                { (yyval.rec_ptr) = ccnot((yyvsp[0].rec_ptr)); }
#line 1864 "y.tab.c"
    break;

  case 61: /* cexpr: expr  */
#line 181 "src/cgram.y"
                                { (yyval.rec_ptr) = ccexpr((yyvsp[0].rec_ptr)); }
#line 1870 "y.tab.c"
    break;

  case 62: /* cexpr: '(' cexpr ')'  */
#line 182 "src/cgram.y"
                                { (yyval.rec_ptr) = (yyvsp[-1].rec_ptr); }
#line 1876 "y.tab.c"
    break;

  case 63: /* exprs: expr  */
#line 185 "src/cgram.y"
                                { (yyval.rec_ptr) = (yyvsp[0].rec_ptr); }
#line 1882 "y.tab.c"
    break;

  case 64: /* exprs: exprs ',' expr  */
#line 186 "src/cgram.y"
                                { (yyval.rec_ptr) = exprs((yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1888 "y.tab.c"
    break;

  case 65: /* expro: %empty  */
#line 189 "src/cgram.y"
                                { }
#line 1894 "y.tab.c"
    break;

  case 66: /* expro: expr  */
#line 190 "src/cgram.y"
                                { }
#line 1900 "y.tab.c"
    break;

  case 67: /* expr: lval SET expr  */
#line 193 "src/cgram.y"
                                { (yyval.rec_ptr) = set((const char*) "",   (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1906 "y.tab.c"
    break;

  case 68: /* expr: lval SETOR expr  */
#line 194 "src/cgram.y"
                                { (yyval.rec_ptr) = set((const char*) "|",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1912 "y.tab.c"
    break;

  case 69: /* expr: lval SETXOR expr  */
#line 195 "src/cgram.y"
                                { (yyval.rec_ptr) = set((const char*) "^",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1918 "y.tab.c"
    break;

  case 70: /* expr: lval SETAND expr  */
#line 196 "src/cgram.y"
                                { (yyval.rec_ptr) = set((const char*) "&",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1924 "y.tab.c"
    break;

  case 71: /* expr: lval SETLSH expr  */
#line 197 "src/cgram.y"
                                { (yyval.rec_ptr) = set((const char*) "<<", (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1930 "y.tab.c"
    break;

  case 72: /* expr: lval SETRSH expr  */
#line 198 "src/cgram.y"
                                { (yyval.rec_ptr) = set((const char*) ">>", (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1936 "y.tab.c"
    break;

  case 73: /* expr: lval SETADD expr  */
#line 199 "src/cgram.y"
                                { (yyval.rec_ptr) = set((const char*) "+",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1942 "y.tab.c"
    break;

  case 74: /* expr: lval SETSUB expr  */
#line 200 "src/cgram.y"
                                { (yyval.rec_ptr) = set((const char*) "-",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1948 "y.tab.c"
    break;

  case 75: /* expr: lval SETMUL expr  */
#line 201 "src/cgram.y"
                                { (yyval.rec_ptr) = set((const char*) "*",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1954 "y.tab.c"
    break;

  case 76: /* expr: lval SETDIV expr  */
#line 202 "src/cgram.y"
                                { (yyval.rec_ptr) = set((const char*) "/",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1960 "y.tab.c"
    break;

  case 77: /* expr: lval SETMOD expr  */
#line 203 "src/cgram.y"
                                { (yyval.rec_ptr) = set((const char*) "%",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1966 "y.tab.c"
    break;

  case 78: /* expr: expr BITOR expr  */
#line 204 "src/cgram.y"
                                { (yyval.rec_ptr) = opb((const char*) "|",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1972 "y.tab.c"
    break;

  case 79: /* expr: expr BITXOR expr  */
#line 205 "src/cgram.y"
                                { (yyval.rec_ptr) = opb((const char*) "^",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1978 "y.tab.c"
    break;

  case 80: /* expr: expr BITAND expr  */
#line 206 "src/cgram.y"
                                { (yyval.rec_ptr) = opb((const char*) "&",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1984 "y.tab.c"
    break;

  case 81: /* expr: expr LSH expr  */
#line 207 "src/cgram.y"
                                { (yyval.rec_ptr) = opb((const char*) "<<", (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1990 "y.tab.c"
    break;

  case 82: /* expr: expr RSH expr  */
#line 208 "src/cgram.y"
                                { (yyval.rec_ptr) = opb((const char*) ">>", (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 1996 "y.tab.c"
    break;

  case 83: /* expr: expr ADD expr  */
#line 209 "src/cgram.y"
                                { (yyval.rec_ptr) = op2((const char*) "+",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 2002 "y.tab.c"
    break;

  case 84: /* expr: expr SUB expr  */
#line 210 "src/cgram.y"
                                { (yyval.rec_ptr) = op2((const char*) "-",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 2008 "y.tab.c"
    break;

  case 85: /* expr: expr MUL expr  */
#line 211 "src/cgram.y"
                                { (yyval.rec_ptr) = op2((const char*) "*",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 2014 "y.tab.c"
    break;

  case 86: /* expr: expr DIV expr  */
#line 212 "src/cgram.y"
                                { (yyval.rec_ptr) = op2((const char*) "/",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 2020 "y.tab.c"
    break;

  case 87: /* expr: expr MOD expr  */
#line 213 "src/cgram.y"
                                { (yyval.rec_ptr) = op2((const char*) "%",  (yyvsp[-2].rec_ptr), (yyvsp[0].rec_ptr)); }
#line 2026 "y.tab.c"
    break;

  case 88: /* expr: BITAND lval  */
#line 214 "src/cgram.y"
                                  { (yyval.rec_ptr) = (yyvsp[0].rec_ptr); }
#line 2032 "y.tab.c"
    break;

  case 89: /* expr: SUB expr  */
#line 215 "src/cgram.y"
                                { (yyval.rec_ptr) = op1((const char*) "-",      (yyvsp[0].rec_ptr)); }
#line 2038 "y.tab.c"
    break;

  case 90: /* expr: COM expr  */
#line 216 "src/cgram.y"
                                { (yyval.rec_ptr) = op1((const char*) "~",      (yyvsp[0].rec_ptr)); }
#line 2044 "y.tab.c"
    break;

  case 91: /* expr: lval  */
#line 217 "src/cgram.y"
                                { (yyval.rec_ptr) = op1((const char*) "@",      (yyvsp[0].rec_ptr)); }
#line 2050 "y.tab.c"
    break;

  case 92: /* expr: ID '(' ')'  */
#line 218 "src/cgram.y"
                                { (yyval.rec_ptr) = call((yyvsp[-2].str_ptr), (struct sem_rec *) NULL); }
#line 2056 "y.tab.c"
    break;

  case 93: /* expr: ID '(' exprs ')'  */
#line 219 "src/cgram.y"
                                { (yyval.rec_ptr) = call((yyvsp[-3].str_ptr), (yyvsp[-1].rec_ptr)); }
#line 2062 "y.tab.c"
    break;

  case 94: /* expr: '(' expr ')'  */
#line 220 "src/cgram.y"
                                { (yyval.rec_ptr) = (yyvsp[-1].rec_ptr); }
#line 2068 "y.tab.c"
    break;

  case 95: /* expr: CON  */
#line 221 "src/cgram.y"
                                { (yyval.rec_ptr) = con((yyvsp[0].str_ptr)); }
#line 2074 "y.tab.c"
    break;

  case 96: /* expr: STR  */
#line 222 "src/cgram.y"
                                { (yyval.rec_ptr) = genstring((yyvsp[0].str_ptr)); }
#line 2080 "y.tab.c"
    break;

  case 97: /* lval: ID  */
#line 225 "src/cgram.y"
                                { (yyval.rec_ptr) = id((yyvsp[0].str_ptr)); }
#line 2086 "y.tab.c"
    break;

  case 98: /* lval: ID '[' expr ']'  */
#line 226 "src/cgram.y"
                                { (yyval.rec_ptr) = indx(id((yyvsp[-3].str_ptr)), (yyvsp[-1].rec_ptr)); }
#line 2092 "y.tab.c"
    break;


#line 2096 "y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 228 "src/cgram.y"




