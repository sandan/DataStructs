#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include <stdint.h>
#include <stdbool.h>
#include "../data/data.h"

#define N 4096
#define FLUSH_SIZE 1024*32

/**
 Binary Trees satisfy :
   Any node has at most two children
   For any cherry, the left < parent < right
**/
//the binary tree 
typedef struct tnode {
 item_t data;                 //data item held in node, 12 bytes x,y,z
 struct tnode *left;          //pointer to right subtree
 struct tnode *right;          //pointer to left subtree
 struct tnode *parent;          //pointer to parent node
} tnode;


//Binary Tree API

tnode* search_tree(tnode *t, item_t data);
tnode* find_min(tnode *t);
tnode* find_max(tnode *t);
void traverse_tree(tnode *t);

#endif
