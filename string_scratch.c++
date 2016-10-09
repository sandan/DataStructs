#include <iostream>
#include <malloc.h>
#include <string.h>

typedef struct {
	int numcols;
	char **cols;
	int *lens;
} row_t;

int show(row_t * src){
	
  if (src != NULL){
	
	printf(
		" \nrow_t = { \n \
	numcols:%d,\n \
	lens: [%d, %d],\n\
	cols: {\n \
	  *[%p]->{%s},\n \
	  *[%p]->{%s},\n \
	}\n\
}\n",
	src->numcols, 
	src->lens[0], src->lens[1] ,
	src->cols[0], src->cols[0], 
	src->cols[1], src->cols[1]);
	
    } 
    else {
    	return 0;
    }
	return 1;
}

int deallocate_row(row_t *src){
	if (src != NULL){

		for(int i = 0; i < src->numcols; i++){
			free(src->cols[i]);
		}
		free(src->lens);
		free(src->cols);
	} 
	else {
		return 1;
	}
	return 0;
}

int make_dummy_row(row_t *src){

	// init a row with dummy data
	src->numcols = 2;
	
	//initialize col pointer array
	src->cols = (char **) malloc(sizeof(char *) * src->numcols);
	
	src->lens = (int *) malloc(sizeof(int) * src->numcols);
	
	//all string literals have an implicit null terminator
	src->cols[0] = (char *) malloc(sizeof(char) * 64);
	src->lens[0] = 11;
	strncpy(src->cols[0], "Hello_World", src->lens[0]);
	
	src->cols[1] = (char *) malloc(sizeof(char) * 64);
	src->lens[1] = 14;
	strncpy(src->cols[1], "Hello_Universe", src->lens[1]);
	
	return 1;
}

int copy_row(row_t *dst, row_t *src){

	if (src != NULL && dst!=NULL){
		dst->numcols = src->numcols;
		dst->cols = (char **) malloc(sizeof(char *) * src->numcols);
        
        for (int i = 0; i < src->numcols; i++){
        	dst->cols[i] = (char *) malloc(sizeof(char) * 64);
        	memcpy(dst->cols[i], src->cols[i], src->lens[i]);
        }
        
        dst->lens = (int *) malloc(sizeof(int) * src->numcols);
        
        for (int i = 0; i < src->numcols; i++){
        	dst->lens[i] = src->lens[i];
        }
    } 
	else{
		return 0;
	}
	
	if (dst == NULL || dst == 0){
		return 0;
	}
	return 1;
}

int main() {
	row_t p = {0};
	row_t q = {0};
	if (make_dummy_row(&p)){
		show(&p);
		if (copy_row(&q,&p)){
			if (show(&q)){
			
				//finally
				if (deallocate_row(&q) || deallocate_row(&p)){
					std::cout << "Error deallocating rows\n";
				}	
			}
			else{
				printf("Error showing row\n");
			}
		}
		else{
			std::cout << "error in copy_row\n";
		}
	}
	else{
		std::cout << "error in make_dummy_row\n";
	}
}
