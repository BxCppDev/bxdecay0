// Copyright 1995-2016 V.I. Tretyak
// Copyright 2011-2017 F. Mauger
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
#include <bxdecay0/Bi208.h>

// Standard library:
#include <cmath>
#include <sstream>
#include <stdexcept>

// This project:
#include <bxdecay0/PbAtShell.h>
#include <bxdecay0/alpha.h>
#include <bxdecay0/beta.h>
#include <bxdecay0/beta1.h>
#include <bxdecay0/beta2.h>
#include <bxdecay0/beta_1fu.h>
#include <bxdecay0/electron.h>
#include <bxdecay0/event.h>
#include <bxdecay0/gamma.h>
#include <bxdecay0/i_random.h>
#include <bxdecay0/nucltransK.h>
#include <bxdecay0/nucltransKL.h>
#include <bxdecay0/nucltransKLM.h>
#include <bxdecay0/nucltransKLM_Pb.h>
#include <bxdecay0/pair.h>
#include <bxdecay0/particle.h>
#include <bxdecay0/positron.h>

namespace bxdecay0 {

  void Bi208(i_random & prng_, event & event_, const double tcnuc_, double & tdnuc_)
  {
    double t;
    double tdlev;
    double pdecay;
    double tclev;
    double thlev;
    double thnuc;
    double Egamma; // Manually added
    // Scheme of Bi208 decay (NDS 47(1986)797 + ToI-1978).
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 17.12.1995
    thnuc  = 1.161288E+13;
    tdnuc_ = tcnuc_ - thnuc / std::log(2.) * std::log(prng_());
    tclev  = 0.;
    pdecay = 100. * prng_();
    if (pdecay <= 43.6)
      Egamma = 0.088; // EC-K 43.6%
    if (pdecay > 43.6 && pdecay <= 83.8)
      Egamma = 0.016; // EC-L 40.2%
    if (pdecay > 83.8)
      Egamma = 0.004; // EC-M 16.2%
    decay0_gamma(prng_, event_, Egamma, 0., 0., t);
    //// label_2615  :
    thlev = 32.e-12;
    decay0_nucltransK(prng_, event_, 2.615, 0.088, 8.5e-3, 4.3e-4, tclev, thlev, tdlev);
    return;
  }
  // end of Bi208.f

} // end of namespace bxdecay0

// end of Bi208.cc
// Local Variables: --
// mode: c++ --
// End: --
