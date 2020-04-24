/** test_dbd_gA.cxx
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
#include <iostream>
#include <exception>
#include <cstdlib>
#include <fstream>

// This project:
#include <bxdecay0/dbd_gA.h>
#include <bxdecay0/std_random.h>

void test1();
void test2();

int main()
{
  int error_code = EXIT_SUCCESS;
  try {
    
    // test1();
    test2();

  } catch (std::exception & error) {
    std::cerr << "[error] " << error.what() << std::endl;
    error_code = EXIT_FAILURE;
  } catch (...) {
    std::cerr << "[error] " << "Unexpected exception!" << std::endl;
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
  
  bxdecay0::dbd_gA gA_generator;
  gA_generator.set_nuclide("Test");
  gA_generator.set_nuclide("Se82");
  gA_generator.set_process(bxdecay0::dbd_gA::PROCESS_G0);
  gA_generator.set_shooting(bxdecay0::dbd_gA::SHOOTING_REJECTION);
  gA_generator.initialize();
  gA_generator.print(std::clog, "gA DBD generator", "[info] ");

  {
    std::ofstream fout1("test_dbd_gA_1.data");
    gA_generator.plot_interpolated_pdf(fout1, 40);
    fout1 << std::endl;
  }
  
  {
    std::ofstream fout2("test_dbd_gA_2.data");
    std::ofstream fout3("test_dbd_gA_3.data");
    std::ofstream fout4("test_dbd_gA_4.data");
    int N = 10000;
    for (int i = 0; i < N; i++) {
      if (i % 1000 == 0) std::cerr << "[log] i = " << i << '\n';
      double e1;
      double e2;
      gA_generator.shoot_e1_e2(prng, e1, e2);
      fout2 << e1 << ' ' << e2 << std::endl;
      double esum = e1 + e2;
      fout3 << esum << std::endl;
      double cos12;
      gA_generator.shoot_cos_theta(prng, e1, e2, cos12);
      fout4 << cos12 << std::endl;
    }
  }
  
  gA_generator.reset();
  return;
}

void test2()
{
  std::clog << "\ntest2:\n";
  unsigned int seed = 314159;
  std::default_random_engine generator(seed);
  bxdecay0::std_random prng(generator);
  bool debug = true;
  bxdecay0::dbd_gA gA_generator;
  gA_generator.set_debug(debug);
  gA_generator.set_nuclide("Se82");
  gA_generator.set_process(bxdecay0::dbd_gA::PROCESS_G0);
  gA_generator.set_shooting(bxdecay0::dbd_gA::SHOOTING_INVERSE_TRANSFORM_METHOD);
  gA_generator.initialize();
  gA_generator.print(std::clog, "gA DBD generator", "[info] ");
  
  {
    std::ofstream fout2("test2_dbd_gA_2.data");
    std::ofstream fout3("test2_dbd_gA_3.data");
    std::ofstream fout4("test2_dbd_gA_4.data");
    int N = 10000;
    for (int i = 0; i < N; i++) {
      if (i % 1000 == 0) std::cerr << "[log] i = " << i << '\n';
      double e1;
      double e2;
      gA_generator.shoot_e1_e2(prng, e1, e2);
      fout2 << e1 << ' ' << e2 << std::endl;
      double esum = e1 + e2;
      fout3 << esum << std::endl;
      double cos12;
      gA_generator.shoot_cos_theta(prng, e1, e2, cos12);
      fout4 << cos12 << std::endl;
    }
  }
  
  gA_generator.reset();
  return;
}
