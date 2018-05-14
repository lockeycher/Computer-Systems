#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<signal.h>
#include	<wait.h>
#include	<unistd.h>

#define		TEXT_LEN	64

void		tickleHandler	(int		sigNum,
				 siginfo_t*	sigInfoPtr,
				 void*		data
				)
{
  if  (sigInfoPtr->si_pid == getppid())
    printf("Elmo: Hee Hee, that tickles!\n");
  else
    printf("Elmo: DIE PUNK!\n");
}


int		main		()
{
  pid_t	pid	= fork();

  if  (pid == 0)
  {
    struct sigaction	action;

    memset(&action,'\0',sizeof(action));
    action.sa_flags= SA_SIGINFO;
    action.sa_sigaction	= tickleHandler;
    sigaction(SIGINT,&action,NULL);

    while  (1)
      sleep(1);

    exit(EXIT_SUCCESS);
  }

  int	i;
  char	text[TEXT_LEN];

  for  (i = 0;  i < 4;  i++)
  {
    printf("Press enter to tickle your Elmo\n");
    fgets(text,TEXT_LEN,stdin);
    kill(pid,SIGINT);
  }

  return(EXIT_SUCCESS);
}
