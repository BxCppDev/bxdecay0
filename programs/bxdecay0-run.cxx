
// Standard library:
#include <cstdlib>
#include <iostream>
#include <exception>
#include <string>

// This project:
// #include <bxdecay0/.h>"
#include "bxdecay0_driver.hpp"
#include "bxdecay0_clparser.hpp"

int main(int argc_, char ** argv_)
{
  int error_code = EXIT_SUCCESS;
  try {

    bxdecay0::driver::config_type driverConfig;
    bxdecay0::cl_parser clParser(argc_, argv_);
    auto parse_status = clParser.parse(driverConfig);
    if (parse_status == bxdecay0::cl_parser::PS_OK) {
      bxdecay0::driver driver(driverConfig);
      driver.run();
    }
    
  } catch (std::exception & error) {
    std::cerr << "[error] " << error.what() << std::endl;
    error_code = EXIT_FAILURE;
  } catch (...) {
    std::cerr << "[error] " << "An unexpected error occured!" << std::endl;
    error_code = EXIT_FAILURE;
  }
  return error_code;
}
