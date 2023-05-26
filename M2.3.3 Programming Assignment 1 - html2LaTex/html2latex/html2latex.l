%{

/**************************************************************************
* Name:         Giuseppe Schintu
* Course:       COSC 561
* Assignment:   M2.3.3 Programming Assignment 1: html2LaTex
*************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int list_type;

%}

%option       noyywrap nounput yylineno
%x            COMMENT PARA PRE OL UL

%%

"<h1>"[^<]*"</h1>" {
    /**************************************************************************
     * Matched an HTML H1 header so print it out as a LateX section title.
     * The beginning and ending tags need to be stripped off before the
     * title can be formatted in LateX.
     *************************************************************************/
    yytext[yyleng-5] = 0;
    printf( "\\section{%s}\n", yytext+4 );
}

"<h2>"[^<]*"</h2>" {
    /**************************************************************************
     * Matched an HTML H2 header so print it out as a LateX section title.
     * The beginning and ending tags need to be stripped off before the
     * title can be formatted in LateX.
     *************************************************************************/
    yytext[yyleng-5] = 0;
    printf( "\\subsection{%s}\n", yytext+4 );
}

"<h3>"[^<]*"</h3>" {
    /**************************************************************************
     * Matched an HTML H3 header so print it out as a LateX subsubsection title.
     * The beginning and ending tags need to be stripped off before the
     * title can be formatted in LateX.
     *************************************************************************/
    yytext[yyleng-5] = 0;
    printf( "\\subsubsection{%s}\n", yytext+4 );
}

"<pre>"[^<]*"</pre>" {
    /**************************************************************************
     * Matched an HTML <pre> so print it out as a LateX subsubsection title.
     * The beginning and ending tags need to be stripped off before the
     * title can be formatted in LateX.
     *************************************************************************/
    yytext[yyleng-6] = 0;
    printf( "\n\\begin{verbatim}\n{%s}\n\\end{verbatim}\n", yytext+5 );
}

"<p>" {
    /**************************************************************************
     * Matched an HTML <p> so print it out as a LateX paragraph title.
     * Since it can hold nested values, we are also starting the initial condition (IC).
     * Starting an IC of PARA allows us to integrate and write easier-to-read rules 
     *************************************************************************/
    printf( "\n\\begin{paragraph}\n");
    BEGIN PARA;
}

<PARA>"</p>" {
    printf( "\n\\end{paragraph}\n");
    BEGIN(INITIAL);
}

"<ol>" {
    /**************************************************************************
     * Matched an HTML <ol> so print it out as a LateX enumerate title.
     * Since it can hold nested values, we are also starting the initial condition (IC).
     * Starting an IC of OL allows us to integrate and write easier-to-read rules 
     *************************************************************************/    
    printf( "\\begin{enumerate}");
    BEGIN OL;   
}

<OL>"</ol>" {
    /**************************************************************************
     * We need to capture this state.
     * We are not outputting the html tag closure as it is not needed in this case
     * However, we need a closure for the enumerate LaTeX structure
     * We are also resetting the IC of OL, as there may be more of this cases
     *************************************************************************/
    printf( "\\end{enumerate}");
    BEGIN(INITIAL);
}

<PARA>"<ol>" {
    /**************************************************************************
     * Matched an HTML <ol> inside an html <p> tag so print it out as a LateX enumerate tag.
     * We dont need to start a condition state as this is a unique rule/state.
     *************************************************************************/     
    printf( "\\begin{enumerate}"); 
}

<PARA>"</ol>" {
    /**************************************************************************
     * Matched an HTML </ol> inside an html <p> tag so print it out as a LateX enumerate closure tag.
     * We dont need to reset a condition state as this is a unique rule/state.
     *************************************************************************/
    printf( "\\end{enumerate}");
}

"<ul>" {
    /**************************************************************************
     * Matched an HTML <ul> so print it out as a LateX itemize title.
     * Since it can hold nested values, we are also starting the initial condition (IC).
     * Starting an IC of UL allows us to integrate and write easier-to-read rules 
     *************************************************************************/ 
    printf( "\\begin{itemize}");
    BEGIN UL;   
}

<UL>"</ul>" {
    /**************************************************************************
     * We need to capture this state.
     * We are not outputting the html tag closure as it is not needed in this case
     * However, we need a closure for the enumerate LaTeX structure
     * We are also resetting the IC of UL, as there may be more of this cases
     *************************************************************************/    
    printf( "\\end{itemize}");
    BEGIN(INITIAL);
}

<PARA>"<ul>" {
    /**************************************************************************
     * Matched an HTML <ul> inside an html <p> tag so print it out as a LateX itemize tag.
     * We dont need to start a condition state as this is a unique rule/state.
     *************************************************************************/      
    printf( "\\begin{itemize}"); 
}

<PARA>"</ul>" {
    /**************************************************************************
     * Matched an HTML </ul> inside an html <p> tag so print it out as a LateX itemize closure tag.
     * We dont need to reset a condition state as this is a unique rule/state.
     *************************************************************************/    
    printf( "\\end{itemize}");
}


<PARA,UL,OL>"<li>" {
    /**************************************************************************
     * Matched an HTML <ul> inside an html <li> tag so print it out as a LateX itemize tag.
     *************************************************************************/ 
    printf( "\\item ");
}

<PARA,UL,OL>"</li>" {
    /**** We need to capture this state, so we can control the output.
    ***** We are not outputting the html tag closure as it is not needed in this case
    ****/
}

<PARA,UL,OL>"<small>"[^<]*"</small>" {
    /**************************************************************************
    * At this point, all the initial conditions that we need have been created.
    * all we need to do is create a rule for all nested html tags.
    * same for all the other html tags <big, b, i,strong, etc...>
    *************************************************************************/
    /*** Parse <small> ***/
    yytext[yyleng-8] = 0;
    printf( "{\\scriptsize %s}", yytext+7 );
}

<PARA,UL,OL>"<big>"[^<]*"</big>" {
    /*** Parse <big> ***/

    yytext[yyleng-6] = 0;
    printf( "{\\Large %s}", yytext+5 );

}

<PARA,UL,OL>"<b>"[^<]*"</b>" {
    /*** Parse <b> ***/

    yytext[yyleng-4] = 0;
    printf( "\\textbf{%s}", yytext+3 );

}

<PARA,UL,OL>"<i>"[^<]*"</i>" {
    /*** Parse <i> ***/

    yytext[yyleng-4] = 0;
    printf( "\\textit{%s}", yytext+3 );

}

<PARA,UL,OL>"<strong>"[^<]*"</strong>" {
    /*** Parse <strong> ***/

    yytext[yyleng-9] = 0;
    printf( "\\textmd{%s}", yytext+8 );

}
<PARA,UL,OL>"<em>"[^<]*"</em>" {
    /*** Parse <em> ***/

    yytext[yyleng-5] = 0;
    printf( "\\emph{%s}", yytext+4 );

}
<PARA,UL,OL>"<sup>"[^<]*"</sup>" {
    /*** Parse <sup> ***/

    yytext[yyleng-6] = 0;
    printf( "\\textsuperscript{%s}", yytext+5 );

}
<PARA,UL,OL>"<sub>"[^<]*"</sub>" {
    /*** Parse <sub> ***/

    yytext[yyleng-6] = 0;
    printf( "\\textsubscript{%s}", yytext+5 );

}

"<!--" {
    /**************************************************************************
     * Matched an HTML comment so print it out as a LateX comment. The
     * beginning and ending tags are stripped off before the LateX comment
     * is emitted.
     *************************************************************************/
    printf( "%% " );
    BEGIN COMMENT;
}

[ \t\n\r]+ {
    /**************************************************************************
     * Matched some whitespace that is not inside of an HTML tag. We
     * just ignore the whitespace.
     *************************************************************************/
}

. {
    /**************************************************************************
     * Matched something that we did not expect to see. Issue an error and
     * exit the program with a failure code.
     *************************************************************************/
    fprintf( stderr, "Unexpected input at line %d: '%s'\n", yylineno, yytext );
    exit( 1 );
}

<COMMENT>"-->" {
    /**************************************************************************
     * Matched an HTML end comment while parsing an HTML comment. Print out
     * a new line and resume normal parsing.
     *************************************************************************/
    printf( "\n" );
    BEGIN 0;
}

<COMMENT>[\n](\r)? {
    /**************************************************************************
     * Matched a newline while parsing an HTML comment. Print out a new
     * line making sure to mark the next line as a comment as well.
     *************************************************************************/
    printf( "\n%% " );
}

<COMMENT>[ \t] {
    /**************************************************************************
     * Matched some white space while parsing an HTML comment. Print out
     * the white space as is.
     *************************************************************************/
    printf( "%s", yytext );
}

<COMMENT>. {
    /**************************************************************************
     * Matched any other text while parsing an HTML comment. Print out
     * the text as is.
     *************************************************************************/
    printf( "%s", yytext );
}

%%

/**************************************************************************
 * The main function for the HTML to LateX converter. Here we do three
 * things:
 *  1. Print out the LateX document header.
 *  2. Invoke the lexer to print out the LateX document
 *  3. Print out the LateX footer.
 *************************************************************************/
int main( int argc, const char *argv[] ) {

    /**************************************************************************
     * Once compiled, we can pass an html file to be processed if needed 
     * (e.g.: html2latex test.html)
     *************************************************************************/    
	if(argc > 1)
	{
		FILE *fp = fopen(argv[1], "r");
		if(fp)
			yyin = fp;
	}

    printf( "\\documentclass[12pt]{article}\n" );
    printf( "\\usepackage{fixltx2e}\n" );
    printf( "\n" );
    printf( "\\setlength{\\parindent}{0.0in}\n" );
    printf( "\\setlength{\\parskip}{0.125in}\n" );
    printf( "\n\n" );   
    printf( "\\begin{document}\n" );
    yylex();
    printf( "\\end{document}\n" );
    return 0;
}
