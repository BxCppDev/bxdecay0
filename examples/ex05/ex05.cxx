// Copyright 2020 François Mauger <mauger@lpccaen.in2p3.fr>

// Standard library:
#include <fstream>
#include <iostream>

// This project:
#include <bxdecay0/dbd_gA.h>
#include <bxdecay0/event.h>
#include <bxdecay0/std_random.h>

int main()
{
  unsigned int seed = 314159;
  std::default_random_engine generator(seed);
  bxdecay0::std_random prng(generator);

  bxdecay0::dbd_gA gA_generator;
  gA_generator.set_debug(true);
  gA_generator.set_nuclide("Se82");
  gA_generator.set_process(bxdecay0::dbd_gA::PROCESS_G0);
  gA_generator.set_shooting(bxdecay0::dbd_gA::SHOOTING_INVERSE_TRANSFORM_METHOD);
  gA_generator.initialize();
  gA_generator.print(std::clog, "gA DBD generator", "[info] ");

  {
    std::ofstream fout("bxdecay0_ex05.data");
    unsigned int nshoots = 10000000;
    for (int i = 0; i < nshoots; i++) {
      if ((i % 10000) == 0)
        std::clog << "[log] #" << i << "/" << nshoots << std::endl;
      double e1;
      double e2;
      double cos12;
      gA_generator.shoot_e1_e2(prng, e1, e2);
      gA_generator.shoot_cos_theta(prng, e1, e2, cos12);
      double esum = e1 + e2;
      fout << e1 << ' ' << e2 << ' ' << esum << ' ' << (cos12 + 1.0) << std::endl;
      bxdecay0::event decay;
      bxdecay0::dbd_gA::export_to_event(prng, e1, e2, cos12, decay);
      // decay.print(std::cerr, "DBD-gA event:", "[debug] ");
    }
    fout.close();
  }

  gA_generator.reset();
  return 0;
}
