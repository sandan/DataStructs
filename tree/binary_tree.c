#include "../headers/binary_tree.h"
#include <stdlib.h>
#include <stdio.h>

tnode *search_tree(tnode *t, item_t data){

  if (t == NULL) return NULL;
  
  if (t->data.data == data.data) return t;

  if (t->data.data > data.data){
    return search_tree(t->left, data);
  } else {
    return search_tree(t->right, data);
  }
}

tnode *find_min(tnode* t){

  if (t == NULL) return NULL;
  
  if (t->left == NULL){
    return t;
  } else {
    return find_min(t->left);
  }
}


tnode *find_max(tnode* t){

  if (t == NULL) return NULL;
  
  if (t->right == NULL){
    return t;
  } else {
    return find_max(t->right);
  }
}

/** 
  In oder traversal (l, me, r) 
  Pre Order traversal (me, l ,r)
  Post Order traversal (l ,r, me)
**/
void traverse_tree(tnode *t){
  if ( t == NULL ) return;
//in order traversal
  traverse_tree(t->left);
  printf("[ %u ] ", t->data.data);
  //process current node
  traverse_tree(t->right);
}

//helper method for insert
//what we need is a pointer to parent->left or parent->right
// or else theres no way to associate parent->left/right 
// with the new node we malloc'd, so not this:
/*
void insert_tree(tnode *t, item_t x, tnode *parent){
  if (t == NULL){
     t = (tnode*)(malloc(sizeof(tnode)));
     t->parent = parent;
     t->left = t->right = NULL;
     t->data = x;
     return;
  }

  if (t->data.data > x.data){
    insert_tree(t->left, x, t);

  } else{
    insert_tree(t->right, x, t);
  }
}

*/

void insert_tree(tnode **t, item_t x, tnode *parent){
  if (*t == NULL){
     *t = (tnode*)(malloc(sizeof(tnode)));
     (*t)->parent = parent;
     (*t)->left = (*t)->right = NULL;
     (*t)->data = x;
     
     return;
  }

  if ((*t)->data.data > x.data){
    insert_tree(&((*t)->left), x, *t);

  } else{
    insert_tree(&((*t)->right), x, *t);
  }
}

//insert takes the pointer of the root node and a data item to insert
void insert(item_t x, tnode *parent){

  if (parent->data.data > x.data){
    insert_tree(&(parent->left), x, parent);
  }else {
    insert_tree(&(parent->right), x, parent);
  }
}


bool isLeaf(tnode *t){
 return (t->left ==NULL && t->right ==NULL) ? true:false;
}

bool isRoot(tnode* t){
  return t->parent == NULL ? true:false;
}

uint32_t max(uint32_t a, uint32_t b){
  return a>b ? a:b;
}

uint32_t min(uint32_t a, uint32_t b){
  return a<b ? a:b;
}

//result should initially be 0, t should be the root
uint32_t max_depth(tnode *t, uint32_t result){
 if (isLeaf(t)) return result;  //optional shortcut
 if (t==NULL) return result -1; //overstepped

 uint32_t l = max_depth(t->left, result+1);
 uint32_t r = max_depth(t->right, result+1);

 return max(l,r);
}


//result should initially be 0, t should be the root
uint32_t min_depth(tnode *t, uint32_t result){
 if (isLeaf(t)) return result;  //optional shortcut
 if (t==NULL) return result -1; //overstepped

 uint32_t l = min_depth(t->left, result+1);
 uint32_t r = min_depth(t->right, result+1);

 //if the l,r is equal to result then you know l,r was null
 if (l == result) return r;
 else if ( r == result) return l;
 else return min(l,r);
}

int main(){

 item_t* t = (item_t*)(malloc(sizeof(item_t)));
 t->data = 10;
 tnode* root = (tnode*)(malloc(sizeof(tnode)));
 root->data=*t;

 item_t* a = (item_t*)(malloc(sizeof(item_t)));
 item_t* b = (item_t*)(malloc(sizeof(item_t)));
 item_t* c = (item_t*)(malloc(sizeof(item_t)));
 a->data = 1;
 b->data = 20;
 c->data = 15;

 printf("root->data.data: %u\n", root->data.data);
 
 insert(*a,root);
 traverse_tree(root);
 printf("root->left->data.data: %u\n",root->left->data.data);

 printf("\n");
 insert(*b,root);
 traverse_tree(root);

 printf("\n");
 insert(*c,root);
 traverse_tree(root);

 printf("\n");
}

