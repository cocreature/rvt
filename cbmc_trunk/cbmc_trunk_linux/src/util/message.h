/*******************************************************************\

Module:

Author: Daniel Kroening, kroening@kroening.com

\*******************************************************************/

#ifndef CPROVER_MESSAGE_H

#define CPROVER_MESSAGE_H

#include <string>
#include <iostream>

#include "location.h"

class message_handlert
{
public:
  virtual void print(unsigned level, const std::string &message) = 0;

  virtual void print(
    unsigned level,
    const std::string &message,
    int sequence_number,
    const locationt &location);

  virtual ~message_handlert()
  {
  }
};
 
class null_message_handlert:public message_handlert
{
public:
  virtual void print(unsigned level, const std::string &message)
  {
  }

  virtual void print(
    unsigned level,
    const std::string &message,
    int sequence_number,
    const locationt &location)
  {
  }
};
 
class stream_message_handlert:public message_handlert
{
public:
  stream_message_handlert(std::ostream &_out):out(_out)
  {
  }

  virtual void print(unsigned level, const std::string &message)
  { out << message << std::endl; }
  
protected:
  std::ostream &out;
};

class message_clientt
{
public:
  virtual ~message_clientt()
  {
  }

  virtual void set_message_handler(message_handlert &_message_handler);

  virtual void set_verbosity(unsigned _verbosity)
  { verbosity=_verbosity; }
  
  // Levels:
  //
  //  0 none
  //  1 only errors
  //  2 + warnings
  //  4 + results
  //  6 + phase information
  //  8 + statistical information
  //  9 + progress information
  // 10 + debug info
  
  virtual unsigned get_verbosity() const
  {
    return verbosity;
  }
  
  message_clientt()
  {
    message_handler=(message_handlert *)NULL;
    verbosity=10;
  }
   
  message_clientt(message_handlert &_message_handler)
  {
    message_handler=&_message_handler;
    verbosity=10;
  }
   
  message_handlert &get_message_handler()
  {
    return *message_handler;
  }

protected:
  unsigned verbosity;
  message_handlert *message_handler;
};
 
class messaget:public message_clientt
{
public:
  messaget()
  {
  }
   
  messaget(message_handlert &_message_handler):
    message_clientt(_message_handler)
  {
  }
   
  virtual void print(const std::string &message)
  { print(1, message); }

  void status(const std::string &message)
  { print(6, message); }
  
  void result(const std::string &message)
  { print(4, message); }
   
  void warning(const std::string &message)
  { print(2, message); }
   
  void debug(const std::string &message)
  { print(9, message); }
   
  void status(
    const std::string &message,
    const std::string &file)
  {
    locationt location;
    location.set_file(file);
    print(6, message, -1, location);
  }
   
  void error(const std::string &message)
  { print(1, message); }

  void statistics(const std::string &message)
  { print(8, message); }

  void error(
    const std::string &message,
    const std::string &file)
  {
    locationt location;
    location.set_file(file);
    print(1, message, -1, location);
  }

  virtual void print(unsigned level, const std::string &message);

  virtual void print(
    unsigned level,
    const std::string &message,
    int sequence_number, // -1: no sequence information
    const locationt &location);
  
  virtual ~messaget() {  }
};

#endif
