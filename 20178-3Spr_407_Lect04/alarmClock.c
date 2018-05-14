#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<signal.h>
#include	<unistd.h>

#define		MAX_LINE	64

int		shouldRun	= 1;

void		sigAlarmHandler	(int	sigNum
				)
{
  shouldRun	= 0;
}


void		sigIntHandler	(int	sigNum
				)
{
  int	numSecsRemaining	= alarm(0);
  char	line[MAX_LINE];

  printf("%d seconds remain, press Enter to continue:",numSecsRemaining);
  fgets(line,MAX_LINE,stdin);
  alarm(numSecsRemaining);
}


int		main		()
{
  int		numSecs;
  char		line[MAX_LINE];
  struct sigaction	act;

  memset(&act,'\0',sizeof(act));
  act.sa_handler	= sigAlarmHandler;
  sigaction(SIGALRM,&act,NULL);

  act.sa_handler	= sigIntHandler;
  sigaction(SIGINT,&act,NULL);

  printf("Please enter the number of seconds: ");
  fgets(line,MAX_LINE,stdin);
  numSecs	= strtol(line,NULL,10);

  alarm(numSecs);

  while  (shouldRun)
    printf("Tick-tock!\n");

  printf("Ding! Ding! Ding!\n");
  return(EXIT_SUCCESS);
}
