#ifndef __POLIZ_H__
#define __POLIZ_H__

#include "Lexeme.h"

class Poliz
{
         Lex        * p;
         int          size;
         int          free;
public:
                      Poliz (int max_size)
                      {
                        p = new Lex [size = max_size];
                        free = 0;
                      }
                     ~Poliz() { delete [] p; }
         void         put_lex ( Lex l )
                      {
                        p [free] = l;
                        free++;
                      }
         void         put_lex ( Lex l, int place) { p [place] = l; }
         void         blank    () { free++; }
         int          get_free () { return free; }
         Lex        & operator[] (int index)
                      {
                        if ( index > size )
                          throw "POLIZ:out of array";
                        else
                          if ( index > free )
                            throw "POLIZ:indefinite element of array";
                          else
                            return p[index];
                      }
         void         print ()
                      {
                        for ( int i = 0; i < free; ++i )
                          cout << p[i];
                      }
};

#endif
