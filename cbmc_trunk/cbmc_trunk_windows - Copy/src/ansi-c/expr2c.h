/*******************************************************************\

Module:

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#ifndef CPROVER_EXPR2C_H
#define CPROVER_EXPR2C_H

#include <string>

class exprt;
class namespacet;
class typet;

std::string expr2c(const exprt &expr, const namespacet &ns);
std::string type2c(const typet &type, const namespacet &ns);

#endif
