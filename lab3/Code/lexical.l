%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "syntax.tab.h"

int yycolumn = 1;
int errorline;

#define YY_USER_ACTION \
    yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; \
    yylloc.last_column = yycolumn + yyleng - 1; \
    yycolumn += yyleng;
    
struct levelNode* createNode(char *, int, char *);

// 结点为特殊词法单元，则只打印该词法单元的名称 + 值，无需打印行号
char* makeLexMsg(char* prestr, char* yytext) {
    int pLen = strlen(prestr), fLen = strlen(yytext);
    char* msg = (char *)malloc( sizeof(char) * (pLen + fLen) );
    strncat(msg, prestr, pLen);
    strncat(msg, yytext, fLen);
    return msg;
}
%}

DEC_INT   0|[1-9][0-9]*
HEX_INT   0[Xx][0-9a-fA-F]+
OCT_INT   0[0-7]+
INT       ({DEC_INT})

COM_FLOAT ({DEC_INT}\.[0-9]*)
FLOAT     ({COM_FLOAT})

ID        [_a-zA-Z][_a-zA-Z0-9]*

SEMI      ;
COMMA     ,
ASSIGN    =
RELOP     >|<|>=|<=|==|!=
PLUS      \+
MINUS     -
STAR      \*
DIV       \/
AND       &&
OR        \|\|
DOT       \.
NOT       !
TYPE      int|float
LP        \(
RP        \)
LB        \[
RB        \]
LC        \{
RC        \}
STRUCT    struct
RETURN    return
IF        if
ELSE      else
WHILE     while

%%
{ASSIGN} {
    yylval.Node = createNode("ASSIGNOP", yylineno, "TOKEN");
    return ASSIGN;
}
{PLUS} {
    yylval.Node = createNode("PLUS", yylineno, "TOKEN");
    return ADD;
}
{MINUS} {
    yylval.Node = createNode("MINUS", yylineno, "TOKEN");
    return SUB;
}
{STAR} {
    yylval.Node = createNode("STAR", yylineno, "TOKEN");
    return MUL;
}
"//" {
    char c = input();
    while (c != '\n' && c != '\0')
        c = input();
    yylineno++;
}
"/*" {
    char c1 = input();
    char c2 = input();
    while (!(c1 == '*' && c2 == '/') && c2 != '\0') {
        if (c1 == '\n') yylineno++;
        c1 = c2;
        c2 = input();
    }
}

{DIV} {
    yylval.Node = createNode("DIV", yylineno, "TOKEN");
    return DIV;
}
{AND} {
    yylval.Node = createNode("AND", yylineno, "TOKEN");
    return AND;
}
{OR} {
    yylval.Node = createNode("OR", yylineno, "TOKEN");
    return OR;
}
{LP} {
    yylval.Node = createNode("LP", yylineno, "TOKEN");
    return LP;
}
{RP} {
    yylval.Node = createNode("RP", yylineno, "TOKEN");
    return RP;
}
{LB} {
    yylval.Node = createNode("LB", yylineno, "TOKEN");
    return LB;
}
{RB} {
    yylval.Node = createNode("RB", yylineno, "TOKEN");
    return RB;
}
{LC} {
    yylval.Node = createNode("LC", yylineno, "TOKEN");
    return LC;
}
{RC} {
    yylval.Node = createNode("RC", yylineno, "TOKEN");
    return RC;
}
{COMMA} {
    yylval.Node = createNode("COMMA", yylineno, "TOKEN");
    return COMMA;
}
{SEMI} {
    yylval.Node = createNode("SEMI", yylineno, "TOKEN");
    return SEMI;
}
{DOT} {
    yylval.Node = createNode("DOT", yylineno, "TOKEN");
    return DOT;
}
{NOT} {
    yylval.Node = createNode("NOT", yylineno, "TOKEN");
    return NOT;
}
{STRUCT} {
    yylval.Node = createNode("STRUCT", yylineno, "TOKEN");
    return STRUCT;
}
{RETURN} {
    yylval.Node = createNode("RETURN", yylineno, "TOKEN");
    return RETURN;
}
{IF} {
    yylval.Node = createNode("IF", yylineno, "TOKEN");
    return IF;
}
{ELSE} {
    yylval.Node = createNode("ELSE", yylineno, "TOKEN");
    return ELSE;
}
{WHILE} {
    yylval.Node = createNode("WHILE", yylineno, "TOKEN");
    return WHILE;
}

{RELOP} {
    char* msg = makeLexMsg("RELOP: ", yytext);          // ADDED IN LAB-3
    yylval.Node = createNode(msg, yylineno, "TOKEN");   // ADDED IN LAB-3
    // yylval.Node = createNode("RELOP", yylineno, "TOKEN");
    return RELOP;
}

{TYPE} {
    char* msg = makeLexMsg("TYPE: ", yytext);
    yylval.Node = createNode(msg, yylineno, "TOKEN");
    return TYPE;
}


{INT} {
    char* msg = makeLexMsg("INT: ", yytext);
    yylval.Node = createNode(msg, yylineno, "TOKEN");
    return INT;
}
{FLOAT} {
    char flt[32];
    char* endptr;
    sprintf(flt, "%.6f", strtof(yytext, &endptr));
    char* msg = makeLexMsg("FLOAT: ", flt);
    yylval.Node = createNode(msg, yylineno, "TOKEN");
    return FLOAT;
}
{ID} {
    char* msg = makeLexMsg("ID: ", yytext);
    yylval.Node = createNode(msg, yylineno, "TOKEN");
    return ID;
}

" " {;}
"\t" {;}
"\r" {
    yycolumn = 1;
}
"\n" {
    yylineno++;
    yycolumn = 1;
}
. {
    if (errorline != yylineno) {
        errorline = yylineno;
        // fprintf(stderr, "Error type A at line %d, column %d:  %s\n", \
        //     yylloc.first_line, yylloc.first_column, "lexical error");
        fprintf(stderr, "Error type A at Line %d:  Mysterious character '%s'\n", yylloc.first_line, yytext);
    }
}

%%