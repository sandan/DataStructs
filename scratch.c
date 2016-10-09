#include <malloc.h>
#include <string.h>

typedef struct {
	int numcols;
	int **cols;
	int *lens;
	
} row_t;

int show(row_t * src){
	
	if (src != NULL){
	
	printf(
		" \nrow_t = { \n \
	numcols:%d,\n \
	lens: [%d, %d],\n\
	cols: {\n \
	  *[%p]->{%d},\n \
	  *[%p]->{%d},\n \
	}\n\
}\n",
	src->numcols, 
	src->lens[0], src->lens[1] ,
	src->cols[0], *src->cols[0], 
	src->cols[1], *src->cols[1]);
	
    } else{
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
 		//free(src); BAD! Don't want to free a stack address...
	} else {
		return 1;
	}
	return 0;
}

int make_dummy_row(row_t *src){

	// init a row with dummy data
	src->numcols = 2;
	
	//initialize col pointer array
	src->cols = (int **) malloc(sizeof(int *) * src->numcols);
	
	src->lens = (int *) malloc(sizeof(int) * src->numcols);
	
	src->cols[0] = (int *) malloc(sizeof(int));
	*src->cols[0] = 256;
	src->lens[0] = 4;
	
	src->cols[1] = (int *) malloc(sizeof(int));
	*src->cols[1] = 1024;
	src->lens[1] = 4;
	
	return 1;
}

int copy_row(row_t *dst, row_t *src){

	if (src != NULL && dst!=NULL){
		dst->numcols = src->numcols;
		dst->cols = (int **) malloc(sizeof(int *) * src->numcols);
        
        for (int i = 0; i < src->numcols; i++){
        	dst->cols[i] = (int *) malloc(sizeof(int));
        	*dst->cols[i] = *src->cols[i];
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
			
				//then cleanup
				if (deallocate_row(&q) || deallocate_row(&p)){
					printf("Error deallocating rows\n");
				}	
			}
			else{
				printf("Error showing row\n");
			}
		}
		else{
			printf("error in copy_row\n");
		}
	}
	else{
    printf("error in make_dummy_row\n");
	}
}
