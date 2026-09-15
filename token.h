#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>  /* 必须包含，因为下面用到了 FILE 类型 */

/* 定义词法分析标记符 */
enum yytokentype {
	num_INT = 258,
	num_FLOAT = 259,

	Y_ID = 260,

	Y_INT = 261,
	Y_VOID = 262,
	Y_CONST = 263,
	Y_IF = 264,
	Y_ELSE = 265,
	Y_WHILE = 266,
	Y_BREAK = 267,
	Y_CONTINUE = 268,
	Y_RETURN = 269,

	Y_ADD = 270,
	Y_SUB = 271,
	Y_MUL = 272,
	Y_DIV = 273,
	Y_MODULO = 274,
	Y_LESS = 275,
	Y_LESSEQ = 276,
	Y_GREAT = 277,
	Y_GREATEQ = 278,
	Y_NOTEQ = 279,
	Y_EQ = 280,
	Y_NOT = 281,
	Y_AND = 282,
	Y_OR = 283,
	Y_ASSIGN = 284,

	Y_LPAR = 285,
	Y_RPAR = 286,
	Y_LBRACKET = 287,
	Y_RBRACKET = 288,
	Y_LSQUARE = 289,
	Y_RSQUARE = 290,
	Y_COMMA = 291,
	Y_SEMICOLON = 292,

	Y_FLOAT = 293
};
/* 声明外部变量 */
/* 注意：这里使用 extern，表示变量在别的地方(如 .l 或 .y 文件)定义 */
extern int yylval;
extern FILE *yyin; 

#endif /* TOKEN_H */
