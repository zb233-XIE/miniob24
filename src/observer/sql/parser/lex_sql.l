%top{
/*
这里的代码会被复制到lex_sql.cpp的最开始位置
定义yy_size_t的原因是因为flex生成的代码，会使用yy_size_t与其他类型的数字
做比较，导致编译报警
*/
#define YY_TYPEDEF_YY_SIZE_T
typedef int yy_size_t;

/* 参考生成的lex_sql.cpp代码，这个宏定义会放在每次运行yylex()最开始的地方 */
#define YY_USER_INIT                                         \
  yycolumn = 0;

/* 参考生成的lex_sql.cpp代码，这个宏定义会放在解析一个token之后，也可以在网上找到大量的参考资料 */
/* 我们在这里设置当前解析的token的位置信息，这样在yacc中就可以使用这些信息了 */
#define YY_USER_ACTION                                       \
do {                                                         \
  yylloc->first_line   = yylloc->last_line = yylineno;       \
  yylloc->first_column = yycolumn;                           \
  yylloc->last_column  = yylloc->first_column + yyleng - 1;  \
  yycolumn += yyleng;                                        \
}                                                            \
while (0);

}

%{
#include<string.h>
#include<stdio.h>
#include<time.h>

/**
 * flex 代码包含三个部分，使用 %% 分隔
 * 第一个部分的代码是C代码，flex会原样复制到目标文件中
 * 第二个部分是规则部分，使用正则表达式定义一系列规则
 * 第三个部分还是C代码，flex 会复制此段代码
 */

#include "sql/parser/parse_defs.h"
#include "common/log/log.h"
#include "yacc_sql.hpp"

#ifndef register
#define register 
#endif // register

extern int atoi();
extern double atof();

#define RETURN_TOKEN(token) LOG_DEBUG("%s", #token);return token

int last_flag = 0;
%}

/* Prevent the need for linking with -lfl */
%option noyywrap
%option nounput
%option noinput
%option bison-bridge
%option reentrant
/* 不区分大小写 */
%option case-insensitive
%option bison-locations

WHITE_SAPCE      [\ \t\b\f]
DIGIT            [0-9]+

ID               [A-Za-z_]+[A-Za-z0-9_]*
DOT              \.
QUOTE            [\'\"]
%x STR

/* 规则匹配的优先级：*/
/* 1. 匹配的规则长的优先 */
/* 2. 写在最前面的优先 */

/* yylval 就可以认为是 yacc 中 %union 定义的结构体(union 结构) */
%%

{WHITE_SAPCE}                                        // ignore whitespace
\n                                                   ;

[\-]?{DIGIT}+                           {\
                                          if (last_flag && yytext[0] == '-') {\
                                            yyless(strlen(yytext) - 1);\
                                            last_flag = 0;\
                                            return '-';\
                                          } else {\
                                            last_flag=1;\
                                            yylval->number=atoi(yytext);\
                                            RETURN_TOKEN(NUMBER);\
                                          }\
                                        }
[\-]?{DIGIT}+{DOT}{DIGIT}+              yylval->floats=(float)(atof(yytext)); RETURN_TOKEN(FLOAT);
{QUOTE}{DIGIT}\-{DIGIT}+\-{DIGIT}+{QUOTE} yylval->date=strdup(yytext); RETURN_TOKEN(DATE);

";"                                     last_flag=0;RETURN_TOKEN(SEMICOLON);
{DOT}                                   RETURN_TOKEN(DOT);
EXIT                                    RETURN_TOKEN(EXIT);
HELP                                    RETURN_TOKEN(HELP);
DESC                                    RETURN_TOKEN(DESC);
CREATE                                  last_flag=0;RETURN_TOKEN(CREATE);
DROP                                    last_flag=0;RETURN_TOKEN(DROP);
TABLE                                   last_flag=0;RETURN_TOKEN(TABLE);
TABLES                                  last_flag=0;RETURN_TOKEN(TABLES);
INDEX                                   last_flag=0;RETURN_TOKEN(INDEX);
ON                                      last_flag=0;RETURN_TOKEN(ON);
SHOW                                    last_flag=0;RETURN_TOKEN(SHOW);
SYNC                                    last_flag=0;RETURN_TOKEN(SYNC);
SELECT                                  last_flag=0;RETURN_TOKEN(SELECT);
CALC                                    last_flag=0;RETURN_TOKEN(CALC);
FROM                                    last_flag=0;RETURN_TOKEN(FROM);
INNER                                   RETURN_TOKEN(INNER);
JOIN                                    RETURN_TOKEN(JOIN);
WHERE                                   last_flag=0;RETURN_TOKEN(WHERE);
AND                                     last_flag=0;RETURN_TOKEN(AND);
INSERT                                  last_flag=0;RETURN_TOKEN(INSERT);
INTO                                    last_flag=0;RETURN_TOKEN(INTO);
VALUES                                  last_flag=0;RETURN_TOKEN(VALUES);
DELETE                                  last_flag=0;RETURN_TOKEN(DELETE);
UPDATE                                  last_flag=0;RETURN_TOKEN(UPDATE);
SET                                     last_flag=0;RETURN_TOKEN(SET);
BEGIN                                   last_flag=0;RETURN_TOKEN(TRX_BEGIN);
COMMIT                                  last_flag=0;RETURN_TOKEN(TRX_COMMIT);
ROLLBACK                                last_flag=0;RETURN_TOKEN(TRX_ROLLBACK);
INT                                     RETURN_TOKEN(INT_T);
CHAR                                    RETURN_TOKEN(STRING_T);
FLOAT                                   RETURN_TOKEN(FLOAT_T);
DATE                                    RETURN_TOKEN(DATE_T);
VECTOR                                  RETURN_TOKEN(VECTOR_T);
LOAD                                    RETURN_TOKEN(LOAD);
DATA                                    RETURN_TOKEN(DATA);
INFILE                                  RETURN_TOKEN(INFILE);
EXPLAIN                                 RETURN_TOKEN(EXPLAIN);
GROUP                                   RETURN_TOKEN(GROUP);
BY                                      RETURN_TOKEN(BY);
STORAGE                                 RETURN_TOKEN(STORAGE);
FORMAT                                  RETURN_TOKEN(FORMAT);
MAX                                     RETURN_TOKEN(MAX);
MIN                                     RETURN_TOKEN(MIN);
COUNT                                   RETURN_TOKEN(COUNT);
AVG                                     RETURN_TOKEN(AVG);
SUM                                     RETURN_TOKEN(SUM);
LIKE                                    RETURN_TOKEN(LK);
"NOT LIKE"                              RETURN_TOKEN(NLK);
UNIQUE                                  RETURN_TOKEN(UNIQUE);
L2_DISTANCE                             RETURN_TOKEN(L2_DISTANCE);
COSINE_DISTANCE                         RETURN_TOKEN(COSINE_DISTANCE);
INNER_PRODUCT                           RETURN_TOKEN(INNER_PRODUCT);
{ID}                                    last_flag=1; yylval->string=strdup(yytext); RETURN_TOKEN(ID);
"("                                     RETURN_TOKEN(LBRACE);
")"                                     last_flag=1; RETURN_TOKEN(RBRACE);
"["                                     RETURN_TOKEN(LBRACKET);
"]"                                     RETURN_TOKEN(RBRACKET);

","                                     last_flag=0;RETURN_TOKEN(COMMA);
"="                                     last_flag=0;RETURN_TOKEN(EQ);
"<="                                    last_flag=0;RETURN_TOKEN(LE);
"<>"                                    last_flag=0;RETURN_TOKEN(NE);
"!="                                    last_flag=0;RETURN_TOKEN(NE);
"<"                                     last_flag=0;RETURN_TOKEN(LT);
">="                                    last_flag=0;RETURN_TOKEN(GE);
">"                                     last_flag=0;RETURN_TOKEN(GT);

"+" |
"-" |
"*" |
"/"                                     { last_flag=0; return yytext[0]; }
\"[^"]*\"                               yylval->string = strdup(yytext); RETURN_TOKEN(SSS);
'[^']*\'                                yylval->string = strdup(yytext); RETURN_TOKEN(SSS);

.                                       LOG_DEBUG("Unknown character [%c]",yytext[0]); return yytext[0];
%%

void scan_string(const char *str, yyscan_t scanner) {
  yy_switch_to_buffer(yy_scan_string(str, scanner), scanner);
}
