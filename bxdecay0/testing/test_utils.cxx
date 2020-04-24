/** test_utils.cxx
 *
 * Copyright 2020 François Mauger <mauger@lpccaen.in2p3.fr>
 * Copyright 2020 Normandie Université
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
#include <cmath>

// This project:
#include <bxdecay0/utils.h>

int main()
{
  int error_code = EXIT_SUCCESS;
  try {

    bxdecay0::vector3 ux = bxdecay0::make_vector3(1.0, 0.0, 0.0);
    bxdecay0::vector3 uy = bxdecay0::make_vector3(0.0, 1.0, 0.0);
    bxdecay0::vector3 uz = bxdecay0::make_vector3(0.0, 0.0, 1.0);
    bxdecay0::vector3 v = bxdecay0::make_vector3(0.5, 0.0, 0.5);

    std::clog << "ux = ";
    bxdecay0::print(ux, std::cout);
    std::cout << '\n';

    std::clog << "uy = ";
    bxdecay0::print(uy, std::cout);
    std::cout << '\n';

    std::clog << "uz = ";
    bxdecay0::print(uz, std::cout);
    std::cout << '\n';

    std::clog << "v = ";
    bxdecay0::print(v, std::cout);
    std::cout << '\n';

    std::cout << '\n';
    std::cout << '\n';
    double phi = M_PI/3;
    bxdecay0::vector3 ux2 = bxdecay0::rotate_zyz(ux, phi);
    bxdecay0::vector3 uy2 = bxdecay0::rotate_zyz(uy, phi);
    bxdecay0::vector3 uz2 = bxdecay0::rotate_zyz(uz, phi);
    bxdecay0::vector3 v2 = bxdecay0::rotate_zyz(v, phi);

    std::clog << "ux2 = ";
    bxdecay0::print(ux2, std::cout);
    std::cout << '\n';
    
    std::clog << "uy2 = ";
    bxdecay0::print(uy2, std::cout);
    std::cout << '\n';
    
    std::clog << "uz2 = ";
    bxdecay0::print(uz2, std::cout);
    std::cout << '\n';
   
    std::clog << "v2 = ";
    bxdecay0::print(v2, std::cout);
    std::cout << '\n';
  
    std::cout << '\n';
    std::cout << '\n';
    double theta = M_PI/6;
    bxdecay0::vector3 ux3 = bxdecay0::rotate_zyz(ux, phi, theta);
    bxdecay0::vector3 uy3 = bxdecay0::rotate_zyz(uy, phi, theta);
    bxdecay0::vector3 uz3 = bxdecay0::rotate_zyz(uz, phi, theta);
    bxdecay0::vector3 v3  = bxdecay0::rotate_zyz(v, phi, theta);
 
    std::clog << "ux3 = ";
    bxdecay0::print(ux3, std::cout);
    std::cout << '\n';
    
    std::clog << "uy3 = ";
    bxdecay0::print(uy3, std::cout);
    std::cout << '\n';
    
    std::clog << "uz3 = ";
    bxdecay0::print(uz3, std::cout);
    std::cout << '\n';
      
    std::clog << "v3 = ";
    bxdecay0::print(v3, std::cout);
    std::cout << '\n';
 
    std::cout << '\n';
    std::cout << '\n';
    double psi = M_PI/4;
    bxdecay0::vector3 ux4 = bxdecay0::rotate_zyz(ux, phi, theta, psi);
    bxdecay0::vector3 uy4 = bxdecay0::rotate_zyz(uy, phi, theta, psi);
    bxdecay0::vector3 uz4 = bxdecay0::rotate_zyz(uz, phi, theta, psi);
    bxdecay0::vector3 v4  = bxdecay0::rotate_zyz(v, phi, theta, psi);
  
    std::clog << "ux4 = ";
    bxdecay0::print(ux4, std::cout);
    std::cout << '\n';
    
    std::clog << "uy4 = ";
    bxdecay0::print(uy4, std::cout);
    std::cout << '\n';
    
    std::clog << "uz4 = ";
    bxdecay0::print(uz4, std::cout);
    std::cout << '\n';
      
    std::clog << "v4 = ";
    bxdecay0::print(v4, std::cout);
    std::cout << '\n';

    
  } catch (std::exception & error) {
    std::cerr << "[error] " << error.what() << std::endl;
    error_code = EXIT_FAILURE;
  } catch (...) {
    std::cerr << "[error] " << "Unexpected exception!" << std::endl;
    error_code = EXIT_FAILURE;
  }
  return error_code;
}
