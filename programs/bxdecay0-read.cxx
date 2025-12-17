
// Standard library:
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>

// This project:
#include <bxdecay0/event_reader.h>
#include <bxdecay0/event.h>

struct app_config_type
{
  int verbosity = 0;
  bool printEvents = false;
  bxdecay0::event_reader::config_type readerConfig;

  void print() const;
};

void cl_parse(int argc_, char ** argv_, app_config_type & app_config_);

int main(int argc_, char ** argv_)
{
  int error_code = EXIT_SUCCESS;
  try {
    
    int verbosity = 0;
    app_config_type appConfig;
    cl_parse(argc_, argv_, appConfig);
    appConfig.print();
    bxdecay0::event_reader reader(appConfig.readerConfig, verbosity);
    auto eventId = 0u;
    while (reader.has_next_event()) {
      bxdecay0::event event;
      reader.load_next_event(event);
      if (event.get_particles().size() == 1) {
	const auto & particle = event.get_particles().front();
	double px = particle.get_px();
	double py = particle.get_py();
	double pz = particle.get_pz();
	double P2 = px*px+py*py+pz*pz;
	double M = particle_mass_MeV(particle.get_code());
	double W2 = M*M+ P2;
	double W = std::sqrt(W2);
	double T = W - M;
	std::cout << T << '\n';
      }
      if (appConfig.printEvents) {
	std::clog << "event #" << eventId << " : \n";
	event.print(std::clog);
      }
      eventId++;
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

void app_config_type::print() const
{
  std::cerr << "Configuration: " << '\n';
  std::cerr << "|-- verbosity = " << verbosity << '\n';
  std::cerr << "|-- printEvents = " << printEvents << '\n';
  std::cerr << "|-- readerConfig  : " << '\n';
  std::cerr << "|   |-- #event_files : " << readerConfig.event_files.size() << '\n';
  std::cerr << "|   |-- start_event : " << readerConfig.start_event << '\n';
  std::cerr << "|   |-- max_nb_events : " << readerConfig.max_nb_events << '\n';
  std::cerr << "o   `-- zero_event_time : " << readerConfig.zero_event_time << '\n';
  return;
}

void cl_parse(int argc_, char ** argv_, app_config_type & app_config_)
{
  std::vector<std::string> tokens;
  tokens.reserve(argc_);
  for (int i = 1; i < argc_; i++) {
    std::string arg = argv_[i];
    if (arg.size()) {
      tokens.push_back(argv_[i]);
    }
  }
  std::cerr << "[debug] tokens.size = " << tokens.size() << '\n';
  int itoken = 0;
  while (itoken < tokens.size()) {
    std::string token = tokens[itoken];
    if (token[0] == '-') {
      std::string opt = token;
      if (opt == "-d" or opt == "--debug") {
	app_config_.verbosity = 1;
      } else if (opt == "-p" or opt == "--print-events") {
	app_config_.printEvents = true;
      // } else if (opt == "-s" or opt == "--start-event") {
      // } else if (opt == "-m" or opt == "--max-nb-events") {
      } else {
	std::logic_error("unsupported option '" + opt + "'");
      }
	
    } else {
      std::string arg = token;
      app_config_.readerConfig.event_files.push_back(arg);
    }
    itoken++;
  }
  
  return;
}
