/*-------------------------------------------------------------------------*
 *---									---*
 *---		safeBustersHeaders.h					---*
 *---									---*
 *---	    This file includes headers and defines constants shared by	---*
 *---	all programs in the safe-cracking thieves application.		---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2018 April 20		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<signal.h>
#include	<wait.h>
#include	<unistd.h>

const int	SIG_QUIT			= SIGINT;

const int	SIG_TRY_NEXT_DIGIT		= SIGUSR1;

const int	SIG_WRONG_DIGIT			= SIGUSR1;

const int	SIG_RIGHT_DIGIT			= SIGUSR2;

const int	NUM_SECS_BETWEEN_HURRY_UPS	= 5;

const int	NUM_SECS_BEFORE_MUST_GO		= 24;
