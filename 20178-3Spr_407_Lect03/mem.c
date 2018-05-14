#include	<stdlib.h>
#include	<stdio.h>

int		data	= 2;
int		bss	= 0;

int		main	()
{
  int		local	= 10;
  int*		heapPtr	= (int*)malloc(sizeof(int));

  *heapPtr		= 7;

  pid_t		pid	= fork();

  if  (pid == 0)
  {
    data--;
    bss--;
    local--;
    (*heapPtr)--;
  }
  else
  {
    data++;
    bss++;
    local++;
    (*heapPtr)++;
  }

  printf("pid = %d, data = %d, bss = %d, local = %d, heap = %d\n",
	 getpid(),data,bss,local,*heapPtr
	);
  return(EXIT_SUCCESS);
}
  
