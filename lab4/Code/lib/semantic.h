#ifndef __SEMANTIC_H__
#define __SEMANTIC_H__
#include "nodes.h"

#define CHECK_TABLE  0  // 1: 输出符号表调试信息

// 符号表大小
int symbTableSize;
int funcTableSize;

SymbNode *symbTable;
FuncNode *funcTable;

// `INDEXED` ARRAIES
SymbNode **symb_table;
FuncNode **func_table;

// 二分查找获取变量表项
SymbNode* getSymb(char* name) {
    int left = 0, right = symbTableSize - 1, mid;
    while (left <= right) {
        mid = (left + right) / 2;
        if (strcmp(symb_table[mid]->name, name) < 0)
            left = mid + 1;
        else if (strcmp(symb_table[mid]->name, name) > 0)
            right = mid - 1;
        else
            return symb_table[mid];
    }
    return NULL;
}
// 二分查找获取函数表项
FuncNode* getFunc(char* name) {
    int left = 0, right = funcTableSize - 1, mid;
    while (left <= right) {
        mid = (left + right) / 2;
        if (strcmp(func_table[mid]->name, name) < 0)
            left = mid + 1;
        else if (strcmp(func_table[mid]->name, name) > 0)
            right = mid - 1;
        else
            return func_table[mid];
    }
    return NULL;
}

// 二分查找获取变量表项中所在位置
// ADDED IN LAB3
int getSymbIndex(char* name) {
    int left = 0, right = symbTableSize - 1, mid;
    while (left <= right) {
        mid = (left + right) / 2;
        if (strcmp(symb_table[mid]->name, name) < 0)
            left = mid + 1;
        else if (strcmp(symb_table[mid]->name, name) > 0)
            right = mid - 1;
        else
            return mid;
    }
    return -1;
}
// 二分查找获取函数表项中所在位置
// ADDED IN LAB3
int getFuncIndex(char* name) {
    int left = 0, right = funcTableSize - 1, mid;
    while (left <= right) {
        mid = (left + right) / 2;
        if (strcmp(func_table[mid]->name, name) < 0)
            left = mid + 1;
        else if (strcmp(func_table[mid]->name, name) > 0)
            right = mid - 1;
        else
            return mid;
    }
    return -1;
}

char* newstr(char* other) {
    char* str = (char *)malloc(sizeof(char) * strlen(other));
    strcpy(str, other);
    return str;
}

// 检查结点是否为自定义`EMPTY`结点
bool isemp(LevelNode* node) {
    return !node || !strcmp(node->msg, "EMPTY");
}

// 检查`ExpType`是否报错
bool iserr(ExpType et) {
    return et.lr == ErrTyp;
}

// 对 `VarDec/Tag`: `->ID: name` -> `"name"`
// `Lab-3 ADDED`: 对`ID`本身, 直接返回对应`ID`字符
char* getID(LevelNode* vardec) {
    while (vardec->childhead)       // Lab-3 ADDED
        vardec = vardec->childhead; // Lab-3 ADDED
    return vardec->msg + 4;
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
void handle_ExtDefList(LevelNode *);

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
    "\"[]\" used on non-array variable.",
    "\"()\" used on non-function variable.",
    "Non-integer used in \"[]\".",
    "Dot \".\" used on non-struct variable.",
    "Accessing an undefined field in a struct.",
    "Duplicate or initialized field name in a struct.",
    "Struct name conflicts.",
    "Using an undefined struct to define a variable."
};
int semErrNum = 0;

void semerror(int errno, int lineno) {
    semErrNum++;
    fprintf(stderr, "Error type %d at Line %d:  %s\n", errno, lineno, semErrInfos[errno]);
}

#endif