/*-------------------------------------------------------------------------*
 *---									---*
 *---		lookoutThief.c						---*
 *---									---*
 *---	    This file defines the lookoutThief program, that starts the ---*
 *---	safe and crackingThief programs, and oversees the whole		---*
 *---	application.							---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2018 April 20		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

#include	"safeBustersHeaders.h"

#define		TEXT_LEN	64

int		isCoastClear	= 1;

int		haveTheGoods	= 0;

pid_t		safePid;

pid_t		crackingThiefPid;

void		sigAlarmHandler	(int	sigInt
				)
{
  printf("Watching thief \"Forget the safe!  We gotta go!\"\n");
  isCoastClear	= 0;
  //  YOUR CODE HERE to send SIG_QUIT to both safePid and crackingThiefPid
  kill(safePid, SIG_QUIT);
  kill(crackingThiefPid, SIG_QUIT);
}


void		sigChildHandler	(int	sigInt
				)
{
  if  (isCoastClear)
  {
    printf("Watching thief \"Good job, let's skedaddle!\"\n");
    haveTheGoods	= 1;
  }

  //  YOUR CODE HERE to send SIG_QUIT to safePid
  kill(safePid, SIG_QUIT);
}


int		main		()
{
  int			time;
  struct sigaction	act;

  //  YOUR CODE HERE
  //  Install sigAlarmHandler() as the SIGALRM handler
  //  Install sigChildHandler() as the SIGCHLD handler
  memset(&act, '\0', sizeof(act));
  act.sa_handler = sigAlarmHandler;
  sigaction(SIGALRM, &act, NULL);

  act.sa_handler = sigChildHandler;
  sigaction(SIGCHLD, &act, NULL);

  safePid	= fork(); // Change that 0 to make a new process 

  if  (safePid == 0)
  {
    //  YOUR CODE HERE to start safe
    execl("./safe", "safe", NULL);
    fprintf(stderr,"Watching thief \"Where's the freaking safe?!\"\n");
    exit(EXIT_FAILURE);
  }

  sleep(1);
  crackingThiefPid	= fork(); // Change that 0 to make a new process 

  if  (crackingThiefPid == 0)
  {
    char	pidText[TEXT_LEN];

    snprintf(pidText,TEXT_LEN,"%d",safePid);
    //  YOUR CODE HERE to start crackingThief with pidText as a command line argument
    execl("./crackingThief", "crackingThief", pidText, NULL);
    fprintf(stderr,"Watching thief \"Where's my partner in crime?!\"\n");
    exit(EXIT_FAILURE);
    
  }

  //  YOUR CODE HERE to get sent SIGALRM NUM_SECS_BEFORE_MUST_GO seconds in the future
  alarm(NUM_SECS_BEFORE_MUST_GO);
  
  for  (time = 0;  isCoastClear && !haveTheGoods;  time++)
  {
    if  ( (time % NUM_SECS_BETWEEN_HURRY_UPS) == 0 )
      printf("Watching thief \"Hurry it up!\"\n");

    sleep(1);
  }

  //  YOUR CODE HERE to wait for both child processes
  waitpid(-1, NULL, 0);
  waitpid(-1, NULL, 0);
  printf("(bye)\n");
  return(EXIT_SUCCESS);
}
