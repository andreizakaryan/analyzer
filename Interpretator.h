#ifndef __INTERPRETATOR_H__
#define __INTERPRETATOR_H__

#include "Executer.h"
#include "Parser.h"

class Interpretator
{
  Parser   pars;
  Executer E;
public:
           Interpretator  (char* program): pars (program) {}
  void     interpretation ();
};

#endif
