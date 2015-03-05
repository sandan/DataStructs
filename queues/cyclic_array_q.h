#ifndef _CYCLIC_Q_H_
#define _CYCLIC_Q_H_

#include <stdint.h>
#include <stdbool.h>
#include "../data/data.h"

//the cyclic array based queue cq
typedef struct {
  uint32_t size;       //size of the queue
  item_t *arr;	       //array of items
  uint32_t front;        //pointer to front of queue
  uint32_t back;        //pointer to back of queue
} ca_q;

//Cyclic Queue API

extern ca_q* create_queue(uint32_t size);
extern void remove_queue(ca_q *q);
extern int enqueue(item_t i, ca_q *q);
extern uint32_t size(ca_q *q);
extern item_t dequeue(ca_q *q);
extern bool empty(ca_q *q);
extern bool full(ca_q *q);

#endif
