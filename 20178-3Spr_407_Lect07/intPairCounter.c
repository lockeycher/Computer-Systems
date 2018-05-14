#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>

#define		LINE_LEN	256
#define		COMMENT_CHAR	'#'

int		main		(int	argc,
				 char*	argv[]
				)
{
  if  (argc < 2)
  {
    fprintf(stderr,"Usage:\tintPairCounter <filename>\n");
    exit(EXIT_FAILURE);
  }

  const char*	filePath	= argv[1];
  int		counter		= 0;
  FILE*		filePtr		= fopen(filePath,"r");

  if  (filePtr == NULL)
  {
    fprintf(stderr,"Cannot open %s\n",filePath);
    exit(EXIT_FAILURE);
  }

  char		line[LINE_LEN];
  int		lineCounter	= 0;

  while  ( fgets(line,LINE_LEN,filePtr) != NULL )
  {
    int	i;

    lineCounter++;

    for  (i = 0;  line[i] != '\0';  i++)
      if  ( !isspace(line[i]) )
	break;

    switch  (line[i])
    {
    case '\0' :
    case COMMENT_CHAR :
      continue;

    case '0' :
    case '1' :
    case '2' :
    case '3' :
    case '4' :
    case '5' :
    case '6' :
    case '7' :
    case '8' :
    case '9' :
      {
	int	int0,int1;

	if  ( sscanf(line+i,"%d %d",&int0,&int1) == 2 )
	  counter++;
	else
	  fprintf(stderr,"Missing integer at line %d\n",lineCounter);
	
      }
      break;

    default :
      fprintf(stderr,"Missing integer at line %d\n",lineCounter);
    }

  }

  fclose(filePtr);
  printf("%d\n",counter);
  return(EXIT_SUCCESS);
}


















