#include	"123.h"

#define		SIZE	64

void		enterBeginEnd	()
{
  char	array[SIZE];

  printf("Please enter a character: ");
  fgets(array,SIZE,stdin);
  begin	= array[0];

  do
  {
    printf("Please enter another character greater than %c: ",begin);
    fgets(array,SIZE,stdin);
    end	= array[0];
  }
  while  (end < begin);
}








  
