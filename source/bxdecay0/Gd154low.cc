// Copyright 1995-2016 V.I. Tretyak
// Copyright 2011-2020 F. Mauger
//
// This program is free software: you  can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free  Software Foundation, either  version 3 of the  License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

// Ourselves:
#include <bxdecay0/Gd154low.h>

// Standard library:
#include <sstream>
#include <stdexcept>
#include <cmath>

// This project:
#include <bxdecay0/i_random.h>
#include <bxdecay0/event.h>
#include <bxdecay0/alpha.h>
#include <bxdecay0/gamma.h>
#include <bxdecay0/electron.h>
#include <bxdecay0/positron.h>
#include <bxdecay0/particle.h>
#include <bxdecay0/pair.h>
#include <bxdecay0/nucltransK.h>
#include <bxdecay0/nucltransKL.h>
#include <bxdecay0/nucltransKLM.h>
#include <bxdecay0/nucltransKLM_Pb.h>
#include <bxdecay0/beta.h>
#include <bxdecay0/beta1.h>
#include <bxdecay0/beta2.h>
#include <bxdecay0/beta_1fu.h>
#include <bxdecay0/PbAtShell.h>

namespace bxdecay0 {

  void Gd154low(i_random & prng_,
                event & event_,
                const int levelkev_)
  {    
    // Subroutine describes the deexcitation process in Gd154 nucleus
    // after 2b- decay of Sm154 to the ground and excited 0+ and 2+ levels
    // of Gd154 (NNDC on 30.11.2018  and NDS 110(2008)2257).
    // Call  : call Gd154low(levelkeV)
    // Input : levelkeV - energy of Gd154 level (integer in keV) occupied
    //               initially; following levels can be occupied:
    //                    0+(gs) -    0 keV,
    //                    2+(1)  -  123 keV,
    //                    0+(1)  -  681 keV,
    //                    2+(2)  -  815 keV,
    //                    2+(3)  -  996 keV,
    //                    0+(2)  - 1182 keV.
    // Output: common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),ptime(100).
    // VIT, 3.12.2018.
    double tdlev;
    double p;
    double tclev;
    double thlev;
    tclev=0.;
    if(levelkev_ == 1182) goto label_1182;
    if(levelkev_ ==  996) goto label_996;
    if(levelkev_ ==  815) goto label_815;
    if(levelkev_ ==  681) goto label_681;
    if(levelkev_ ==  123) goto label_123;
    if(levelkev_ ==    0) goto label_10000;
    goto label_20000;
  label_1182:
    thlev=0.;
    p=100.*prng_();
    if(p <= 17.18) goto label_11821;
    if(p <= 18.00) goto label_11822;
    if(p <= 99.80) goto label_11823;
    goto label_11824;
  label_11821:
    decay0_nucltransK(prng_, event_, 0.367,0.050,3.3e-2,0.,tclev,thlev,tdlev);
    goto label_815;
  label_11822:
    decay0_electron(prng_, event_, 0.501-0.050,tclev,thlev,tdlev); // only ce in 0+ -> 0+
    decay0_gamma(prng_, event_, 0.050,0.,0.,tdlev);
    goto label_681;
  label_11823:
    decay0_nucltransK(prng_, event_, 1.059,0.050,2.4e-3,0.,tclev,thlev,tdlev);
    goto label_123;
  label_11824:
    decay0_electron(prng_, event_, 1.182-0.050,tclev,thlev,tdlev); // only ce in 0+ -> 0+
    decay0_gamma(prng_, event_, 0.050,0.,0.,tdlev);
    return;
  label_996:
    thlev=0.95e-12;
    p=100.*prng_();
    if(p <=  0.031) goto label_9961;
    if(p <=  0.072) goto label_9962;
    if(p <=  1.449) goto label_9963;
    if(p <= 54.207) goto label_9964;
    goto label_9965;
  label_9961:
    decay0_nucltransK(prng_, event_, 0.181,0.050,3.5e-1,0.,tclev,thlev,tdlev);
    goto label_815;
  label_9962:
    decay0_nucltransK(prng_, event_, 0.316,0.050,5.2e-2,0.,tclev,thlev,tdlev);
    goto label_681;
  label_9963:
    decay0_nucltransK(prng_, event_, 0.625,0.050,7.9e-3,0.,tclev,thlev,tdlev);
    goto label_371;
  label_9964:
    decay0_nucltransK(prng_, event_, 0.873,0.050,3.7e-3,0.,tclev,thlev,tdlev);
    goto label_123;
  label_9965:
    decay0_nucltransK(prng_, event_, 0.996,0.050,2.8e-3,0.,tclev,thlev,tdlev);
    return;
  label_815:
    thlev=6.4e-12;
    p=100.*prng_();
    if(p <=  0.50) goto label_8151;
    if(p <= 19.43) goto label_8152;
    if(p <= 82.57) goto label_8153;
    goto label_8154;
  label_8151:
    decay0_nucltransK(prng_, event_, 0.135,0.050,8.6e-1,0.,tclev,thlev,tdlev);
    goto label_681;
  label_8152:
    decay0_nucltransK(prng_, event_, 0.444,0.050,1.9e-2,0.,tclev,thlev,tdlev);
    goto label_371;
  label_8153:
    decay0_nucltransK(prng_, event_, 0.692,0.050,4.6e-2,0.,tclev,thlev,tdlev);
    goto label_123;
  label_8154:
    decay0_nucltransK(prng_, event_, 0.815,0.050,4.3e-3,0.,tclev,thlev,tdlev);
    return;
  label_681:
    thlev=4.56e-12;
    p=100.*prng_();
    if(p <= 97.94) goto label_6811;
    goto label_6812;
  label_6811:
    decay0_nucltransK(prng_, event_, 0.558,0.050,1.1e-2,0.,tclev,thlev,tdlev);
    goto label_123;
  label_6812:
    decay0_electron(prng_, event_, 0.681-0.050,tclev,thlev,tdlev); // only ce in 0+ -> 0+
    decay0_gamma(prng_, event_, 0.050,0.,0.,tdlev);
    return;
  label_371:
    thlev=45.6e-12;
    decay0_nucltransK(prng_, event_, 0.248,0.050,1.1e-1,0.,tclev,thlev,tdlev);
    goto label_123;
  label_123:
    thlev=1.184e-9;
    decay0_nucltransK(prng_, event_, 0.123,0.050,1.197,0.,tclev,thlev,tdlev);
    return;
  label_10000:
    return;
  label_20000:
    //print *,'Gd154: wrong level [keV] ',levelkev
    return;
  }

} // end of namespace bxdecay0

// end of Gd154low.cc
// Local Variables: --
// mode: c++ --
// End: --
