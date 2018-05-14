#include        <stdlib.h>
#include        <stdio.h>
#include        <unistd.h>
#include        <pthread.h>
int*		countArray;
#include        "Unsafe_Buffer.h"
  
const int       NUM_INTEGERS_TO_BUFFER  = 0x1000;
    
void*   stuffIntegersIn (void*  vPtr)
{     
  Buffer* bufferPtr = (Buffer*)vPtr;
  for  (int i = 0;  i < NUM_INTEGERS_TO_BUFFER;  i++)
    bufferPtr->putIn(i);
    
  return(NULL);
}   
    
void*   pullIntegersOut (void*  vPtr)
{
  Buffer* bufferPtr = (Buffer*)vPtr;
  for  (int i = 0;  i < NUM_INTEGERS_TO_BUFFER;  i++)
  {
    int j = bufferPtr->pullOut();

    printf("Trial %d got %d%s.\n",
           i,j,(i==j) ? "" : "");
    fflush(stdout);
  }

  return(NULL);
}


int     main    ()
{
  pthread_t     producer0;
  pthread_t     producer1;
  pthread_t     consumer0;
  pthread_t     consumer1;
  Buffer        buffer;
  countArray	= (int*)calloc(NUM_INTEGERS_TO_BUFFER,sizeof(int));

  pthread_create(&consumer0,NULL,pullIntegersOut,&buffer);
  pthread_create(&consumer1,NULL,pullIntegersOut,&buffer);
  pthread_create(&producer0,NULL,stuffIntegersIn,&buffer);
  pthread_create(&producer1,NULL,stuffIntegersIn,&buffer);

  pthread_join(producer1,NULL);
  pthread_join(producer0,NULL);
  pthread_join(consumer1,NULL);
  pthread_join(consumer0,NULL);

  for  (int i = 0;  i < NUM_INTEGERS_TO_BUFFER;  i++)
    if  (countArray[i] < 0)
      printf("%d was gotten too many times!\n",i);
    else
    if  (countArray[i] > 0)
      printf("%d was put too many times!\n",i);
  return(EXIT_SUCCESS);
}
