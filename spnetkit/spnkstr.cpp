/*
 * Copyright 2008 Stephen Liu
 * For license terms, see the file COPYING along with this library.
 */

#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "spnkstr.hpp"

char * SP_NKStr :: strsep( char ** s, const char * del )
{
	char *d, *tok;

	if (!s || !*s) return NULL;
	tok = *s;
	d = strstr(tok, del);

	if (d) {
		*s = d + strlen(del);
		*d = '\0';
	} else {
		*s = NULL;
	}

	return tok;
}

size_t SP_NKStr :: strlcpy( char *dst, const char *src, size_t dst_sz )
{
    size_t n;
    char *p;

    for (p = dst, n = 0;
	 n + 1 < dst_sz && *src != '\0';
	 ++p, ++src, ++n)
	*p = *src;
    *p = '\0';
    if (*src == '\0')
	return n;
    else
	return n + strlen (src);
}

int SP_NKStr :: getToken( const char * src, int index, char * dest, int len,
		char delimiter, const char ** next )
{
	int ret = 0;

	const char * pos1 = src, * pos2 = NULL;

	while ( isspace( delimiter ) && delimiter == * pos1 && '\0' != * pos1 ) pos1++;
	for ( int i = 0; i < index; i++ ) {
		pos1 = strchr ( pos1, delimiter );
		if ( NULL == pos1 ) break;
		while ( isspace( delimiter ) && delimiter == * pos1 && '\0' != * pos1 ) pos1++;
	}

	*dest = '\0';
	if( NULL != next ) *next = NULL;

	if ( NULL != pos1 && '\0' != * pos1 ) {
		if( delimiter == *pos1 ) pos1++;
		pos2 = strchr ( pos1, delimiter );
		if ( NULL == pos2 ) {
			strncpy ( dest, pos1, len );
			if ( ((int)strlen(pos1)) >= len ) ret = -2;
		} else {
			if( pos2 - pos1 >= len ) ret = -2;
			len = ( pos2 - pos1 + 1 ) > len ? len : ( pos2 - pos1 + 1 );
			strncpy( dest, pos1, len );

			while ( isspace( delimiter ) && delimiter == * pos2 && '\0' != * pos2 ) pos2++;
			if( NULL != next && '\0' != *pos2 ) *next = pos2;
		}
	} else {
		ret = -1;
	}

	dest[ len - 1 ] = '\0';

	return ret;
}

