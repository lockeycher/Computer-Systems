#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<unistd.h>
#include	<wait.h>
#include	<signal.h>

#define		TEXT_LEN	256
#define		QUIT_CMD	"exit"

void		sigChildHandler	(int	sigNum
				)
{
  pid_t	pid;
  int	status;

  while  ( (pid = waitpid(-1,&status,WNOHANG)) > 0)
  {

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
}


int		main		()
{
  struct sigaction	action;
  char			text[TEXT_LEN];

  memset(&action,'\0',sizeof(action));
  action.sa_flags	= SA_NOCLDSTOP | SA_RESTART;
  action.sa_handler	= sigChildHandler;
  sigaction(SIGCHLD,&action,NULL);

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

  }

  return(EXIT_SUCCESS);
}
