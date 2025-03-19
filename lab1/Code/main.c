#include <stdio.h>
// #define YYDEBUG 1

#if YYDEBUG
extern int yydebug;
#endif
extern FILE* yyin;
// extern int yylex(void);
extern int yyparse(void);
extern void yyrestart(FILE *);
extern int errorline;
extern struct levelNode {
    char* msg;
    int line;
    char* typ;
    struct levelNode* childhead, *childtail;
    struct levelNode* next;
} *root;
extern void recurPrintSynTree(struct levelNode* , int);

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
            recurPrintSynTree(root, 0);
        }
        fclose(f);
    }
    return 0;
}