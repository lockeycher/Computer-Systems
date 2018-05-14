#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<sys/types.h>
#include	<dirent.h>
#include	<sys/stat.h>
#include	<unistd.h>

#define		BUFFER_LEN	512

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
  {
    char	entryPath[BUFFER_LEN];
    struct stat statBuffer;

    snprintf(entryPath,BUFFER_LEN,"%s/%s",dirName,entryPtr->d_name);
    stat(entryPath,&statBuffer);

    if  ( S_ISREG(statBuffer.st_mode) )
      printf("%23s\t(%ld)\n",entryPath,statBuffer.st_size);
    else
    if  ( S_ISDIR(statBuffer.st_mode) )
      printf("%23s\t(dir)\n",entryPath);
    else
      printf("%23s\t(other)\n",entryPath);

  }
  closedir(dirPtr);
  return(EXIT_SUCCESS);
}
