/*实验一 词法分析器tokenizer的实现*/
/*宏名定义部分*/

%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "token.h"

char *yylval_str;   // 用于存放标识符名字
double yylval_num;  // 用于存放数字值
%}

%option noyywrap  // 该指令意为不处理多个文件。yywrap是用来处理多个文件的

DIGIT   [0-9]
LETTER  [A-Za-z_]
ID      {LETTER}({LETTER}|{DIGIT})*
INT     {DIGIT}+
FLOAT   {DIGIT}+\.{DIGIT}+

/*规则定义部分*/
%%
"int"       { return Y_INT;}
"if"        { return Y_IF; }
"else"      { return Y_ELSE;}
"void"	    { return Y_VOID;}
"const" 	{ return Y_CONST;}
"while"	    { return Y_WHILE;}
"break" 	{ return Y_BREAK;}
"continue"	{ return Y_CONTINUE;}
"return"	{ return Y_RETURN;}

"+"         { return Y_ADD;}
"-"	        { return Y_SUB;}
"*"     	{ return Y_MUL;}
"/"	        { return Y_DIV;}
"%"	        { return Y_MODULO;}
"<="	    { return Y_LESSEQ;}
"<"         { return Y_LESS;}
">="		{ return Y_GREATEQ;}
">"         { return Y_GREAT;}
"!"         { return Y_NOT;}
"!="	    { return Y_NOTEQ;}
"=="	    { return Y_EQ;}	
"&&"	    { return Y_AND;}
"||"	    { return Y_OR;}
"="         { return Y_ASSIGN;}
"("	        { return Y_LPAR;}
")"     	{ return Y_RPAR;}
"{"	        { return Y_LBRACKET;}
"}"	        { return Y_RBRACKET;}
"["	        { return Y_LSQUARE;}
"]"     	{ return Y_RSQUARE;}
","	        { return Y_COMMA;}
";"	        { return Y_SEMICOLON;}

{ID}        { yylval_str = strdup(yytext); return Y_ID; }  // strdup()是字符串复制函数
{FLOAT}     { yylval_num = atof(yytext); return num_FLOAT; } // atof()是字符串转浮点数函数
{INT}       { yylval_num = atof(yytext); return num_INT; }

[ \t\n]     ;
.           { printf("Invalid letter: %s\n", yytext); }
%%

/*主函数部分*/
int main(void) {
    int token;
    while ((token = yylex()) != 0) {
        if (token == Y_ID) {
            printf("<%d, %s>\n", token, yylval_str);
        } else if (token == num_INT) {
            printf("<%d, %d>\n", token, (int)yylval_num);
        } else if (token == num_FLOAT) {
            printf("<%d, %g>\n", token, yylval_num); 
            // %g 是 printf 家族里一个很特别的格式说明符，专门用来智能地打印浮点数
        } else if (token >= Y_INT && token <= Y_RETURN) {
            printf("<%d, KEYWORD>\n", token);
        } else if (token >= Y_ADD && token <= Y_ASSIGN) {
            printf("<%d, OPERATOR>\n", token);
        } else {
            printf("<%d, SYMBOL>\n", token);
        }
    }
    return 0;
}
