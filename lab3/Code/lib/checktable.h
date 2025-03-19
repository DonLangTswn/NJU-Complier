#ifndef __CHECKTABLE_H__
#define __CHECKTABLE_H__

#include "nodes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printSpace(int level, char* msg) {
    for (int i = 0; i < level; i++) 
        printf("\t");
    printf("%s\n", msg);
}

void print_SymbNode(SymbNode* cchar, int level);
void print_FuncNode(FuncNode* cfunc, int level);

void print_Type(Type* ctype, int level) {
    if (!ctype) return;
    switch (ctype->type)
    {
    case 0:
        printSpace(level, "INT");
        break;
    case 1:
        printSpace(level, "FLOAT");
        break;
    case 2:
        printSpace(level, "STRUCT");
        print_SymbNode(ctype->value.Struct, level + 1);
        break;
    case 3:
        printSpace(level, "ARRAY");
        char* size_info = (char*)malloc(sizeof(char) * 12);
        sprintf(size_info, "size = %d", ctype->value.Array.arraySize);
        printSpace(level, size_info);
        printSpace(level, "Type:");
        print_Type(ctype->value.Array.arrayElem, level + 1);
        break;
    case 4:
        printSpace(level, "STRUCT_TYPE");
        printSpace(level, "Params:");
        print_SymbNode(ctype->value.StructMember, level + 1);
        break;
    default:
        printSpace(level, "ERROR");
        break;
    }
}

void print_SymbNode(SymbNode* cchar, int level) {
    if (!cchar) return;
    printSpace(level, "SymbNode:");
    char* name_info = (char*)malloc(sizeof(char) * 12);
    sprintf(name_info, "name = %s", cchar->name);
    printSpace(level, name_info);
    char* def_info = (char*)malloc(sizeof(char) * 12);
    sprintf(def_info, "def = %d", cchar->def);
    printSpace(level, def_info);
    printSpace(level, "Type:");
    print_Type( &(cchar->dType), level + 1);
    char* nxt_info = (char*)malloc(sizeof(char) * 12);
    if (cchar->next)
        sprintf(nxt_info, "Next: %s", cchar->next->name);
    else
        strcpy(nxt_info, "Next: null\n");
    printSpace(level, nxt_info);
    print_SymbNode(cchar->next, level + 1);
}

void print_FuncNode(FuncNode* cfunc, int level) {
    if (!cfunc) return;
    char* name_info = (char*)malloc(sizeof(char) * 12);
    sprintf(name_info, "name = %s", cfunc->name);
    printSpace(level, name_info);
    char* def_info = (char*)malloc(sizeof(char) * 12);
    sprintf(def_info, "def = %d", cfunc->def);
    printSpace(level, def_info);
    printSpace(level, "Type:");
    print_Type( &(cfunc->rType), level + 1);
    printSpace(level, "Params:");
    print_SymbNode(cfunc->params, level + 1);
    printf("\n");
    print_FuncNode(cfunc->next, level);
}

void check_SymbTable(SymbNode** ctable, int csize) {
    for (int i = 0; i < csize; i++) {
        print_SymbNode(ctable[i], 0);
    }
}

void check_FuncTable(FuncNode** ftable, int fsize) {
    for (int i = 0; i < fsize; i++) {
        print_FuncNode(ftable[i], 0);
    }
}

#endif