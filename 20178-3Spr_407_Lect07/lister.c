#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<sys/types.h>
#include	<dirent.h>

int		main		(int	argc,
				 char*	argv[]
				)
{
  const char*	dirName	= (argc < 2) ? "." : argv[1];
  DIR*		dirPtr	= opendir(dirName);

  if  (dirPtr == NULL)
  {
    fprintf(stderr,"Cannot open directory %s\n",dirName);
    exit(EXIT_FAILURE);
  }

  struct dirent*	entryPtr;

  while  ( (entryPtr = readdir(dirPtr)) != NULL )
    printf("%s\n",entryPtr->d_name);

  closedir(dirPtr);
  return(EXIT_SUCCESS);
}
