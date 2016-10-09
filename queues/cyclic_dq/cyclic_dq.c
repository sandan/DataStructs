#include <stdio.h>
#include <stdlib.h>
#include "../../headers/cyclic_dq.h"

/** Doubly Linked List implemented in a cyclic fashion**/
// the only difference really are the pointers back to q->entry

dq* create_dqueue(void){
 dq* q= (dq *)malloc(sizeof(dq));
 q->entry = (node *) malloc(sizeof(node)); //inititalize pointer node
 q->entry->next = q->entry;
 q->entry->prev = q->entry;
 q->len = 0;

 return q;
}


void remove_dqueue(dq *q){
 node *Q = q->entry->prev; //front node
 node *to_del;             //tmp pointer to hold next node to delete
 q->entry->next->prev = NULL;     //remove pointer to q
 do {
   to_del = Q->prev;
   free(Q);
   Q = to_del;
 }
 while (Q != NULL);

 free(q);                   //free up the q
}

bool empty_dq(dq* q){
  return q->len == 0;
}

/** Uses malloc, could possibly have a free list of nodes at initialization**/
int enqueue_dq(item_t i, dq *q){
  node *n = (node *) malloc(sizeof(node));
  n->data = i;

  //enqueue to back 
  q->entry->next->prev = n;
  n->next = q->entry->next;
  n->prev = q->entry;
  q->entry->next = n;
  
  q->len += 1;
  return q->len;
}

item_t dequeue_dq(dq *q){
 if(!empty_dq(q)){
   node* removed = q->entry->prev; //front node
   item_t result = removed->data;

   q->entry->prev->prev->next = q->entry;
   q->entry->prev = removed->prev;

   free(removed);
   q->len -= 1;
   
   return result;
 } else {
   return sentinel;
 }

}
