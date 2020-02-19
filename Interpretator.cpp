#include "Interpretator.h"

void Interpretator::interpretation ()
{
  pars.analyze ();
  E.execute ( pars.prog );
}
