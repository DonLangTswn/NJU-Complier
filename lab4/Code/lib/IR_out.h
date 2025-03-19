#ifndef __IR_OUT_H__
#define __IR_OUT_H__
#include "IR.h"

char* itoa(int i) {
    char* a = (char*)malloc(sizeof(char) * 10);
    sprintf(a, "%d", i);
    return a;
}
char* ftoa(float f) {
    char* a = (char*)malloc(sizeof(char) * 20);
    sprintf(a, "%.6f", f);
    return a;
}

// 将操作数转化为字符串
char* strof_Operand(Operand opd) {
    char* res = (char *)malloc(sizeof(char) * 5);
    switch (opd.vtype) {
    case _VAR:
        if (opd.prefix == _GET_ADDR) {
            sprintf(res, "&v");
        }
        else if (opd.prefix == _GET_VAL) {
            sprintf(res, "*v");
        }
        else sprintf(res, "v");
        break;
    case _TEMP:
        if (opd.prefix == _GET_ADDR) {
            sprintf(res, "&t");
        }
        else if (opd.prefix == _GET_VAL) {
            sprintf(res, "*t");
        }
        else sprintf(res, "t");
        break;
    case _LABEL:
        sprintf(res, "label");
        break;
    case _CONST_INT:
        sprintf(res, "#%s", itoa(opd.value.vint));
        return res;
    case _CONST_FLO:
        sprintf(res, "#%s", ftoa(opd.value.vflo));
        return res;
    case _FUNC:
        return opd.value.vfunc;
    default:
        sprintf(res, "`Undef`");
        return res;
    }
    strcat(res, itoa(opd.value.vint));
    return res;
}

// 将`InterCode`中间赋值代码转化为字符串
char* strof_InterCode(InterCode icode) {
    char* res = (char *)malloc(sizeof(char) * 20);
    switch (icode.oprt) {
    case _ADD:
        sprintf(res, "%s := %s + %s", 
            strof_Operand(icode.oprds.binopr.lvar),
            strof_Operand(icode.oprds.binopr.op1),
            strof_Operand(icode.oprds.binopr.op2));
        return res;
    case _SUB:
        sprintf(res, "%s := %s - %s", 
            strof_Operand(icode.oprds.binopr.lvar),
            strof_Operand(icode.oprds.binopr.op1),
            strof_Operand(icode.oprds.binopr.op2));
        return res;
    case _MUL:
        sprintf(res, "%s := %s * %s", 
            strof_Operand(icode.oprds.binopr.lvar),
            strof_Operand(icode.oprds.binopr.op1),
            strof_Operand(icode.oprds.binopr.op2));
        return res;
    case _DIV:
        sprintf(res, "%s := %s / %s", 
            strof_Operand(icode.oprds.binopr.lvar),
            strof_Operand(icode.oprds.binopr.op1),
            strof_Operand(icode.oprds.binopr.op2));
        return res;
    case _ASSIGN:
        sprintf(res, "%s := %s", 
            strof_Operand(icode.oprds.sinopr.lvar),
            strof_Operand(icode.oprds.sinopr.rop));
        return res;
    case _CALL:
        sprintf(res, "%s := CALL %s", 
            strof_Operand(icode.oprds.sinopr.lvar),
            strof_Operand(icode.oprds.sinopr.rop));
        return res;
    }
}

// 将`IRNode`节点信息转化为字符串
char* strof_IRNode(IRNode* node) {
    char* ir = (char *)malloc(sizeof(char) * 30);
    switch (node->gramm) {
    case _IR_LABEL:
        sprintf(ir, "LABEL %s :", strof_Operand(node->detail.ioprds.x));
        return ir;
    case _IR_FUNC:
        sprintf(ir, "FUNCTION %s :", strof_Operand(node->detail.ioprds.x));
        return ir;
    case _IR_ASSIGN:
        return strof_InterCode(node->detail.icode);
    case _JMP:
        sprintf(ir, "GOTO %s", strof_Operand(node->detail.ioprds.x));
        return ir;
    case _COND_JMP:
        sprintf(ir, "IF %s %s %s GOTO %s",
            strof_Operand(node->detail.icond.comp.x), node->detail.icond.comp.relop,
            strof_Operand(node->detail.icond.comp.y),
            strof_Operand(node->detail.icond.z));
        return ir;
    case _RET:
        sprintf(ir, "RETURN %s", strof_Operand(node->detail.ioprds.x));
        return ir;
    case _DEC:
        sprintf(ir, "DEC %s %d", strof_Operand(node->detail.dec.x), node->detail.dec.size);
        return ir;
    case _ARG:
        sprintf(ir, "ARG %s", strof_Operand(node->detail.ioprds.x));
        return ir;
    case _PARAM:
        sprintf(ir, "PARAM %s", strof_Operand(node->detail.ioprds.x));
        return ir;
    case _READ:
        sprintf(ir, "READ %s", strof_Operand(node->detail.ioprds.x));
        return ir;
    case _WRITE:
        sprintf(ir, "WRITE %s", strof_Operand(node->detail.ioprds.x));
        return ir;
    default:
        sprintf(ir, "`NOP`");
        return ir;
    }
}

IRNode* curr_ir_ptr;

void ir_output() {
    char* irInfo;
    curr_ir_ptr = entry->next;
    int irCnt = 0;
    while (curr_ir_ptr != entry) {
        irInfo = strof_IRNode(curr_ir_ptr);
        printf("%s\n", irInfo);
        curr_ir_ptr = curr_ir_ptr->next;
        irCnt++;
    }
}

#endif