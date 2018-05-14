#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<unistd.h>
#include	<wait.h>

#define		TEXT_LEN	256
#define		QUIT_CMD	"exit"

int		main		()
{

  char		text[TEXT_LEN];

  while  (1)
  {
    printf("Type something (or \"%s\" to quit): ",QUIT_CMD);
    fgets(text,TEXT_LEN,stdin);

    char* cPtr	= strchr(text,'\n');

    if  (cPtr != NULL)
      *cPtr = '\0';

    if  ( strcmp(text,QUIT_CMD) == 0 )
      break;

    pid_t	pid = fork();

    if  (pid == 0)
    {
      execl(text,text,NULL);
      fprintf(stderr,"Could not run %s\n",text);
      exit(EXIT_FAILURE);
    }

    int	status;

    pid = wait(&status);

    if  (WIFEXITED(status) )
    {
      printf("Child %d did not crash ",pid);

      if  (WEXITSTATUS(status) == EXIT_SUCCESS)
        printf("and it succeeded.\n");
      else
        printf("but it failed.\n");
    }
    else
      printf("Child %d crashed.\n",pid);
  }

  return(EXIT_SUCCESS);
}
