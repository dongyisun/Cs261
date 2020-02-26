/* ENTER YOUR FIRST AND LAST NAME:      */

/* TO COMPILE, ENTER:  gcc -Wall -ansi -o prog Bag.c */

/* TO RUN, ENTER PROGRAM ARGUMENTS: CAPACITY, SIZE  */
/* FOR EXAMPLE:  ./prog 10 4    */


#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<assert.h>

#define TYPE int
#define LT(a, b) (a<b)
#define GT(a, b) (a>b)
#define EQ(a, b) (a == b)

struct DynArr { 
   TYPE * data;
   int size;
   int capacity; 
};

/*----------------------------------------------*/
/*Interface for Dynamic Array*/
void initDynArr(struct DynArr * da, int capacity);
void addDynArr(struct DynArr * da, TYPE val);
void sortAscendBag(struct DynArr * da);

/*----------------------------------------------*/
/*Internal functions*/
void _doubleCapacity (struct DynArr * da);
void _swap(TYPE *a, TYPE *b);
void _printDynArr(struct DynArr * da);

/*----------------------------------------------*/
int main(int argc, char **argv){
   struct DynArr bag;
   int i;
   int  capacity = atoi(argv[1]);
   int  size = atoi(argv[2]);

   initDynArr(&bag, capacity);

   srand ( time(NULL) ); 
   /*Generate and add elements to the bag*/
   for(i=0; i<size; i++) addDynArr(&bag, rand()%100);
     
   printf("\nBag before sorting:\n");
   _printDynArr(&bag);

   sortAscendBag(&bag);
    
   printf("\nBag after sorting:\n");
   _printDynArr(&bag);
   
   return 0;
}

/*----------------------------------------------*/
/* Initializes a dynamic array */
void initDynArr(struct DynArr * da, int cap) {
   assert (da!=0 && cap>0);
   da->capacity = cap;
   da->size = 0;
   da->data = (TYPE *) malloc(cap * sizeof(TYPE));
   assert (da->data != 0);
}


/*----------------------------------------------*/
/* Doubles the memory capacity of a dynamic array */
void _doubleCapacity (struct DynArr * da) {
  assert (da);
  int j;
  TYPE * oldData = da->data; /*memorize old data*/
  int oldSize = da->size; /*memorize old size*/
  initDynArr(da, 2 * da->capacity); /*new memory allocation*/
  for (j = 0 ; j < oldSize; j++) {/*copy old data*/
    da->data[j] = oldData[j];
  }
  free(oldData);
  da->size = oldSize;
}

/*----------------------------------------------*/
/* Prints out all elements of a dynamic array*/
void _printDynArr(struct DynArr * da) {
   assert (da);
   int i;
   for(i=0; i< da->size; i++) printf("%d \n", da->data[i]);
}

/*----------------------------------------------*/
/* input arguments: 
  da -- pointer to a dynamic array
  val -- value of the data element to be added 
*/
void addDynArr(struct DynArr * da, TYPE val) {  
   assert(da);
   if (da->size == da->capacity) _doubleCapacity(da); 
   da->data[da->size] = val; 
   da->size ++;
}


/*----------------------------------------------*/
/* input arguments: 
  da -- pointer to a dynamic array
*/
void sortAscendBag(struct DynArr* bag){
   /*Sort the bag*/   
   int i,j;

   for(i=0;i<bag->size-1;i++){
      for(j=i+1;j<bag->size;j++){
         if(LT(bag->data[j], bag->data[i]))
            _swap(bag->data+i, bag->data+j);
   }  }
}

void _swap(TYPE *a, TYPE *b){
   TYPE tmp;
   tmp = *a;
   *a = *b;
   *b = tmp;
}

