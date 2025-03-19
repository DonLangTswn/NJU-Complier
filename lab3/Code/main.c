#include <stdio.h>

#define YYDEBUG     0
#define LAB_1_TREE  0    // lab1输出语法树
#define IR_REDIREC  1    // lab3后，重定向输出

#if YYDEBUG
extern int yydebug;
#endif
extern FILE* yyin;
// 词法分析
// extern int yylex(void);
// 语法分析
extern int yyparse(void);
extern void yyrestart(FILE *);
extern int errorline;
extern struct levelNode *root;
extern void recurPrintSynTree(struct levelNode* , int);
// 语义分析
extern int semErrNum;
extern int semantic(struct levelNode* );
// 中间代码生成
extern int inter_repres(struct levelNode* );

int main(int argc, char** argv) {
    int totchars = 0, totwords = 0, totlines = 0;
#if IR_REDIREC
    if (argc < 3)
#else
    if (argc < 2)
#endif
    {
        // yylex();
        fprintf(stderr, "Unmatched input & output file number.\n");
        return 0;
    }
    FILE* input = fopen(argv[1], "r");
#if IR_REDIREC
    FILE* output = freopen(argv[2], "w", stdout);
#endif
    if (!input) {
        fprintf(stderr, "Error opening input file %s.\n", argv[1]);
        return 1;
    }
#if IR_REDIREC
    if (!output) {
        fprintf(stderr, "Error redirecting stdout to output file %s.\n", argv[2]);
        return 1;
    }
#endif
    yyrestart(input);
#if YYDEBUG
    yydebug = 1;
#endif
    yyparse();
    if (!errorline) {
#if LAB_1_TREE
        recurPrintSynTree(root, 0);
#endif
        semantic(root);
        if (!semErrNum) {
            inter_repres(root);
        }
    }
    fclose(input);
    fclose(stdout);
    return 0;
}