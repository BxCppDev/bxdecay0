// Ourselves:
#include <bxdecay0/Ra226.h>

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

  // Ra226.cc
  // Copyright 2013, F. Mauger
  //
  // This program is free software
  // it under the terms of the GNU General Public License as published by
  // the Free Software Foundation
  // your option) any later version.
  //
  // This program is distributed in the hope that it will be useful, but
  // WITHOUT ANY WARRANTY
  // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  // General Public License for more details.
  //
  // You should have received a copy of the GNU General Public License
  // along with this program
  // Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
  //


  void Ra226(i_random & prng_,
             event & event_,
             const double tcnuc_,
             double & tdnuc_)
  {
    bool debug = false;
    double t;
    double tdlev;
    double p;
    double palpha;
    double tclev;
    double thlev;
    double thnuc;
    double RnElectronBindingEnergyK=0.098; // MeV
    double RnElectronBindingEnergyL=0.017; // MeV
    double RnElectronBindingEnergyM=0.004; // MeV
    // Models for scheme of Ra226 decay:
    //  - http://www.nucleide.org/DDEP_WG/Nuclides/Ra-226_tables.pdf
    //  - http://www.nucleide.org/DDEP_WG/Nuclides/Ra-226_com.pdf
    //  - ENSDF at NNDC site on 11.07.2013
    //  - http://xdb.lbl.gov/Section1/Table_1-1c.htm
    // Input : prng  - PRNG
    //         event - primary event model
    //         tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    thnuc=5.03e10; // 1600 y
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    t=0.0;
    if (debug) std::cerr << "genbb::decay0::Ra226: " << "t=" << t << " sec" << std::endl;

    palpha=100.*prng_();
    if (palpha <= 0.0002)  {
      // Alpha 4160 keV:
      decay0_alpha(prng_, event_, 4.160,0.,0.,t);
      if (debug) std::cerr << "genbb::decay0::Ra226: " << "alpha 4160" << std::endl;
      if (debug) std::cerr << "genbb::decay0::Ra226: " << "   with t=" << t << " sec" << std::endl;
      goto level_635000;
    } else if (palpha <= 0.0010) {
      // Alpha 4191 keV:
      decay0_alpha(prng_, event_, 4.191,0.,0.,t);
      if (debug) std::cerr << "genbb::decay0::Ra226: " << "alpha 4191" << std::endl;
      if (debug) std::cerr << "genbb::decay0::Ra226: " << "   with t=" << t << " sec" << std::endl;
      goto level_600000;
    } else if (palpha <= 0.0076) {
      // Alpha 4340 keV:
      decay0_alpha(prng_, event_, 4.340,0.,0.,t);
      if (debug) std::cerr << "genbb::decay0::Ra226: " << "alpha 4340" << std::endl;
      if (debug) std::cerr << "genbb::decay0::Ra226: " << "   with t=" << t << " sec" << std::endl;
      goto level_448000;
    } else if (palpha <= 5.9576) {
      // Alpha 4601 keV:
      decay0_alpha(prng_, event_, 4.601,0.,0.,t);
      if (debug) std::cerr << "genbb::decay0::Ra226: " << "alpha 4601" << std::endl;
      if (debug) std::cerr << "genbb::decay0::Ra226: " << "   with t=" << t << " sec" << std::endl;
      goto level_186000;
    } else {
      // Alpha 4784 keV:
      if (debug) std::cerr << "genbb::decay0::Ra226: " << "alpha 4784" << std::endl;
      decay0_alpha(prng_, event_, 4.78434,0.,0.,t);
      if (debug) std::cerr << "genbb::decay0::Ra226: " << "   with t=" << t << " sec" << std::endl;
      goto level_000000;
    }

  level_635000  :
    // Level 635.5 keV:
    if (debug) std::cerr << "genbb::decay0::Ra226: " << "level 635.5" << std::endl;
    thlev=0.;
    decay0_nucltransKLM(prng_, event_, 0.44937,
                        RnElectronBindingEnergyK, 0.01123,
                        RnElectronBindingEnergyL, 0.00191,
                        RnElectronBindingEnergyM, 0.000449,
                        0.,tclev,thlev,tdlev);
    goto level_186000;

  level_600000  :
    // Level 600.7 keV:
    if (debug) std::cerr << "genbb::decay0::Ra226: " << "level 600.7" << std::endl;
    thlev=0.;
    p=100.*prng_();
    if (p <= 62.5) {
      decay0_nucltransKLM(prng_, event_, 0.60066,
                          RnElectronBindingEnergyK, 0.00627,
                          RnElectronBindingEnergyL, 0.00103,
                          RnElectronBindingEnergyM, 0.000243,
                          0.,tclev,thlev,tdlev);
      goto level_000000;
    } else {
      decay0_nucltransKLM(prng_, event_, 0.4146,
                          RnElectronBindingEnergyK, 0.01329,
                          RnElectronBindingEnergyL, 0.00228,
                          RnElectronBindingEnergyM, 0.000537,
                          0.,tclev,thlev,tdlev);
      goto level_186000;
    }

  level_448000  :
    // Level 448.4 keV:
    if (debug) std::cerr << "genbb::decay0::Ra226: " << "level 448.4" << std::endl;
    thlev=0.;
    decay0_nucltransKLM(prng_, event_, 0.26227,
                        RnElectronBindingEnergyK, 0.0923,
                        RnElectronBindingEnergyL, 0.0868,
                        RnElectronBindingEnergyM, 0.0230,
                        0.,tclev,thlev,tdlev);
    goto level_186000;

  level_186000  :
    // Level 186.2 keV:
    if (debug) std::cerr << "genbb::decay0::Ra226: " << "level 186.2" << std::endl;
    thlev=0.32e-9;
    decay0_nucltransKLM(prng_, event_, 0.186211,
                        RnElectronBindingEnergyK, 0.190,
                        RnElectronBindingEnergyL, 0.360,
                        RnElectronBindingEnergyM, 0.0963,
                        0.,tclev,thlev,tdlev);
    if (debug) std::cerr << "genbb::decay0::Ra226: " << "   with tdlev=" << tdlev << " sec" << std::endl;
    goto level_000000;

  level_000000 :
    return;
  }

} // end of namespace bxdecay0

// end of Ra226.cc
// Local Variables: --
// mode: c++ --
// End: --
