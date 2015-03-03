#include <stdio.h>
#include <stdlib.h>

//8-byte data items
typedef struct {
 int x;
 int y;
 int z;
} item_t;

//the stack
typedef struct {
 item_t *base;   //pointer to base of stack
 item_t *top;    //pointer to the top to insert
 int size;       //size of stack
} stack;

//Stack API

stack *create_stack(int size){
  //initialize space for the stack pointer
  stack *st_ptr;
  st_ptr = (stack *) malloc(sizeof(stack));

  //initialize a pointer to point to array of (size * 12) bytes
  st_ptr->base = (item_t *) malloc(size * sizeof(item_t));
  
  //set the size variable of the stack
  st_ptr->size = size;

  //set the top of the pointer to the first item_t slot in stack
  st_ptr->top = st_ptr->base;

  printf("sizeof(ptr) = %lu \n", sizeof(int *));
  return st_ptr;


/* DEBUG
  printf("sizeof(item_t) = %lu \n", sizeof(item_t));
  printf("sizeof(item_t*) = %lu \n", sizeof(i_ptr));
  printf("sizeof(stack) = %lu \n", sizeof(stack));
  printf("sizeof(stack pointer) = %lu \n", sizeof(st_ptr));
  return NULL;
*/
}



int main(void){
  create_stack(10);
  return 0;
}
