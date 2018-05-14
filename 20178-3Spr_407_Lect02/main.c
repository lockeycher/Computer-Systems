/*-------------------------------------------------------------------------*
 *---									---*
 *---		main.c							---*
 *---									---*
 *---	    This file defines the variable strLen and function swap()	---*
 *---	needed for the program of assignment 1.				---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2018 April 2		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

#include	"header.h"

#define		TEXT_LEN	256


//  PURPOSE:  To tell the length of the strings to sort.
int		strLen;


//  PURPOSE:  To swap the strings in 'array[]' at indices 'index0' and 'index1'.
//	No return value.
void		swap		(char**		array,
				 int		index0,
				 int		index1
				)
{
  // YOUR CODE HERE
}


//  PURPOSE:  To repeatedly ask the user the text "Please enter ", followed
//	by the text in 'descriptionCPtr', followed by the numbers 'min' and
//	'max', and to get an entered integer from the user.  If this entered
//	integer is either less than 'min', or is greater than 'max', then
//	the user is asked for another number.  After the user finally enters
//	a legal number, this function returns that number.
int		obtainIntInRange(const char*	descriptionCPtr,
				 int   		min,
				 int		max
				)
{
  int		entry;
  char		text[TEXT_LEN];

  // YOUR CODE HERE

  return(entry);
}


//  PURPOSE:  To generate the array of strings.
char**		generateStringArray
				(int	numStrings
				)
{
  char**	array = (char**)calloc(numStrings,sizeof(char*));
  int		i;
  int		j;

  for  (i = 0;  i < numStrings;  i++)
  {
    array[i]	= (char*)malloc(strLen);

    for  (j = 0;  j < strLen;  j++)
    {
      array[i][j] = (rand() % 16) + 'A';
    }

  }

  return(array);
}


void		print		(char**		array,
				 int		arrayLen
				)
{
  int	i;
  int	j;

  for  (i = 0;  i < arrayLen;  i++)
  {
    for  (j = 0;  j < strLen;  j++)
    {
      putchar(array[i][j]);
    }

    putchar('\n');
  }

}


void		releaseMem	(char**		array,
				 int		arrayLen
				)
{
  int	i;

  for  (i = 0;  i < arrayLen;  i++)
  {
    free(array[i]);
  }

  free(array);
}


int		main		()
{
  int		arrayLen;
  char**	array;
  int		choice;

  arrayLen = obtainIntInRange("number of strings",1,65536*16);
  strLen   = obtainIntInRange("length of each string",1,16);
  choice   = obtainIntInRange("1 for insertion sort or 2 for quicksort",1,2);
  array	   = generateStringArray(arrayLen);

  switch  (choice)
  {
  case 1 :
    insertionSort(array,arrayLen);
    break;

  case 2 :
    quickSort(array,arrayLen);
    break;
  }

  print(array,arrayLen);
  releaseMem(array,arrayLen);
  return(EXIT_SUCCESS);
}
