// Copyright 2017 François Mauger <mauger@lpccaen.in2p3.fr>
#include <iostream>
#include <bxdecay0/std_random.h>
#include <bxdecay0/event.h>
#include <bxdecay0/decay0_generator.h>

int main()
{
  unsigned int seed = 314159;
  std::default_random_engine generator(seed);
  bxdecay0::std_random prng(generator);

  bxdecay0::decay0_generator decay0;
  decay0.set_decay_category(bxdecay0::decay0_generator::DECAY_CATEGORY_DBD);
  decay0.set_decay_isotope("Mo100");
  decay0.set_decay_dbd_level(0);
  decay0.set_decay_dbd_mode(bxdecay0::DBDMODE_1);
  decay0.initialize(prng);

  std::size_t nevents = 10;
  for (std::size_t ievent = 0; ievent < nevents; ievent++) {
    bxdecay0::event gendecay;
    decay0.shoot(prng, gendecay);
    gendecay.store(std::cout);
  }

  decay0.reset();
  return 0;
}
