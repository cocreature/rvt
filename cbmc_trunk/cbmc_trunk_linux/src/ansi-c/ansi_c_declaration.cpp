/*******************************************************************\

Module: ANSI-C Language Type Checking

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#include <assert.h>

#include "ansi_c_declaration.h"

/*******************************************************************\

Function: ansi_c_declarationt::ansi_c_declarationt

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

ansi_c_declarationt::ansi_c_declarationt():exprt(ID_declaration)
{
}
  
/*******************************************************************\

Function: ansi_c_declarationt::to_symbol

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void ansi_c_declarationt::to_symbol(symbolt &symbol) const
{
  symbol.clear();    
  symbol.location=location();
  symbol.value=value();
  symbol.type=type();
  symbol.name=get_name();
  symbol.base_name=get_base_name();
  symbol.is_type=get_is_type();
  symbol.is_extern=get_is_extern();
  symbol.is_macro=get_is_macro();
  symbol.is_actual=get_is_argument();

  bool is_code=symbol.type.id()==ID_code;

  symbol.static_lifetime=
    !symbol.is_macro &&
    !symbol.is_type &&
    (get_is_global() || get_is_static()) &&
    !is_code;
    
  symbol.thread_local=
    (!get_is_global() && !is_code &&
     !get_is_static() && !symbol.is_type &&
     !symbol.is_macro) ||
    (get_is_global() && !is_code && get_is_thread_local());
     
  symbol.file_local=
    get_is_static() || symbol.is_macro || 
    (!get_is_global() && !get_is_extern() && !is_code);
  
  if(get_is_inline())
    symbol.type.set(ID_C_inlined, true);
}
