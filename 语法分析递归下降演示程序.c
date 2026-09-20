#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
/* ============================================================
 *  递归下降语法分析程序
 * 
 *  对算术表达式进行文法分析
 *
 *  文法（已消除左递归）：
 *      E  → T E'
 *      E' → + T E' | - T E' | ε
 *      T  → F T'
 *      T' → * F T' | / F T' | ε
 *      F  → (E) | id
 *
 *  运算符优先级（低 -> 高）：
 *      + -   <   * /   <   ( ) id
 *
 *  结合性：
 *      + - * /   均为左结合
 *
 *  支持的表达式示例：
 *      a + b
 *      a + b * c
 *      (a + b) * c
 *      a - b / c + d
 *      ((a))
 *
 *  程序结构：
 *      E()   —— 处理最低优先级 + -
 *      E1()  —— 对应 E'，处理 + - 或 ε
 *      T()   —— 处理 * /
 *      T1()  —— 对应 T'，处理 * / 或 ε
 *      F()   —— 处理原子 (E) 或 id
 *
 *  辅助函数：
 *      advance()        —— 跳过空白，定位到下一个有效字符
 *      match(char c)    —— 匹配并消耗字符 c，失败则报错
 *      error()          —— 打印错误位置并退出
 *
 *  输入：从标准输入读取一行表达式
 *  输出：分析过程 + 成功/失败提示
 * ============================================================ */

/* ========== 全局变量 ========== */
char input[256];        // 输入串
int  pos = 0;           // 当前字符位置

/* ========== 函数声明 ========== */
void E();
void E1();
void T();
void T1();
void F();
void advance();
void match(char expected);
void error();

/* ========== 错误处理 ========== */
void error() {
    printf("\n语法错误：位置 %d，字符 '%c'\n",
           pos, input[pos] ? input[pos] : 'EOF');
    exit(1);
}

/* ========== 读下一个字符 ========== */
/* 跳过空白，pos 指向下一个有效字符 */
void advance() {
    while (input[pos] == ' ' || input[pos] == '\t') {
        pos++;
    }
    /* 注意：不主动 pos++，让 match() 来消耗 */
}

/* ========== 匹配并消耗一个字符 ========== */
void match(char expected) {
    advance();                  // 先跳到有效字符
    if (input[pos] == expected) {
        pos++;                  // 消耗掉
        advance();              // 再跳到下一个有效字符
    } else {
        error();
    }
}

/* ========== E → T E' ========== */
void E() {
    printf("进入 E\n");
    T();
    E1();
}

/* ========== E' → + T E' | - T E' | ε ========== */
void E1() {
    printf("进入 E'\n");
    advance();                          // 跳到有效字符
    if (input[pos] == '+') {
        match('+');
        T();
        E1();                           // 递归处理后续
    } else if (input[pos] == '-') {
        match('-');
        T();
        E1();
    }
    /* else: ε，直接返回 */
}

/* ========== T → F T' ========== */
void T() {
    printf("进入 T\n");
    F();
    T1();
}

/* ========== T' → * F T' | / F T' | ε ========== */
void T1() {
    printf("进入 T'\n");
    advance();
    if (input[pos] == '*') {
        match('*');
        F();
        T1();
    } else if (input[pos] == '/') {
        match('/');
        F();
        T1();
    }
    /* else: ε */
}

/* ========== F → (E) | id ========== */
void F() {
    printf("进入 F\n");
    advance();

    if (isalpha(input[pos])) {
        /* 读标识符：字母开头，后跟字母数字 */
        printf("  读到 id: ");
        while (isalnum(input[pos])) {
            printf("%c", input[pos]);
            pos++;
        }
        printf("\n");
        advance();
    } else if (input[pos] == '(') {
        match('(');
        E();
        match(')');
    } else {
        error();
    }
}

/* ========== 主程序 ========== */
int main() {
    printf("Enter an arithmetic expression: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    /* 去掉换行符 */
    input[strcspn(input, "\n")] = '\0';

    pos = 0;
    advance();          // 初始化，跳到第一个有效字符

    E();                // 从开始符号 E 分析

    advance();
    if (input[pos] == '\0') {
        printf("\nnput successfully parsed\n");
    } else {
        error();
    }
    return 0;
}
