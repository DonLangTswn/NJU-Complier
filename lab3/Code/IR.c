#include "lib/IR.h"
#include "lib/IR_out.h"

/*----------------------------------------
    新建操作数 ( Operand )
    - `newVTYPE(...)`
    - 利用`IR.h`中的预编译指令，批量定义函数
    - 基本类型的常数, 特别处理
 ----------------------------------------*/
NEW_OPERAND_METHOD(VAR)
NEW_OPERAND_METHOD(TEMP)
NEW_OPERAND_METHOD(LABEL)

Operand newINT(int i) {
    Operand res;
    res.vtype = _CONST_INT;
    res.value.vint = i;
    return res;
}
Operand newFLO(float f) {
    Operand res;
    res.vtype = _CONST_FLO;
    res.value.vflo = f;
    return res;
}
Operand newFUNC(char* fname) { 
    Operand res;
    res.vtype = _FUNC;
    res.value.vfunc = (char *)malloc(sizeof(char) * strlen(fname));
    strcpy(res.value.vfunc, fname);
    return res; 
}

// 自动检测表中是否分配变量`Operand`，若无则调用`newVAR()`
Operand alloc_VAR(char* id) {
    int symInd = getSymbIndex(id);
    int varInd = table_VAR[symInd];
    Operand var;
    if (!varInd) {
        table_VAR[symInd] = cnt_VAR;
        var = newVAR(cnt_VAR);
        cnt_VAR++;
    }
    else var = newVAR(varInd);
    return var;
}
Operand alloc_TEMP() {
    return newTEMP(cnt_TEMP++);
}
Operand alloc_LABEL() {
    return newLABEL(cnt_LABEL++);
}

/* -----------------------------
    新建`InterCode`中间代码表示
    - `genOPRT(...)`
    - 利用预编译指令
    - 右侧可能出现一元/二元操作数
 ----------------------------- */
GEN_INTERCODE_METHOD_1op(ASSIGN)
GEN_INTERCODE_METHOD_2op(ADD)
GEN_INTERCODE_METHOD_2op(SUB)
GEN_INTERCODE_METHOD_2op(MUL)
GEN_INTERCODE_METHOD_2op(DIV)
GEN_INTERCODE_METHOD_1op(CALL)

/*--------------------------
    新建`IR`节点 ( IRNode )
    - `mkGRAMM(...)`
    - 利用预编译指令 (一元操作)
    - 注意三种特殊情况
 --------------------------*/
MK_IRNODE_METHOD_1op(IR_LABEL) // LABEL x
MK_IRNODE_METHOD_1op(IR_FUNC)  // FUNCTION f
MK_IRNODE_METHOD_1op(JMP)   // GOTO x
MK_IRNODE_METHOD_1op(ARG)   // ARG x
MK_IRNODE_METHOD_1op(PARAM) // PARAM x
MK_IRNODE_METHOD_1op(READ)  // READ x
MK_IRNODE_METHOD_1op(WRITE) // WRITE x
MK_IRNODE_METHOD_1op(RET)   // RETURN x

// IF x [relop] y GOTO z
IRNode* mkCOND_JMP(Operand x, char* relop, Operand y, Operand z) {
    IRNode* res = (IRNode *)malloc(sizeof(IRNode));
    res->gramm = _COND_JMP;
    res->detail.icond.comp.relop = relop;
    res->detail.icond.comp.x = x;
    res->detail.icond.comp.y = y;
    res->detail.icond.z = z;
    return res;
}
// IR_ASSIGN
IRNode* mkIR_ASSIGN(InterCode code) {
    IRNode* res = (IRNode *)malloc(sizeof(IRNode));
    res->gramm = _IR_ASSIGN;
    res->detail.icode = code;
    return res;
}
// DEC x [size]
IRNode* mkDEC(Operand x, int size) {
    IRNode* res = (IRNode *)malloc(sizeof(IRNode));
    res->gramm = _DEC;
    res->detail.dec.x = x;
    res->detail.dec.size = size;    // Attention!
    return res;
}

/*-------------------------
    # transl_函数部分 #
    - 读取语法树节点
    - 分类翻译成三地址码
 ------------------------*/

// Args -> Exp , Args | Exp
// 注意：实参传入顺序和形参顺序相反，因此先递归调用，再进行输出
// 注意：实参若为结构体类型，需要传入地址
// `bool isWrite`: 为了调用`write(int)`的时候能够得到参数，令其只返回首个(即唯一一个)参数
Operand transl_Args(LevelNode* Args, bool isWrite) {
    LevelNode* Exp = Args->childhead;
    if (Exp->next) {
        Args = Exp->next->next;
        transl_Args(Args, isWrite);
    }
    Operand arg = transl_Exp(Exp, alloc_TEMP());
    if (handle_Exp(Exp).etype.type == _STRUCT) {
        arg.prefix = _GET_ADDR;
    }
    if (!isWrite) {
        addIRNode(mkARG(arg));
        // -----------------------------------
        //  特判：S[i]为结构体，但传参时多余取值
        // ---- [eg]: ----
        //  t1 := &v1 + #12
        //  t2 := *t1
        // "ARG &t2"        <--- tail
        // -----------------------------------

        // IRNode* tail = entry->prev;
        // if (tail->detail.ioprds.x.vtype == _TEMP \
        //     && tail->prev->gramm == _IR_ASSIGN \
        //     && tail->prev->detail.icode.oprt == _ASSIGN \
        //     && tail->prev->detail.icode.oprds.sinopr.rop.prefix == _GET_VAL \
        //     && tail->prev->detail.icode.oprds.sinopr.lvar.vtype == _TEMP \
        //     && tail->prev->prev->detail.icode.oprds.sinopr.lvar.vtype == _TEMP \
        //     && tail->prev->detail.icode.oprds.sinopr.lvar.value.vint == tail->detail.ioprds.x.value.vint \
        //     && tail->prev->detail.icode.oprds.sinopr.rop.value.vint == tail->prev->prev->detail.icode.oprds.sinopr.lvar.value.vint) {
        //         // delete extra irNode
        //         IRNode* extra = tail->prev;
        //         tail->prev = extra->prev;
        //         tail->prev->next = tail;
        //         free(extra);
        //         // edit tail
        //         tail->detail.ioprds.x = tail->prev->detail.icode.oprds.sinopr.lvar;
        // }
    }
    return arg;
}

// 如果数组之间赋值的话....(听说只有单个数组赋值情况)
// 注意：以左值数组的大小作为`asize`
void assign_if_array(int lsize, Operand res, Operand lvar) {
    // int A[5], B[5];  A = B;
    Operand asize = newINT(lsize * 4);
    Operand t0 = alloc_TEMP();
    addIRNode(mkIR_ASSIGN(genASSIGN(t0, newINT(0))));   // t0 := #0
    Operand label0;
    if (entry->prev->gramm == _IR_LABEL) {
        label0 = entry->detail.ioprds.x;
    } else {
        label0 = alloc_LABEL();
    }
    Operand label1 = alloc_LABEL();
    Operand label2 = alloc_LABEL();
    Operand t1 = alloc_TEMP(), t2 = alloc_TEMP();
    addIRNode(mkIR_LABEL(label0));                      // LABEL label0 :
    addIRNode(mkCOND_JMP(t0, LT, asize, label1));       // if t0 < `asize` GOTO label1
    addIRNode(mkJMP(label2));                           // GOTO label2
    addIRNode(mkIR_LABEL(label1));                      // LABEL label1 :
    lvar.prefix = res.prefix = _GET_ADDR;
    addIRNode(mkIR_ASSIGN(genADD(t1, lvar, t0)));       // t1 := &v1 + t0
    addIRNode(mkIR_ASSIGN(genADD(t2, res, t0)));        // t2 := &v2 + t0
    t1.prefix = t2.prefix = _GET_VAL;
    addIRNode(mkIR_ASSIGN(genASSIGN(t1, t2)));          // *t1 := *t2
    addIRNode(mkIR_ASSIGN(genADD(t0, t0, newINT(4))));  // t0 := t0 + #4
    addIRNode(mkJMP(label0));                           // GOTO label0
    addIRNode(mkIR_LABEL(label2));                      // LABEL label2 :
}

// ID   若左值为`VAR`，回传给左值，否则直接作为`VAR`形式返回
Operand transl_exp_id(LevelNode* Exp, Operand lvar) {
    if (isundef(lvar))  return lvar;
    Operand res = alloc_VAR(getID(Exp->childhead));
    if (lvar.vtype != _TEMP || lvar.prefix) {   // `*t`也可以担任左值
        Type rtyp = getSymb(getID(Exp->childhead))->dType;
        if (rtyp.type == _ARRAY) {
            int lsize = symb_table[lvar.value.vint]->dType.value.Array.arraySize;
            assign_if_array(lsize, res, lvar);
        }
        else addIRNode(mkIR_ASSIGN(genASSIGN(lvar, res)));
    }
    return res;
}

// INT | FLOAT  回传给左值，作为立即数形式返回
Operand transl_exp_basic(LevelNode* Exp, Operand lvar) {
    if (isundef(lvar))  return lvar;
    Operand res;
    LevelNode* basic = Exp->childhead;
    if (!strncmp(basic->msg, "INT", 3))
        res = newINT(getVINT(basic));
    else
        res = newFLO(getVFLO(basic));
    if (lvar.vtype != _TEMP || lvar.prefix) {   // `*t`也可以担任左值
        addIRNode(mkIR_ASSIGN(genASSIGN(lvar, res)));
        return lvar;
    }
    return res;
}

// SUB Exp  1. 调用处理`EXP` 2. 若为常数，直接加负号返回常数
//      3. 若非常数，`0 - 之`赋给临时变量返回
Operand transl_exp_ngtv(LevelNode* Exp, Operand lvar) {
    if (isundef(lvar))  return lvar;
    Exp = Exp->childhead->next;
    Operand res = transl_Exp(Exp, alloc_TEMP());
    if (res.vtype == _CONST_INT) {
        res.value.vint *= -1;
        return res;
    }
    else if (res.vtype == _CONST_FLO) {
        res.value.vflo *= -1;
        return res;
    }
    addIRNode(mkIR_ASSIGN(genSUB(lvar, newINT(0), res)));
    return lvar;
}

/* Exp ASSIGN Exp   1. 调用处理`EXP`, 2. 返回值即为自身左值
    3. 赋值操作逻辑：将所有赋值语句的赋值（回传）操作放在右`EXP`内部进行
    4. 若赋值语句存在左值，即`x = (y = z)`:
    - 先调用处理自身，即`(y = z)`
    - 在自身内部将自身*右值*回传给上一级
*/
Operand transl_exp_assign(LevelNode* Exp, Operand lvar) {
    Exp = Exp->childhead;
    Operand def = transl_Exp(Exp, newTEMP(-1)); // 用`vint = -1`表示担任左值
    Operand use;
    if (def.prefix == _GET_VAL) {
        use = transl_Exp(Exp->next->next, alloc_TEMP());
        addIRNode(mkIR_ASSIGN(genASSIGN(def, use)));
    }
    else use = transl_Exp(Exp->next->next, def);
    if (!isundef(lvar)) {
        addIRNode(mkIR_ASSIGN(genASSIGN(lvar, def)));
    }
    return use; // 赋值语句: 返回"="右边的
}

/* Exp PLUS Exp | Exp MINUS Exp | Exp STAR Exp | Exp DIV Exp
    1. 对两个操作数，调用处理`EXP`  2. 根据符号生成中间代码
    3. 回传给左值 (左值可能是`v1`, 也可能是`t1`...)
*/
Operand transl_exp_arithm(LevelNode* Exp, Operand lvar) {
    if (isundef(lvar))  return lvar;
    Exp = Exp->childhead;
    Operand op1 = transl_Exp(Exp, alloc_TEMP());
    Operand op2 = transl_Exp(Exp->next->next, alloc_TEMP());
    LevelNode* opr = Exp->next;
    InterCode arithm;
    // -------- 特判：常数直接计算 --------
    if (op1.vtype == op2.vtype == _CONST_INT) {
        int res_v;
        if (!strcmp(opr->msg, "PLUS")) {
            res_v = op1.value.vint + op2.value.vint;
        }
        else if (!strcmp(opr->msg, "MINUS")) {
            res_v = op1.value.vint - op2.value.vint;
        }
        else if (!strcmp(opr->msg, "STAR")) {
            res_v = op1.value.vint * op2.value.vint;
        }
        else if (!strcmp(opr->msg, "DIV")) {
            res_v = op1.value.vint / op2.value.vint;
        }
        Operand res = newINT(res_v);
        return res;
    }
    // -------- 特判：常数直接计算 --------
    if (op1.vtype == op2.vtype == _CONST_FLO) {
        float res_v;
        if (!strcmp(opr->msg, "PLUS")) {
            res_v = op1.value.vflo + op2.value.vflo;
        }
        else if (!strcmp(opr->msg, "MINUS")) {
            res_v = op1.value.vflo - op2.value.vflo;
        }
        else if (!strcmp(opr->msg, "STAR")) {
            res_v = op1.value.vflo * op2.value.vflo;
        }
        else if (!strcmp(opr->msg, "DIV")) {
            res_v = op1.value.vflo / op2.value.vflo;
        }
        Operand res = newFLO(res_v);
        return res;
    }
    
    if (!strcmp(opr->msg, "PLUS")) {
        arithm = genADD(lvar, op1, op2);
    }
    else if (!strcmp(opr->msg, "MINUS")) {
        arithm = genSUB(lvar, op1, op2);
    }
    else if (!strcmp(opr->msg, "STAR")) {
        arithm = genMUL(lvar, op1, op2);
    }
    else if (!strcmp(opr->msg, "DIV")) {
        arithm = genDIV(lvar, op1, op2);
    }
    addIRNode(mkIR_ASSIGN(arithm));
    return lvar;
}

/* Exp [ Exp ]  1. 对左边的数组`Exp`调用`transl_Exp()`获得`Operand`
    2. 对左边的数组`Exp`调用`handle_Exp()`得到类型值，调用`getSzieOf()`获得空间大小
    3. 若下标`Exp`不为常数`0`，需要计算首地址 + 偏移量获取地址
    4. 注意，`*t`不能直接作为右操作数，只有在复制赋值语句中可以直接用
    5. `S.id[i]`情况，特判`IR`代码末尾并删除
*/
Operand transl_exp_array(LevelNode* Exp, Operand lvar) {
    if (isundef(lvar))  return lvar;
    Exp = Exp->childhead;
    Operand array = transl_Exp(Exp, alloc_TEMP());
    Operand index = transl_Exp(Exp->next->next, alloc_TEMP());
    Type arrTyp = *handle_Exp(Exp).etype.value.Array.arrayElem;
    if (arrTyp.type == _ARRAY) {
        fprintf(stderr, "[Cannot translate]: Variables of multi-dimensional array type.\n");
        exit(0);
    }
    int asize = getSizeOf(arrTyp);    // 只可能一维
    Operand t2;
    if (index.vtype == _CONST_INT && index.value.vint == 0) {
        t2 = alloc_TEMP();          // t2 := &array
        array.prefix = _GET_ADDR;
        addIRNode(mkIR_ASSIGN(genASSIGN(t2, array)));
    }
    else {
        Operand t1;
        if (index.vtype == _CONST_INT) {
            t1 = newINT(index.value.vint * asize);
        } else {
            t1 = alloc_TEMP();      // t1 := index * `asize`
            addIRNode(mkIR_ASSIGN(genMUL(t1, index, newINT(asize))));
        }
        t2 = alloc_TEMP();          // t2 := &array + t1
        array.prefix = _GET_ADDR;
        addIRNode(mkIR_ASSIGN(genADD(t2, array, t1)));
    }
    // -------------------------------------------------------
    //  S.id[i]情况特判:
    // 若出现对取过值的临时变量取地址，则对tail更改，直接对原地址操作
    // ---- [eg]: ----
    //  DEC v3 44
    //  t3 := &v3 + #4
    //  t1 := *t3       <--- struct_id
    //   ....
    //  t5 := ....      (array offset)
    // "t6 := &t1 + t5" <--- tail
    // -------------------------------------------------------

    // IRNode* tail = entry->prev;
    // if (tail->gramm == _IR_ASSIGN \
    //     && tail->detail.icode.oprds.sinopr.rop.prefix == _GET_ADDR \
    //     && tail->detail.icode.oprds.sinopr.rop.vtype == _TEMP \
    //     && struct_id->gramm == _IR_ASSIGN \
    //     && struct_id->detail.icode.oprt == _ASSIGN \
    //     && struct_id->detail.icode.oprds.sinopr.rop.prefix == _GET_VAL \
    //     && tail->detail.icode.oprds.sinopr.rop.value.vint ==  struct_id->detail.icode.oprds.sinopr.lvar.value.vint \
    //     && struct_id->prev->gramm == _IR_ASSIGN \
    //     && struct_id->prev->detail.icode.oprds.sinopr.lvar.vtype == _TEMP \
    //     && struct_id->detail.icode.oprds.sinopr.lvar.value.vint == tail->detail.icode.oprds.sinopr.rop.value.vint) {
    //         // Edit tail info
    //         Operand t3 = struct_id->prev->detail.icode.oprds.sinopr.lvar;
    //         t3.prefix = _NOTHING;
    //         tail->detail.icode.oprds.sinopr.rop = t3;
    //         // delete struct_id IRNode
    //         struct_id->prev->next = struct_id->next;
    //         struct_id->next->prev = struct_id->prev;
    //         free(struct_id);
    // }

    t2.vstate = _ADDR;
    t2.prefix = _GET_VAL;       // *t2
    // 除复制赋值外，`*t`不能直接作为右操作数，但是可以担任左值
    if (lvar.vtype == _TEMP && lvar.value.vint > 0) {   // 情况1：右操作数
        addIRNode(mkIR_ASSIGN(genASSIGN(lvar, t2)));
        return lvar;
    }
    if (!(lvar.vtype == _TEMP && lvar.value.vint < 0))  // 情况2：不担任左值-复制赋值
        addIRNode(mkIR_ASSIGN(genASSIGN(lvar, t2)));    // 情况3：担任左值
    return t2;
}

/* Exp DOT ID   1. 计算结构体内部成员`ID`偏移量  2. 取到地址后再取值返回
    3. 对左`Exp`调用`handle_Exp()`得到类型值，调用`getSzieOf()`获得`id`偏移量
    4. 若下标`Exp`不为常数`0`，需要计算首地址 + 偏移量获取地址
    5. 注意，`*t`不能直接作为右操作数，只有在复制赋值语句中可以直接用
    6. `S[i].id`情况, 特判`IR`代码末尾并删除
*/
Operand transl_exp_struct(LevelNode* Exp, Operand lvar) {
    if (isundef(lvar))  return lvar;
    Exp = Exp->childhead;
    Operand stru = transl_Exp(Exp, alloc_TEMP());
    // 处理结构体内部成员`ID`
    char* id = getID(Exp->next->next);
    Type stype = handle_Exp(Exp).etype;
    SymbNode* member = stype.value.Struct->dType.value.StructMember;
    int offset = 0;
    while (member && strcmp(member->name, id) != 0) {
        offset += getSizeOf(member->dType);
        member = member->next;
    }
    Operand t1;
    t1 = alloc_TEMP();
    if (stru.vstate == _VALUE)
        stru.prefix = _GET_ADDR;
    if (offset)         // t1 := &stru + offset
        addIRNode(mkIR_ASSIGN(genADD(t1, stru, newINT(offset))));
    else                // t1 := &stru
        addIRNode(mkIR_ASSIGN(genASSIGN(t1, stru)));
    // ------------------------------------------------------
    //  S[i].id情况特判:
    // 若出现对取过值的临时变量取地址，则删除前两行，直接对原地址操作
    // ---- [eg]: ----
    //  DEC v1 80
    //  t1 := ....      (array offset)
    //  t2 := &v1 + t1
    //  t3 := *t2
    // "t4 := &t3 + #4"  <--- tail
    // ------------------------------------------------------ 

    // IRNode* tail = entry->prev;
    // if (tail->gramm == _IR_ASSIGN \
    //     && tail->detail.icode.oprds.sinopr.rop.prefix == _GET_ADDR \
    //     && tail->detail.icode.oprds.sinopr.rop.vtype == _TEMP \
    //     && tail->prev->gramm == _IR_ASSIGN \
    //     && tail->prev->detail.icode.oprt == _ASSIGN \
    //     && tail->prev->detail.icode.oprds.sinopr.rop.prefix == _GET_VAL \
    //     && tail->detail.icode.oprds.binopr.op1.value.vint == tail->prev->detail.icode.oprds.sinopr.lvar.value.vint \
    //     && tail->prev->prev->gramm == _IR_ASSIGN \
    //     && tail->prev->prev->detail.icode.oprds.binopr.lvar.vtype == _TEMP \
    //     && tail->prev->prev->detail.icode.oprds.binopr.lvar.value.vint == tail->prev->detail.icode.oprds.sinopr.rop.value.vint) {
    //         // delete tail
    //         tail = entry->prev->prev;
    //         free(entry->prev);
    //         entry->prev = tail;
    //         tail->next = entry;
    //         // delete tail->prev
    //         tail = entry->prev->prev;
    //         free(entry->prev);
    //         entry->prev = tail;
    //         tail->next = entry;
    //         // new tail
    //         Operand t2 = tail->detail.icode.oprds.sinopr.lvar;
    //         t2.prefix = _NOTHING;
    //         if (offset)
    //             addIRNode(mkIR_ASSIGN(genADD(t1, t2, newINT(offset))));
    //         else t1 = t2;
    // }

    t1.vstate = _ADDR;
    // 除复制赋值外，`*t`不能直接作为右操作数；但是可以担任左值
    if (lvar.vtype == _TEMP && lvar.value.vint > 0) {   // 情况1：右操作数
        t1.prefix = _GET_VAL;   // *t1
        addIRNode(mkIR_ASSIGN(genASSIGN(lvar, t1)));
        struct_id = entry->prev;    // 解决结构体中数组问题：指向对结构体成员`id`取值那一行
        return lvar;
    }
    if (!(lvar.vtype == _TEMP && lvar.value.vint < 0)) {// 情况2：不担任左值-复制赋值
        t1.prefix = _GET_VAL;   // *t1
        addIRNode(mkIR_ASSIGN(genASSIGN(lvar, t1)));    // 情况3：担任左值
        struct_id = entry->prev;    // 解决结构体中数组问题：指向对结构体成员`id`取值那一行
    }
    return t1;
}

// ID ( Args ) | ID ( )  1. 先处理传入参数   2. `CALL`函数, 将函数返回值回传 
Operand transl_exp_func(LevelNode* Exp, Operand lvar) {
    LevelNode* ID = Exp->childhead;
    LevelNode* Args = ID->next->next;
    Operand arg;
    char* funId = getID(ID);
    if (!strcmp(Args->msg, "Args")) {
        arg = transl_Args(Args, !strcmp(funId, "write"));
    }
    if (!strcmp(funId, "read")) {
        addIRNode(mkREAD(lvar));
    }
    else if (!strcmp(funId, "write")) {
        addIRNode(mkWRITE(arg));
        if (!isundef(lvar)) {
            addIRNode(mkIR_ASSIGN(genASSIGN(lvar, newINT(0))));
        }
    }
    else {
        if (isundef(lvar))  lvar = alloc_TEMP();
        addIRNode(mkIR_ASSIGN(genCALL(lvar, newFUNC(funId))));
    }
    return lvar;
}

// Exp RELOP Exp
void transl_Cond_comp(LevelNode* Exp, Operand labelT, Operand labelF) {
    Exp = Exp->childhead;
    Operand t1 = transl_Exp(Exp, alloc_TEMP());
    Operand t2 = transl_Exp(Exp->next->next, alloc_TEMP());
    char* relop = getRELOP(Exp->next);
    addIRNode(mkCOND_JMP(t1, relop, t2, labelT));
    addIRNode(mkJMP(labelF));
}

// Exp && Exp
void transl_Cond_and(LevelNode* Exp, Operand labelT, Operand labelF) {
    Exp = Exp->childhead;
    Operand label1 = alloc_LABEL();
    transl_Cond(Exp, label1, labelF);
    addIRNode(mkIR_LABEL(label1));      // "LABEL label1 :"
    transl_Cond(Exp->next->next, labelT, labelF);
}

// Exp || Exp
void transl_Cond_or(LevelNode* Exp, Operand labelT, Operand labelF) {
    Exp = Exp->childhead;
    Operand label1 = alloc_LABEL();
    transl_Cond(Exp, labelT, label1);
    addIRNode(mkIR_LABEL(label1));      // "LABEL label1 :"
    transl_Cond(Exp->next->next, labelT, labelF);
}

/* NOT Exp | Exp AND Exp | Exp OR Exp | Exp RELOP Exp
    - | ( Exp ): 递归调用
    - `transl_Cond_and()`
    - `transl_Cond_or()`
    - `transl_Cond_comp()`
*/
void transl_Cond(LevelNode* Exp, Operand labelT, Operand labelF) {
    if (!strcmp(Exp->childhead->msg, "LP")) {   // ( Exp )
        Exp = Exp->childhead->next;
        transl_Cond(Exp, labelT, labelF);
    }
    if (!strcmp(Exp->childhead->msg, "NOT")) {  // ! Exp
        Exp = Exp->childhead->next;
        transl_Cond(Exp, labelF, labelT);
    }
    else {
        LevelNode* opr = Exp->childhead->next;
        if (!strncmp(opr->msg, "RELOP", 5)) {   // Comparing
            transl_Cond_comp(Exp, labelT, labelF);
        }
        else if (!strcmp(opr->msg, "AND")) {    // bool-AND
            transl_Cond_and(Exp, labelT, labelF);
        }
        else if (!strcmp(opr->msg, "OR")) {     // bool-OR
            transl_Cond_or(Exp, labelT, labelF);
        }
        else {  // (other case)
            Operand t1 = transl_Exp(Exp, alloc_TEMP());
            addIRNode(mkCOND_JMP(t1, NE, newINT(0), labelT));
            addIRNode(mkJMP(labelF));
        }
    }
}

/* 分类处理`Exp`部分的各种表达式类型
Exp ->
    ( Exp ): 嵌套调用即可
    `transl_exp_id()`:      ID
    `transl_exp_basic()`:   INT | FLOAT
    `transl_exp_func()`:    ID ( Args ) | ID ( )
    `transl_exp_ngtv()`:    SUB Exp
    `transl_exp_assign()`:  Exp ASSIGN Exp
    `transl_exp_arithm()`:  Exp ADD Exp | Exp SUB Exp | Exp MUL Exp | Exp DIV Exp
    `transl_exp_array()`:   Exp [ Exp ]
    `transl_exp_struct()`:  Exp DOT ID
    `transl_condition()`:   Exp AND Exp | Exp OR Exp | NOT Exp | Exp RELOP Exp
*/
Operand transl_Exp(LevelNode* Exp, Operand lvar) {
    if (!strcmp(Exp->childhead->msg, "LP")) {
        Exp = Exp->childhead->next;
        return transl_Exp(Exp, lvar);
    }
    else if (!Exp->childhead->next) {
        if (!strncmp(Exp->childhead->msg, "ID", 2))
            return transl_exp_id(Exp, lvar);
        else
            return transl_exp_basic(Exp, lvar);
    }
    else if (!strcmp(Exp->childhead->msg, "MINUS")) {
        return transl_exp_ngtv(Exp, lvar);
    }
    else if (!strcmp(Exp->childhead->msg, "NOT")) {
        // 布尔表达式赋值，利用`if-else`条件语句分情况赋`1`或`0`
        Operand labelT = alloc_LABEL();
        Operand labelF = alloc_LABEL();
        transl_Cond(Exp, labelT, labelF);
        addIRNode(mkIR_LABEL(labelT));
        addIRNode(mkIR_ASSIGN(genASSIGN(lvar, newINT(true))));
        addIRNode(mkIR_LABEL(labelF));
        addIRNode(mkIR_ASSIGN(genASSIGN(lvar, newINT(false))));
    }
    else if (!strncmp(Exp->childhead->msg, "ID", 2)) {
        return transl_exp_func(Exp, lvar);
    }
    LevelNode* opr = Exp->childhead->next;
    if (!strcmp(opr->msg, "ASSIGNOP")) {
        return transl_exp_assign(Exp, lvar);
    }
    else if (!strcmp(opr->msg, "AND") || !strcmp(opr->msg, "OR") || !strcmp(opr->msg, "RELOP")) {
        // 布尔表达式赋值，利用`if-else`条件语句分情况赋`1`或`0`
        Operand labelT = alloc_LABEL();
        Operand labelF = alloc_LABEL();
        transl_Cond(Exp, labelT, labelF);
        addIRNode(mkIR_LABEL(labelT));
        addIRNode(mkIR_ASSIGN(genASSIGN(lvar, newINT(true))));
        addIRNode(mkIR_LABEL(labelF));
        addIRNode(mkIR_ASSIGN(genASSIGN(lvar, newINT(false))));
    }
    else if (!strcmp(opr->msg, "PLUS") || !strcmp(opr->msg, "MINUS") || !strcmp(opr->msg, "STAR") || !strcmp(opr->msg, "DIV")) {
        return transl_exp_arithm(Exp, lvar);
    }
    else if (!strcmp(opr->msg, "LB")) {
        return transl_exp_array(Exp, lvar);
    }
    else if (!strcmp(opr->msg, "DOT")) {
        return transl_exp_struct(Exp, lvar);
    }
}

/* Stmt:  
    -> `Exp ;`
    -> `CompSt`
    -> `RETURN Exp ;`
    -> `IF ( Exp ) Stmt`
    -> `IF ( Exp ) Stmt ELSE Stmt`
    -> `WHILE ( Exp ) Stmt`
*/
void transl_Stmt(LevelNode* Stmt) {
    if (!strcmp(Stmt->childhead->msg, "Exp")) {
        transl_Exp(Stmt->childhead, UNDEF);   
    }
    else if (!strcmp(Stmt->childhead->msg, "CompSt")) {
        LevelNode* CompSt = Stmt->childhead;
        transl_CompSt(CompSt);
    }
    else if (!strcmp(Stmt->childhead->msg, "RETURN")) {
        LevelNode* Exp = Stmt->childhead->next;
        Operand ret = alloc_TEMP();
        ret = transl_Exp(Exp, ret);
        addIRNode(mkRET(ret));
    }
    else if (!strcmp(Stmt->childhead->msg, "IF")) {
        LevelNode* Exp = Stmt->childhead->next->next;
        Stmt = Exp->next->next;
        Operand labelT = alloc_LABEL();
        Operand labelF = alloc_LABEL();
        if (!Stmt->next) {  // IF ( Exp ) Stmt
            transl_Cond(Exp, labelT, labelF);
            addIRNode(mkIR_LABEL(labelT));      // "LABEL labelT :"
            transl_Stmt(Stmt);
            addIRNode(mkIR_LABEL(labelF));      // "LABEL labelF :"
        }
        else {  // IF ( Exp ) Stmt ELSE Stmt
            Operand label1 = alloc_LABEL();
            transl_Cond(Exp, labelT, labelF);
            addIRNode(mkIR_LABEL(labelT));      // "LABEL labelT :"
            transl_Stmt(Stmt);
            addIRNode(mkJMP(label1));           // "GOTO label1"    <--- goto_exit
            IRNode* goto_exit = entry->prev;
            addIRNode(mkIR_LABEL(labelF));      // "LABEL labelF :"
            transl_Stmt(Stmt->next->next);
            if (entry->prev->gramm == _IR_LABEL) {
                goto_exit->detail.ioprds.x = entry->prev->detail.ioprds.x;
            }else {
                addIRNode(mkIR_LABEL(label1));  // "LABEL label1 :"
            }
        }
    }
    else if (!strcmp(Stmt->childhead->msg, "WHILE")) {
        LevelNode* Exp = Stmt->childhead->next->next;
        Stmt = Exp->next->next;
        Operand label1;
        if (entry->prev->gramm == _IR_LABEL) {
            label1 = entry->prev->detail.ioprds.x;
        }else {
            label1 = alloc_LABEL();
            addIRNode(mkIR_LABEL(label1));  // "LABEL label1 :"
        }
        Operand labelT = alloc_LABEL();
        Operand labelF = alloc_LABEL();
        transl_Cond(Exp, labelT, labelF);
        addIRNode(mkIR_LABEL(labelT));  // "LABEL labelT :"
        transl_Stmt(Stmt);
        addIRNode(mkJMP(label1));       // "GOTO label1"
        addIRNode(mkIR_LABEL(labelF));  // "LABEL labelF :"
    }
}

// `StmtList -> Stmt StmtList | 空`
void transl_StmtList(LevelNode* StmtList) {
    if (!isemp(StmtList)) {
        LevelNode* Stmt = StmtList->childhead;
        StmtList = Stmt->next;
        transl_Stmt(Stmt);
        transl_StmtList(StmtList);
    }
}


// `ParamDec -> Specifier VarDec`
void transl_ParamDec(LevelNode* ParamDec) {
    LevelNode* VarDec = ParamDec->childhead->next;
    transl_VarDec(VarDec, true);
}

// `VarList -> ParamDec , VarList | ParamDec`
void transl_VarList(LevelNode* VarList) {
    LevelNode* ParamDec = VarList->childhead;
    transl_ParamDec(ParamDec);
    if (ParamDec->next) {
        transl_VarList(ParamDec->next->next);
    }
}

// `FunDec -> ID ( ) | ID ( VarList )`
void transl_FunDec(LevelNode* FunDec) {
    LevelNode* ID = FunDec->childhead;
    addIRNode(mkIR_FUNC(newFUNC(getID(ID))));
    if (ID->next->next->next) {
        transl_VarList(ID->next->next);
    }
}

// `VarDec -> ID | VarDec [ INT ]`
// - 若为函数参数，都需要分配`PARAM`、都不需要`DEC`空间
// - 需要用一个`SYMB - VAR_NUM`映射存下刚刚存取的`VAR`
Operand transl_VarDec(LevelNode* VarDec, bool isParam) {
    if (!strcmp(VarDec->childhead->msg, "VarDec")) {    // VarDec [ INT ]
        VarDec = VarDec->childhead;
        return transl_VarDec(VarDec, isParam);  // 放心交给`ID`去处理
    }
    else {  // ID
        Operand oprd = alloc_VAR(getID(VarDec));
        if (isParam) {  // 函数参数
            if (getSymb(getID(VarDec))->dType.type == _ARRAY) {
                fprintf(stderr, "[Cannot translate]: Parameters of array type.\n");
                exit(0);
            }
            else if (getSymb(getID(VarDec))->dType.type == _STRUCT) {
                oprd.vstate = _ADDR;
            }
            addIRNode(mkPARAM(oprd));   // PARAM x
            VarIsParam[oprd.value.vint] = true; // 函数参数
        }
        else {  // 查看变量类型，是否需要`DEC`分配空间
            SymbNode* symb = getSymb(getID(VarDec));
            if (symb->dType.type != _INT && symb->dType.type != _FLOAT) {
                int vsize = getSizeOf(symb->dType);
                addIRNode(mkDEC(oprd, vsize));
            }
        }
        return oprd;
    }
}

/* `Dec` = `VarDec` (+ 赋值)
    - `-> VarDec`       # 不赋值: 若为`INT`or`FLOAT`，暂时不分配`VAR`；否则也要`DEC`
    - `-> VarDec = Exp` # 赋值，调用`transl_VarDec()`分配`VAR`，调用`transl_Exp()`进行赋值操作
*/
void transl_Dec(LevelNode* Dec) {
    LevelNode* VarDec = Dec->childhead;
    Type vtyp = getSymb(getID(VarDec))->dType;
    if (VarDec->next || vtyp.type != _INT && vtyp.type != _FLOAT) {
        Operand lvar = transl_VarDec(VarDec, false);
        if (VarDec->next) {
            LevelNode* Exp = VarDec->next->next;
            transl_Exp(Exp, lvar);
        }
    }
}

// `DecList -> Dec | Dec , DecList`
void transl_DecList(LevelNode* DecList) {
    LevelNode* Dec = DecList->childhead;
    transl_Dec(Dec);
    if (Dec->next) {
        DecList = Dec->next->next;
        transl_DecList(DecList); 
    }
}

// `Def -> Specifier DecList ;`
void transl_Def(LevelNode* Def) {
    LevelNode* Specifier = Def->childhead;
    transl_DecList(Specifier->next);
}

// `DefList -> Def DefList | 空`
void transl_DefList(LevelNode* DefList) {
    if (!isemp(DefList)) {
        LevelNode* Def = DefList->childhead;
        DefList = Def->next;
        transl_Def(Def);
        transl_DefList(DefList);
    }
}

// `CompSt -> { DefList StmtList }`
void transl_CompSt(LevelNode* CompSt) {
    LevelNode* DefList = CompSt->childhead->next;
    transl_DefList(DefList);
    transl_StmtList(DefList->next);
}

/* ExtDef:
    - `-> Specifier ; ` 无操作
    - `-> Specifier FunDec CompSt`
    - 全局变量定义不会在本次实验中出现
*/
void transl_ExtDef(LevelNode* ExtDef) {
    LevelNode* Specifier = ExtDef->childhead;
    // Specifier 无操作
    if (!strcmp(Specifier->next->msg, "FunDec")) {
        transl_FunDec(Specifier->next);
        transl_CompSt(Specifier->next->next);
    }
    else ;
}

// 程序分析入口: `ExtDefList -> ExtDef ExtDefList | 空`
void transl_ExtDefList(LevelNode* ExtDefList) {
    if (!isemp(ExtDefList)) {
        LevelNode* ExtDef = ExtDefList->childhead;
        ExtDefList = ExtDef->next;
        transl_ExtDef(ExtDef);
        transl_ExtDefList(ExtDefList);
    }
}

int inter_repres(LevelNode* root) {
    initEntryIRNode();
    initVarFuncTable();
    transl_ExtDefList(root->childhead);
    ir_output();
}