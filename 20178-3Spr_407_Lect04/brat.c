#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<signal.h>

int		main		()
{
  struct sigaction act;

  memset(&act,'\0',sizeof(act));
  act.sa_handler = SIG_IGN;
  sigaction(SIGINT,&act,NULL);

  while  (1)
  {
    printf("You can't stop me!  Ngyeah-ngyeah!\n");
    sleep(2);
  }

  return(EXIT_SUCCESS);
}
