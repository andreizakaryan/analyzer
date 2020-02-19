#ifndef __SCANNER_H__
#define __SCANNER_H__

#include <cstdio>
#include <cstring>
#include "Lexeme.h"
#include "Tabl_ident.h"

extern Tabl_ident TID;

class Scanner
{
    enum state { H, IDENT, NUMB, COM, ALE, DELIM, NEQ };
  	static char* TW[];
  	static type_of_lex words[];
  	static char* TD[];
  	static type_of_lex dlms[];
    state CS;
    FILE* fp;
    char c;
    char buf [ 80 ];
    int buf_top;
    void clear ()
    {
        buf_top = 0;
        for ( int j = 0; j < 80; j++ )
            buf[j] = '\0';
    }
    void add ()
    {
        buf [ buf_top++ ] = c;
    }
    int look ( const char *buf, char **list )
    {
        int i = 0;
        while (list[i])
        {
        	if ( !strcmp(buf, list[i]) )
            	return i;
            ++i;
        }
        return 0;
    }
    void gc ()
    {
        c = fgetc (fp);
    }
public:
    Scanner (const char * program)
    {
        fp = fopen ( program, "r" );
        CS = H;
        clear();
        gc();
    }
    Lex get_lex();
};

#endif
