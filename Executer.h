#ifndef __EXECUTER_H__
#define __EXECUTER_H__

#include "Stack.h"
#include "Lexeme.h"
#include "Poliz.h"
#include "Tabl_ident.h"

extern Tabl_ident TID;

class Executer
{
         Lex          pc_el;
public:
         void         execute ( Poliz & prog );
};

#endif
