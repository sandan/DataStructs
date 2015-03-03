#include "heap.h"
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>

#define MISSING() missing(__func__,__FILE__,__LINE__)

/*pointer to the head of the free list embedded in the heap*/
uint32_t* free_list_ptr;
uint32_t extra_pad=0;

void missing(const char* msg, const char* file, int line) {
    printf("---> finish %s @ %s:%d <---\n",msg,file,line);
    exit(0);
}

/*Debugging helper functions*/
void peekMem(void* p,uint32_t size){
 int i;
// printf("*free_list_ptr: %d\n",*free_list_ptr);
 //printf("free_list_ptr adddr @: %p\n",free_list_ptr);

 for(i=0; i<size; i++){
   printf("%p: %d\n",p+i,((char*)p)[i]);
 }
}

void clear(void* p,uint32_t size){
 int i;
 for(i=0;i<size;i++){
  ((char*)p)[i]=1;
 }
}
/* Helper functions*/
/*Returns the effective size of the user request size or 0 if too large*/
uint32_t insertEntry(uint32_t req_size,uint32_t consumed, uint32_t max){
  uint32_t eff_size=0;//effective size of the allocation

  if ((req_size%4) >0 || req_size==0){
   eff_size=8+req_size+4+(4-req_size%4);
  }
  else{
   eff_size=8+req_size+4;
  }

  /*check if allocation fits into whats left on heap*/
   if (eff_size >max-consumed){
     return 0;
   }
   return eff_size;
}

/*Returns a pointer to the base of the next free block via freePtr*/
/*Assumes free blocks have been merged*/
uint32_t* nextFreeBlock(uint32_t eff_size, uint32_t* prev,
          uint32_t* current)
{ 

   if (current==0){
    return 0; //search failed
   }
   else if(current[1]<eff_size){//traverse to next free block
      return nextFreeBlock(eff_size, current, (uint32_t*)current[0]);
   }
   else{//size of free block is >= effective size
     if(current[1]==eff_size){//found an exact match
        if (prev==0 && current[0]==0){//the head of the free list is current
           free_list_ptr=0;//no more space in heap
           return current;
        }
        else if(prev==0 && current[0]!=0){//more free entries after head
           free_list_ptr=(uint32_t*)current[0];//update head of the free block list
           return current;
        }
        else{//there is a previous free block
         prev[0]=current[0]; //remove current free block from list
         current[0]=0;//erase ptr to next free block
         return current;
        }      
     }
     else{//have to split the free block

          //printf("%s","splitting a free block\n");
         /*calculate the split size*/
         uint32_t split_size=current[1]-eff_size;
         uint32_t* base=(uint32_t*)((((char*)current)+current[1])-eff_size);
         if (split_size >16){//OK to split
          /*update the size of the free block*/
          current[1]-=eff_size;
          return base;
         }
         /*Otherwise splitting leaves <16 bytes, use entire block*/  
          extra_pad=split_size;

         /*update the free list*/
          if (prev==0){//head of list has space to only entry big enough
            free_list_ptr=0;
            current[0]=0;   
            return current;
          }
          
       return 0;         
     }
   }
}

/*Assumes pointer to the base of the free block*/
void mergeFreeBlocks(uint32_t* prev,uint32_t* freeBlockptr){
  
  if (freeBlockptr==0 || freeBlockptr[0]==0){
    /*Check to see if you can merge*/
    if (prev!=0 && freeBlockptr!=0){//you can still merge
       
   /*Check the to see if the top can be merged*/
    if (((char*)prev+prev[1])==(char*)freeBlockptr){
       //then blocks are adjacent to each other, so merge
      /*Update the size*/
      prev[1]+=freeBlockptr[1];
      /*remove the next block from the free list*/
      prev[0]=freeBlockptr[0];
     
      return mergeFreeBlocks(prev,(uint32_t*) prev[0]);
    }
    }

    return; //no blocks or not enough blocks
  }
  else{

    uint32_t* nextFreeBlock=(uint32_t*)freeBlockptr[0];
  
   /*Check the to see if the top can be merged*/
    if (((char*)freeBlockptr+freeBlockptr[1])==(char*)nextFreeBlock){
       //then blocks are adjacent to each other, so merge
      /*Update the size*/
      freeBlockptr[1]+=nextFreeBlock[1];
   
      /*remove the next block from the free list*/
      freeBlockptr[0]=nextFreeBlock[0];
     
      return mergeFreeBlocks((uint32_t*)freeBlockptr,(uint32_t*)nextFreeBlock[0]);
    }
   /*Check to see if the bottom can be merged*/
    else if(((char*)nextFreeBlock+nextFreeBlock[1])==(char*)freeBlockptr){
      /*Update the size of the block*/
      nextFreeBlock[1]+=freeBlockptr[1];

     /*remove the top block from the free list*/
     if (prev==0){//start of the free list has a mergeable bottom entry
       /*erase the reference*/
       free_list_ptr[0]=0;
       /*update the head of the free list*/
       free_list_ptr=(uint32_t*)nextFreeBlock;
       return mergeFreeBlocks(free_list_ptr,(uint32_t*)nextFreeBlock[0]);
     }      
     else{//some intermediate entry in the free list has some mergable bottom entry
       /*erase the reference*/
       freeBlockptr[0]=0;
       /*update the free list*/
       prev[0]=(uint32_t)nextFreeBlock;
       return mergeFreeBlocks((uint32_t*)prev[0],(uint32_t*)nextFreeBlock[0]);
     }
    }
  }

}
heap_s* heap_new(uint32_t size) {
/*Allocate contiguous memory for the heap*/
    void* p = mmap(0, size, PROT_READ | PROT_WRITE,
        MAP_ANONYMOUS | MAP_PRIVATE,
        -1, 0);
    if (p == MAP_FAILED) {
        perror("mmap");
        exit(-1);
    }
/*Clear mem for debugging purposes*/
    clear(p,size);

/*Create and Initialize a heap*/
  
 /*

   |___________________|  entries 
   |  free list ptr    |
   |  size (max bytes) |
   |  consumed bytes   |
   |  required bytes   |
   +===================+
       Base of Heap
*/
    heap_s* heap=(heap_s*)p;  //pointer to the base of the heap

    //heap->block_ptr=((uint32_t*)p+4); //stores the free list pointer
    heap->size=size;          //heap size (max)
    heap->consumed=16;        //consumed size of heap
    heap->required=0;         //required size taken by user
    
/*Initialize the free block, min entry is 16 bytes and free blocks
  don't store any user data, so store free block metadata in them*/
/*
 A free block stores it's size and a pointer to the next free block or 0
 ========
 |      |  junk
 |______|
 | size | 4 bytes
 | ptr  | 4 bytes
 ========
*/
    free_list_ptr=((uint32_t*)p+4); //initialize free_ptr
    free_list_ptr[0]=0;      //store the pointer to next free block
    free_list_ptr[1]=heap->size-heap->consumed; //size of free block
    
//    peekMem(p,size);
   
    return heap;
}

void heap_freeAll(heap_s *heap) {
   free_list_ptr=(uint32_t*)heap+4;
   free_list_ptr[0]=0;
   free_list_ptr[1]=heap->size-16;
   heap->required=0;
   heap->consumed=16;
}

void* heap_malloc(heap_s *heap, uint32_t size) {
   /*Check for mergeable free blocks in free list before malloc*/
    mergeFreeBlocks(0,free_list_ptr);

  /*Find the size of entry*/
    uint32_t eff_size=insertEntry(size,heap->consumed,heap->size);
    if (eff_size>0){
        /*get the next free block in the heap*/
        uint32_t* entry=nextFreeBlock(eff_size,0,free_list_ptr);
        if (entry>0){
           /*check if the extra_pad is set for small split blocks*/
          if (extra_pad){
            eff_size+=extra_pad;
            extra_pad=0;
          }  
          entry[1]=size;//place user requested size in block overhead
          entry[0]=eff_size;//place the effective size of the block also
         
         /*update the heap*/
         heap->required+=size;
         heap->consumed+=eff_size;
         return (void*) ((entry+2));
        }
    }
    return 0;
}

/*Assumes the pointed block is a pointer returned from alloc and is not a free block*/
void heap_free(heap_s *heap, void *ptr) {
   if (ptr==0){
    printf("%s\n","passed bad pointer");
   }
   else{
   /*pointer is to a block entry at start of user request, so we need the base*/
    uint32_t* base=(uint32_t*)ptr-2;

   /*update the heap stats*/
    heap->required-=base[1];
    heap->consumed-=base[0];
  
    /*Save the effective size of the previous user block*/
    uint32_t sizeBlock=base[0];

    /*Link the new block to point to the previous head of the list*/
    base[0]=(uint32_t)free_list_ptr;
    free_list_ptr=(uint32_t*)ptr-2; //move the new block to head of the list
   
    /*update the metadata for the new block entered*/
    free_list_ptr[1]=sizeBlock;
   }
}
    
uintptr_t heap_relptr(heap_s *heap, void* ptr) {
    //peekMem((void*)heap,100);     
    return ptr-((void*)heap);
}

void heap_stats(heap_s *heap) {
    printf("%d %d %d\n",heap->size,heap->consumed,heap->required);
}

