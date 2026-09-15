%{
#include <stdio.h>
#include <stdlib.h>
#include "token.h"
%}

%option noyywrap

DIGIT   [0-9]
LETTER  [a-zA-Z_]
ID      {LETTER}({LETTER}|{DIGIT})*
INT     {DIGIT}+
FLOAT   {DIGIT}+\.{DIGIT}+

%%

{INT}       { printf("<%d, %s>\n", num_INT, yytext); }
{FLOAT}     { printf("<%d, %s>\n", num_FLOAT, yytext); }

"int"       { printf("<%d, KEYWORD>\n", Y_INT); }
"float"     { printf("<%d, KEYWORD>\n", Y_FLOAT); }
"return"    { printf("<%d, KEYWORD>\n", Y_RETURN); }

{ID}        { printf("<%d, %s>\n", Y_ID, yytext); }

"+"         { printf("<%d, OPERATOR>\n", Y_ADD); }
"="         { printf("<%d, OPERATOR>\n", Y_ASSIGN); }

"("         { printf("<%d, SYMBOL>\n", Y_LPAR); }
")"         { printf("<%d, SYMBOL>\n", Y_RPAR); }
"{"         { printf("<%d, SYMBOL>\n", Y_LBRACKET); }
"}"         { printf("<%d, SYMBOL>\n", Y_RBRACKET); }
";"         { printf("<%d, SYMBOL>\n", Y_SEMICOLON); }

[ \t\n]+    ;

%%

int main(int argc, char *argv[]) {
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
        if (!yyin) { perror("fopen"); return 1; }
    }
    yylex();
    if (argc == 2) fclose(yyin);
    return 0;
}
