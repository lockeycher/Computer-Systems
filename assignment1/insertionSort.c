/*-------------------------------------------------------------------------*
 *---									---*
 *---		insertionSort.c						---*
 *---									---*
 *---	    This file defines a function that implements the insertion-	---*
 *---	sort algorithm.							---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2018 April 2		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

#include	"header.h"

//  PURPOSE:  To sort the 'arrayLen' strings in array 'array' with the
//	insertion-sort algorithm.  No return value.
void		insertionSort	(char**		array,
				 int		arrayLen
				)
{
  int	i;
  int	j;

  for  (i = 0;  i < arrayLen-1;  i++)
    for  (j = i+1;  j < arrayLen;  j++)
      if  ( strncmp(array[i],array[j],strLen) > 0 )
	swap(array,i,j);
}
