// Ourselves:
#include <bxdecay0/Am241.h>

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

  // Am241.f
  // This file was extracted from the 'decay0' program by V.I. Tretyak
  // Copyright 1995-2011 V.I. Tretyak
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

  void Am241(i_random & prng_,
             event & event_,
	     const double tcnuc_,
	     double & tdnuc_)
  {
    double t;
    double tdlev;
    double p;
    double palpha;
    double tclev;
    double thlev;
    double thnuc;
    // Model for scheme of Am241 decay (NDS 107(2006)3323 and ENSDF at NNDC site
    // on 15.01.2011). Decays to excited levels of 237-Np with probabilities <0.01%
    // are neglected.
    // Input : tcnuc - time of creation of nucleus (sec)
    // Output: tdnuc - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 23.01.2011.
    thnuc=1.365144e10;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    palpha=100.*prng_();
    //palpha=99.5; //XXX
    if (palpha <=  0.015) goto label_226;
    if (palpha <=  1.672) goto label_159;
    if (palpha <=  1.682) goto label_130;
    if (palpha <= 14.758) goto label_103;
    if (palpha <= 99.406) goto label_60;
    if (palpha <= 99.631) goto label_33;
    goto label_10000;
  label_226  :
    decay0_alpha(prng_, event_, 5.322,0.,0.,t);
    //// label_22600  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  0.43) goto label_22601;
    if (p <= 34.21) goto label_22602;
    goto label_22603;
  label_22601  :
    decay0_nucltransKLM(prng_, event_, 0.150,0.119,1.5e-1,0.022,3.4e-2,0.005,8.4e-3,
                        0.,tclev,thlev,tdlev);
    goto label_76000;
  label_22602  :
    decay0_nucltransKLM(prng_, event_, 0.123,0.119,1.9e-1,0.022,4.13,0.005,1.59,
                        0.,tclev,thlev,tdlev);
    goto label_10300;
  label_22603  :
    decay0_nucltransKLM(prng_, event_, 0.067,0.119,0.,0.022,23.,0.005,8.1,
                        0.,tclev,thlev,tdlev);
    goto label_15900;
  label_159  :
    decay0_alpha(prng_, event_, 5.388,0.,0.,t);
  label_15900  :
    thlev=0.;
    p=100.*prng_();
    if (p <=  0.34) goto label_15901;
    if (p <= 21.79) goto label_15902;
    goto label_15903;
  label_15901  :
    decay0_nucltransKLM(prng_, event_, 0.125,0.119,2.3e-1,0.022,5.5e-2,0.005,1.7e-2,
                        0.,tclev,thlev,tdlev);
    goto label_33000;
  label_15902  :
    decay0_nucltransKLM(prng_, event_, 0.099,0.119,0.,0.022,11.3,0.005,4.33,
                        0.,tclev,thlev,tdlev);
    goto label_60000;
  label_15903  :
    decay0_nucltransKLM(prng_, event_, 0.056,0.119,0.,0.022,49.,0.005,18.,
                        0.,tclev,thlev,tdlev);
    goto label_10300;
  label_130  :
    decay0_alpha(prng_, event_, 5.416,0.,0.,t);
    //// REMOVE WARNING: label_13000  :
    thlev=0.;
    decay0_nucltransKLM(prng_, event_, 0.054,0.119,0.,0.022,23.2,0.005,7.7,
                        0.,tclev,thlev,tdlev);
    goto label_76000;
  label_103  :
    decay0_alpha(prng_, event_, 5.443,0.,0.,t);
  label_10300  :
    thlev=80.e-12;
    p=100.*prng_();
    if (p <=  0.18) goto label_10301;
    if (p <=  0.21) goto label_10302;
    goto label_10303;
  label_10301  :
    decay0_nucltransKLM(prng_, event_, 0.103,0.119,0.,0.022,9.1e-2,0.005,3.0e-2,
                        0.,tclev,thlev,tdlev);
    return;
  label_10302  :
    decay0_nucltransKLM(prng_, event_, 0.070,0.119,0.,0.022,2.5e-1,0.005,8.4e-2,
                        0.,tclev,thlev,tdlev);
    goto label_33000;
  label_10303  :
    decay0_nucltransKLM(prng_, event_, 0.043,0.119,0.,0.022,124.,0.005,43.,
                        0.,tclev,thlev,tdlev);
    goto label_60000;
  label_76000  :
    thlev=56.e-12;
    p=100.*prng_();
    if (p <=  7.02) goto label_76001;
    goto label_76002;
  label_76001  :
    decay0_nucltransKLM(prng_, event_, 0.076,0.119,0.,0.022,39.4,0.005,15.0,
                        0.,tclev,thlev,tdlev);
    return;
  label_76002  :
    decay0_nucltransKLM(prng_, event_, 0.043,0.119,0.,0.022,59.,0.005,21.,
                        0.,tclev,thlev,tdlev);
    goto label_33000;
  label_60  :
    decay0_alpha(prng_, event_, 5.486,0.,0.,t);
  label_60000  :
    thlev=67.e-9;
    p=100.*prng_();
    if (p <= 78.20) goto label_60001;
    goto label_60002;
  label_60001  :
    decay0_nucltransKLM(prng_, event_, 0.060,0.119,0.,0.022,0.84,0.005,0.32,
                        0.,tclev,thlev,tdlev);
    return;
  label_60002  :
    decay0_nucltransKLM(prng_, event_, 0.026,0.119,0.,0.022,6.,0.005,2.,
                        0.,tclev,thlev,tdlev);
    goto label_33000;
  label_33  :
    decay0_alpha(prng_, event_, 5.512,0.,0.,t);
  label_33000  :
    thlev=54.e-12;
    decay0_nucltransKLM(prng_, event_, 0.033,0.119,0.,0.022,138.,0.005,47.,
			0.,tclev,thlev,tdlev);
    return;
  label_10000  :
    decay0_alpha(prng_, event_, 5.544,0.,0.,t);
    return;
  }
  // end of Am241.f




} // end of namespace bxdecay0

// end of Am241.cc
// Local Variables: --
// mode: c++ --
// End: --
