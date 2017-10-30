/** ex02.cxx
 *
 * Copyright 2017 François Mauger <mauger@lpccaen.in2p3.fr>
 * Copyright 2017 Normandie Université
 *
 * This file is part of BxDecay0.
 *
 * BxDecay0 is free software: you  can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free  Software Foundation, either  version 3 of the  License, or
 * (at your option) any later version.
 *
 * BxDecay0 is distributed  in the hope that it will  be useful, but
 * WITHOUT  ANY   WARRANTY;  without  even  the   implied  warranty  of
 * MERCHANTABILITY or  FITNESS FOR A  PARTICULAR PURPOSE.  See  the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BxDecay0.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

// Standard library:
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <fstream>

// Third party library:
// - HepMC:
#include <HepMC/GenRunInfo.h>
#include <HepMC/GenParticle.h>
#include <HepMC/GenEvent.h>
#include <HepMC/GenVertex.h>
#include <HepMC/Attribute.h>
#include <HepMC/FourVector.h>
#include <HepMC/WriterAscii.h>

// This project:
#include <bxdecay0/std_random.h> // Random number interface
#include <bxdecay0/event.h>      // Generated event model
#include <bxdecay0/bb.h>         // Nuclear decay and double beta decay parameters
#include <bxdecay0/genbbsub.h>   // Main decay generation routine
#include <bxdecay0/version.h>    // Library version

int main()
{
  int error_code = EXIT_SUCCESS;
  try {

    /****************************/
    /* Configuration parameters */
    /****************************/

    // Debug flag:
    bool debug = true;

    // Random seed:
    unsigned int seed = 314159;

    // Number of generated events:
    std::size_t nevents = 100;

    // Parameters of the decay:
    bxdecay0::bbpars bb_params;
    bb_params.ebb1 = 0.0; // Minimum energy (MeV)
    bb_params.ebb2 = 4.3; // Maximum energy (MeV)
    bb_params.toallevents = 1.0; /* Statistical weight of the event
                                  * with respect to the total energy
                                  * spectrum.
                                  */
    // Mode: double beta decay:
    int i2bbs = bxdecay0::GENBBSUB_I2BBS_DBD;

    // Isotope:
    std::string chnuclide = "Mo100";

    // Daughter's energy level (ground state):
    int ilevel = 0;

    // DBD mode (neutrinoless):
    int modebb = bxdecay0::MODEBB_0NUBB_0_2N;

    // Activity of the decaying source in becquerel:
    double activity = 2.0;

    /***************************************/
    /* Initialization of working resources */
    /***************************************/

    // Random generator:
    std::default_random_engine generator(seed);
    bxdecay0::std_random prng(generator);

    // Decay event (collection of generated particles):
    bxdecay0::event decay;

    // Initialize the generator:
    int ier = 0;
    bxdecay0::genbbsub(prng,
                       decay,
                       i2bbs,
                       chnuclide,
                       ilevel,
                       modebb,
                       bxdecay0::GENBBSUB_ISTART_INIT,
                       ier,
                       bb_params);
    if (ier != 0) {
      throw std::logic_error("genbbsub initialization !");
    }
    decay.reset();

    // Run info:
    std::shared_ptr<HepMC::GenRunInfo> runInfoPtr(std::make_shared<HepMC::GenRunInfo>());
    runInfoPtr->add_attribute("weight",
                              std::make_shared<HepMC::DoubleAttribute>(bb_params.toallevents));

    HepMC::GenRunInfo::ToolInfo random_info;
    random_info.name = "bxdecay0::std_random";
    random_info.version = std::to_string(seed);
    random_info.description = "BxDecay0 random number generator";
    runInfoPtr->tools().push_back(random_info);

    HepMC::GenRunInfo::ToolInfo decay0_info;
    decay0_info.name = "BxDecay0";
    decay0_info.version = BXDECAY0_LIB_VERSION;
    decay0_info.description = "BxDecay0 nuclear decay event generator";
    runInfoPtr->tools().push_back(decay0_info);

    HepMC::WriterAscii writer("gendecay0-hepmc3-ascii.data", runInfoPtr);

    /**************************/
    /* Decay Event generation */
    /**************************/

    std::exponential_distribution<> decay_timer(activity);
    // Loop on events:
    for (std::size_t ievent = 0; ievent < nevents; ievent++) {

      // Randomize the decay event:
      bxdecay0::genbbsub(prng,
                         decay,
                         i2bbs,
                         chnuclide,
                         ilevel,
                         modebb,
                         bxdecay0::GENBBSUB_ISTART_GENERATE,
                         ier,
                         bb_params);
      if (ier != 0) {
        throw std::logic_error("genbbsub failed!");
      }

      // Force the time of the decay:
      double evtime = decay_timer(generator);
      decay.set_time(evtime);

      // Debug dump:
      if (debug) decay.print(std::cerr, "DBD event:", "[debug] ");

      // Build a Hep MC event:
      std::shared_ptr<HepMC::GenEvent> genEvtPtr =
        std::make_shared<HepMC::GenEvent>(runInfoPtr,
                                          HepMC::Units::MEV,
                                          HepMC::Units::MM);
      genEvtPtr->set_event_number(ievent);
      std::shared_ptr<HepMC::GenVertex> genVtxPtr
        = std::make_shared<HepMC::GenVertex>(HepMC::FourVector(0.,0.,0.,decay.get_time()));
      genEvtPtr->add_vertex(genVtxPtr);

      double part_time = 0.0;
      for (const auto & particle : decay.get_particles()) {
        std::shared_ptr<HepMC::GenParticle> genPartPtr
          = std::make_shared<HepMC::GenParticle>();
        // http://pdg.lbl.gov/mc_particle_id_contents.html
        int pid = 0;
        switch (particle.get_code()) {
        case bxdecay0::GAMMA : pid = 22; break;
        case bxdecay0::POSITRON : pid = -11; break;
        case bxdecay0::ELECTRON : pid = 11; break;
        case bxdecay0::NEUTRON : pid = 2112; break;
        case bxdecay0::PROTON : pid = 2212; break;
        case bxdecay0::ALPHA : pid = 1000020040; break;
        default: break;
        }
        if (particle.has_time()) {
          part_time += particle.get_time();
        }
        static const double C_LIGHT_MM_PER_SEC = 3e11;
        genPartPtr->set_pid(pid);
        genPartPtr->set_momentum(HepMC::FourVector(particle.get_px(),
                                                   particle.get_py(),
                                                   particle.get_pz(),
                                                   part_time * C_LIGHT_MM_PER_SEC));
        genVtxPtr->add_particle_out(genPartPtr);
      }
      writer.write_event(*genEvtPtr.get());

      // Clear the event:
      decay.reset();
    }

  } catch (std::exception & error) {
    std::cerr << "[error] " << error.what() << std::endl;
    error_code = EXIT_FAILURE;
  } catch (...) {
    std::cerr << "[error] " << "Unexpected exception!" << std::endl;
    error_code = EXIT_FAILURE;
  }
  return error_code;
}
