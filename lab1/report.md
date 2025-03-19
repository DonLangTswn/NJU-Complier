# 编译原理lab1 实验报告

### 一、功能实现

- 识别词法错误 (错误类型 A)
- 识别语法错误 (错误类型 B)
- 无错误时输出相应的语法树
- **选做三**：识别`“//”`和`“/*…*/”`形式的注释。若输入文件中包含不符合定义的注释，给出由不符合定义的注释所引发的错误的提示信息

### 二、实现思路

#### 	词法分析

根据实验手册，在`Code\lexical.l`中定义每个token对应的正则表达式，并在检测到相应词法时匹配相应的规则。当匹配到`.`时，为之报出词法错误。以下用整数类型示例：

```latex
DEC_INT   0|[1-9][0-9]*
HEX_INT   0[Xx][0-9a-fA-F]+
OCT_INT   0[0-7]+
INT       ({DEC_INT})
WRONG_INT ({HEX_INT}|{OCT_INT})
```

```c
{WRONG_INT} {
    isError = 1;
    fprintf(stderr, "Error type A at Line %d:  Illegal hex/oct type integer '%s'\n", yylloc.first_line, yytext);
    char* msg = makeLexMsg("ERROR: WROGN_INT = ", yytext);
    yylval.Node = createNode(msg, yylineno, "TOKEN");
    return INT;
}
{INT} {
    char* msg = makeLexMsg("INT: ", yytext);
    yylval.Node = createNode(msg, yylineno, "TOKEN");
    return INT;
}
```

#### 	语法分析

1. 根据实验手册，在`Code\syntax.y`中定义不同非终结符的文法并匹配相应的规则。在语法规则中加入`error`用以识别和规约可能出现的语法错误。以下用`Exp -> Exp ADD Exp`的规则部分代码举例：

   ```c
   Exp: ... 
   	| Exp ADD Exp {
           struct levelNode* newNode = createNode("Exp", $1->line, "NON_TERMINAL");
           addChild(newNode, $1);
           addChild(newNode, $2);
           addChild(newNode, $3);
           $$ = newNode;
       }
   ```

2. 定义`levelNode`结构体类型，用于统一语法树中结点的结构，并且在文法规则中，所有token和非终结符都用`levelNode`进行定义：

   ```c
   struct levelNode {
       char* msg;
       int line;
       char* typ;
       struct levelNode* childhead, *childtail;
       struct levelNode* next;
   } *root;
   	...
   %token<Node> INT FLOAT ID TYPE
       ...
   %type<Node> CompSt StmtList Stmt
       ...
   ```

3. 设置全局变量`int errorline = 0`，一旦在`lexical.l`或`syntax.y`中检测到出现A或B类型的错误，则将其更新为`yylineno`，若`errorline == yylineno`则意味着同一行已经报过一次错，则不再报错；若`errorline`不等于`0`，意味着存在错误行，在main函数中则不再输出语法树。
4. 输出语法树：利用之前定义的结构体`struct levelNode`，结合自定义递归输出函数，打印语法树：

```c
void recurPrintSynTree(struct levelNode* root, int level) {
    struct levelNode* curr = root;
    while (curr) {
        if (strcmp(curr->msg, "EMPTY")) {
            if (strcmp(curr->typ, "TOKEN"))
                printNodeMsg(level, makeSynMsg(curr->msg, curr->line));
            else
                printNodeMsg(level, curr->msg);
            recurPrintSynTree(curr->childhead, level + 1);
        }
        curr = curr->next;
    }
}
```

#### 	选做三：识别注释

在`lexical.l`中加入如下代码，分别用于识别单行注释和多行注释。

1. 在识别单行注释时，利用`input()`库函数，每次读入一个词，检测是否为换行符。若为其它字符则忽略不处理，继续读入；一旦换行则退出循环

```c
"//" {
    char c = input();
    while (c != '\n' && c != '\0')
        c = input();
    yylineno++;
}
```
2. 在处理多行注释时，利用`input()`，逐个字符向后检测，如果并不是多行注释终结符`*/`，则忽略不做处理，继续读入；一旦检测到`*/`则退出循环

```c
"/*" {
    char c1 = input();
    char c2 = input();
    while (!(c1 == '*' && c2 == '/') && c2 != '\0') {
        if (c1 == '\n') yylineno++;
        c1 = c2;
        c2 = input();
    }
}
```

### 三、编译方式

可以使用`Code/Makefile`结合命令行进行编译：

```makefile
make clean: # 清除所有生成文件 
make test: # 用自定义测试样例测试
make t-%: # 用某个测试样例测试
make io-%: # 用某个样例测试并输出到out.txt
make c-%: #用某个样例测试并输出到out.txt，与预期输出文件比较
```

### 四、编译环境

操作系统：GNU Linux Release: Ubuntu 22.04 LTS, Kernel version 5.15.153.1-2；
编译器：GCC version 7.5.0；
词法分析工具：GNU Flex version 2.6.4；
语法分析工具：GNU Bison version 3.0.4。
