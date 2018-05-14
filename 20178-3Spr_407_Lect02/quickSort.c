/*-------------------------------------------------------------------------*
 *---									---*
 *---		quickSort.c						---*
 *---									---*
 *---	    This file defines a function that implements the quick-sort	---*
 *---	algorithm.							---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1b		2018 April 2		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

#include	"header.h"


int		partition	(char**		array,
				 char*		pivot,
				 int		lo,
				 int		hi
				)
{
  lo--;
  hi++;

  while  (1)
  {
    do
    {
      lo++;
    }
    while  (strncmp(array[lo],pivot,strLen) < 0);

    do
    {
      hi--;
    }
    while  (strncmp(array[hi],pivot,strLen) > 0);

    if  (lo >= hi)
      break;

    swap(array,lo,hi);
  }

  return(hi);
}


int		pivot		(char**		array,
				 int		lo,
				 int		hi
				)
{
  char*	atLo	= array[lo];
  char*	atMid	= array[(lo+hi)/2];
  char*	atHi	= array[hi];

  if  ( ((strncmp(atLo,atMid,strLen)<=0) && (strncmp(atMid,atHi,strLen)<=0))  ||
        ((strncmp(atLo,atMid,strLen)>=0) && (strncmp(atMid,atHi,strLen)>=0))
      )
    return((lo+hi)/2);

  if  ( ((strncmp(atMid,atLo,strLen)<=0) && (strncmp(atLo,atHi,strLen)<=0))  ||
	((strncmp(atMid,atLo,strLen)>=0) && (strncmp(atLo,atHi,strLen)>=0))
	)
    return(lo);

  return(hi);
}


void		quickSort_	(char**		array,
				 int		lo,
				 int		hi
				)
{
  if  (lo < hi)
  {
    int	left;
    int	right;
    int	p	= pivot(array,lo,hi);

    p		= partition(array,array[p],lo,hi);
    quickSort_(array,lo,p);
    quickSort_(array,p+1,hi);
  }
}


//  PURPOSE:  To sort the 'arrayLen' strings in array 'array' with the
//	quick-sort algorithm.  No return value.
void		quickSort	(char**		array,
				 int		arrayLen
				)
{
  quickSort_(array,0,arrayLen-1);
}
