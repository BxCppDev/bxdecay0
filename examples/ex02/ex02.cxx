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
#include <fstream>
#include <cmath>
#include <iostream>
#include <stdexcept>

// Third party library:
// - HepMC:
#include <HepMC3/Attribute.h>
#include <HepMC3/FourVector.h>
#include <HepMC3/GenEvent.h>
#include <HepMC3/GenParticle.h>
#include <HepMC3/GenRunInfo.h>
#include <HepMC3/GenVertex.h>
#include <HepMC3/WriterAscii.h>

// This project:
#include <bxdecay0/decay0_generator.h> // Main decay0 generator
#include <bxdecay0/event.h>            // Generated event model
#include <bxdecay0/particle_utils.h>   // Particle masses in BxDecay0
#include <bxdecay0/std_random.h>       // Random number interface
#include <bxdecay0/version.h>          // Library version

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
    std::size_t nevents = 10;

    // Output file name:
    std::string fout_name("bxdecay_ex02-hepmc3-ascii.data");

    // Parameters of the decay:

    // Isotope:
    std::string nuclide = "Mo100";

    // Daughter's energy level (ground state):
    int level = 0;

    // Decay category:
    bxdecay0::decay0_generator::decay_category_type decay_cat = bxdecay0::decay0_generator::DECAY_CATEGORY_DBD;

    // DBD mode (two neutrino):
    bxdecay0::dbd_mode_type dbd_mode = bxdecay0::DBDMODE_2NUBB_0_2N; // 2vbb

    // Activity of the decaying source (becquerel):
    double activity = 2.0;

    // The random generator:
    std::default_random_engine generator(seed);
    bxdecay0::std_random prng(generator);

    // The event generator:
    bxdecay0::decay0_generator decay0;

    // Variant:

    // Feel free to comment out and make a try with some background radioactity !
    // decay_cat = bxdecay0::decay0_generator::DECAY_CATEGORY_BACKGROUND;
    // nuclide = "Co60";

    // Configuration:
    decay0.set_debug(false);
    decay0.set_decay_category(decay_cat);
    decay0.set_decay_isotope(nuclide);
    if (decay0.get_decay_category() == bxdecay0::decay0_generator::DECAY_CATEGORY_DBD) {
      decay0.set_decay_dbd_level(level);         // to ground state of daughter isotope
      decay0.set_decay_dbd_mode(dbd_mode);       // specific DBD process/mechanism
      decay0.set_decay_dbd_esum_range(2.0, 4.3); // generate only high energy part of the spectrum (MeV)
    }

    // Initialization;
    decay0.initialize(prng);

    // Print:
    decay0.smart_dump(std::clog, "Decay0 DBD generator: ", "[info] ");
    /* Statistical weight of the event
     * with respect to the total energy
     * spectrum.
     */
    double toallevents = decay0.get_bb_params().toallevents;
    std::clog << "test1: Ratio toallevents = " << toallevents << "\n";

    /***************************************/
    /* Initialization of working resources */
    /***************************************/

    // HepMC run info:
    std::shared_ptr<HepMC3::GenRunInfo> runInfoPtr(std::make_shared<HepMC3::GenRunInfo>());
    runInfoPtr->add_attribute("seed", std::make_shared<HepMC3::IntAttribute>(seed));
    runInfoPtr->add_attribute("activity", std::make_shared<HepMC3::DoubleAttribute>(activity));
    runInfoPtr->add_attribute("nevents", std::make_shared<HepMC3::IntAttribute>(nevents));
    std::string cat_string = bxdecay0::decay0_generator::decay_category_to_label(decay0.get_decay_category());
    runInfoPtr->add_attribute("category", std::make_shared<HepMC3::StringAttribute>(cat_string));
    runInfoPtr->add_attribute("nuclide", std::make_shared<HepMC3::StringAttribute>(decay0.get_decay_isotope()));
    if (decay0.get_decay_category() == bxdecay0::decay0_generator::DECAY_CATEGORY_DBD) {
      runInfoPtr->add_attribute("daughter_level", std::make_shared<HepMC3::IntAttribute>(decay0.get_decay_dbd_level()));
      runInfoPtr->add_attribute("dbd_mode", std::make_shared<HepMC3::IntAttribute>(decay0.get_decay_dbd_mode()));
      if (decay0.has_decay_dbd_esum_range()) {
        runInfoPtr->add_attribute("min_energy",
                                  std::make_shared<HepMC3::DoubleAttribute>(decay0.get_decay_dbd_esum_range_lower()));
        runInfoPtr->add_attribute("max_energy",
                                  std::make_shared<HepMC3::DoubleAttribute>(decay0.get_decay_dbd_esum_range_upper()));
        runInfoPtr->add_attribute("toallevents", std::make_shared<HepMC3::DoubleAttribute>(toallevents));
      }
    }

    HepMC3::GenRunInfo::ToolInfo decay0_info;
    decay0_info.name        = "bxdecay0";
    decay0_info.version     = BXDECAY0_LIB_VERSION;
    decay0_info.description = "BxDecay0 nuclear decay event generator";
    runInfoPtr->tools().push_back(decay0_info);

    // HepMC output:
    HepMC3::WriterAscii writer(fout_name.c_str(), runInfoPtr);

    /**************************/
    /* Decay Event generation */
    /**************************/

    // Random engine for the event time:
    std::exponential_distribution<> decay_timer(activity);

    // Generated decay event (collection of generated particles):
    bxdecay0::event gendecay;

    // Loop on events:
    for (std::size_t ievent = 0; ievent < nevents; ievent++) {

      // Randomize the decay event:
      decay0.shoot(prng, gendecay);

      // Force the time of the decay:
      double evtime = decay_timer(generator);
      gendecay.set_time(evtime);

      // Debug dump:
      if (debug)
        gendecay.print(std::cerr, "DBD event:", "[debug] ");

      // Build a Hep MC event:
      static const double C_LIGHT_MM_PER_SEC = 3e11;
      std::shared_ptr<HepMC3::GenEvent> genEvtPtr
          = std::make_shared<HepMC3::GenEvent>(runInfoPtr, HepMC3::Units::MEV, HepMC3::Units::MM);
      genEvtPtr->set_event_number(ievent);
      std::shared_ptr<HepMC3::GenVertex> genVtxPtr = std::make_shared<HepMC3::GenVertex>(
          HepMC3::FourVector(0., 0., 0., gendecay.get_time() * C_LIGHT_MM_PER_SEC));
      genEvtPtr->add_vertex(genVtxPtr);

      double part_time = 0.0;
      for (const auto & particle : gendecay.get_particles()) {
        std::shared_ptr<HepMC3::GenParticle> genPartPtr = std::make_shared<HepMC3::GenParticle>();
        // http://pdg.lbl.gov/mc_particle_id_contents.html
        int pid = 0;
        switch (particle.get_code()) {
        case bxdecay0::GAMMA:
          pid = 22;
          break;
        case bxdecay0::POSITRON:
          pid = -11;
          break;
        case bxdecay0::ELECTRON:
          pid = 11;
          break;
        case bxdecay0::NEUTRON:
          pid = 2112;
          break;
        case bxdecay0::PROTON:
          pid = 2212;
          break;
        case bxdecay0::ALPHA:
          pid = 1000020040;
          break;
        default:
          break;
        }
        if (particle.has_time()) {
          // Cumulative particle time:
          part_time += particle.get_time();
        }
        genPartPtr->set_pid(pid);
        genPartPtr->set_momentum(HepMC3::FourVector(particle.get_px(),
                                                    particle.get_py(),
                                                    particle.get_pz(),
                                                    part_time * C_LIGHT_MM_PER_SEC));
        genPartPtr->set_generated_mass(bxdecay0::particle_mass_MeV(particle.get_code()));
        // std::clog << "[debug] ??? Mass set = " << genPartPtr->is_generated_mass_set() << std::endl;
        // std::clog << "[debug] ??? Mass     = " << genPartPtr->generated_mass() << std::endl;
        genVtxPtr->add_particle_out(genPartPtr);
      }

      // Store the HepMC event:
      writer.write_event(*genEvtPtr.get());

      // Clear the event:
      gendecay.reset();
    }

    /***************/
    /* Termination */
    /***************/

    // terminate the generator:
    decay0.reset();

  } catch (std::exception & error) {
    std::cerr << "[error] " << error.what() << std::endl;
    error_code = EXIT_FAILURE;
  } catch (...) {
    std::cerr << "[error] "
              << "Unexpected exception!" << std::endl;
    error_code = EXIT_FAILURE;
  }
  return error_code;
}
