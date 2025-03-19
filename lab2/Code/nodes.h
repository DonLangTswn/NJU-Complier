#ifndef __NODES_H__
#define __NODES_H__

typedef struct levelNode LevelNode;

// 语法树结点定义
struct levelNode {
    char* msg;
    int line;
    char* typ;
    struct levelNode* childhead, *childtail;
    struct levelNode* next;
};

#endif