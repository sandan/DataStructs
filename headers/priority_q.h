#ifndef _PRIORITY_Q_H_
#define _PRIORITY_Q_H_

#include <stdint.h>
#include <stdbool.h>
#include "../data/data.h"

#define N 4096
#define FLUSH_SIZE 1024*32

//the priority queue 
typedef struct node {
 item_t data;                 //data item held in node, 12 bytes x,y,z
 struct node *next;           //pointer to next node
 struct node *prev;           //pointer to previous node
} node;

typedef struct priority_q {
  uint32_t len;              //size of the queue
  int keys[N*3]
  node *entry;               //pointer to front,back of queue
} pq;

//Doubly Linked Queue API

dq* create_dqueue();
void remove_dqueue(dq *q);
int enqueue_dq(item_t i, dq *q);
item_t dequeue_dq(dq *q);
bool empty_dq(dq *q);

#endif
