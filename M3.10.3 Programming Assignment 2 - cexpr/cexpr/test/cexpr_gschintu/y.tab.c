/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20170709

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "ex.y"

/**************************************************************************
* Name:         Giuseppe Schintu
* Course:       COSC 561
* Assignment:   M3.10.3 Programming Assignment 2: cexpr
*************************************************************************/

/************************************************************
 * Set production rules [a-z] variables and for all the assignment (+-*%<<>>&^|=) cases.
 * Notice logical_expression will handle all logical and arithmetical expressions (a+b)/2+c+(d*e)...this includes bitwise operations as well.
*************************************************************/

/************************************************************
 * The principle with logical expressions is to breakdown productions into its simplest form considering the basic arithmetic
 * components and basic laws of algebra and the fact that yacc is a bottom-up parser.
 * A [factor] production can allow a [value] (number or a [a-z] named variable) in parentheses or not, potentially with - + ~ in front.
 * A [term] production allows a factor or another term with its possible operators, * / %
 * An [arith_expr] production allows a [term] or a sequence of terms with additions and subtractions.
 * [shift_expression], [xor_expression], [and_expression] are logical(bitwise) expressions that can result from a combination of arithmetical expressions 
 * and logical expressions.
*************************************************************/

#include <stdio.h>
#include <limits.h>

int yylex();
void yyerror(char *);
int alph[26];
void dump_value();
void clear_value();

#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#line 35 "ex.y"
typedef union {
  int num;
  char *string;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 65 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define NUM 257
#define VAR 258
#define SEMICOLON 259
#define DUMP 260
#define CLEAR 261
#define ADD_ASSIGN 262
#define SUB_ASSIGN 263
#define MULT_ASSIGN 264
#define DIVD_ASSIGN 265
#define REM_ASSIGN 266
#define LEFT_SHIFT_ASSIGN 267
#define RIGHT_SHIFT_ASSIGN 268
#define AND_ASSIGN 269
#define XOR_ASSIGN 270
#define OR_ASSIGN 271
#define BITWISE_OR 272
#define BITWISE_XOR 273
#define BITWISE_AND 274
#define LEFT_SHIFT 275
#define RIGHT_SHIFT 276
#define ADD 277
#define SUB 278
#define MULT 279
#define DIVD 280
#define REM 281
#define NEGAT 282
#define BITWISE_NOT 283
#define OPEN_PAREN 284
#define CLOSE_PAREN 285
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,   11,   11,   11,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    2,    2,    3,
    3,    4,    4,    5,    5,    5,    6,    6,    6,    7,
    7,    7,    7,    8,    8,    8,    8,    9,    9,   10,
   10,
};
static const YYINT yylen[] = {                            2,
    0,    2,    2,    2,    2,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    1,    1,    3,    1,
    3,    1,    3,    1,    3,    3,    1,    3,    3,    1,
    3,    3,    3,    1,    2,    2,    2,    1,    3,    1,
    1,
};
static const YYINT yydefred[] = {                         1,
    0,   40,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   30,   34,   38,    2,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    4,    5,   41,   36,   35,   37,    0,    3,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    7,
    8,    9,   10,   11,   12,   13,   14,   15,   16,    6,
   39,    0,    0,    0,    0,    0,    0,    0,   31,   32,
   33,
};
static const YYINT yydgoto[] = {                          1,
   10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
   20,
};
static const YYINT yysindex[] = {                         0,
 -256,    0,  -61, -239, -234, -251, -251, -251, -248, -228,
 -264, -263, -218, -261, -226, -262,    0,    0,    0,    0,
 -245, -245, -245, -245, -245, -245, -245, -245, -245, -245,
 -245,    0,    0,    0,    0,    0,    0, -269,    0, -248,
 -248, -248, -248, -248, -248, -248, -248, -248, -248,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -263, -218, -261, -226, -226, -262, -262,    0,    0,
    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0, -113,    0,    0,    0,    0,    0,    0,    0,
 -200, -130, -134, -154, -182, -229,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -127, -131, -137, -164, -159, -209, -189,    0,    0,
    0,
};
static const YYINT yygindex[] = {                         0,
  148,   51,   21,   30,   20,   10,   12,  -25,   34,    0,
    0,
};
#define YYTABLESIZE 210
static const YYINT yytable[] = {                         31,
    2,    3,   40,    4,    5,    2,   34,   40,    2,   34,
   41,    2,    3,   43,   44,   61,   47,   48,   49,   32,
    6,   69,   70,   71,   33,    7,    8,    9,    6,   27,
   39,    6,    9,    7,    8,    9,    7,    8,    9,   35,
   36,   37,   27,   27,   27,   27,   27,   27,   27,   28,
   45,   46,   65,   66,   42,   27,   67,   68,   17,   38,
   62,   64,   28,   28,   28,   28,   28,   28,   28,   29,
   63,    0,    0,    0,    0,   28,   24,    0,    0,    0,
    0,    0,   29,   29,   29,   29,   29,   29,   29,   24,
   24,   24,   24,   24,   25,   29,    0,    0,    0,   26,
    0,    0,   24,    0,   22,    0,    0,   25,   25,   25,
   25,   25,   26,   26,   26,   26,   26,   22,   22,   22,
   25,   23,    0,    0,   20,   26,    0,   21,   18,    0,
   22,   19,    0,    0,   23,   23,   23,   20,    0,   20,
   21,   18,   21,    0,   19,   41,    0,   23,    0,    0,
   20,    0,    0,   21,   18,    0,    0,   19,   41,   41,
   41,   41,   41,   41,   41,   41,   41,   41,   50,   51,
   52,   53,   54,   55,   56,   57,   58,   59,   60,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   21,   22,   23,   24,   25,   26,   27,   28,   29,   30,
};
static const YYINT yycheck[] = {                         61,
  257,  258,  272,  260,  261,  257,  258,  272,  257,  258,
  274,  257,  258,  275,  276,  285,  279,  280,  281,  259,
  277,   47,   48,   49,  259,  282,  283,  284,  277,  259,
  259,  277,  284,  282,  283,  284,  282,  283,  284,    6,
    7,    8,  272,  273,  274,  275,  276,  277,  278,  259,
  277,  278,   43,   44,  273,  285,   45,   46,  259,    9,
   40,   42,  272,  273,  274,  275,  276,  277,  278,  259,
   41,   -1,   -1,   -1,   -1,  285,  259,   -1,   -1,   -1,
   -1,   -1,  272,  273,  274,  275,  276,  277,  278,  272,
  273,  274,  275,  276,  259,  285,   -1,   -1,   -1,  259,
   -1,   -1,  285,   -1,  259,   -1,   -1,  272,  273,  274,
  275,  276,  272,  273,  274,  275,  276,  272,  273,  274,
  285,  259,   -1,   -1,  259,  285,   -1,  259,  259,   -1,
  285,  259,   -1,   -1,  272,  273,  274,  272,   -1,  274,
  272,  272,  274,   -1,  272,  259,   -1,  285,   -1,   -1,
  285,   -1,   -1,  285,  285,   -1,   -1,  285,  272,  273,
  274,  275,  276,  277,  278,  279,  280,  281,   21,   22,
   23,   24,   25,   26,   27,   28,   29,   30,   31,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  262,  263,  264,  265,  266,  267,  268,  269,  270,  271,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 285
#define YYUNDFTOKEN 299
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'='",0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"NUM","VAR","SEMICOLON",
"DUMP","CLEAR","ADD_ASSIGN","SUB_ASSIGN","MULT_ASSIGN","DIVD_ASSIGN",
"REM_ASSIGN","LEFT_SHIFT_ASSIGN","RIGHT_SHIFT_ASSIGN","AND_ASSIGN","XOR_ASSIGN",
"OR_ASSIGN","BITWISE_OR","BITWISE_XOR","BITWISE_AND","LEFT_SHIFT","RIGHT_SHIFT",
"ADD","SUB","MULT","DIVD","REM","NEGAT","BITWISE_NOT","OPEN_PAREN",
"CLOSE_PAREN",0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : commands",
"commands :",
"commands : commands command",
"command : expr SEMICOLON",
"command : DUMP SEMICOLON",
"command : CLEAR SEMICOLON",
"expr : VAR '=' expr",
"expr : VAR ADD_ASSIGN expr",
"expr : VAR SUB_ASSIGN expr",
"expr : VAR MULT_ASSIGN expr",
"expr : VAR DIVD_ASSIGN expr",
"expr : VAR REM_ASSIGN expr",
"expr : VAR LEFT_SHIFT_ASSIGN expr",
"expr : VAR RIGHT_SHIFT_ASSIGN expr",
"expr : VAR AND_ASSIGN expr",
"expr : VAR XOR_ASSIGN expr",
"expr : VAR OR_ASSIGN expr",
"expr : logical_expression",
"logical_expression : and_expression",
"logical_expression : logical_expression BITWISE_OR and_expression",
"and_expression : xor_expression",
"and_expression : and_expression BITWISE_AND xor_expression",
"xor_expression : shift_expression",
"xor_expression : xor_expression BITWISE_XOR shift_expression",
"shift_expression : arith_expr",
"shift_expression : shift_expression LEFT_SHIFT arith_expr",
"shift_expression : shift_expression RIGHT_SHIFT arith_expr",
"arith_expr : term",
"arith_expr : arith_expr ADD term",
"arith_expr : arith_expr SUB term",
"term : factor",
"term : term MULT factor",
"term : term DIVD factor",
"term : term REM factor",
"factor : primary",
"factor : NEGAT primary",
"factor : ADD primary",
"factor : BITWISE_NOT primary",
"primary : value",
"primary : OPEN_PAREN logical_expression CLOSE_PAREN",
"value : NUM",
"value : VAR",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 140 "ex.y"

void yyerror(char *s)
{
    fprintf(stderr, "%s\n", s);
}

void dump_value(){
    int i = 0;
    for (i = 0; i < 26; i++) {
        printf("%c: %d\n", (97+i), alph[i]);
    }
}

void clear_value(){
    int i;
    for (i = 0; i < 26; i++) {
        alph[i] = 0;
    }
}

int main()
{
   if (yyparse())
      printf("\nInvalid expression.\n");
   else
      printf("\nCalculator off.\n");
}

#line 360 "y.tab.c"

#if YYDEBUG
#include <stdio.h>	/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yym = 0;
    yyn = 0;
    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        yychar = YYLEX;
        if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if (((yyn = yysindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if (((yyn = yyrindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag != 0) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab; /* redundant goto avoids 'unused label' warning */
yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if (((yyn = yysindex[*yystack.s_mark]) != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym > 0)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);

    switch (yyn)
    {
case 3:
#line 67 "ex.y"
	{ printf("%d\n", yystack.l_mark[-1].num); }
break;
case 4:
#line 68 "ex.y"
	{ dump_value(); }
break;
case 5:
#line 69 "ex.y"
	{ clear_value(); }
break;
case 6:
#line 74 "ex.y"
	{ alph[yystack.l_mark[-2].num] = yystack.l_mark[0].num; yyval.num = alph[yystack.l_mark[-2].num]; }
break;
case 7:
#line 75 "ex.y"
	{ if (yystack.l_mark[-2].num <= INT_MAX - yystack.l_mark[0].num) { alph[yystack.l_mark[-2].num] += yystack.l_mark[0].num; yyval.num = alph[yystack.l_mark[-2].num];} else { printf("overflow\n"); yyval.num = yystack.l_mark[-2].num; } }
break;
case 8:
#line 76 "ex.y"
	{if (yystack.l_mark[-2].num > INT_MIN + yystack.l_mark[0].num) { alph[yystack.l_mark[-2].num] -= yystack.l_mark[0].num; yyval.num = alph[yystack.l_mark[-2].num];} else { printf("overflow\n"); yyval.num = yystack.l_mark[-2].num; } }
break;
case 9:
#line 77 "ex.y"
	{ if(yystack.l_mark[0].num == 0) yyval.num = 0; else if (yystack.l_mark[-2].num <= INT_MAX / yystack.l_mark[0].num) {alph[yystack.l_mark[-2].num] *= yystack.l_mark[0].num; yyval.num = alph[yystack.l_mark[-2].num];} else { printf("overflow\n"); yyval.num = yystack.l_mark[-2].num; } }
break;
case 10:
#line 78 "ex.y"
	{ if (yystack.l_mark[0].num != 0) {alph[yystack.l_mark[-2].num] /= yystack.l_mark[0].num; yyval.num = alph[yystack.l_mark[-2].num];} else { printf("dividebyzero\n"); yyval.num = yystack.l_mark[-2].num; } }
break;
case 11:
#line 79 "ex.y"
	{ if (yystack.l_mark[0].num != 0) {alph[yystack.l_mark[-2].num] %= yystack.l_mark[0].num; yyval.num = alph[yystack.l_mark[-2].num];} else { printf("dividebyzero\n"); yyval.num = yystack.l_mark[-2].num; } }
break;
case 12:
#line 80 "ex.y"
	{ alph[yystack.l_mark[-2].num] <<= yystack.l_mark[0].num; yyval.num = alph[yystack.l_mark[-2].num]; }
break;
case 13:
#line 81 "ex.y"
	{ alph[yystack.l_mark[-2].num] >>= yystack.l_mark[0].num; yyval.num = alph[yystack.l_mark[-2].num]; }
break;
case 14:
#line 82 "ex.y"
	{ alph[yystack.l_mark[-2].num] &= yystack.l_mark[0].num; yyval.num = alph[yystack.l_mark[-2].num]; }
break;
case 15:
#line 83 "ex.y"
	{ alph[yystack.l_mark[-2].num] ^= yystack.l_mark[0].num; yyval.num = alph[yystack.l_mark[-2].num]; }
break;
case 16:
#line 84 "ex.y"
	{ alph[yystack.l_mark[-2].num] |= yystack.l_mark[0].num; yyval.num = alph[yystack.l_mark[-2].num]; }
break;
case 17:
#line 85 "ex.y"
	{ yyval.num = yystack.l_mark[0].num; }
break;
case 19:
#line 90 "ex.y"
	{ yyval.num = yystack.l_mark[-2].num | yystack.l_mark[0].num; }
break;
case 21:
#line 95 "ex.y"
	{ yyval.num = yystack.l_mark[-2].num; }
break;
case 23:
#line 100 "ex.y"
	{ yyval.num = yystack.l_mark[-2].num ^ yystack.l_mark[0].num; }
break;
case 25:
#line 105 "ex.y"
	{ yyval.num = yystack.l_mark[-2].num << yystack.l_mark[0].num; }
break;
case 26:
#line 106 "ex.y"
	{ yyval.num = yystack.l_mark[-2].num >> yystack.l_mark[0].num; }
break;
case 28:
#line 111 "ex.y"
	{ if (yystack.l_mark[-2].num <= INT_MAX - yystack.l_mark[0].num) yyval.num = yystack.l_mark[-2].num + yystack.l_mark[0].num; else printf("overflow\n"); }
break;
case 29:
#line 112 "ex.y"
	{ yyval.num = yystack.l_mark[-2].num - yystack.l_mark[0].num; }
break;
case 31:
#line 117 "ex.y"
	{ if (yystack.l_mark[-2].num <= INT_MAX / yystack.l_mark[0].num) yyval.num = yystack.l_mark[-2].num * yystack.l_mark[0].num; else printf("overflow\n"); }
break;
case 32:
#line 118 "ex.y"
	{ if (yystack.l_mark[0].num != 0) yyval.num = yystack.l_mark[-2].num / yystack.l_mark[0].num; else printf("dividebyzero\n"); }
break;
case 33:
#line 119 "ex.y"
	{ if (yystack.l_mark[0].num != 0) yyval.num = yystack.l_mark[-2].num % yystack.l_mark[0].num; else printf("dividebyzero\n"); }
break;
case 35:
#line 124 "ex.y"
	{ yyval.num = -yystack.l_mark[0].num; }
break;
case 36:
#line 125 "ex.y"
	{ yyval.num = yystack.l_mark[0].num; }
break;
case 37:
#line 126 "ex.y"
	{ yyval.num = ~ yystack.l_mark[0].num; }
break;
case 39:
#line 131 "ex.y"
	{ yyval.num = yystack.l_mark[-1].num; }
break;
case 40:
#line 135 "ex.y"
	{ yyval.num = yystack.l_mark[0].num; }
break;
case 41:
#line 136 "ex.y"
	{ yyval.num = alph[yystack.l_mark[0].num]; }
break;
#line 683 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            yychar = YYLEX;
            if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if (((yyn = yygindex[yym]) != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
