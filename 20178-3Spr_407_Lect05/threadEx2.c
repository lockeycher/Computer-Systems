#include	<stdlib.h>
#include	<stdio.h>
#include	<pthread.h>

int		global		= 5;

void*		threadFnc	(void*	vPtr
				)
{
  int	theInt	= *(int*)vPtr;
  int*	sumPtr	= (int*)malloc(sizeof(int));

  *sumPtr	= global + theInt;

  return((void*)sumPtr);
}


int		main		()
{
  pthread_t	tId;
  int*	iPtr	= (int*)malloc(sizeof(int));

  *iPtr		= 10;
  pthread_create(&tId,NULL,threadFnc,(void*)iPtr);
  int*	iPtr2;

  pthread_join(tId,(void**)&iPtr2);

  printf("%d + %d = %d\n",*iPtr,global,*iPtr2);
  free(iPtr2);
  free(iPtr);
  return(EXIT_SUCCESS);
}
