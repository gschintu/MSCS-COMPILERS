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
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
  int num;
  char *string;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
