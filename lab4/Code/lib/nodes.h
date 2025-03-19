#ifndef __NODES_H__
#define __NODES_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ------------------- DEBUG ----------------------
#define __DEBUG_MOD__  0    // Debug mode switch

#define MY_DEBUG \
    if( __DEBUG_MOD__ ) \
    fprintf(stderr, "[%s, line %d]:  OK here.\n", __FILE__, __LINE__);

#define DIY_DEBUG(info, format) \
    if( __DEBUG_MOD__ ) \
    fprintf(stderr, "[%s, line %d]:  "#info": "#format"\n", __FILE__, __LINE__, info);

// ----------------- Lab - 1 ----------------------

typedef struct levelNode LevelNode; 
// 语法树结点定义
struct levelNode {
    char* msg;
    int line;
    char* typ;
    struct levelNode* childhead, *childtail;
    struct levelNode* next;
};

// ----------------- Lab - 2 ----------------------

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
        SymbNode* StructMember;   // STRUCT_TYPE
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

// ----------------- Lab - 3 ----------------------

typedef struct _Operand Operand;
typedef struct _InterCode InterCode;
typedef struct _IRNode IRNode;

struct _Operand {
    enum {
        _UNDEF,
        _VAR,       // v: 源代码中命名过的变量
        _TEMP,      // t: 源代码中未命名，但是IR中需要临时使用的变量或地址
        _CONST_INT, // 常数，`value`即值
        _CONST_FLO,
        _FUNC,      // 函数: 用函数名表示
        _LABEL      // label: 跳转标签
    } vtype;
    enum {
        _VALUE,
        _ADDR
    } vstate;
    enum {
        _NOTHING,
        _GET_ADDR,  // &v
        _GET_VAL    // *v
    } prefix;
    union {
        int vint;
        float vflo;
        char* vfunc;
    } value;
    int offset;
};

struct _InterCode {
    enum {
        _ASSIGN,
        _ADD,
        _SUB,
        _MUL,
        _DIV,
        _CALL,
    } oprt;
    union {
        struct {
            Operand lvar;
            Operand op1, op2;
        } binopr;
        struct {
            Operand lvar;
            Operand rop;
        } sinopr;
    } oprds;
};

struct _IRNode {
    enum {
        _NOP,
        _IR_LABEL,  // LABEL x
        _IR_FUNC,   // FUNCTION f
        _IR_ASSIGN,
        _JMP,       // GOTO x
        _COND_JMP,  // IF x [relop] y GOTO z
        _RET,       // RETURN x
        _DEC,       // DEC x [size]
        _ARG,       // ARG x
        _PARAM,     // PARAM x
        _READ, _WRITE   // READ/WRITE x
    } gramm;

    union {
        struct {
            Operand x, y, z;
        } ioprds;   // 操作数
        struct {
            Operand x;
            int size;
        } dec;      // `DEC`操作数
        struct {
            struct {
                char* relop;
                Operand x, y;
            } comp;
            Operand z;
        } icond;    // 条件跳转
        InterCode icode;    // 运算操作
    } detail;

    IRNode *prev, *next;
};

#endif