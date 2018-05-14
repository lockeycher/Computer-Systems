#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>

char* naughtyCopy (const char* fromP, size_t n)
{
  size_t length  = strlen(fromP) + 1;
 
  if  (n == 0)
    n = 1;

  if  (length > n)
    length = n;

  char* toReturn = (char*)malloc(length);
  char* toP	 = toReturn;

  for ( ; *fromP != '\0' &&  length > 1; fromP++, toP++, length--)
    *toP = *fromP;

  *toP	= '\0';
  return(toReturn);
}


int	main	()
{
  int i;

  for  (i = 0;  i < 20;  i++)
  {
    char*	cPtr	= naughtyCopy("Hello class!",i);

    printf("%s\n",cPtr);
    free(cPtr);
  }

  return(EXIT_SUCCESS);
}
