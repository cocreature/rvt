/*******************************************************************\

Module: Goto Program Template

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#ifndef CPROVER_GOTO_PROGRAM_TEMPLATE_H
#define CPROVER_GOTO_PROGRAM_TEMPLATE_H

#include <assert.h>

#include <iostream>
#include <set>

#include <namespace.h>

typedef enum { NO_INSTRUCTION_TYPE=0,
               GOTO=1,          // branch, possibly guarded
               ASSUME=2,        // non-failing guarded self loop
               ASSERT=3,        // assertions
               OTHER=4,         // anything else
               SKIP=5,          // just advance the PC
               START_THREAD=6,  // spawns an asynchronous thread
               END_THREAD=7,    // end the current thread
               LOCATION=8,      // semantically like SKIP
               END_FUNCTION=9,  // exit point of a function
               ATOMIC_BEGIN=10, // marks a block without interleavings
               ATOMIC_END=11,   // end of a block without interleavings
               RETURN=12,       // return from a function
               ASSIGN=13,       // assignment lhs:=rhs
               DECL=14,         // declare a local variable
               DEAD=15,         // marks the end-of-live of a local variable
               FUNCTION_CALL=16,// call a function
               THROW=17,        // throw an exception
               CATCH=18         // catch an exception
             }
  goto_program_instruction_typet;

std::ostream &operator<<(std::ostream &, goto_program_instruction_typet);

template <class codeT, class guardT>
class goto_program_templatet
{
public:
  // DO NOT COPY ME! I HAVE POINTERS IN ME!
  goto_program_templatet(const goto_program_templatet &src)
  {
    assert(src.instructions.empty());
  }

  // DO NOT COPY ME! I HAVE POINTERS IN ME!
  goto_program_templatet &operator=(const goto_program_templatet &src)
  {
    assert(src.instructions.empty());
    instructions.clear();
    update();
    return *this;
  }

  class instructiont
  {
  public:
    codeT code;
    
    // function this belongs to
    irep_idt function;
    
    // keep track of the location in the source file
    locationt location;
    
    // what kind of instruction?
    goto_program_instruction_typet type;

    // for gotos, assume, assert
    guardT guard;
    
    // for gotos
    typedef typename std::list<class instructiont>::iterator targett;
    typedef typename std::list<class instructiont>::const_iterator const_targett;
    typedef std::list<targett> targetst;
    typedef std::list<const_targett> const_targetst;

    targetst targets;
    
    typedef std::list<irep_idt> labelst;
    labelst labels;

    std::set<targett> incoming_edges;

    bool is_target() const
    { return target_number!=unsigned(-1); }
    
    void make_goto()
    {
      type=GOTO;
      targets.clear();
      guard.make_true();
      code.make_nil();
    }
     
    void make_return()
    {
      type=RETURN;
      targets.clear();
      guard.make_true();
      code.make_nil();
    }
     
    void make_function_call(const codeT &_code)
    {
      type=FUNCTION_CALL;
      targets.clear();
      guard.make_true();
      code=_code;
    }
    
    void make_skip()
    {
      type=SKIP;
      targets.clear();
      guard.make_true();
      code.make_nil();
    }
     
    void make_throw()
    {
      type=THROW;
      targets.clear();
      guard.make_true();
      code.make_nil();
    }
     
    void make_catch()
    {
      type=CATCH;
      targets.clear();
      guard.make_true();
      code.make_nil();
    }
     
    void make_assertion(const guardT &g)
    {
      type=ASSERT;
      targets.clear();
      guard=g;
      code.make_nil();
    }
     
    void make_assumption(const guardT &g)
    {
      type=ASSUME;
      targets.clear();
      guard=g;
      code.make_nil();
    }
     
    void make_assignment()
    {
      type=ASSIGN;
      targets.clear();
      guard.make_nil();
      code.make_nil();
    }
     
    void make_goto(typename std::list<class instructiont>::iterator _target)
    {
      make_goto();
      targets.push_back(_target);
    }
    
    void make_goto(typename std::list<class instructiont>::iterator _target, const guardT &g)
    {
      make_goto(_target);
      guard=g;
    }
    
    void make_other()
    {
      type=OTHER;
      targets.clear();
      guard.make_true();
      code.make_nil();
    }
    
    void make_decl()
    {
      type=DECL;
      targets.clear();
      guard.make_true();
      code.make_nil();
    }
    
    void make_dead()
    {
      type=DEAD;
      targets.clear();
      guard.make_true();
      code.make_nil();
    }
    
    inline bool is_goto         () const { return type==GOTO;          }
    inline bool is_return       () const { return type==RETURN;        }
    inline bool is_assign       () const { return type==ASSIGN;        }
    inline bool is_function_call() const { return type==FUNCTION_CALL; }
    inline bool is_throw        () const { return type==THROW; }
    inline bool is_catch        () const { return type==CATCH;         }
    inline bool is_skip         () const { return type==SKIP;          }
    inline bool is_location     () const { return type==LOCATION;      }
    inline bool is_other        () const { return type==OTHER;         }
    inline bool is_decl         () const { return type==DECL;          }
    inline bool is_dead         () const { return type==DEAD;          }
    inline bool is_assume       () const { return type==ASSUME;        }
    inline bool is_assert       () const { return type==ASSERT;        }
    inline bool is_atomic_begin () const { return type==ATOMIC_BEGIN;  }
    inline bool is_atomic_end   () const { return type==ATOMIC_END;    }
    inline bool is_start_thread () const { return type==START_THREAD;  }
    inline bool is_end_thread   () const { return type==END_THREAD;    }
    inline bool is_end_function () const { return type==END_FUNCTION;  }

    instructiont():
      location(static_cast<const locationt &>(get_nil_irep())),
      type(NO_INSTRUCTION_TYPE),
      location_number(0),
      target_number(unsigned(-1))
    {
      guard.make_true();
    }

    instructiont(goto_program_instruction_typet _type):
      location(static_cast<const locationt &>(get_nil_irep())),
      type(_type),
      location_number(0),
      target_number(unsigned(-1))
    {
      guard.make_true();
    }
    
    void swap(instructiont &instruction)
    {
      instruction.code.swap(code);
      instruction.location.swap(location);
      std::swap(instruction.type, type);
      instruction.guard.swap(guard);
      instruction.targets.swap(targets);
      instruction.function.swap(function);
    }
    
    // a globally unique number to identify a program location
    // it's guaranteed to be ordered in program order within
    // one goto_program
    unsigned location_number;
    
    // number unique per function to identify loops
    unsigned loop_number;
    
    // a number to identify branch targets
    // this is -1 if it's not a target
    unsigned target_number;

    bool is_backwards_goto() const
    {
      if(!is_goto()) return false;

      for(typename targetst::const_iterator
          it=targets.begin();
          it!=targets.end();
          it++)
        if((*it)->location_number<=location_number)
          return true;
          
      return false;
    }    
  };

  typedef std::list<class instructiont> instructionst;
  
  typedef typename instructionst::iterator targett;
  typedef typename instructionst::const_iterator const_targett;
  typedef typename std::list<targett> targetst;
  typedef typename std::list<const_targett> const_targetst;

  instructionst instructions;
  
  void get_successors(
    targett target,
    targetst &successors)
  {
    successors.clear();
    if(target==instructions.end()) return;

    targett next=target;
    next++;
    
    const instructiont &i=*target;
  
    if(i.is_goto())
    {
      for(typename targetst::const_iterator
          t_it=i.targets.begin();
          t_it!=i.targets.end();
          t_it++)
        successors.push_back(*t_it);
  
      if(!i.guard.is_true())
        successors.push_back(next);
    }
    else if(i.is_start_thread())
    {
      for(typename targetst::const_iterator
          t_it=i.targets.begin();
          t_it!=i.targets.end();
          t_it++)
        successors.push_back(*t_it);
  
      successors.push_back(next);
    }
    else if(i.is_end_thread())
    {
      // no successors
    }
    else if(i.is_return())
    {
      // the successor is the end_function at the end
      successors.push_back(--instructions.end());
    }
    else if(i.is_assume())
    {
      if(!i.guard.is_false())
        successors.push_back(next);
    }
    else
      successors.push_back(next);
  }

  void get_successors(
    const_targett target,
    const_targetst &successors) const
  {
    successors.clear();
    if(target==instructions.end()) return;

    const_targett next=target;
    next++;
    
    const instructiont &i=*target;
  
    if(i.is_goto())
    {
      for(typename targetst::const_iterator
          t_it=i.targets.begin();
          t_it!=i.targets.end();
          t_it++)
        successors.push_back(*t_it);
  
      if(!i.guard.is_true())
        successors.push_back(next);
    }
    else if(i.is_start_thread())
    {
      for(typename targetst::const_iterator
          t_it=i.targets.begin();
          t_it!=i.targets.end();
          t_it++)
        successors.push_back(*t_it);
  
      successors.push_back(next);
    }
    else if(i.is_end_thread())
    {
      // no successors
    }
    else if(i.is_return())
    {
      // the successor is the end_function at the end
      successors.push_back(--instructions.end());
    }
    else if(i.is_assume())
    {
      if(!i.guard.is_false())
        successors.push_back(next);
    }
    else
      successors.push_back(next);
  }

  void compute_incoming_edges();

  // insertion that preserves jumps to "target"
  void insert_before_swap(targett target, instructiont &instruction)
  {
    targett next=target;
    next++;
    instructions.insert(next, instructiont())->swap(*target);
    target->swap(instruction);
  }
  
  // insertion that preserves jumps to "target"
  void insert_before_swap(targett target, goto_program_templatet<codeT, guardT> &p)
  {
    if(p.instructions.empty()) return;
    insert_before_swap(target, p.instructions.front());
    targett next=target;
    next++;
    p.instructions.erase(p.instructions.begin());
    instructions.splice(next, p.instructions);
  }
  
  // this does not preserve jumps to target -- these move
  targett insert_before(targett target)
  {
    return instructions.insert(target, instructiont());
  }
  
  targett insert_after(targett target)
  {
    targett t=target;
    t++;
    return instructions.insert(t, instructiont());
  }
  
  inline void destructive_append(goto_program_templatet<codeT, guardT> &p)
  {
    instructions.splice(instructions.end(),
                        p.instructions);
  }

  inline void destructive_insert(
    targett target,
    goto_program_templatet<codeT, guardT> &p)
  {
    instructions.splice(target,
                        p.instructions);
  }

  targett add_instruction()
  {
    instructions.push_back(instructiont());
    return --instructions.end();
  }

  targett add_instruction(goto_program_instruction_typet type)
  {
    instructions.push_back(instructiont(type));
    return --instructions.end();
  }

  // these assume that the targets are computed and numbered
  std::ostream &output(
    const class namespacet &ns,
    const irep_idt &identifier,
    std::ostream &out) const;
  
  std::ostream& output(std::ostream &out) const
  {
    return output(namespacet(contextt()), "", out);
  }
  
  virtual std::ostream& output_instruction(
    const class namespacet &ns,
    const irep_idt &identifier,
    std::ostream &out,
    typename instructionst::const_iterator it) const=0;

  // compute the target numbers
  void compute_target_numbers();

  // compute location numbers
  void compute_location_numbers(unsigned &nr)
  {
    for(typename instructionst::iterator
        it=instructions.begin();
        it!=instructions.end();
        it++)
      it->location_number=nr++;
  }
  
  // compute location numbers
  void compute_location_numbers()
  {
    unsigned nr=0;
    compute_location_numbers(nr);
  }
  
  // compute loop numbers
  void compute_loop_numbers()
  {
    unsigned nr=0;
    for(typename instructionst::iterator
        it=instructions.begin();
        it!=instructions.end();
        it++)
      if(it->is_backwards_goto())
        it->loop_number=nr++;
  }
  
  void update();
  
  // empty program?
  bool empty() const
  {
    return instructions.empty();
  }

  // constructor/destructor
  goto_program_templatet()
  {
  }

  virtual ~goto_program_templatet()
  {
  }
   
  void swap(goto_program_templatet<codeT, guardT> &program)
  {
    program.instructions.swap(instructions);
  }
  
  void clear()
  {
    instructions.clear();
  }
  
  void copy_from(const goto_program_templatet<codeT, guardT> &src);
  
  bool has_assertion() const;
}; 

#include <langapi/language_util.h>
#include <iomanip>

template <class codeT, class guardT>
void goto_program_templatet<codeT, guardT>::update()
{
  compute_incoming_edges();
  compute_target_numbers();
  compute_location_numbers();
}

template <class codeT, class guardT>
std::ostream& goto_program_templatet<codeT, guardT>::output(
  const namespacet &ns,
  const irep_idt &identifier,
  std::ostream& out) const
{
  // output program

  for(typename instructionst::const_iterator
      it=instructions.begin();
      it!=instructions.end();
      it++)
    output_instruction(ns, identifier, out, it);

  return out;  
}

template <class codeT, class guardT>
void goto_program_templatet<codeT, guardT>::compute_target_numbers()
{
  // reset marking
  
  for(typename instructionst::iterator
      it=instructions.begin();
      it!=instructions.end();
      it++)
    it->target_number=-1;
  
  // mark the goto targets

  for(typename instructionst::const_iterator
      it=instructions.begin();
      it!=instructions.end();
      it++)
  {
    for(typename instructiont::targetst::const_iterator
        t_it=it->targets.begin();
        t_it!=it->targets.end();
        t_it++)
    {
      targett t=*t_it;
      if(t!=instructions.end())
        t->target_number=0;
    }
  }
  
  // number the targets properly
  unsigned cnt=0;
  
  for(typename instructionst::iterator
      it=instructions.begin();
      it!=instructions.end();
      it++)
  {
    if(it->is_target())
      it->target_number=++cnt;
  }

  // check the targets!
  // (this is a consistency check only)

  for(typename instructionst::const_iterator
      it=instructions.begin();
      it!=instructions.end();
      it++)
  {
    for(typename instructiont::targetst::const_iterator
        t_it=it->targets.begin();
        t_it!=it->targets.end();
        t_it++)
    {
      targett t=*t_it;
      if(t!=instructions.end())
        assert(t->target_number!=0);
    }
  }
  
}

template <class codeT, class guardT>
void goto_program_templatet<codeT, guardT>::copy_from(
  const goto_program_templatet<codeT, guardT> &src)
{
  // Definitions for mapping between the two programs
  typedef std::map<const_targett, targett> targets_mappingt;
  targets_mappingt targets_mapping;

  clear();

  // Loop over program - 1st time collects targets and copy

  for(typename instructionst::const_iterator
      it=src.instructions.begin();
      it!=src.instructions.end();
      it++)
  {
    targett new_instruction=add_instruction();
    targets_mapping[it]=new_instruction;
    *new_instruction=*it;
  }

  // Loop over program - 2nd time updates targets
  
  for(typename instructionst::iterator
      it=instructions.begin();
      it!=instructions.end();
      it++)
  {
    for(typename instructiont::targetst::iterator
        t_it=it->targets.begin();
        t_it!=it->targets.end();
        t_it++)
    {
      typename targets_mappingt::iterator
        m_target_it=targets_mapping.find(*t_it);

      if(m_target_it==targets_mapping.end())
        throw "copy_from: target not found";

      *t_it=m_target_it->second;
    }
  }

  compute_incoming_edges();
  compute_target_numbers();
}

// number them
template <class codeT, class guardT>
bool goto_program_templatet<codeT, guardT>::has_assertion() const
{
  for(typename instructionst::const_iterator
      it=instructions.begin();
      it!=instructions.end();
      it++)
    if(it->is_assert() && !it->guard.is_true())
      return true;

  return false;
}

template <class codeT, class guardT>
void goto_program_templatet<codeT, guardT>::compute_incoming_edges()
{
  for(typename instructionst::iterator
      it=instructions.begin();
      it!=instructions.end();
      it++)
  {
    it->incoming_edges.clear();
  }

  for(typename instructionst::iterator
      it=instructions.begin();
      it!=instructions.end();
      it++)
  {
    targetst successors;
  
    get_successors(it, successors);
    
    for(typename targetst::const_iterator
        s_it=successors.begin();
        s_it!=successors.end();
        s_it++)
    {
      targett t=*s_it;

      if(t!=instructions.end())
        t->incoming_edges.insert(it);
    }
  }
}

template <class codeT, class guardT>
inline bool order_const_target(
  const typename goto_program_templatet<codeT, guardT>::const_targett i1,
  const typename goto_program_templatet<codeT, guardT>::const_targett i2)
{
  const typename goto_program_templatet<codeT, guardT>::instructiont &_i1=*i1;
  const typename goto_program_templatet<codeT, guardT>::instructiont &_i2=*i2;
  return &_i1<&_i2;
}

#endif
