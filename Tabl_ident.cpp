#include "Tabl_ident.h"

int Tabl_ident::put ( const char *buf )
{
	for (int j = 1; j < top; j++)
    	if (!strcmp(buf, p[j].get_name()))
      		return j;
  	p[top].put_name(buf);
  	++top;
  	return top - 1;
}