#ifndef _CYCLIC_Q_H_
#define _CYCLIC_Q_H_

#include <stdint.h>
#include <stdbool.h>
#include "../data/data.h"

//the doubly linked queue dq
/**TODO: refactor into two types? one data, other next/prev?**/
typedef struct node {
 item_t data;          //data item held in node
 struct node *next;           //pointer to next node
 struct node *prev;           //pointer to previous node
} node;

typedef struct {
  uint32_t len;       //size of the queue
  node *entry;         //pointer to front,back of queue
} dq;

//Doubly Linked Queue API

dq* create_dqueue();
void remove_dqueue(dq *q);
int enqueue_dq(item_t i, dq *q);
item_t dequeue_dq(dq *q);
bool empty_dq(dq *q);

#endif
