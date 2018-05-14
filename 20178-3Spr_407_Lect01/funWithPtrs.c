#include	<stdlib.h>
#include	<stdio.h>

int		main		()
{
  // Example
  int intArray[5] = {10,20,30,40,50};
  int* intPtr = intArray;

  // What will this print?
  printf("%p %p\n",intArray,intPtr);

  intPtr++;
  (*intPtr) *= 10;

  // What will this print?
  printf("%d\n",intArray[1]);

  return(EXIT_SUCCESS);
}
