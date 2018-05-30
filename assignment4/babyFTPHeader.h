/*-------------------------------------------------------------------------*
 *---									---*
 *---		babyFTPHeader.h						---*
 *---									---*
 *---	    This file defines common constants for a very simple remote	---*
 *---	file listing server.						---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1.0		2012 August 9		Joseph Phillips	---*
 *---									---*
 *---	Version 1.1		2013 August 15		Joseph Phillips	---*
 *---									---*
 *---	    Adapted to do more than just list remote files as the	---*
 *---	previous remoteFileListingHeader.h.				---*
 *---									---*
 *-------------------------------------------------------------------------*/

#include	<cstdlib>
#include	<cstdio>
#include	<cstring>
#include	<unistd.h>	// for close(), read(), write()
#include	<arpa/inet.h>	// for htons(), bind(), socket()
#include	<ncurses.h>	// for cursor control

typedef		unsigned int			uint;

const int	MAX_STRING			= 80;

const int	MAX_PASSWORD_LEN		= MAX_STRING;

const int	MAX_LINE			= 256;

const char	DUMMY_PASSWORD_VISIBLE_CHAR	= '.';

const char	BACKSPACE_CHAR			= 127;

const int	NO_FILE_RESPONSE		= -1;

#define		BAD_PASSWORD_RESPONSE		"Bad password!"

#define		GOOD_PASSWORD_RESPONSE		"Login successful."

#define		END_RESPONSE			"<end>"

typedef		enum
		{
		  NULL_FTP_ACTION,
		  LIST_FTP_ACTION,
		  GET_FTP_ACTION,
		  PUT_FTP_ACTION,
		  QUIT_FTP_ACTION
		}
		ftp_action_t;

#define		LIST_CMD			"list"

const int	LIST_CMD_LEN			= sizeof(LIST_CMD) - 1;

#define		GET_CMD				"get "

const int	GET_CMD_LEN			= sizeof(GET_CMD) - 1;

#define		PUT_CMD				"put "

const int	PUT_CMD_LEN			= sizeof(PUT_CMD) - 1;

#define		QUIT_CMD			"quit"

const int	QUIT_CMD_LEN			= sizeof(QUIT_CMD) - 1;