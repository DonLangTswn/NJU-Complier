#ifndef ASSEMBLE_H
#define ASSEMBLE_H
#include "nodes.h"

// -------- #include "IR.h" --------
extern char* itoa(int i);
extern char* ftoa(float f);

#define GT ">"
#define LT "<"
#define EQ "=="
#define GE ">="
#define LE "<="
#define NE "!="
extern int* VarIsParam;
extern bool isparam(Operand var);
extern int cnt_offset;
extern IRNode *entry;
extern IRNode* curr_ir_ptr;
extern int inter_repres(LevelNode* , bool);
// -------- #include "IR.h" --------

int VAR_AREA;   // 栈帧var部分的开始
int TEMP_AREA;  // 栈帧tmp部分的开始
int FRAME_SIZE;

int is_const(Operand opd) {
    if (opd.vtype != _CONST_INT && opd.vtype != _CONST_FLO)
        return 0;
    return opd.vtype;
}

int frame_offset(Operand opd) {
    if (opd.vtype == _VAR || opd.vtype == _TEMP) {
        if (isparam(opd)) {
            return VarIsParam[opd.value.vint] * 4 + 4;
        }
        else {
            DIY_DEBUG(opd.vtype, %d)
            DIY_DEBUG(opd.offset, %d)
            return -(opd.offset);
        }
    }
    return 0;
}

// 将IR中的操作数由内存加载到寄存器中，同时输出相应的机器指令
char* compile_Operand(Operand opd, int reg);
// 实现IR中基本运算和赋值语句的翻译
void compile_InterCode(InterCode icode);
// 对每个中间代码节点进行翻译，递归翻译下一级节点和语句、操作数
void compile_IRNode(IRNode* node);

void initAssemble() {
    FRAME_SIZE = cnt_offset;
    curr_ir_ptr = entry->next;
}

void asm_output() {
    printf("\
.data\n\
_prompt: .asciiz \"Enter an integer:\"\n\
_ret: .asciiz \"\\n\"\n\
.globl main\n\
.text\n\
read:\n\
    li $v0, 4\n\
    la $a0, _prompt\n\
    syscall\n\
    li $v0, 5\n\
    syscall\n\
    jr $ra\n\
\n\
write:\n\
    li $v0, 1\n\
    syscall\n\
    li $v0, 4\n\
    la $a0, _ret\n\
    syscall\n\
    move $v0, $0\n\
    jr $ra\n\
    \n\
");

    int assCnt = 0;
    while (curr_ir_ptr != entry) {
        compile_IRNode(curr_ir_ptr);
        curr_ir_ptr = curr_ir_ptr->next;
        assCnt++;
    }
}

#endif // ASSEMBLE_H