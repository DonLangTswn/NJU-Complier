# 编译原理lab2 实验报告

221220070 刁涟承

### 一、功能实现

- 在词法分析和语法分析程序的基础上，实现语义分析和类型检查；
- 无错误时应没有错误输出，有语法错误时准确报告错误类型、错误信息。
- **选做三**：将结构体间的类型等价机制由名等价改为**结构等价（*Structural Equivalence*）**

### 二、实现思路

#### 符号表设计

符号表对于编译器至关重要。为了尽可能实现时间和空间上的平衡，在实验初期阶段，我选择了***Multiset Discrimination***的形式进行符号表设计。这张表会记录下来程序中每个定义语句中出现的变量名，然后依照其名称进行排序，申请一张和总数一样大的符号表，每次查表二分查找即可。

```c
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
```

#### 类型表示

在设计类型结构体时，我用`struct SymbNode`类型存储变量内容，其中包含一个`struct Type`类型，用于存储变量的类型信息；用`struct FuncNode`类型存储函数信息，与`struct SymbNode`的唯一区别就是多了一个存放函数参数的链表。对于类型信息`Type`，比较重要的是数组和结构体的实现，均用多级链表的形式存储，结构体指针指向符号表中存放结构体类型的符号空间，其中也用链表存放了内部的成员变量：

```c
struct _Type {
    enum {
        _INT, _FLOAT, _STRUCT, _ARRAY, _STRUCT_TYPE,
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
```

#### 语义分析

语义分析分为两轮：

* 第一轮中，遍历全部语法树，找到诸如`VarDec`、`FunDec`、`OptTag`这样的节点，获取其定义的变量名称，根据名称大小插入符号表但状态为未定义，也不对类型进行定义；第一轮遍历结束后，根据得到的有序符号表和符号表大小，定义有序数组，可通过二分查找获取表项。
* 第二轮中，将程序语法树的`ExtDefList`作为入口，分别每个类型的节点进行语义分析处理，在每个节点内部再对其子节点进行分类型语义分析，主要检查变量类型、定义与否、重复定义等问题。这部分是主要的代码段内容，在其中分类讨论，检查类型和定义，并根据手册报告错误信息。

在语义分析中，比较突出重要的是`Exp`的分析。我将`Exp`根据语法分为如

> `exp_assign_opr()`: Exp ASSIGN Exp
> `exp_logic_opr()`:   Exp AND Exp | Exp OR Exp
> `exp_relop_opr()`:   Exp RELOP Exp
> `exp_2op_opr()`:       Exp ADD Exp | Exp SUB Exp | Exp MUL Exp | Exp DIV Exp

等等，多个类型处理，分别检测`Exp`的类型、左右值、运算符和赋值号左右两边类型匹配等问题，形成了不同分支的处理模式。

#### 	选做三：结构等价

选作三为了实现结构体结构等价，我将结构体的本体类型记作`STRUCT_TYPE`，对两个符号表中的`STRUCT_TYPE`，对其成员变量链表`StructMember`进行循环遍历比较，若数目不符或类型不匹配，则认为结构不等价，如果数目一致、类型相同，则认为结构等价。

```c
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
```

### 三、编译方式

可以使用`Code/Makefile`结合命令行进行编译：

```makefile
make clean: # 清除所有生成文件 
make t-%: # 用某个测试样例测试
make io-%: # 用某个样例测试并输出到out.txt
make c-%: #用某个样例测试并输出到out.txt，与预期输出文件比较
```

### 四、编译环境

操作系统：GNU Linux Release: Ubuntu 22.04 LTS, Kernel version 5.15.153.1-2；
编译器：GCC version 7.5.0；
词法分析工具：GNU Flex version 2.6.4；
语法分析工具：GNU Bison version 3.0.4。