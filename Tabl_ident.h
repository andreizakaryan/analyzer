#ifndef __TABL_IDENT_H__
#define __TABL_IDENT_H__

#include "Ident.h"
#include "Lexeme.h"
#include <cstring>

class Tabl_ident
{
    Ident* p;
    int size;
    int top;
public:
    Tabl_ident (int max_size)
    {
        p = new Ident[size = max_size];
        top = 1;
    }
    ~Tabl_ident() { delete [] p; }
    Ident& operator[] (int k) { return p[k]; }
    int put (const char *buf);
};

#endif