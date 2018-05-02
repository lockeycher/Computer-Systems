#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#include  "safeBustersHeaders.h"

int program_still_run = 1;
int safe_opened = 0;
int firstNum;
int secondNum;
int thirdNum;

pid_t crackingThief;

void sig_quit_handler(int signum)
{
  program_still_run = 0;
}


int computeResponse(int* countPtr)
{
  int toReturn;

  sleep(1);
  (*countPtr)--;

  if  (*countPtr == 0)
  {
    printf("Safe \"Click!\"\n");
    toReturn= SIG_RIGHT_DIGIT;
  }
  else
  {
    printf("Safe \"Nope.\"\n");
    toReturn= SIG_WRONG_DIGIT;
  }

  return(toReturn);
}


void sig_try_next_digit_handler(int signum, siginfo_t* sigInfoPtr, void* data)
{
  crackingThief = sigInfoPtr -> si_pid;

  int address = 0;
  if (firstNum > 0)
  {
    address = computeResponse(&firstNum);
  } 
  else if (secondNum > 0)
  {
    address = computeResponse(&secondNum);
  }
  else if (thirdNum > 0)
  { 
    address = computeResponse(&thirdNum);
    if (address == SIG_RIGHT_DIGIT)
    {
      safe_opened = 1;
    }
  }
  kill(crackingThief, address);
}


int main()
{

  // initialize the random number combination
  srand(getpid());

  // install simple handler SIG_QUIT
  struct sigaction act;

  memset(&act,'\0',sizeof(act));
  act.sa_handler = sig_quit_handler;
  sigaction(SIG_QUIT, &act, NULL);


  // install advance handler SIG_TRY_NEXT_DIGIT
  act.sa_flags = SA_SIGINFO;
  act.sa_sigaction = sig_try_next_digit_handler;
  sigaction(SIG_TRY_NEXT_DIGIT, &act, NULL);


  // initialize all combination numbers
  firstNum = (rand() % 16) + 1;
  secondNum = (rand() % 16) + 1;
  thirdNum = (rand() % 16) + 1;


  // print the number combination
  printf("Don't tell, but my combination is %d-%d-%d \n", firstNum, secondNum, thirdNum);


  // hangout in a loop
  while (program_still_run)
  {
    sleep(1);
  }

  // note whether the safe was opened
  if (safe_opened)
  {
    printf("Can't believe I just let you in! \n");
  }
  else
  {
    printf("Haha! Keep going thief. \n");
  }

  return(EXIT_SUCCESS);
}
