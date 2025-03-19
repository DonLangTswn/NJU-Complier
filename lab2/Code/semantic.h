#ifndef __LIB_H__
#define __LIB_H__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "nodes.h"

#define CHECK_TABLE  0  // 1: 输出符号表调试信息

typedef struct _SymbNode SymbNode;
typedef struct _FuncNode FuncNode;
typedef struct _Type Type;
typedef struct _ExpType ExpType;

// 符号类型
struct _Type {
    enum {
        _INT, 
        _FLOAT, 
        _STRUCT,
        _ARRAY,
        _STRUCT_TYPE,
    } type;

    union {
        int Int;            // INT
        float Float;        // FLOAT
        SymbNode* Struct;   // STRUCT
        struct {            // ARRAY
            Type* arrayElem;
            int arraySize;
        } Array;
        SymbNode* StructMember;   // STRUCT_TYPE;
    } value;
};

// 变量表结点结构体
struct _SymbNode {
    char* name;
    short def;  // 定义次数
    Type dType;
    SymbNode* next;
};

// 函数表结点结构体
struct _FuncNode {
    char* name;
    short def;  // 定义次数
    Type rType;
    SymbNode* params;   // 参数列表
    FuncNode* next;
};

// Exp表达式属性
struct _ExpType {
    enum {
        ErrTyp, // 错误类型
        LValue, // 左值亦可作右值
        RValue
    } lr;
    Type etype;
    ExpType* next;
};


char* newstr(char* other) {
    char* str = (char *)malloc(sizeof(char) * strlen(other));
    strcpy(str, other);
    return str;
}

// 检查结点是否为自定义`EMPTY`结点
bool isemp(LevelNode* node) {
    if(!node || !strcmp(node->msg, "EMPTY"))
        return true;
    else
        return false;
}

bool iserr(ExpType et) {
    return et.lr == ErrTyp;
}

// 对 VarDec/Tag: "->ID: name" -> "name"
char* getID(LevelNode* vardec) {
    return vardec->childhead->msg + 4;
}
// 对 VarDec: "VarDec-> VarDec [ INT ]" -> "INT"
char* getINT(LevelNode* vardec) {
    return vardec->childhead->next->next->msg + 5;
}

// 检查两个结构体类型的本体是否相同
bool check_Struct(SymbNode *, SymbNode *);
// 检查两个类型是否相同
bool check_Type(Type* one, Type* other) {
    SymbNode *ap, *bp;
    if (one->type == other->type) {
        switch (one->type) {
        case _INT:
        case _FLOAT:
            return true;
        case _STRUCT:
            return check_Struct(one->value.Struct, other->value.Struct);
        case _ARRAY:
            return check_Type(one->value.Array.arrayElem, other->value.Array.arrayElem);
            // return one->value.Array.arraySize == other->value.Array.arraySize \
            //     && check_Type(one->value.Array.arrayElem, other->value.Array.arrayElem);
        case _STRUCT_TYPE:
            ap = one->value.StructMember;
            bp = other->value.StructMember;
            while (ap || bp) {
                if (!(ap && bp) || !check_Type(&ap->dType, &bp->dType))
                    return false;
                ap = ap->next; bp = bp->next;
            }
            return true;
        }
    }
    return false;
}
bool check_Struct(SymbNode* one, SymbNode* other) {
    return check_Type(&one->dType, &other->dType);
}

ExpType handle_Exp(LevelNode *);
void handle_Stmt(LevelNode *, Type *);
void handle_StmtList(LevelNode *, Type *);
Type* handle_Specifier(LevelNode *);
SymbNode* handle_StructSpecifier(LevelNode *);
char* handle_OptTag(LevelNode *);
SymbNode* handle_VarDec(LevelNode *, Type *, bool);
SymbNode* handle_Dec(LevelNode *, Type *, bool);
SymbNode* handle_DecList(LevelNode *, Type *, bool);
SymbNode* handle_Def(LevelNode *, bool);
SymbNode* handle_DefList(LevelNode *, bool);
void handle_FunDec(LevelNode *, Type *);
SymbNode* handle_VarList(LevelNode *);
SymbNode* handle_ParamDec(LevelNode *);
void handle_CompSt(LevelNode *, Type *);
void handle_ExtDecList(LevelNode *, Type *);
void handle_ExtDef(LevelNode *);

const char* semErrInfos[18] = {
    "0",
    "Variable used before definition.",
    "Function called before definition.",
    "Variable redefined or conflicts with struct.",
    "Function redefined.",
    "Type mismatch on either side of \"=\".",
    "RValue on the left side of \"=\".",
    "Operand or operator type mismatch.",
    "Return type mismatch.",
    "Function arguments mismatch.",
    "[] used on non-array variable.",
    "() used on non-function variable.",
    "Non-integer used in [].",
    "Dot . used on non-struct variable.",
    "Accessing an undefined field in a struct.",
    "Duplicate or initialized field name in a struct.",
    "Struct name conflicts.",
    "Using an undefined struct to define a variable."
};

void semerror(int errno, int lineno) {
    fprintf(stderr, "Error type %d at Line %d:  %s\n", errno, lineno, semErrInfos[errno]);
}

#endif