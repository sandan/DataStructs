#include <stdio.h>
#include <stdlib.h>
#include "../../headers/cyclic_array_q.h"

ca_q* create_ca_queue(uint32_t size){
  ca_q *q = (ca_q *) malloc(sizeof(ca_q));
  q->arr = (item_t *) malloc(sizeof(item_t) * size);
  q->front = q->back = 0;
  q->len = 0;
  q->size = size;
  return q;

}

void remove_ca_queue(ca_q *q){
 free(q->arr);
 free(q);
}

bool empty_ca(ca_q *q){
  return (q->len == 0) && (q->front == q-> back); 
}

bool full_ca(ca_q *q){
  return (q->front == q->back) && (q->len == q->size);
}

int enqueue_ca(item_t i, ca_q *q){
  if (!full_ca(q)){
   q->arr[q->back++] = i;
   q->back%=q->size;
   q->len += 1;

   return 1;
  } else {
   return -1;
  }
}

item_t dequeue_ca(ca_q *q){
  if (!empty_ca(q)){
    item_t result = q->arr[q->front++];
    q->front%=q->size;
    q->len -= 1;

    return result;
  } else {
    return sentinel;
  }
}
