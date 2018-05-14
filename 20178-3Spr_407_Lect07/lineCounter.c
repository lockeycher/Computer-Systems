#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>

#define		LINE_LEN	256

int		main		(int		argc,
				 char*		argv[]
				)
{
  if  (argc < 3)
  {
    fprintf(stderr,"Usage:\tlineCounter <string> <filename>\n");
    exit(EXIT_FAILURE);
  }

  const char*	lookFor	= argv[1];
  const char*	filePath= argv[2];
  FILE*		filePtr	= fopen(filePath,"r");

  if  (filePtr == NULL)
  {
    fprintf(stderr,"Cannot open %s\n",filePath);
    exit(EXIT_FAILURE);
  }

  char		buffer[LINE_LEN];
  int		lookForLen	= strlen(lookFor);
  int		count		= 0;

  while  ( fgets(buffer,LINE_LEN,filePtr) != NULL )
    if  ( strncmp(buffer,lookFor,lookForLen) == 0 )
      count++;

  fclose(filePtr);
  printf("%d\n",count);
  return(EXIT_SUCCESS);
}







