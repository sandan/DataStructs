#include <stdio.h>
#include <stdlib.h>
#include "cyclic_array_q.h"

def ca_q* create_queue(uint32_t size){
  ca_q *q = (ca_q *) malloc(sizeof(ca_q));
  q->arr = (item_t *) malloc(sizeof(item_t) * size);
  q->front = q->back = 0;
  q->len = 0;
  q->size = size;
}

def void remove_queue(ca_q *q){
 free(q->arr);
 free(q);
}

def bool empty(ca_q *q){
  return (q->len == 0) && (q->front == q-> back); 
}

def bool full(ca_q *q){
  return (q->front == q->back) && (q->len == q->size);
}

def int enqueue(item_t i, ca_q *q){
  if (!full(q)){
   q->arr[q->back++] = i;
   q->back%=q->size;
   q->len += 1;

   return 1;
  } else {
   return -1;
  }
}

def item_t dequeue(ca_q *q){
  if (!empty(q)){
    item_t result = q->arr[q->front++];
    q->front%=q->size;
    q->len -= 1;

    return result;
  } else {
    return sentinel;
  }
}
