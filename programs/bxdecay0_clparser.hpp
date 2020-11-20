#ifndef BXDECAY0_CLPARSER_HPP
#define BXDECAY0_CLPARSER_HPP

// Standard library:
#include <vector>
#include <string>

// This project:
#include "bxdecay0_driver.hpp"

namespace bxdecay0 {

  /// \brief Command line parser
  class cl_parser
  {
  public:

    enum parse_status_type
      {
       PS_OK    = 0,
       PS_ERROR = 1,
       PS_USAGE = 2
      };
    
    struct parsing_context_type
    {
      bool help = false;
      bool parse_error = false;
      std::string error_message;        
    };
    
    cl_parser(int argc_, char ** argv_);
    
    ~cl_parser();

    parse_status_type parse(driver::config_type & config_);

  private:

    std::vector<std::string> _args_;            ///< Command line arguments to be parsd
    parsing_context_type     _parsing_context_; ///< Parsing context 
    
  };
   
} // namespace bxdecay0

#endif // BXDECAY0_CLPARSER_HPP

