#ifndef __IR_H__
#define __IR_H__
#include "nodes.h"

// -------- #include "semantic.h" --------
extern int symbTableSize;
extern int funcTableSize;
extern SymbNode** symb_table;
SymbNode* getSymb(char *);
FuncNode* getFunc(char *);
int getSymbIndex(char *);
int getFuncIndex(char *);
char* getID(LevelNode *);
char* getINT(LevelNode *);
bool isemp(LevelNode *);
ExpType handle_Exp(LevelNode *);
// -------- #include "semantic.h" --------

#define GT ">"
#define LT "<"
#define EQ "=="
#define GE ">="
#define LE "<="
#define NE "!="

Operand UNDEF;
IRNode *entry;

IRNode *struct_id;  // 解决结构体中数组问题：指向结构体成员`id`取值那一行

int cnt_VAR;
int cnt_TEMP;
int cnt_LABEL;

int *table_VAR;     // 记录`符号表下标 - VAR_NO`的映射, `VAR_NO > 0`
int *table_FUNC;    // 记录`函数表下标 - FUNC_NO`的映射, `FUNC_NO > 0`
int *VarIsParam;    // true if: `VAR[i]`为函数参数

// Initialize the Map Tables, with the default `0`
void initVarFuncTable() {
    table_VAR  = (int *)malloc(sizeof(int) * symbTableSize);
    table_FUNC = (int *)malloc(sizeof(int) * funcTableSize);
    VarIsParam = (int *)malloc(sizeof(int) * symbTableSize);
    memset(table_VAR , 0, sizeof(int) * symbTableSize);
    memset(table_FUNC, 0, sizeof(int) * funcTableSize);
    memset(VarIsParam, 0, sizeof(int) * symbTableSize);
}

// Initialize the Entry of the Double-linked-list
void initEntryIRNode() {
    cnt_VAR = cnt_TEMP = cnt_LABEL = 1;
    entry = (IRNode *)malloc(sizeof(IRNode));
    entry->gramm = _NOP;
    entry->next = entry->prev = entry;
}

void addIRNode(IRNode* irnode) {
    IRNode* tail = entry->prev;
    entry->prev = irnode;
    tail->next = irnode;
    irnode->next = entry;
    irnode->prev = tail;
}

// `"INT: x"` -> `x`, 获取`INT`节点中的整型常量
int getVINT(LevelNode* INT) {
    char* constr = INT->msg + 5;
    return atoi(constr);
}
// `"FLOAT: x"` -> `x`, 获取`FLOAT`节点中的浮点型常量
float getVFLO(LevelNode* INT) {
    char* constr = INT->msg + 7;
    return atof(constr);
}

// `"RELOP: <="` -> `"<="` -> `LE`
char* getRELOP(LevelNode* RELOP) {
    char* relop = (char *)malloc(sizeof(char) * 2);
    strcpy(relop, RELOP->msg + 7);
    return relop;
}

// 对一个变量类型，求所占用的空间
int getSizeOf(Type typ) {
    int ssz;
    SymbNode* sm;
    switch (typ.type) {
    case _INT:
    case _FLOAT:
        return 4;
    case _ARRAY:
        return getSizeOf(*typ.value.Array.arrayElem) * typ.value.Array.arraySize;
    case _STRUCT:
        return getSizeOf(typ.value.Struct->dType);
    case _STRUCT_TYPE:
        sm = typ.value.StructMember;
        ssz = 0;
        while (sm) {
            ssz += getSizeOf(sm->dType);
            sm = sm->next;
        }
        return ssz;
    }
    return 0;
}

// `VAR是否为函数参数
bool isparam(Operand var) {
    return var.vtype == _VAR && VarIsParam[var.value.vint];
}

// 是否为`UNDEF`变量
bool isundef(Operand opd) {
    return opd.prefix == UNDEF.prefix && opd.vtype == UNDEF.vtype \
        && opd.value.vint == UNDEF.value.vint;
}

IRNode* mkNOP() {
    IRNode* res = (IRNode *)malloc(sizeof(IRNode));
    res->gramm = _NOP;
    return res;
}

void transl_Cond(LevelNode *, Operand, Operand);
Operand transl_Exp(LevelNode *, Operand);
Operand transl_Args(LevelNode *, bool);
void transl_Stmt(LevelNode *);
void transl_StmtList(LevelNode *);

Operand transl_VarDec(LevelNode *, bool);
void transl_Dec(LevelNode *);
void transl_DecList(LevelNode *);

void transl_Def(LevelNode *);
void transl_DefList(LevelNode *);
void transl_FunDec(LevelNode *);
void transl_VarList(LevelNode *);
void transl_ParamDec(LevelNode *);
void transl_CompSt(LevelNode *);
void transl_ExtDef(LevelNode *);
void transl_ExtDefList(LevelNode *);


#define NEW_OPERAND_METHOD(VTYPE) \
    Operand new##VTYPE(int no) {  \
        Operand res;  \
        res.vtype = _##VTYPE;  \
        res.prefix = _NOTHING; \
        res.value.vint = no;  \
        return res;    \
    }
#define GEN_INTERCODE_METHOD_1op(OPRT)  \
    InterCode gen##OPRT(Operand lvar, Operand rop) {    \
        InterCode res;    \
        res.oprt = _##OPRT;    \
        res.oprds.sinopr.lvar = lvar;  \
        res.oprds.sinopr.rop = rop;    \
        return res;    \
    }
#define GEN_INTERCODE_METHOD_2op(OPRT) \
    InterCode gen##OPRT(Operand lvar, Operand op1, Operand op2) {  \
        InterCode res;    \
        res.oprt = _##OPRT;   \
        res.oprds.binopr.lvar = lvar;  \
        res.oprds.binopr.op1 = op1;    \
        res.oprds.binopr.op2 = op2;    \
        return res;    \
    }
#define MK_IRNODE_METHOD_1op(GRAMM) \
    IRNode* mk##GRAMM(Operand x) {  \
        IRNode* res = (IRNode *)malloc(sizeof(IRNode)); \
        res->gramm = _##GRAMM;    \
        res->detail.ioprds.x = x;   \
        return res; \
    }

#endif