
/**
 *  The idea is to mnake sure s[j-1] < s[j].
 *  As long as we swap cases where s[j] > s[j-1], we get the ascending sort.
 */
void swap (int *x, int *y) {
     if (x != y) { //or it zeroes out the value
         *x ^= *y;
         *y ^= *x;
         *x ^= *y;
     }
}

void insertion_sort(int s[]){

  int i,j;
  int n = sizeof(s)/sizeof(int);
  for(i=0; i<n; i++){
   j=i;
   while ( (j>0) && (s[j] < s[j-1]) ){
    swap(s+j, s+(j-1));
    j-=1;
   }
  }

}

int test(void){
 int s[10]= {9,1,4,6,1,2,4,3,2,0}; 
 insertion_sort(s);

 return 1;
}

