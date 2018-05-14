#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<signal.h>

void	sigIntHandler	(int	signum)
{
  switch  (rand() % 4)
  {
  case 0 :
    printf("Ouch!\n");
    break;
  case 1 :
    printf("Stop that!\n");
    break;
  case 2 :
    printf("Serenity now!\n");
    break;
  case 3 :
    printf("Yow!\n");
    break;
  }
}

int		main		()
{
  struct sigaction act;

  memset(&act,'\0',sizeof(act));
  act.sa_handler = sigIntHandler;
  sigaction(SIGINT,&act,NULL);

  while  (1)
  {
    printf("You can't stop me!  Ngyeah-ngyeah!\n");
    sleep(2);
  }

  return(EXIT_SUCCESS);
}
