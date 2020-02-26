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
void removeAllDynArr(struct DynArr * da, TYPE val);

/*----------------------------------------------*/
/*Internal functions*/
void _doubleCapacity (struct DynArr * da);
void _printDynArr(struct DynArr * da);

/*----------------------------------------------*/
int main(int argc, char **argv){
   struct DynArr bag;
   int i;
   TYPE val;
   int  capacity = atoi(argv[1]);
   int  size = atoi(argv[2]);

   initDynArr(&bag, capacity);

   srand ( time(NULL) ); 
   /*Generate and add elements to the bag*/
   for(i=0; i<size; i++){
      val = rand()%5;
      addDynArr(&bag, val);
   }
     
   printf("\nBag before remove:\n");
   _printDynArr(&bag);

   removeAllDynArr(&bag, val);
    
   printf("\nBag after removing all occurrences of %d:\n", val);
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
  val -- value to be removed at every occurrence
*/
void removeAllDynArr(struct DynArr* da, TYPE val){  
   assert(da);
   int i=0;
   while (i < da->size) {
      if ( EQ(val, da->data[i]) ) {
         da->data[i] = da->data[da->size-1];
         da->size--;
      }
      else
         i++; 
   }
}

