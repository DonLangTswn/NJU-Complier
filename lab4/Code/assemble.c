#include "lib/assemble.h"

int assemble(LevelNode* root) {
    MY_DEBUG
    // LAB 3: IR
    inter_repres(root, false);
    // LAB 4: Assemble
    initAssemble();
    asm_output();
}

char* compile_Operand(Operand opd, int reg) {
    char* res = (char *)malloc(sizeof(char) * 5);
    int offset;
    switch (opd.vtype) {
    case _VAR:
    case _TEMP:
        offset = frame_offset(opd);
        if (opd.prefix == _GET_ADDR) {
            printf("\taddi  $t%d, $fp, %d\n", reg, offset);
            sprintf(res, "$t%d", reg);
        }
        else if (opd.prefix == _GET_VAL) {
            printf("\tlw  $t%d, %d($fp)\n", reg, offset);
            sprintf(res, "0($t%d)", reg);
        }
        else {
            printf("\tlw  $t%d, %d($fp)\n", reg, offset);
            sprintf(res, "$t%d", reg);
        }
        return res;
    case _CONST_INT:
        printf("\tli  $t%d, %d\n", reg, opd.value.vint);
        sprintf(res, "$t%d", reg);
        return res;
    case _CONST_FLO:
        printf("\tli  $t%d, %.6f\n", reg, opd.value.vflo);
        sprintf(res, "$t%d", reg);
        return res;
    case _LABEL:
        sprintf(res, "label%d", opd.value.vint);
        return res;
    case _FUNC:
        return opd.value.vfunc;
    }
}

void compile_InterCode(InterCode icode) {
    MY_DEBUG
    Operand lvar, op1, op2;
    char* opt = (char *)malloc(sizeof(char) * 10);
    char* lvar_, *op1_, *op2_;
    int offset;
    bool has_const;
    switch (icode.oprt) {
    case _ADD:
        DIY_DEBUG("ADD", %s)
        strcpy(opt, "add");
        lvar = icode.oprds.binopr.lvar;
        op1 = icode.oprds.binopr.op1;
        op2 = icode.oprds.binopr.op2;
        lvar_ = compile_Operand(lvar, 1);
        offset = frame_offset(lvar);
        // has_const = false;
        // if (is_const(op1)) {
        //     op1_ = is_const(op1) == _CONST_INT ? itoa(op1.value.vint) : ftoa(op1.value.vflo);
        //     has_const = true;
        // }
        // else {
            op1_ = compile_Operand(op1, 2);
        // }
        // if (is_const(op2)) {
        //     op2_ = is_const(op2) == _CONST_INT ? itoa(op2.value.vint) : ftoa(op2.value.vflo);
        //     has_const = true;
        // }
        // else {
            op2_ = compile_Operand(op2, 3);
        // }
        // DIY_DEBUG(opt, %s);
        // if (has_const) {
        //     strcat(opt, "i");
        // }
        // lvar_ = "0($t1)"
        if (*lvar_ == '0') {
            printf("\t%s  $t4, %s, %s\n", opt, op1_, op2_);
            printf("\tsw  $t4, %s\n", lvar_);
        }
        // lvar_ = "$t1"
        else {
            printf("\t%s  %s, %s, %s\n", opt, lvar_, op1_, op2_);
            printf("\tsw  %s, %d($fp)\n", lvar_, offset);
        }
        break;
    case _SUB:
        DIY_DEBUG("SUB", %s)
        strcpy(opt, "sub");
        lvar = icode.oprds.binopr.lvar;
        op1 = icode.oprds.binopr.op1;
        op2 = icode.oprds.binopr.op2;
        lvar_ = compile_Operand(lvar, 1);
        offset = frame_offset(lvar);
        // has_const = false;
        // if (is_const(op1)) {
        //     op1_ = is_const(op1) == _CONST_INT ? itoa(op1.value.vint) : ftoa(op1.value.vflo);
        //     has_const = true;
        // }
        // else {
            op1_ = compile_Operand(op1, 2);
        // }
        // if (is_const(op2)) {
        //     op2_ = is_const(op2) == _CONST_INT ? itoa(op2.value.vint) : ftoa(op2.value.vflo);
        //     has_const = true;
        // }
        // else {
            op2_ = compile_Operand(op2, 3);
        // }
        // DIY_DEBUG(opt, %s);
        // if (has_const) {
        //     // lvar_ = "0($t1)"
        //     if (*lvar_ == '0') {
        //         printf("\taddi  $t4, %s, -%s\n", op1_, op2_);
        //         printf("\tsw  $t4, %s\n", lvar_);
        //     }
        //     // lvar_ = "$t1"
        //     else {
        //         printf("\taddi  %s, %s, -%s\n", lvar_, op1_, op2_);
        //         printf("\tsw  %s, %d($fp)\n", lvar_, offset);
        //     }
        // }
        // else {
            // lvar_ = "0($t1)"
            if (*lvar_ == '0') {
                printf("\t%s  $t4, %s, %s\n", opt, op1_, op2_);
                printf("\tsw  $t4, %s\n", lvar_);
            }
            // lvar_ = "$t1"
            else {
                printf("\t%s  %s, %s, %s\n", opt, lvar_, op1_, op2_);
                printf("\tsw  %s, %d($fp)\n", lvar_, offset);
            }
        // }
        break;
    case _MUL:
        strcpy(opt, "mul");
        DIY_DEBUG("MUL", %s)
        lvar = icode.oprds.binopr.lvar;
        op1 = icode.oprds.binopr.op1;
        op2 = icode.oprds.binopr.op2;
        lvar_ = compile_Operand(lvar, 1);
        offset = frame_offset(lvar);
        op1_ = compile_Operand(op1, 2);
        op2_ = compile_Operand(op2, 3);
        // lvar_ = "0($t1)"
        if (*lvar_ == '0') {
            printf("\t%s  $t4, %s, %s\n", opt, op1_, op2_);
            printf("\tsw  $t4, %s\n", lvar_);
        }
        // lvar_ = "$t1"
        else {
            printf("\t%s  %s, %s, %s\n", opt, lvar_, op1_, op2_);
            printf("\tsw  %s, %d($fp)\n", lvar_, offset);
        }
        break;
    case _DIV:
        DIY_DEBUG("DIV", %s)
        lvar = icode.oprds.binopr.lvar;
        op1 = icode.oprds.binopr.op1;
        op2 = icode.oprds.binopr.op2;
        lvar_ = compile_Operand(lvar, 1);
        offset = frame_offset(lvar);
        op1_ = compile_Operand(op1, 2);
        op2_ = compile_Operand(op2, 3);
        // lvar_ = "0($t1)"
        if (*lvar_ == '0') {
            printf("\tdiv  %s, %s\n", op1_, op2_);
            printf("\tmflo  $t4\n");
            printf("\tsw  $t4, %s\n", lvar_);
        }
        // lvar_ = "$t1"
        else {
            printf("\tdiv  %s, %s\n", op1_, op2_);
            printf("\tmflo  %s\n", lvar_);
            printf("\tsw  %s, %d($fp)\n", lvar_, offset);
        }
        break;
    case _ASSIGN:
        DIY_DEBUG("ASSIGN", %s)
        lvar = icode.oprds.sinopr.lvar;
        offset = frame_offset(lvar);
        op1 = icode.oprds.sinopr.rop;
        if (is_const(op1)) {
            op1_ = is_const(op1) == _CONST_INT ? itoa(op1.value.vint) : ftoa(op1.value.vflo);
            strcpy(opt, "li");
        }
        else {
            op1_ = compile_Operand(op1, 2);
            if (op1.prefix == _GET_VAL)
                strcpy(opt, "lw");
            else strcpy(opt, "move");
        }
        // lvar_ = "0($t1)"
        if (lvar.prefix == _GET_VAL) {
            lvar_ = compile_Operand(lvar, 1);
            printf("\t%s  $t4, %s\n", opt, op1_);
            printf("\tsw  $t4, %s\n", lvar_);
        }
        // lvar_ = "$t1"
        else {
            printf("\t%s  $t1, %s\n", opt, op1_);
            printf("\tsw  $t1, %d($fp)\n", offset);
        }
        break;
    case _CALL:
        DIY_DEBUG("CALL", %s)
        lvar = icode.oprds.sinopr.lvar;
        lvar_ = compile_Operand(lvar, 1);
        offset = frame_offset(lvar);
        op1_ = compile_Operand(icode.oprds.sinopr.rop, 0);
        DIY_DEBUG(op1_, %s)
        // 保存活动空间现场
        printf("\taddi  $sp, $sp, -4\n");
        printf("\tsw  $ra, 0($sp)\n");
        printf("\taddi  $sp, $sp, -4\n");
        printf("\tsw  $fp, 0($sp)\n");
        // 调用者调用
        printf("\tjal  %s\n", op1_);
        // 被调用者返回，恢复活动空间
        printf("\tlw  $ra, 4($fp)\n");
        printf("\tlw  $fp, 0($fp)\n");
        printf("\taddi  $sp, $fp, -%d\n", FRAME_SIZE);
        printf("\tmove  %s, $v0\n", lvar_);
        printf("\tsw  %s, %d($fp)\n", lvar_, offset);
    }
}

void compile_IRNode(IRNode* node) {
    char* relop;
    char* x_, *y_, *z_;
    Operand x, y, z;
    int offset;
    switch (node->gramm) {
    case _IR_LABEL:
        x = node->detail.ioprds.x;
        DIY_DEBUG(x.value.vint, %d)
        printf("%s:\n", compile_Operand(x, 0));
        break;
    case _IR_FUNC:
    MY_DEBUG
        x = node->detail.ioprds.x;
        printf("%s:\n", compile_Operand(x, 0));
        printf("\tmove  $fp, $sp\n");
        printf("\taddi  $sp, $fp, -%d\n", FRAME_SIZE);
        break;
    case _IR_ASSIGN:
        compile_InterCode(node->detail.icode);
        break;
    case _JMP:
        x = node->detail.ioprds.x;
        printf("\tj  %s\n", compile_Operand(x, 0));
        break;
    case _COND_JMP:
    MY_DEBUG
        relop = node->detail.icond.comp.relop;
        x = node->detail.icond.comp.x;
        y = node->detail.icond.comp.y;
        z = node->detail.icond.z;
        x_ = compile_Operand(x, 1);
        y_ = compile_Operand(y, 2);
        z_ = compile_Operand(z, 0);
        if (!strcmp(relop, EQ)) {
            printf("\tbeq  %s, %s, %s\n", x_, y_, z_);
        }
        else if (!strcmp(relop, NE)) {
            printf("\tbne  %s, %s, %s\n", x_, y_, z_);
        }
        else if (!strcmp(relop, GT)) {
            printf("\tbgt  %s, %s, %s\n", x_, y_, z_);
        }
        else if (!strcmp(relop, LT)) {
            printf("\tblt  %s, %s, %s\n", x_, y_, z_);
        }
        else if (!strcmp(relop, GE)) {
            printf("\tbge  %s, %s, %s\n", x_, y_, z_);
        }
        else if (!strcmp(relop, LE)) {
            printf("\tble  %s, %s, %s\n", x_, y_, z_);
        }
        break;
    case _RET:
        MY_DEBUG
        x = node->detail.ioprds.x;
        x_ = compile_Operand(x, 1);
        printf("\tmove  $v0, %s\n", x_);
        printf("\tjr  $ra\n");
        MY_DEBUG
        break;
    case _ARG:
        MY_DEBUG
        printf("\taddi  $sp, $sp, -4\n");
        x = node->detail.ioprds.x;
        x_ = compile_Operand(x, 1);
        printf("\tsw  %s, 0($sp)\n", x_);
        break;
    case _DEC:
    case _PARAM:
        break;
    case _READ:
        x = node->detail.ioprds.x;
        offset = frame_offset(x);
        printf("\taddi  $sp, $sp, -4\n");
        printf("\tsw  $ra, 0($sp)\n");
        printf("\tjal  read\n");
        printf("\tlw  $ra, 0($sp)\n");
        printf("\taddi  $sp, $sp, 4\n");
        printf("\tmove  $t1, $v0\n");
        printf("\tsw  $t1, %d($fp)\n", offset);
        break;
    case _WRITE:
        x = node->detail.ioprds.x;
        printf("\taddi  $sp, $sp, -4\n");
        printf("\tsw  $ra, 0($sp)\n");
        if (is_const(x)) {
            printf("\tli  $a0, %s\n", x.vtype == _CONST_INT ? 
                itoa(x.value.vint) : ftoa(x.value.vflo));
        }
        else {
            x_ = compile_Operand(x, 1);
            printf("\tmove  $a0, %s\n", x_);
        }
        printf("\tjal  write\n");
        printf("\tlw  $ra, 0($sp)\n");
        printf("\taddi  $sp, $sp, 4\n");
        break;
    default:
        printf("nop\n"); break;
    }
}