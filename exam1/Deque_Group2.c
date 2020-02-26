/* ENTER YOUR FIRST AND LAST NAME:      */

/* TO COMPILE, ENTER:  gcc -Wall -ansi -o prog Deque.c */

/* TO RUN, ENTER PROGRAM ARGUMENTS: CAPACITY, SIZE, FLAG */
/* FOR EXAMPLE:  ./prog 10 4 -1 */


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
void addFrontDeque(struct Deque *dq, TYPE val);
void addBackDeque(struct Deque *dq, TYPE val);
void printDeque(struct Deque *dq);
void removeAllDeque(struct Deque *dq, int flag);
void _doubleCapacityDeque (struct Deque *dq);


/*----------------------------------------------*/
int main(int argc, char **argv){
   struct Deque dq;
   int i;
   TYPE val;
   int  capacity = atoi(argv[1]);
   int  size = atoi(argv[2]);
   int flag = atoi(argv[3]);

   assert(capacity > 0 && size >= 0);

   srand(time(NULL)); /*initialize random generator*/

   initDeque(&dq, capacity); /*initialize Deque*/

   for(i=1; i<=size; i++)
   {
      val = (TYPE) rand() % 100;
      addFrontDeque(&dq, val); /*add val to Deque*/
   }
   if(flag == 1){
      for(i=1; i<=size; i++) addFrontDeque(&dq, val); /*add val to front of Deque*/
   }
   else if(flag == -1){
     for(i=1; i<=size; i++) addBackDeque(&dq, val); /*add val to back of Deque*/
   }
   else printf("flag must be 1 or -1\n");

   printf("Deque before remove:\n");
   printDeque(&dq); /*print all elements*/

   removeAllDeque(&dq, flag);

   printf("Deque after remove:\n");
   printDeque(&dq); /*print all elements*/

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
void _doubleCapacityDeque (struct Deque *dq) {
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
*/
void addFrontDeque(struct Deque *dq, TYPE val) {  
   assert(dq);
   if (dq->size == dq->capacity) _doubleCapacityDeque(dq); 
   dq->front--;
   if (dq->front < 0) dq->front += dq->capacity; 
   dq->data[dq->front] = val; 
   dq->size ++;
}

/*----------------------------------------------*/
/* input arguments: 
  dq -- pointer to deque
  val -- value of the data element to be added 
*/
void addBackDeque(struct Deque *dq, TYPE val) {  
   assert(dq);
   if (dq->size == dq->capacity) _doubleCapacityDeque(dq); 
   int backIndex = (dq->front + dq->size) % dq->capacity; /*empty spot*/
   dq->data[backIndex] = val; 
   dq->size ++;
}


/*----------------------------------------------*/
/* input arguments: 
  dq -- pointer to deque
  flag -- flag = 1 remove from front; flag = -1 remove from back
*/

void removeAllDeque(struct Deque *dq, int flag)
{ 
   TYPE val; /*auxiliary variable*/
   assert(dq && (flag == 1 || flag == -1) && dq->size > 0); 
   if(flag == 1){  /* remove from front */  
      val = dq->data[dq->front];
      while (EQ(val, dq->data[dq->front]) && dq->size > 0){
         dq->front++;
         if(dq->front == dq->capacity) dq->front = 0;
         dq->size--;
      }
   }
   else{ /* remove from back */ 
      int backIndex = (dq->front + dq->size - 1) % dq->capacity;
      val = dq->data[backIndex];
      while (EQ(val, dq->data[backIndex]) && dq->size > 0){
         backIndex--;
         if(backIndex == 0) backIndex = dq->capacity - 1;
         dq->size--;
      }
   }
}


