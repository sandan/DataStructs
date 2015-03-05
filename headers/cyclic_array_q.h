#ifndef _CYCLIC_ARRAY_H_
#define _CYCLIC_ARRAY_H_

#include <stdint.h>
#include <stdbool.h>
#include "../data/data.h"

//the cyclic array based queue cq
typedef struct {
  uint32_t size;       //max size of the queue
  uint32_t len;       //size of the queue
  item_t *arr;	       //array of items
  uint32_t front;        //pointer to front of queue
  uint32_t back;        //pointer to back of queue
} ca_q;

//Cyclic Queue API

ca_q* create_ca_queue(uint32_t size);
void remove_ca_queue(ca_q *q);
int enqueue_ca(item_t i, ca_q *q);
uint32_t size_ca(ca_q *q);
item_t dequeue_ca(ca_q *q);
bool empty_ca(ca_q *q);
bool full_ca(ca_q *q);

#endif
