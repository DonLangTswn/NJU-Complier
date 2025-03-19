#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "nodes.h"
#include "semantic.h"
#include "checktable.h"

// 符号表大小
int symbTableSize = 0;
int funcTableSize = 0;

SymbNode *symbTable;
FuncNode *funcTable;

// `INDEXED` ARRAIES
SymbNode **symb_table;
FuncNode **func_table;

/* --------------------
    第一次遍历语法树
    - 初始化表
    - 确定表长
    - 分配空间
 -------------------- */

// 分配新变量表节点的空间
SymbNode* newSymbNode(char* name) {
    SymbNode* new = (SymbNode *)malloc(sizeof(SymbNode));
    new->def = 0;
    new->name = (char *)malloc(sizeof(char) * strlen(name));
    strcpy(new->name, name);
    return new;
}
// 分配新函数表节点的空间
FuncNode* newFuncNode(char* name) {
    FuncNode* new = (FuncNode *)malloc(sizeof(FuncNode));
    new->def = 0;
    new->name = (char *)malloc(sizeof(char) * strlen(name));
    strcpy(new->name, name);
    return new;
}
// 将新节点加入变量符号表
void addSymbTable(SymbNode* node, int lineno) {
    SymbNode* curr = symbTable;
    while (curr->next && strcmp(node->name, curr->next->name) >= 0) {
        curr = curr->next;
    }
    if (!strcmp(node->name, curr->name)) {
        return ;
    } else {
        node->next = curr->next;
        curr->next = node;
    }
    symbTableSize++;
}
// 将新节点加入函数符号表
void addFuncTable(FuncNode* node, int lineno) {
    FuncNode* curr = funcTable;
    while (curr->next && strcmp(node->name, curr->next->name) >= 0) {
        curr = curr->next;
    }
    if (!strcmp(node->name, curr->name)) {
        return ;
    } else {
        node->next = curr->next;
        curr->next = node;
    }
    funcTableSize++;
}

// 用Dummy-node初始化链表
void initDummyNode() {
    symbTable = newSymbNode("DUMMY");
    funcTable = newFuncNode("DUMMY");
}

// 第一次递归遍历语法树
void firstReadTree(LevelNode* root) {
    LevelNode* curr = root;
    while (curr) {
        if (!strcmp(curr->msg, "VarDec") && strcmp(curr->childhead->msg, "VarDec")) {
            addSymbTable(newSymbNode(getID(curr)), curr->line);
        }
        else if (!strcmp(curr->msg, "OptTag") && !isemp(curr)) {
            addSymbTable(newSymbNode(getID(curr)), curr->line);
        }
        else if (!strcmp(curr->msg, "FunDec")) {
            addFuncTable(newFuncNode(getID(curr)), curr->line);
        }
        firstReadTree(curr->childhead);
        curr = curr->next;
    }
}

// 初始化变量名表、函数名表的下标
void initIndexedTable() {
    // 初始化变量名表
    symb_table = (SymbNode**)malloc(sizeof(SymbNode *) * symbTableSize);
    int index = 0;
    SymbNode* ptr = symbTable->next;
    while (ptr) {
        symb_table[index++] = ptr;
        SymbNode* tmp = ptr;
        ptr = ptr->next;
        tmp->next = NULL;
    }
    // 初始化函数名表
    func_table = (FuncNode**)malloc(sizeof(FuncNode *) * funcTableSize);
    index = 0;
    FuncNode* fptr = funcTable->next;
    while (fptr) {
        func_table[index++] = fptr;
        FuncNode* tmp = fptr;
        fptr = fptr->next;
        tmp->next = NULL;
    }
}

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

/* --------------------
    第二次遍历语法树
    - 检查定义
    - 赋类型值
    - 检查调用（类型）
-------------------- */

// `Args -> Exp , Args | Exp`
ExpType* handle_Args(LevelNode* Args) {
    LevelNode* Exp = Args->childhead;
    ExpType* argTyp = (ExpType *)malloc(sizeof(ExpType));
    ExpType tempTyp = handle_Exp(Exp);
    argTyp->etype = tempTyp.etype;
    argTyp->lr = tempTyp.lr;
    if (Exp->next) {
        Args = Exp->next->next;
        argTyp->next = handle_Args(Args);
    }
    return argTyp;
}

// ID ( Args ) | ID ( )   1.检查是否为函数类型  2.比较实参和形参列表  3.返回右值
ExpType exp_func_call(LevelNode* Exp) {
    ExpType EType;
    FuncNode* func = getFunc(getID(Exp));
    if (!func) {
        if (getSymb(getID(Exp)))
            semerror(11, Exp->line);
        else semerror(2, Exp->line);
        EType.lr = ErrTyp;
    }
    else if (!strcmp(Exp->childhead->next->next->msg, "Args")) {
        // 有实参传入，处理实参：
        ExpType* arglist = handle_Args(Exp->childhead->next->next);
        ExpType* arg = arglist;
        SymbNode* param = func->params;
        while (param && arg) {
            if (!check_Type(&param->dType, &arg->etype))
                break;
            arg = arg->next;
            param = param->next;
        }
        if (!param && !arg) {
            EType.etype = func->rType;
            EType.lr = RValue;
        }
        else {
            semerror(9, Exp->line);
            EType.lr = ErrTyp;
        }
    }
    else {  // 无实参传入，若亦无形参，则正确，返回返回值类型
        if (!func->params) {
            EType.etype = func->rType;
            EType.lr = RValue;
        }
        else {
            semerror(9, Exp->line);
            EType.lr = ErrTyp;
        }
    }
    return EType;
}

// SUB Exp  0. 检查有无 ErrTyp  1. 检查是否为基本类型， 2. 保持原类型， 3. 返回右值
ExpType exp_ngtv_opr(LevelNode* Exp) {
    Exp = Exp->childhead->next;
    ExpType Etype = handle_Exp(Exp);
    if (iserr(Etype))
        Etype.lr = ErrTyp;
    else if (Etype.etype.type != _INT && Etype.etype.type != _FLOAT) {
        semerror(7, Exp->line);
        Etype.lr = ErrTyp;
    }
    else Etype.lr = RValue;
    return Etype;
}

// NOT Exp  0. 检查有无 ErrTyp  1. 检查是否为`INT`类型， 2. 保持`INT`类型， 3. 返回右值
ExpType exp_not_opr(LevelNode* Exp) {
    Exp = Exp->childhead->next;
    ExpType Etype = handle_Exp(Exp);
    if (iserr(Etype))
        Etype.lr = ErrTyp;
    else if (Etype.etype.type != _INT) {
        semerror(7, Exp->line);
        Etype.lr = ErrTyp;
    }
    else Etype.lr = RValue;
    return Etype;
}

// ID   1. 在符号表中查找， 2. 返回符号表中类型， 3. 返回左值
ExpType exp_id(LevelNode* Exp) {
    ExpType EType;
    SymbNode* symb = getSymb(getID(Exp));
    if (!symb) {
        semerror(1, Exp->line);
        EType.lr = ErrTyp;
    } else {
        EType.etype = symb->dType;
        EType.lr = LValue;
    }
    return EType;
}

// INT | FLOAT  返回右值
ExpType exp_basic(LevelNode* Exp) {
    ExpType EType;
    LevelNode* basic = Exp->childhead;
    EType.etype.type = !strncmp(basic->msg, "INT", 3) ? _INT : _FLOAT;
    EType.lr = RValue;
    return EType;
}

// Exp ASSIGN Exp   0. 检查有无 ErrTyp  1. 检查是否为左值 2. 检查类型匹配  3. 返回右值
ExpType exp_assign_opr(LevelNode* Exp) {
    ExpType EType1, EType2, EType;
    Exp = Exp->childhead;
    EType1 = handle_Exp(Exp);
    EType2 = handle_Exp(Exp->next->next);
    if (iserr(EType1) || iserr(EType2))
        EType.lr = ErrTyp;
    else if (EType1.lr == LValue) {
        if (check_Type(&EType1.etype, &EType2.etype)) {
            EType.lr = RValue;
            EType.etype = EType1.etype;
        } else {
            semerror(5, Exp->line);
            EType.lr = ErrTyp;
        }
    } else {
        semerror(6, Exp->line);
        EType.lr = ErrTyp;
    }
    return EType;
}

// Exp AND Exp | Exp OR Exp    0. 检查有无 ErrTyp  1. 检查是否为INT 2.返回INT  3.返回右值
ExpType exp_logic_opr(LevelNode* Exp) {
    ExpType EType1, EType2, EType;
    Exp = Exp->childhead;
    EType1 = handle_Exp(Exp);
    EType2 = handle_Exp(Exp->next->next);
    if (iserr(EType1) || iserr(EType2))
        EType.lr = ErrTyp;
    else if (EType1.etype.type != _INT || EType2.etype.type != _INT) {
        semerror(7, Exp->line);
        EType.lr = ErrTyp;
    }
    else {
        EType.etype.type = _INT;
        EType.lr = RValue;
    }
    return EType;
}

// Exp RELOP Exp    0.检查有无 ErrTyp  1.检查是否为基本类型  2.检查类型是否一致  3.返回`INT`  4.返回右值
ExpType exp_relop_opr(LevelNode* Exp) {
    ExpType EType1, EType2, EType;
    Exp = Exp->childhead;
    EType1 = handle_Exp(Exp);
    EType2 = handle_Exp(Exp->next->next);
    if (iserr(EType1) || iserr(EType2))
        EType.lr = ErrTyp;
    else if (EType1.etype.type == _INT && EType2.etype.type == _INT || EType1.etype.type == _FLOAT && EType2.etype.type == _FLOAT) {
        EType.etype.type = _INT;
        EType.lr = RValue;
    }
    else {
        semerror(7, Exp->line);
        EType.lr = ErrTyp;
    }
    return EType;
}

// Exp ADD Exp | Exp SUB Exp | Exp MUL Exp | Exp DIV Exp
// 0.检查有无 ErrTyp  1.检查是否为基本类型  2.检查类型是否一致  3.返回原类型  4.返回右值
ExpType exp_2op_opr(LevelNode* Exp) {
    ExpType EType1, EType2, EType;
    Exp = Exp->childhead;
    EType1 = handle_Exp(Exp);
    EType2 = handle_Exp(Exp->next->next);
    if (iserr(EType1) || iserr(EType2))
        EType.lr = ErrTyp;
    else if (EType1.etype.type == _INT && EType2.etype.type == _INT || EType1.etype.type == _FLOAT && EType2.etype.type == _FLOAT) {
        EType = EType1;
        EType.lr = RValue;
    }
    else {
        semerror(7, Exp->line);
        EType.lr = ErrTyp;
    }
    return EType;
}

/* Exp [ Exp ]  
    0. 检查有无 ErrTyp  
    1. 检查第二个`Exp`是否为`INT`类型  2.检查第一个`Exp`是否为`Array`类型 
    3. 返回数组下一层的Type  4.返回左值 
*/
ExpType exp_array_ind(LevelNode* Exp) {
    ExpType EType1, EType2, EType;
    Exp = Exp->childhead;
    EType1 = handle_Exp(Exp);
    EType2 = handle_Exp(Exp->next->next);
    if (iserr(EType1) || iserr(EType2))
        EType.lr = ErrTyp;
    else if (EType1.etype.type != _ARRAY) {
        semerror(10, Exp->line);
        EType.lr = ErrTyp;
    }
    else if (EType2.etype.type != _INT) {
        semerror(12, Exp->line);
        EType.lr = ErrTyp;
    }
    else {
        EType.lr = LValue;
        EType.etype = *EType1.etype.value.Array.arrayElem;
    }
    return EType;
}

/* Exp DOT ID
    0. 检查有无 ErrTyp  
    1. 检查第一个`Exp`是否为`STRUCT`类型
    2. 检查该结构体中是否存在域为`id`
    3. 返回`Struct.id`的类型
    4. 返回左值
*/
ExpType exp_struct_dot(LevelNode* Exp) {
    Exp = Exp->childhead;
    ExpType EType = handle_Exp(Exp);
    if (EType.etype.type != _STRUCT) {
        semerror(13, Exp->line);
        EType.lr = ErrTyp;
    }
    else {
        SymbNode* stru = EType.etype.value.Struct;
        SymbNode* member = stru->dType.value.StructMember;
        char* scopId = Exp->next->next->msg + 4;
        while (member) {
            if (!strcmp(member->name, scopId)) {
                EType.etype = member->dType;
                EType.lr = LValue;
                break;
            }
            member = member->next;
        }
        if (!member) {
            semerror(14, Exp->line);
            EType.lr = ErrTyp;
        }
    }
    return EType;
}

/* 分类处理`Exp`部分的各种表达式类型
Exp ->
    ( Exp ): 嵌套调用即可
    `exp_id()`:         ID
    `exp_basic()`:      INT | FLOAT
    `exp_func_call()`:  ID ( Args ) | ID ( )
    `exp_ngtv_opr()`:   SUB Exp
    `exp_not_opr()`:    NOT Exp
    `exp_assign_opr()`: Exp ASSIGN Exp
    `exp_logic_opr()`:  Exp AND Exp | Exp OR Exp
    `exp_relop_opr()`:  Exp RELOP Exp
    `exp_2op_opr()`:    Exp ADD Exp | Exp SUB Exp | Exp MUL Exp | Exp DIV Exp
    `exp_array_ind()`:  Exp [ Exp ]
    `exp_struct_dot()`: Exp DOT ID
*/
ExpType handle_Exp(LevelNode* Exp) {
    if (!strcmp(Exp->childhead->msg, "LP")) {
        Exp = Exp->childhead->next;
        return handle_Exp(Exp);
    }
    else if (!Exp->childhead->next) {
        if (!strncmp(Exp->childhead->msg, "ID", 2)) {
            return exp_id(Exp);
        }
        else {
            return exp_basic(Exp);
        }
    }
    else if (!strcmp(Exp->childhead->msg, "MINUS")) {
        return exp_ngtv_opr(Exp);
    }
    else if (!strcmp(Exp->childhead->msg, "NOT")) {
        return exp_not_opr(Exp);
    }
    else if (!strncmp(Exp->childhead->msg, "ID", 2)) {
        return exp_func_call(Exp);
    }
    LevelNode* opr = Exp->childhead->next;
    if (!strcmp(opr->msg, "ASSIGNOP")) {
        return exp_assign_opr(Exp);
    }
    else if (!strcmp(opr->msg, "AND") || !strcmp(opr->msg, "OR")) {
        return exp_logic_opr(Exp);
    }
    else if (!strcmp(opr->msg, "RELOP")) {
        return exp_relop_opr(Exp);
    }
    else if (!strcmp(opr->msg, "PLUS") || !strcmp(opr->msg, "MINUS") || !strcmp(opr->msg, "STAR") || !strcmp(opr->msg, "DIV")) {
        return exp_2op_opr(Exp);
    }
    else if (!strcmp(opr->msg, "LB")) {
        return exp_array_ind(Exp);
    }
    else if (!strcmp(opr->msg, "DOT")) {
        return exp_struct_dot(Exp);
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
void handle_Stmt(LevelNode* Stmt, Type* rtype) {
    if (!strcmp(Stmt->childhead->msg, "Exp")) {
        handle_Exp(Stmt->childhead);   
    }
    else if (!strcmp(Stmt->childhead->msg, "CompSt")) {
        LevelNode* CompSt = Stmt->childhead;
        handle_CompSt(CompSt, rtype);
    }
    else if (!strcmp(Stmt->childhead->msg, "RETURN")) {
        LevelNode* Exp = Stmt->childhead->next;
        // Check return type & function type
        if (!rtype) return;
        ExpType EType = handle_Exp(Exp);
        if (!iserr(EType) && !check_Type(rtype, &EType.etype)) {
            semerror(8, Exp->line);
        }
    }
    else if (!strcmp(Stmt->childhead->msg, "IF")) {
        LevelNode* Exp = Stmt->childhead->next->next;
        Stmt = Exp->next->next;
        ExpType EType = handle_Exp(Exp);
        if (!iserr(EType) && EType.etype.type != _INT) {   // Check type of `Exp`: int only
            semerror(7, Exp->line);
        }
        handle_Stmt(Stmt, rtype);
        if (Stmt->next) {
            Stmt = Stmt->next->next;
            handle_Stmt(Stmt, rtype);
        }
    }
    else if (!strcmp(Stmt->childhead->msg, "WHILE")) {
        LevelNode* Exp = Stmt->childhead->next->next;
        Stmt = Exp->next->next;
        ExpType EType = handle_Exp(Exp);
        if (!iserr(EType) && EType.etype.type != _INT) {   // Check type of `Exp`: int only
            semerror(7, Exp->line);
        }
        handle_Stmt(Stmt, rtype);
    }
}

// `StmtList -> Stmt StmtList | 空`
void handle_StmtList(LevelNode* StmtList, Type* rtype) {
    if (!isemp(StmtList)) {
        LevelNode* Stmt = StmtList->childhead;
        StmtList = Stmt->next;
        handle_Stmt(Stmt, rtype);
        handle_StmtList(StmtList, rtype);
    }
}

// 处理`Specifier`部分并将类型返回给程序
Type* handle_Specifier(LevelNode* Specifier) {
    Type* dtype = (Type *)malloc(sizeof(Type));
    if (!strncmp(Specifier->childhead->msg, "TYPE", 4)) {
        char* typMsg = Specifier->childhead->msg + 6;
        if (!strcmp(typMsg, "int"))
            dtype->type = _INT;
        else if (!strcmp(typMsg, "float"))
            dtype->type = _FLOAT;
    }
    else {  // StructSpecifier
        dtype->type = _STRUCT;
        dtype->value.Struct = handle_StructSpecifier(Specifier->childhead);
        // 若返回NULL，则无`StructType`定义
        if (!dtype->value.Struct) {
            dtype = NULL;
        }
    }
    return dtype;
}


/* `StructSpecifier`
    `-> STRUCT OptTag { DefList }`
    `-> STRUCT Tag`
 作为处理`StructSpecifier`的函数，两个任务：
    - 1-1，若为新定义`STRUCT_TYPE`，建立并填写对应的结点`SymbNode`
    - 1-2，若为`STRUCT Tag`，在符号表中检查定义并报未定义错，在上一级`Specifier`里检查`NULL`指针
    - 2，返回`STRUCT_TYPE`的`SymbNode *`指针
 */
SymbNode* handle_StructSpecifier(LevelNode* StructSpecifier) {
    LevelNode* tag = StructSpecifier->childhead->next;
    SymbNode* struTyp;
    if (!strcmp(tag->msg, "Tag")) {  // STRUCT `Tag`, 检查定义
        struTyp = getSymb(getID(tag));;
        if (!struTyp || struTyp->def == 0) {
            semerror(17, StructSpecifier->line);  // 没找到定义，报错并返回 NULL
        }
    }
    else {  // STRUCT `OptTag` { DefList }，新定义
        LevelNode* DefList = tag->next->next;
        char* optID = handle_OptTag(tag);
        if (optID) {    // 将新定义加入符号表
            struTyp = getSymb(optID);
            if (!struTyp->def) {
                struTyp->def = 1;
                struTyp->dType.type = _STRUCT_TYPE;
                struTyp->dType.value.StructMember = handle_DefList(DefList, true);
            }
            else {
                semerror(16, StructSpecifier->line);
            }
        }
        else {
            struTyp = (SymbNode *)malloc(sizeof(SymbNode));
            struTyp->name = "";
            struTyp->def = 1;
            struTyp->dType.type = _STRUCT_TYPE;
            struTyp->dType.value.StructMember = handle_DefList(DefList, true);
        }
    }
    return struTyp;
}

// `OptTag -> ID | 空 ("EMPTY")`
char* handle_OptTag(LevelNode* OptTag) {
    if (!isemp(OptTag)) {
        return getID(OptTag);
    }
    else return NULL;
}

/* 递归处理`VarDec`中的内容
    - `ID`: 
    - `VarDec [ INT ]`:
*/
SymbNode* handle_VarDec(LevelNode* VarDec, Type* dtype, bool in_struct) {
    if (!dtype) {
        return NULL;
    }
    Type* currType = (Type *)malloc(sizeof(Type));
    if (!strcmp(VarDec->childhead->msg, "VarDec")) {    // VarDec [ INT ]
        currType->type = _ARRAY;
        currType->value.Array.arraySize = atoi(getINT(VarDec));   // 'INT: x'
        currType->value.Array.arrayElem = dtype;
        return handle_VarDec(VarDec->childhead, currType, in_struct);
    }
    else {  // ID
        SymbNode* symb = getSymb(getID(VarDec));
        if (!symb->def) {
            symb->def = 1;
            symb->dType = *dtype;
            return symb;
        }
        else {
            if (in_struct) {
                semerror(15, VarDec->line);
            }
            else semerror(3, VarDec->line);
            return NULL;
        }
    }
}

/* 在`VarDec`基础上，增加了赋值的功能
    - `-> VarDec`
    - `-> VarDec = Exp`  #只有结构体之外可以
*/
SymbNode* handle_Dec(LevelNode* Dec, Type* dtype, bool in_struct) {
    LevelNode* VarDec = Dec->childhead;
    if (in_struct && VarDec->next) {
        semerror(15, Dec->line);
    }
    else if (VarDec->next) {
        LevelNode* Exp = VarDec->next->next;
        ExpType etype = handle_Exp(Exp);
        //  Compare Types ...
        if (!iserr(etype) && !check_Type(dtype, &etype.etype))
            semerror(5, Dec->line);
    }
    return handle_VarDec(VarDec, dtype, in_struct);
}

// `DecList -> Dec | Dec , DecList`，定义语句中的变量列表，逗号隔开
SymbNode* handle_DecList(LevelNode* DecList, Type* dtype, bool in_struct) {
    if (!DecList)
        return NULL;
    LevelNode* Dec = DecList->childhead;
    SymbNode* dec_list = handle_Dec(Dec, dtype, in_struct);
    if (Dec->next) {
        DecList = Dec->next->next;
        if (dec_list)
            dec_list->next = handle_DecList(DecList, dtype, in_struct);
        else dec_list = handle_DecList(DecList, dtype, in_struct);
    }
    return dec_list;
}

// `Def -> Specifier DecList ;`, 单句定义语句
SymbNode* handle_Def(LevelNode* Def, bool in_struct) {
    LevelNode* Specifier = Def->childhead;
    LevelNode* DecList = Def->childhead->next;
    Type* dtype = handle_Specifier(Specifier);
    return handle_DecList(DecList, dtype, in_struct);
}

/* `DefList -> Def DefList | 空`，递归处理非空`DefList`, 调用处理每个`Def`
    + 为了实现结构体内部变量定义，需要将每个变量`next`指向下一个，以此形成变量链表
    + 另加一个，是否为结构体内部: `bool in_struct`
*/
SymbNode* handle_DefList(LevelNode* DefList, bool in_struct) {
    SymbNode* def_list = NULL;
    if (!isemp(DefList)) {
        LevelNode* Def = DefList->childhead;
        DefList = Def->next;
        def_list = handle_Def(Def, in_struct);
        if (def_list) {
            SymbNode* p_def = def_list;
            while (p_def->next) p_def = p_def->next;
            p_def->next = handle_DefList(DefList, in_struct);
        }
        else def_list = handle_DefList(DefList, in_struct);
    }
    return def_list;
}

// `ParamDec -> Specifier VarDec`，函数参数列表中的单个参数定义
SymbNode* handle_ParamDec(LevelNode* ParamDec) {
    LevelNode* Specifier = ParamDec->childhead;
    LevelNode* VarDec = Specifier->next;
    Type* dtype = handle_Specifier(Specifier);
    return handle_VarDec(VarDec, dtype, false);
}

// `VarList -> ParamDec , VarList | ParamDec`, 函数的参数列表
SymbNode* handle_VarList(LevelNode* VarList) {
    LevelNode* ParamDec = VarList->childhead;
    SymbNode* var_list = handle_ParamDec(ParamDec);
    if (ParamDec->next) {
        if (var_list)
            var_list->next = handle_VarList(ParamDec->next->next);
        else var_list = handle_VarList(ParamDec->next->next);
    }
    return var_list;
}

// `FunDec -> ID ( ) | ID ( VarList )`，函数头部定义
void handle_FunDec(LevelNode* FunDec, Type* dtype) {
    LevelNode* ID = FunDec->childhead;
    FuncNode* func = getFunc(getID(FunDec));
    if (!func->def) {
        func->def = 1;
        if (dtype)
            func->rType = *dtype;
    }
    else semerror(4, FunDec->line);
    if (!strcmp(ID->next->next->msg, "RP")) {   // 无参数
        func->params = NULL;
    }
    else {  // 有参数
        func->params = handle_VarList(ID->next->next);
    }
}

// `CompSt -> { DefList StmtList }`
void handle_CompSt(LevelNode* CompSt, Type* rtype) {
    LevelNode* DefList = CompSt->childhead->next;
    LevelNode* StmtList = DefList->next;
    handle_DefList(DefList, false);
    handle_StmtList(StmtList, rtype);
}

// 遍历`ExtDecList`中的每个`VarDec`，并且为每个变量赋类型`dtype`属性
void handle_ExtDecList(LevelNode* ExtDecList, Type* dtype) {
    LevelNode* VarDec = ExtDecList->childhead;
    handle_VarDec(VarDec, dtype, false);
    if (VarDec->next) {     // `VarDec COMMA ExtDecList`
        handle_ExtDecList(VarDec->next->next, dtype);
    }
}

/* ExtDef：
    - `-> Specifier ExtDecList ;`
    - `-> Specifier ;`
    - `-> Specifier FunDec CompSt`
*/
void handle_ExtDef(LevelNode* ExtDef) {
    LevelNode *Specifier = ExtDef->childhead;
    Type* dtype = handle_Specifier(Specifier);
    if (!strcmp(Specifier->next->msg, "ExtDecList")) {
        handle_ExtDecList(Specifier->next, dtype);
    }
    else if (!strcmp(Specifier->next->msg, "FunDec")) {
        handle_FunDec(Specifier->next, dtype);
        handle_CompSt(Specifier->next->next, dtype);
    }
    else ;  // -> Specifier ;
}
 
// 第二轮遍历：分析程序的入口 `ExtDefList -> ExtDef ExtDefList | 空`
void handle_ExtDefList(LevelNode* ExtDefList) {
    if (!isemp(ExtDefList)) {
        LevelNode* ExtDef = ExtDefList->childhead;
        ExtDefList = ExtDef->next;
        handle_ExtDef(ExtDef);
        handle_ExtDefList(ExtDefList);
    }
}

void printTables() {
    printf("SymbTable: ");
    SymbNode* pchar = symbTable->next;
    while (pchar) {
        printf("%s ", pchar->name);
        pchar = pchar->next;
    } printf("\nFuncTable: ");
    FuncNode* pfunc = funcTable->next;
    while (pfunc) {
        printf("%s ", pfunc->name);
        pfunc = pfunc->next;
    } printf("\n");
}

void checkTables() {
    printf("---------- SymbTable: ----------\n");
    check_SymbTable(symb_table, symbTableSize);
    printf("---------- FuncTable: ----------\n");
    check_FuncTable(func_table, funcTableSize);
    printf("\n");
}

// 相当于main函数
int semantic(LevelNode* root) {
    initDummyNode();
    firstReadTree(root);
#if CHECK_TABLE
    printTables();
#endif
    initIndexedTable();
    handle_ExtDefList(root->childhead);
#if CHECK_TABLE
    checkTables();
#endif
    return 0;
}