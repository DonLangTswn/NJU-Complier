#include <stdio.h>

#define YYDEBUG     0
#define LAB_1_TREE  0    // lab1输出语法树

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
extern int semantic(struct levelNode* );

int main(int argc, char** argv) {
    int i, totchars = 0, totwords = 0, totlines = 0;
    if (argc < 2) {
        // yylex();
        printf("\nDone.\n");
        return 0;
    }
    for (i = 1; i < argc; i++) {
        FILE* f = fopen(argv[i], "r");
        if (!f) {
            perror(argv[i]);
            return 1;
        }
        yyrestart(f);
#if YYDEBUG
        yydebug = 1;
#endif
        yyparse();
        if (!errorline) {
#if LAB_1_TREE
            recurPrintSynTree(root, 0);
#endif
            semantic(root);
            fclose(f);
        }
    }
    return 0;
}