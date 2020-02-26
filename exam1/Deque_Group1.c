/* ENTER YOUR FIRST AND LAST NAME:      */

/* TO COMPILE:  gcc -Wall -ansi -o prog Deque.c */

/* TO RUN, ENTER CAPACITY AND SIZE OF DEQUE */
/* FOR EXAMPLE:  ./prog 10 20 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TYPE int
#define EQ(a,b) (a == b)  

struct Deque{
    TYPE *data; 
    int size; /* number of elements in data */
    int capacity; /* memory capacity of the deque */
    int front; /* index of the front end of deque  */
};

void initDeque(struct Deque * dq, int cap);
void addDeque(struct Deque *dq, TYPE val, int flag);
void printDeque(struct Deque *dq);
void _doubleCapDeque (struct Deque *dq);


/*----------------------------------------------*/
int main(int argc, char **argv){
   struct Deque dq;
   int i;
   int flag = -1;
   TYPE val;
   int  capacity = atoi(argv[1]);
   int  size = atoi(argv[2]);

   assert(capacity > 0 && size >= 0);

   srand(time(NULL)); /*initialize random generator*/

   initDeque(&dq, capacity); /*initialize Deque*/

   for(i=1; i<=size; i++)
   {
      val = (TYPE) rand() % 100;
      addDeque(&dq, val, flag); /*add val to Deque*/
      flag = flag * (-1); /*flip front/end */
   }
   printDeque(&dq); /*print all elements of Deque*/
   return 0;
}


/*----------------------------------------------*/
/* Initializes a deque */
void initDeque(struct Deque * dq, int cap) {
   assert (dq);
   dq->capacity = cap;
   dq->size = dq->front = 0;
   dq->data = (TYPE *) malloc(dq->capacity * sizeof(TYPE));
   assert (dq->data != 0);
}

/*----------------------------------------------*/
/* Prints out all elements of a deque starting from the front */
void printDeque(struct Deque * dq) {
   assert (dq);
   int i;

   printf("FRONT: ");
   for(i=0; i< dq->size; i++)
      printf("%d ", dq->data[(dq->front + i) % dq->capacity]);
 
   printf(" :END\n");
}

/*----------------------------------------------*/
/* Doubles the memory capacity of a deque */
void _doubleCapDeque (struct Deque *dq) {
  assert (dq);
  int j;
  TYPE * oldData = dq->data; /*memorize old data*/
  int oldFront = dq->front; /*memorize old index of the front end of deque*/
  int oldSize = dq->size; /*memorize old size*/
  int oldCapacity = dq->capacity; /*memorize old capacity*/
  initDeque(dq, 2 * oldCapacity); /*new memory allocation*/
  for (j = 0 ; j < oldSize; j++) {/*copy back old data*/
    dq->data[j] = oldData[oldFront++];
    if (oldFront >= oldCapacity) oldFront = 0;
  }
  free(oldData);
  dq->size = oldSize;
}

/*----------------------------------------------*/
/* input arguments: 
  dq -- pointer to deque
  val -- value of the data element to be added 
  flag -- 1 => add to the front, flag = -1 => add to the back  
*/
void addDeque(struct Deque *dq, TYPE val, int flag) {  
   assert(dq && (flag == 1 || flag == -1));
   if (dq->size == dq->capacity) _doubleCapDeque(dq); 
   if(flag == 1){  /* add to front */  

      /* Decrement the front index modulo capacity */
      dq->front--;
      if (dq->front < 0) dq->front += dq->capacity; 
  
      dq->data[dq->front] = val; /* add the new value */
   }
   else if (flag == -1){   /* add to back */
      int backIndex = (dq->front + dq->size) % dq->capacity; 
      dq->data[backIndex] = val; /* add the new value */
  }
  dq->size ++;   /* increment the size */
}

