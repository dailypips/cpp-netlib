// Copyright 2011 A. Joel Lamotte <mjklaim@gmail.com>.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef NETWORK_LOGGING_HPP_20121112
#define NETWORK_LOGGING_HPP_20121112

#include <sstream>
#include <functional>

namespace network { namespace logging { 

class log_record;

//using log_record_handler = std::function< void (const std::string&) >; // use this when VS can compile it...
typedef std::function< void (const log_record&) > log_record_handler;

void set_log_record_handler( log_record_handler handler );
void log( const log_record& message );

namespace handler
{
  log_record_handler get_std_log_handler();
  log_record_handler get_default_log_handler();
}

/** Helper to build a log record as a stream. */
class log_record
{
public:
  log_record(){} // = default;

  // Implicit construction from string
  log_record( const std::string& message ) 
  {
    write( message );
  }

  ~log_record()
  { 
    log( *this );
  }
  
  template< typename TypeOfSomething >
  log_record& write( TypeOfSomething&& something )
  {
    m_text_stream << something;
    return *this;
  }

  std::string full_message() const { return m_text_stream.str(); }

private:
  // disable copy
  log_record( const log_record& ); // = delete;
  log_record& operator=( const log_record& ); // = delete;

  std::ostringstream m_text_stream; // stream in which we build the message
    
};
  
template< typename TypeOfSomething >
inline log_record& operator<<( log_record& log, TypeOfSomething&& something )
{
  return log.write( std::forward<TypeOfSomething>(something) );
}

}}


#endif /* end of include guard: NETWORK_LOGGING_HPP_20121112 */
