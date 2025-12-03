/** test_decay0_generator.cxx
 *
 * Copyright 2017 François Mauger <mauger@lpccaen.in2p3.fr>
 * Copyright 2017 LPC Caen, Université de Caen Normandie
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
#include <chrono>
#include <cstdlib>
#include <cstdio>
#include <exception>
#include <iostream>
#include <limits>
#include <random>
#include <fstream>

// GSL:
#include <gsl/gsl_histogram.h>

// This project:
#include <bxdecay0/bb_utils.h>
#include <bxdecay0/config.h>
#include <bxdecay0/decay0_generator.h>
#include <bxdecay0/event.h>
#include <bxdecay0/std_random.h>
#include <bxdecay0/mdl_event_op.h>

void test1();
void test2();
void test3();
void test4();
void test5();
void test_backgrounds();
void test_cs137_mdl();
void test_cs137_mdlr();
void test20();
void test_Gd160_dbd();

int main()
{
  int error_code = EXIT_SUCCESS;
  try {
    test1();
    test2();
    test3();
    test4();
    test5();
    test_backgrounds();
    test_cs137_mdl();
    test_cs137_mdlr();
    test20();
    test_Gd160_dbd();
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

void test1()
{
  std::clog << "\ntest1:\n";
  unsigned int seed = 314159;
  std::default_random_engine generator(seed);
  bxdecay0::std_random prng(generator);

  bxdecay0::decay0_generator decay0;
  decay0.set_debug(true);
  decay0.set_decay_category(bxdecay0::decay0_generator::DECAY_CATEGORY_DBD);
  decay0.set_decay_isotope("Mo100");
  decay0.set_decay_dbd_level(0);
  decay0.set_decay_dbd_mode(bxdecay0::DBDMODE_4); // DBDMODE_2NUBB_0_2N
  decay0.set_decay_dbd_esum_range(2.0, 4.3);
  decay0.initialize(prng);
  decay0.smart_dump(std::clog, "Decay0 DBD generator: ", "[info] ");
  double toallevents = decay0.get_bb_params().toallevents;
  std::clog << "test1: Ratio toallevents = " << toallevents << "\n";

  bxdecay0::event decay;
  std::size_t nevents = 1;
  for (std::size_t ievent = 0; ievent < nevents; ievent++) {
    decay0.shoot(prng, decay);
    decay.set_time(0.0);
    decay.print(std::clog, "DBD event:", "[info] ");
    decay.store(std::cout);
  }

  decay0.reset();
  return;
}

void test2()
{
  std::clog << "\ntest2:\n";
  unsigned int seed = 314159;
  std::default_random_engine generator(seed);
  bxdecay0::std_random prng(generator);

  bxdecay0::decay0_generator decay0;
  // decay0.set_debug(true);
  decay0.set_decay_category(bxdecay0::decay0_generator::DECAY_CATEGORY_BACKGROUND);
  decay0.set_decay_isotope("Co60");
  decay0.initialize(prng);
  decay0.smart_dump(std::clog, "Decay0 background generator: ", "[info] ");

  bxdecay0::event decay;
  std::size_t nevents = 1;
  for (std::size_t ievent = 0; ievent < nevents; ievent++) {
    decay0.shoot(prng, decay);
    decay.set_time(0.0);
    decay.print(std::clog, "Background event:", "[info] ");
    decay.store(std::cout);
  }

  decay0.reset();
  return;
}

void test3()
{
  std::clog << "\ntest3:\n";
  unsigned int seed = 314159;
  std::default_random_engine generator(seed);
  bxdecay0::std_random prng(generator);

  bxdecay0::decay0_generator decay0;
  decay0.set_debug(true);
  decay0.set_decay_category(bxdecay0::decay0_generator::DECAY_CATEGORY_DBD);
  decay0.set_decay_isotope("Se82");
#if BXDECAY0_WITH_DBD_GA == 1
  decay0.set_decay_dbd_mode(bxdecay0::DBDMODE_21); // DBDMODE_2NUBB_GA_G0
#else
  decay0.set_decay_dbd_mode(bxdecay0::DBDMODE_1);
#endif
  decay0.set_decay_dbd_level(0);
  decay0.initialize(prng);
  decay0.smart_dump(std::clog, "DBD generator: ", "[info] ");

  bxdecay0::event decay;
  std::size_t nevents = 2;
  for (std::size_t ievent = 0; ievent < nevents; ievent++) {
    decay0.shoot(prng, decay);
    decay.set_time(0.0);
    decay.print(std::clog, "DBD event:", "[info] ");
    decay.store(std::cout);
  }

  decay0.reset();
  return;
}

void test4()
{
  std::clog << "\ntest4:\n";
  unsigned int seed = 314159;
  std::default_random_engine generator(seed);
  bxdecay0::std_random prng(generator);

  bxdecay0::decay0_generator decay0;
  // decay0.set_debug(true);
  decay0.set_decay_category(bxdecay0::decay0_generator::DECAY_CATEGORY_BACKGROUND);
  decay0.set_decay_isotope("Rn222");
  // decay0.set_decay_isotope("Ra228");
  decay0.initialize(prng);
  decay0.smart_dump(std::clog, "Decay0 background generator: ", "[info] ");

  bxdecay0::event decay;
  std::size_t nevents = 1;
  for (std::size_t ievent = 0; ievent < nevents; ievent++) {
    decay0.shoot(prng, decay);
    decay.set_time(0.0);
    decay.print(std::clog, "Background event:", "[info] ");
    decay.store(std::cout);
  }

  decay0.reset();
  return;
}

void test5()
{
  std::clog << "\ntest5:\n";
  unsigned int seed = 314159;
  std::default_random_engine generator(seed);
  bxdecay0::std_random prng(generator);

  bxdecay0::decay0_generator decay0;
  // decay0.set_debug(true);
  decay0.set_decay_category(bxdecay0::decay0_generator::DECAY_CATEGORY_BACKGROUND);
  decay0.set_decay_isotope("Ra226");
  // decay0.set_decay_isotope("Ra228");
  decay0.initialize(prng);
  decay0.smart_dump(std::clog, "Decay0 background generator: ", "[info] ");

  bxdecay0::event decay;
  std::size_t nevents = 1;
  for (std::size_t ievent = 0; ievent < nevents; ievent++) {
    decay0.shoot(prng, decay);
    decay.set_time(0.0);
    decay.print(std::clog, "Background event:", "[info] ");
    decay.store(std::cout);
  }

  decay0.reset();
  return;
}

void test_backgrounds()
{
  std::clog << "\ntest_backgrounds:\n";

  const auto & background_isotopes = bxdecay0::background_isotopes();
  for (const auto & name : background_isotopes) {
    std::clog << "Decay from isotope: '" << name << "'" << std::endl;
    unsigned int seed = 314159;
    std::default_random_engine generator(seed);
    bxdecay0::std_random prng(generator);

    bxdecay0::decay0_generator decay0;
    // decay0.set_debug(true);
    decay0.set_decay_category(bxdecay0::decay0_generator::DECAY_CATEGORY_BACKGROUND);
    decay0.set_decay_isotope(name);
    decay0.initialize(prng);
    decay0.smart_dump(std::clog, "Decay0 background generator: ", "[info] ");

    bxdecay0::event decay;
    std::size_t nevents = 1;
    for (std::size_t ievent = 0; ievent < nevents; ievent++) {
      decay0.shoot(prng, decay);
      decay.set_time(0.0);
      decay.print(std::clog, "Background event:", "[info] ");
      decay.store(std::cout);
    }

    decay0.reset();
  }
  return;
}

void test_cs137_mdl()
{
  std::clog << "\ntest_cs137_mdl:\n";

  const auto & background_isotopes = bxdecay0::background_isotopes();
  std::string name("Cs137");
  {
    std::clog << "Decay from isotope: '" << name << "'" << std::endl;
    unsigned int seed = 314159;
    std::default_random_engine generator(seed);
    bxdecay0::std_random prng(generator);

    bxdecay0::decay0_generator decay0;
    decay0.set_debug(true);
    decay0.set_decay_category(bxdecay0::decay0_generator::DECAY_CATEGORY_BACKGROUND);
    decay0.set_decay_isotope(name);

    // Install a MDL post-generation operation: force X direction for the first rank emitted gamma
    // and rotate the full event in these conditions
    bxdecay0::event_op_ptr mdlPtr(new bxdecay0::momentum_direction_lock_event_op(decay0.is_debug()));
    bxdecay0::momentum_direction_lock_event_op & mdl = dynamic_cast<bxdecay0::momentum_direction_lock_event_op&>(*mdlPtr);
    bxdecay0::particle_code requestedCode = bxdecay0::GAMMA;
    int requestedRank = 0;
    requestedCode = bxdecay0::INVALID_PARTICLE;
    // requestedRank = -1;
    // requestedCode = bxdecay0::ELECTRON;
    requestedRank = -1;
    mdl.set(requestedCode,        // Select only gammas
            requestedRank,        // Rank of the target gamma in the event (0 : first, 1: second, 2: third...)
            1.0, 0.0, 0.0,        // Emission cone is aligned on the X-axis
            M_PI / 4,             //   with an angle of aperture of 45 degrees
            false);               // Do not generate an error if no target particle is found. Just no-op and pass.
    decay0.add_operation(mdlPtr); // Install the MDL post-generation operation in the generator 
    decay0.initialize(prng);      // Initialize and lock the generator
    decay0.smart_dump(std::clog, "Decay0 background generator: ", "[info] ");

    double cosMin = -1.0;
    double cosMax = +1.0;
    size_t nBins = 220;    
    gsl_histogram * h1 = gsl_histogram_alloc(nBins);
    gsl_histogram_set_ranges_uniform(h1, cosMin * 1.1, cosMax * 1.1);
    gsl_histogram * h2 = gsl_histogram_alloc(nBins);
    gsl_histogram_set_ranges_uniform(h2, cosMin * 1.1, cosMax * 1.1);
    
    bxdecay0::event decay;
    std::size_t nevents = 10000;
    for (std::size_t ievent = 0; ievent < nevents; ievent++) {
      decay0.shoot(prng, decay);
      decay.set_time(0.0);
      decay.print(std::clog, name + " decay event:", "[info] ");
      decay.store(std::cout);
      int targetParticleIndex = mdl.get_last_target_index();
      if (requestedRank >= 0) {
        if (targetParticleIndex >= 0) {
          const auto & targetParticle = decay.get_particles()[targetParticleIndex];
          double cosPsi = targetParticle.get_px() / targetParticle.get_p();
          if (decay0.is_debug()) {
            std::cerr << "[debug] cosPsi=" << cosPsi << "\n";
          }
          gsl_histogram_increment(h1, cosPsi);
        }
        const auto & betaParticle = decay.get_particles()[0];
        double cosPsibeta = betaParticle.get_px() / betaParticle.get_p();
        gsl_histogram_increment(h2, cosPsibeta);
      } else {
        for (const auto & part : decay.get_particles()) {
          double cosPsi = part.get_px() / part.get_p();
          if (part.get_code() == bxdecay0::GAMMA) {
            gsl_histogram_increment(h1, cosPsi);            
          } else if (part.get_code() == bxdecay0::ELECTRON) {
            gsl_histogram_increment(h2, cosPsi);            
          } 
        }
      }
    }

    if (requestedRank >= 0) { 
      FILE * h1Out = fopen("h1.his", "w");
      gsl_histogram_fprintf(h1Out, h1, "%g", "%g");
      fclose(h1Out);
      gsl_histogram_free(h1);
      FILE * h2Out = fopen("h2.his", "w");
      gsl_histogram_fprintf(h2Out, h2, "%g", "%g");
      fclose(h2Out);
      gsl_histogram_free(h2);
    } else {
      FILE * h1Out = fopen("h1bis.his", "w");
      gsl_histogram_fprintf(h1Out, h1, "%g", "%g");
      fclose(h1Out);
      gsl_histogram_free(h1);
      FILE * h2Out = fopen("h2bis.his", "w");
      gsl_histogram_fprintf(h2Out, h2, "%g", "%g");
      fclose(h2Out);
      gsl_histogram_free(h2);
    }
    
    decay0.reset();
  }
  return;
}

void test_cs137_mdlr()
{
  std::clog << "\ntest_cs137_mdlr:\n";

  const auto & background_isotopes = bxdecay0::background_isotopes();
  std::string name("Cs137");
  {
    std::clog << "Decay from isotope: '" << name << "'" << std::endl;
    unsigned int seed = 314159;
    std::default_random_engine generator(seed);
    bxdecay0::std_random prng(generator);

    bxdecay0::decay0_generator decay0;
    decay0.set_debug(true);
    decay0.set_decay_category(bxdecay0::decay0_generator::DECAY_CATEGORY_BACKGROUND);
    decay0.set_decay_isotope(name);

    // Install a MDL post-generation operation: force X direction for the first rank emitted gamma
    // and rotate the full event in these conditions
    bxdecay0::event_op_ptr mdlPtr(new bxdecay0::momentum_direction_lock_event_op(decay0.is_debug()));
    bxdecay0::momentum_direction_lock_event_op & mdl = dynamic_cast<bxdecay0::momentum_direction_lock_event_op&>(*mdlPtr);
    bxdecay0::particle_code requestedCode = bxdecay0::GAMMA;
    int requestedRank = 0;
    requestedCode = bxdecay0::INVALID_PARTICLE;
    // requestedRank = -1;
    // requestedCode = bxdecay0::ELECTRON;
    // requestedRank = -1;
    // Rectangular cut on conical aperture:
    mdl.set_with_aperture_rectangular_cut(requestedCode, // Select only gammas
                                          requestedRank, // Rank of the target gamma in the event (0 : first, 1: second, 2: third...)
                                          1.0,
                                          0.0,
                                          0.0,           // Emission cone is aligned on the X-axis
                                          M_PI / 4,      //   with first angle of aperture of 45 degrees
                                          M_PI / 10,     //   and second angle of aperture of 18 degrees
                                          false);        // Do not generate an error if no target particle is found. Just no-op and pass.
    decay0.add_operation(mdlPtr); // Install the MDL post-generation operation in the generator 
    decay0.initialize(prng);      // Initialize and lock the generator
    decay0.smart_dump(std::clog, "Decay0 background generator: ", "[info] ");

    double cosMin = -1.0;
    double cosMax = +1.0;
    size_t nBins = 220;    
    gsl_histogram * h1 = gsl_histogram_alloc(nBins);
    gsl_histogram_set_ranges_uniform(h1, cosMin * 1.1, cosMax * 1.1);
    gsl_histogram * h2 = gsl_histogram_alloc(nBins);
    gsl_histogram_set_ranges_uniform(h2, cosMin * 1.1, cosMax * 1.1);
    
    bxdecay0::event decay;
    std::size_t nevents = 10000;
    for (std::size_t ievent = 0; ievent < nevents; ievent++) {
      decay0.shoot(prng, decay);
      decay.set_time(0.0);
      decay.print(std::clog, name + " decay event:", "[info] ");
      decay.store(std::cout);
      int targetParticleIndex = mdl.get_last_target_index();
      if (requestedRank >= 0) {
        if (targetParticleIndex >= 0) {
          const auto & targetParticle = decay.get_particles()[targetParticleIndex];
          double cosPsi = targetParticle.get_px() / targetParticle.get_p();
          if (decay0.is_debug()) {
            std::cerr << "[debug] cosPsi=" << cosPsi << "\n";
          }
          gsl_histogram_increment(h1, cosPsi);
        }
        const auto & betaParticle = decay.get_particles()[0];
        double cosPsibeta = betaParticle.get_px() / betaParticle.get_p();
        gsl_histogram_increment(h2, cosPsibeta);
      } else {
        for (const auto & part : decay.get_particles()) {
          double cosPsi = part.get_px() / part.get_p();
          if (part.get_code() == bxdecay0::GAMMA) {
            gsl_histogram_increment(h1, cosPsi);            
          } else if (part.get_code() == bxdecay0::ELECTRON) {
            gsl_histogram_increment(h2, cosPsi);            
          } 
        }
      }
    }

    if (requestedRank >= 0) { 
      FILE * h1Out = fopen("h1r.his", "w");
      gsl_histogram_fprintf(h1Out, h1, "%g", "%g");
      fclose(h1Out);
      gsl_histogram_free(h1);
      FILE * h2Out = fopen("h2r.his", "w");
      gsl_histogram_fprintf(h2Out, h2, "%g", "%g");
      fclose(h2Out);
      gsl_histogram_free(h2);
    } else {
      FILE * h1Out = fopen("h1rbis.his", "w");
      gsl_histogram_fprintf(h1Out, h1, "%g", "%g");
      fclose(h1Out);
      gsl_histogram_free(h1);
      FILE * h2Out = fopen("h2rbis.his", "w");
      gsl_histogram_fprintf(h2Out, h2, "%g", "%g");
      fclose(h2Out);
      gsl_histogram_free(h2);
    }
    
    decay0.reset();
  }
  return;
}

void test20()
{
  std::clog << "\ntest20:\n";
  unsigned int seed = 314159;
  std::default_random_engine generator(seed);
  bxdecay0::std_random prng(generator);

  bxdecay0::decay0_generator decay0;
  decay0.set_debug(true);
  decay0.set_decay_category(bxdecay0::decay0_generator::DECAY_CATEGORY_DBD);
  decay0.set_decay_isotope("Nd150");
  // decay0.set_decay_isotope("Mo100"); // Fails as expected
  decay0.set_decay_dbd_level(0);
  // decay0.set_decay_dbd_level(1); // Fails as expected
  decay0.set_decay_dbd_mode(bxdecay0::DBDMODE_20); 
  decay0.initialize(prng);
  decay0.smart_dump(std::clog, "Decay0 DBD generator: ", "[info] ");

  bxdecay0::event decay;
  std::size_t nevents = 1;
  for (std::size_t ievent = 0; ievent < nevents; ievent++) {
    decay0.shoot(prng, decay);
    decay.set_time(0.0);
    decay.print(std::clog, "DBD event:", "[info] ");
    decay.store(std::cout);
  }

  decay0.reset();
  return;
}

void test_Gd160_dbd()
{
  std::clog << "\ntest_Gd160_dbd:\n";
  unsigned int seed = 314159;
  std::default_random_engine generator(seed);
  bxdecay0::std_random prng(generator);

  bxdecay0::decay0_generator decay0;
  decay0.set_debug(true);
  decay0.set_decay_category(bxdecay0::decay0_generator::DECAY_CATEGORY_DBD);
  decay0.set_decay_isotope("Gd160");
  decay0.set_decay_dbd_mode(bxdecay0::DBDMODE_4);
  decay0.set_decay_dbd_level(0);
  decay0.initialize(prng);
  decay0.smart_dump(std::clog, "DBD generator: ", "[info] ");
  std::ofstream fout("Gd160_dbd.data");
  bxdecay0::event decay;
  std::size_t nevents = 100;
  for (std::size_t ievent = 0; ievent < nevents; ievent++) {
    decay0.shoot(prng, decay);
    decay.set_time(0.0);
    if (ievent < 3) {
      decay.print(std::clog, "DBD event:", "[info] ");
      decay.store(std::cout);
    }
    const auto & particles = decay.get_particles();
    auto el1 = particles[0];
    auto el2 = particles[1];
    auto p1 = el1.get_p();
    auto p2 = el2.get_p();
    const auto me = bxdecay0::electron_mass_MeV();
    auto K1 = std::sqrt(me * me + p1 * p1) - me;
    auto K2 = std::sqrt(me * me + p2 * p2) - me;
    fout << K1 << ' ' << K1 << ' ' << (K1+K2) << '\n';
  }
  fout.close();
  decay0.reset();
  return;
}
