%{

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
 * The principle with logical expressions is to breakdown productions into in its simplest form considering the basic arithmetic
 * components and basic laws of algebra and the fact that yacc is a bottom-up parser.
 * A [factor] production can allow a [value] (number or a [a-z] named variable) in parentheses or not, potentially with - + ~ in front.
 * A [term] production allows a factor or another term with its possible operators, * / %
 * An [arith_expr] production allows a [term] or a sequence of terms with additions and subtractions.
 * [shift_expression], [xor_expression], [and_expression] are logical(bitwise) expressions that can result from a combination of arithmetical expressions and logical expressions.
*************************************************************/

#include <stdio.h>
#include <limits.h>

int yylex();
void yyerror(char *);
int alph[26];
void dump_value();
void clear_value();

%}

%union {
  int num;
  char *string;
}

%token <num> NUM
%token <num> VAR
%token <num> SEMICOLON
%token <string> DUMP
%token <string> CLEAR
%token <num> ADD_ASSIGN
%token <num> SUB_ASSIGN MULT_ASSIGN DIVD_ASSIGN REM_ASSIGN LEFT_SHIFT_ASSIGN RIGHT_SHIFT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%token <num> BITWISE_OR BITWISE_XOR BITWISE_AND LEFT_SHIFT RIGHT_SHIFT ADD SUB MULT DIVD REM NEGAT BITWISE_NOT
%token <num> OPEN_PAREN CLOSE_PAREN

%type <num> expr
%type <num> logical_expression
%type <num> and_expression
%type <num> xor_expression
%type <num> shift_expression
%type <num> arith_expr
%type <num> term
%type <num> factor
%type <num> primary
%type <num> value


%%
commands:
	|	commands command
	;

command	:	expr SEMICOLON    { printf("%d\n", $1); }
      |   	DUMP SEMICOLON    { dump_value(); }
      |   	CLEAR SEMICOLON   { clear_value(); }
	;


expr : 
    VAR '=' expr                        { alph[$1] = $3; $$ = alph[$1]; }
    | 	VAR ADD_ASSIGN expr  		    { if ($1 <= INT_MAX - $3) { alph[$1] += $3; $$ = alph[$1];} else { printf("overflow\n"); $$ = $1; } }
    | 	VAR SUB_ASSIGN expr  		    {if ($1 > INT_MIN + $3) { alph[$1] -= $3; $$ = alph[$1];} else { printf("overflow\n"); $$ = $1; } }  
	| 	VAR MULT_ASSIGN expr  		    { if($3 == 0) $$ = 0; else if ($1 <= INT_MAX / $3) {alph[$1] *= $3; $$ = alph[$1];} else { printf("overflow\n"); $$ = $1; } }
    | 	VAR DIVD_ASSIGN expr  		    { if ($3 != 0) {alph[$1] /= $3; $$ = alph[$1];} else { printf("dividebyzero\n"); $$ = $1; } }
    | 	VAR REM_ASSIGN expr  		    { if ($3 != 0) {alph[$1] %= $3; $$ = alph[$1];} else { printf("dividebyzero\n"); $$ = $1; } }
    | 	VAR LEFT_SHIFT_ASSIGN expr  	{ alph[$1] <<= $3; $$ = alph[$1]; }
    | 	VAR RIGHT_SHIFT_ASSIGN expr  	{ alph[$1] >>= $3; $$ = alph[$1]; }
    | 	VAR AND_ASSIGN expr  		    { alph[$1] &= $3; $$ = alph[$1]; }
    | 	VAR XOR_ASSIGN expr  		    { alph[$1] ^= $3; $$ = alph[$1]; }
	|	VAR OR_ASSIGN expr  		    { alph[$1] |= $3; $$ = alph[$1]; }
    | logical_expression                { $$ = $1; }
    ;

logical_expression
    : and_expression
    | logical_expression BITWISE_OR and_expression { $$ = $1 | $3; }
    ;

and_expression
    : xor_expression
    | and_expression BITWISE_AND xor_expression { $$ = $1; }
    ;

xor_expression
    : shift_expression
    | xor_expression BITWISE_XOR shift_expression { $$ = $1 ^ $3; }
    ;

shift_expression
    : arith_expr
    | shift_expression LEFT_SHIFT arith_expr { $$ = $1 << $3; }
    | shift_expression RIGHT_SHIFT arith_expr { $$ = $1 >> $3; }
    ;

arith_expr
    : term
    | arith_expr ADD term { if ($1 <= INT_MAX - $3) $$ = $1 + $3; else printf("overflow\n"); }
    | arith_expr SUB term { $$ = $1 - $3; }
    ;

term
    : factor
    | term MULT factor { if ($1 <= INT_MAX / $3) $$ = $1 * $3; else printf("overflow\n"); }
    | term DIVD factor { if ($3 != 0) $$ = $1 / $3; else printf("dividebyzero\n"); }
    | term REM factor { if ($3 != 0) $$ = $1 % $3; else printf("dividebyzero\n"); }
    ;

factor
    : primary
    | NEGAT primary { $$ = -$2; }
    | ADD primary { $$ = $2; }
    | BITWISE_NOT primary { $$ = ~ $2; }
    ;

primary
    : value
    | OPEN_PAREN logical_expression CLOSE_PAREN { $$ = $2; }
    ;

value
    : NUM { $$ = $1; }
    | VAR { $$ = alph[$1]; }
    ;   

%%

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

