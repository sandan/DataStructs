#include <stdio.h>
#include <stdlib.h>
#include "array_based.h"


//Stack API implementation

stack *create_stack(uint32_t size){
  //initialize space for the stack pointer
  stack *st_ptr;
  st_ptr = (stack *) malloc(sizeof(stack));

  //initialize a pointer to point to array of (size * 12) bytes
  st_ptr->base = (item_t *) malloc(size * sizeof(item_t));
  
  //set the size variable of the stack
  st_ptr->size = size;

  //set the top of the pointer to the first item_t slot in stack
  st_ptr->top = st_ptr->base;

  return st_ptr;
}

void remove_stack(stack *st_ptr){
  free(st_ptr->base); //reclaim memory allocated for item_t
  free(st_ptr);       //reclaim memory pointed to by st_ptr
}


bool empty(stack *st_ptr){
  return st_ptr->base == st_ptr->top ? true:false;
}

item_t peek(stack *st_ptr){
  if (empty(st_ptr)){
    return sentinel; //a default item_t sentinel instead of NULL
  } else {
    item_t result = *(st_ptr->top); 
    return result;  //return a pointer to what the stack currently points to
  }
}

int push(item_t i, stack * st_ptr){
  if (st_ptr->top < (st_ptr->base + st_ptr->size)){
    *(st_ptr->top) = i; //set the item into the free slot 
     st_ptr->top +=1;   //move pointer to the next free location
     return 1;          //success 
  } else{
     return 0;          //no space
  }
}

item_t pop(stack * st_ptr){
  if (!empty(st_ptr)){
    item_t result = *(st_ptr->top);     //retrieve result
    st_ptr->top-=1;			//decrement top to base or prev item_t 
    return result;		     
  }else{
    return sentinel;			//default sentinel item_t
  }
}
