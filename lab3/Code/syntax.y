%{
#include <stdio.h>    
#include "lex.yy.c"

void yyerror(const char *msg) {
    if (yylloc.first_line == errorline)  return ;
    errorline = yylloc.first_line;
    // fprintf(stderr, "Error type B at line %d, column %d:  %s\n", \
    //     yylloc.first_line, yylloc.first_column, msg);
    fprintf(stderr, "Error type B at Line %d:  %s\n", yylloc.first_line, msg);
}

// 语法树结点定义
struct levelNode {
    char* msg;
    int line;
    char* typ;
    struct levelNode* childhead, *childtail;
    struct levelNode* next;
}* root;

int errorline = 0;

// Create a new levelNode (Type == "NON_TERMINAL" / "TOKEN")
struct levelNode* createNode(char* msg, int line, char* typ) {
    struct levelNode* newNode = (struct levelNode* )malloc(sizeof(struct levelNode));
    newNode->msg = strdup(msg);
    newNode->line = line;
    newNode->typ = strdup(typ);
    newNode->childhead = NULL; newNode->next = NULL;
    newNode->childtail = newNode->childhead;
    return newNode;
}

// Add a child to a levelNode
void addChild(struct levelNode* parent, struct levelNode* child) {
    if (parent->childtail)
        parent->childtail->next = child;
    else
        parent->childhead = child;
    parent->childtail = child;
}

// Int to String
char* itos(int i) {
    char* res = (char *)malloc(sizeof(char) * 20);
    sprintf(res, "%d", i);
    return res;
}

// 结点为语法单元，打印该语法单元的名称以及行号
char* makeSynMsg(char* msg, int line) {
    char* res = (char *)malloc(sizeof(char) * (3 + strlen(itos(line))));
    strcat(res, msg);
    strcat(res, " (");
    strcat(res, itos(line));
    strcat(res, ")");
    return res;
}

void printNodeMsg(int level, char* msg) {
    for (int i = 0; i < level; i++) 
        printf("  ");
    printf("%s\n", msg);
}

void recurPrintSynTree(struct levelNode* root, int level) {
    struct levelNode* curr = root;
    while (curr) {
        if (strcmp(curr->msg, "EMPTY")) {
            if (strcmp(curr->typ, "TOKEN"))
                printNodeMsg(level, makeSynMsg(curr->msg, curr->line));
            else
                printNodeMsg(level, curr->msg);
            recurPrintSynTree(curr->childhead, level + 1);
        }
        curr = curr->next;
    }
}
%}

%define parse.error verbose
%locations

/* declared tokens */
%union {
    struct levelNode* Node;
}
%token<Node> INT FLOAT ID TYPE
%token<Node> COMMA SEMI ASSIGN RELOP LP RP LB RB LC RC
%token<Node> OR AND ADD SUB MUL DIV NOT DOT
%token<Node> STRUCT RETURN IF ELSE WHILE

%type<Node> Program ExtDefList ExtDef ExtDecList
%type<Node> Specifier StructSpecifier OptTag Tag
%type<Node> VarDec FunDec VarList ParamDec
%type<Node> CompSt StmtList Stmt
%type<Node> DefList Def DecList Dec
%type<Node> Exp Args

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%right ASSIGN                 // =
%left OR                      // ||
%left AND                     // &&
%left RELOP                   // > < >= <= == !=
%left ADD SUB                 // + -
%left MUL DIV                 // * /
%right NOT                    // ! 
%left LP RP LB RB LC RC DOT   // ()[]{} .

%%
// High-level Definition
// 全局变量声明  函数定义
Program:  ExtDefList {      // 整个程序
        struct levelNode* newNode = createNode("Program", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        $$ = newNode;
        root = $$;
    }
    ;
ExtDefList:  {              // 很多个全局变量定义
        struct levelNode* newNode = createNode("EMPTY", 0, "EMPTY");
        $$ = newNode;
    }
    | ExtDef ExtDefList {   // int g1, g2; float m;...
        struct levelNode* newNode = createNode("ExtDefList", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        $$ = newNode;
    }
    ;
ExtDef:  Specifier ExtDecList SEMI { // 全局变量定义：int g1, g2;
        struct levelNode* newNode = createNode("ExtDef", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        $$ = newNode;
    }
    | Specifier SEMI  {              // 结构体定义：/struct {...}/ ;/
        struct levelNode* newNode = createNode("ExtDef", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        $$ = newNode;
    }
    | Specifier FunDec CompSt {     // 函数定义：int/ main()/ {...}/
        struct levelNode* newNode = createNode("ExtDef", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        $$ = newNode;
    }
    | Specifier error CompSt {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        $$ = newNode;
        // printf("Specifier e CompSt -> ExtDef\n");
    }
    | error FunDec CompSt {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        $$ = newNode;
    }
    | Specifier FunDec error {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        $$ = newNode;
    }
    | Specifier ExtDecList error {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        $$ = newNode;
    }
    | error SEMI {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        $$ = newNode;
    }
    ;
ExtDecList:  VarDec {           // 一个变量或多个变量用","连接
        struct levelNode* newNode = createNode("ExtDecList", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        $$ = newNode;
    }
    | VarDec COMMA ExtDecList { // a, A[3], b,...
        struct levelNode* newNode = createNode("ExtDecList", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        $$ = newNode;
    }
    | VarDec error COMMA ExtDecList {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        $$ = newNode;
    }
    ;

//   Specifier
// 类型  结构体类型
Specifier:  TYPE {      // int float
        struct levelNode* newNode = createNode("Specifier", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        $$ = newNode;
    }
    | StructSpecifier { // 结构体类型
        struct levelNode* newNode = createNode("Specifier", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        $$ = newNode;
    }
    ;
StructSpecifier:  STRUCT OptTag LC DefList RC { // struct Complex(可无) { int real, image; }
        struct levelNode* newNode = createNode("StructSpecifier", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        addChild(newNode, $4);
        addChild(newNode, $5);
        $$ = newNode;
    }
    | STRUCT Tag {  // struct name
        struct levelNode* newNode = createNode("StructSpecifier", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        $$ = newNode;
    }
    | STRUCT error {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        $$ = newNode;
    }
    | STRUCT error LC DefList RC {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        $$ = newNode;
    }
    | STRUCT OptTag LC error RC {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        $$ = newNode;
    }
    ;
OptTag:  {   // 可有可无的结构体名
        struct levelNode* newNode = createNode("EMPTY", 0, "EMPTY");
        $$ = newNode;
    }
    | ID {
        struct levelNode* newNode = createNode("OptTag", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        $$ = newNode;
    }
    ;
Tag:  ID {   // 结构体名
        struct levelNode* newNode = createNode("Tag", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        $$ = newNode;
    }
    ;

//    Declarators
// 变量声明  函数声明
VarDec:  ID {            // a
        struct levelNode* newNode = createNode("VarDec", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        $$ = newNode;
    }
    | VarDec LB INT RB { // A[3]
        struct levelNode* newNode = createNode("VarDec", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        addChild(newNode, $4);
        $$ = newNode;
    }
    | VarDec LB error RB {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        $$ = newNode;
        // printf("e RB -> VarDec\n");
    }
    ;
FunDec:  ID LP VarList RP { // func(int x, float y[3],...), 内为VarList
        struct levelNode* newNode = createNode("FunDec", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        addChild(newNode, $4);
        $$ = newNode;
    }
    | ID LP RP {             // func()
        struct levelNode* newNode = createNode("FunDec", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        $$ = newNode;
    }
    | ID LP error RP {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        $$ = newNode;
        // printf("e RP -> FunDec\n");
    }
    ;
VarList:  ParamDec COMMA VarList {  // int a, b, c
        struct levelNode* newNode = createNode("VarList", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        $$ = newNode;
    }
    | ParamDec {                    // int a
        struct levelNode* newNode = createNode("VarList", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        $$ = newNode;
    }
    ;
ParamDec:  Specifier VarDec {       // 类型+VarDec, int a  int A[10]
        struct levelNode* newNode = createNode("ParamDec", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        $$ = newNode;
    }
    ;

// Statements
//  语句块
CompSt:  LC DefList StmtList RC {   // 大括号语句块, { 开头定义，之后使用 }
        struct levelNode* newNode = createNode("CompSt", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        addChild(newNode, $4);
        $$ = newNode;
    }
    | LC error RC {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        $$ = newNode;
    }
    ;
StmtList:  { // 多个Stmt的连接, Stmt为一条语句
        struct levelNode* newNode = createNode("EMPTY", 0, "EMPTY");
        $$ = newNode;
    }
    | Stmt StmtList {
        struct levelNode* newNode = createNode("StmtList", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        $$ = newNode;
    }
    ;
Stmt:  Exp SEMI {               // i + 1; a && b;
        struct levelNode* newNode = createNode("Stmt", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        $$ = newNode;
    }
    | CompSt {                  // 另一个语句块
        struct levelNode* newNode = createNode("Stmt", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        $$ = newNode;
    }
    | RETURN Exp SEMI {         // return 0;
        struct levelNode* newNode = createNode("Stmt", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        $$ = newNode;
    }
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE { // if (...) ...
        struct levelNode* newNode = createNode("Stmt", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        addChild(newNode, $4);
        addChild(newNode, $5);
        $$ = newNode;
    }
    | IF LP Exp RP Stmt ELSE Stmt {             // if (...) ... else ...
        struct levelNode* newNode = createNode("Stmt", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        addChild(newNode, $4);
        addChild(newNode, $5);
        addChild(newNode, $6);
        addChild(newNode, $7);
        $$ = newNode;
    }
    | WHILE LP Exp RP Stmt {    // while (...) ...
        struct levelNode* newNode = createNode("Stmt", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        addChild(newNode, $4);
        addChild(newNode, $5);
        $$ = newNode;
    }
    | error SEMI {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        $$ = newNode;
        // printf("e SEMI -> Stmt\n");
    }
    | IF LP error RP Stmt ELSE Stmt {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        $$ = newNode;
    }
    | IF LP error RP Stmt %prec LOWER_THAN_ELSE {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        $$ = newNode;
    }
    | error LP Exp RP {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        $$ = newNode;
    }
    | WHILE LP error RP {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        $$ = newNode;
    }
    ;

// Local Definitions
//   局部变量的定义
DefList:  {  // 多个Def的连接, Def为一个定义语句
        struct levelNode* newNode = createNode("EMPTY", 0, "EMPTY");
        $$ = newNode;
    }
    | Def DefList {
        struct levelNode* newNode = createNode("DefList", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        $$ = newNode;
    }
    ;
Def:  Specifier DecList SEMI {   // int a, b = 3, C[4]; struct {..} A[3], B;
        struct levelNode* newNode = createNode("Def", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        $$ = newNode;
    }
    | error SEMI {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        $$ = newNode;
    }
    ;
DecList:  Dec {         // 一个Dec  b = 3
        struct levelNode* newNode = createNode("DecList", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        $$ = newNode;
    }
    | Dec COMMA DecList { // 多个Dec通过","连接  a, b = 3, C[4]
        struct levelNode* newNode = createNode("DecList", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        $$ = newNode;
    }
    | Dec error DecList {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        $$ = newNode;
    }
    | error COMMA DecList {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        $$ = newNode;
    }
    ;
Dec:  VarDec {            // a  A[3]
        struct levelNode* newNode = createNode("Dec", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        $$ = newNode;
    }
    | VarDec ASSIGN Exp { // a = 10
        struct levelNode* newNode = createNode("Dec", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        $$ = newNode;
    }
    | VarDec ASSIGN error {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        $$ = newNode;
    }
    | error Exp {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        $$ = newNode;
    }
    ;

// Expretion
Exp:  Exp ASSIGN Exp {
        struct levelNode* newNode = createNode("Exp", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        $$ = newNode;
    }
    | Exp AND Exp  {
        struct levelNode* newNode = createNode("Exp", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        $$ = newNode;
    }
    | Exp OR Exp {
        struct levelNode* newNode = createNode("Exp", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        $$ = newNode;
    } 
    | Exp RELOP Exp {
        struct levelNode* newNode = createNode("Exp", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        $$ = newNode;
    }
    | Exp ADD Exp {
        struct levelNode* newNode = createNode("Exp", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        $$ = newNode;
    }
    | Exp SUB Exp {
        struct levelNode* newNode = createNode("Exp", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        $$ = newNode;
    }
    | Exp MUL Exp {
        struct levelNode* newNode = createNode("Exp", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        $$ = newNode;
    }
    | Exp DIV Exp {
        struct levelNode* newNode = createNode("Exp", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        $$ = newNode;
    }
    | SUB Exp {
        struct levelNode* newNode = createNode("Exp", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        $$ = newNode;
    }
    | NOT Exp {
        struct levelNode* newNode = createNode("Exp", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        $$ = newNode;
    }
    | LP Exp RP {
        struct levelNode* newNode = createNode("Exp", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        $$ = newNode;
    }
    | ID LP Args RP {
        struct levelNode* newNode = createNode("Exp", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        addChild(newNode, $4);
        $$ = newNode;
    }
    | ID LP RP {
        struct levelNode* newNode = createNode("Exp", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        $$ = newNode;
    }
    | Exp LB Exp RB {
        struct levelNode* newNode = createNode("Exp", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        addChild(newNode, $4);
        $$ = newNode;
    }
    | Exp DOT ID {
        struct levelNode* newNode = createNode("Exp", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        $$ = newNode;
    }
    | ID {
        struct levelNode* newNode = createNode("Exp", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        $$ = newNode;
    }
    | INT {
        struct levelNode* newNode = createNode("Exp", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        $$ = newNode;
    }
    | FLOAT {
        struct levelNode* newNode = createNode("Exp", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        $$ = newNode;
    }
    | ID LP error RP {
        errorline = yylloc.first_line;
        struct levelNode* newNode = createNode("ERROR", 0, "ERROR");
        $$ = newNode;
    }
    ;
Args:  Exp COMMA Args {
        struct levelNode* newNode = createNode("Args", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        addChild(newNode, $2);
        addChild(newNode, $3);
        $$ = newNode;
    }
    | Exp {
        struct levelNode* newNode = createNode("Args", $1->line, "NON_TERMINAL");
        addChild(newNode, $1);
        $$ = newNode;
    }
    ;
%%