// Ourselves:
#include <bxdecay0/Bi207.h>

// Standard library:
#include <sstream>
#include <stdexcept>
#include <cmath>

// Third party:
#include <gsl/gsl_math.h>

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

  // Bi207.f
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

  void Bi207(i_random & prng_,
             event & event_,
             const double tcnuc_,
             double & tdnuc_)
  {
    static const double pi=M_PI;
    static const double twopi=2*pi;
    double t;
    double tdlev;
    double a2;
    double a4;
    double cg;
    double cK;
    double cL;
    double cM;
    double cp;
    double ctet;
    double ctet1;
    double ctet2;
    double EbindK;
    double EbindL;
    double EbindM;
    double Egamma;
    particle * ip1064 = nullptr;
    particle * ip570 = nullptr;
    particle * ipg1064 = nullptr;
    particle * ipg570 = nullptr;
    particle * ipe1064 = nullptr;
    particle * ipe570 = nullptr;
    double p;
    double p1064;
    double p2;
    double p4;
    double p570;
    double pdecay;
    double pec;
    double phi1;
    double phi2;
    double stet1;
    double stet2;
    double tclev;
    double thlev;
    double thnuc;
    // Scheme of Bi207+Pb207m decay (Nucl. Data Sheets 70(1993)315)
    // with NNDC corrections of 10.10.2000 and 20.04.2005.
    // To describe the deexcitation processes in atomic shell of Pb207,
    // the information of PC Nuclear Data File retrieval program and data
    // base (last updated on 16-Aug-1994) was used.
    // Gammas, beta+, e+e- pairs, K, L and M conversion electrons, K, L and M
    // X-rays and K and L Auger electrons are emitted.
    // Input : tcnuc_ - time of creation of nucleus (sec)
    // Output: tdnuc_ - time of decay of nucleus (sec)
    // // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),// ptime(100).
    // VIT, 7.07.1995, 22.10.1995, 11.09.2005, 3.10.2005.
    // common/genevent/tevst,npfull,npgeant(100),pmoment(3,100),
    // ptime(100)
    thnuc=1.0382166E+09;
    tdnuc_=tcnuc_-thnuc/std::log(2.)*std::log(prng_());
    tclev=0.;
    EbindK=0.088;
    EbindL=0.015;
    EbindM=0.003;
    cg=1.;
    pdecay=100.*prng_();
    if (pdecay <= 99.988) goto label_1;  // 99.988 EC
    goto label_2;  // 0.012 b+
    // EC to Pb207 or Pb207m
  label_1  :
    pec=pdecay;
    if (pec <=  7.027) goto label_2340;  // 7.027%
    if (pec <= 90.992) goto label_1633;  // 83.965%
    goto label_570;  // 8.996%
    // b+ to Pb207
  label_2  :
    decay0_beta(prng_, event_, 0.807,-82.,0.,0.,t);
    goto label_57000;
  label_2340  :
    if (prng_() <= 0.70) {
      PbAtShell(prng_, event_, 88,0.,0.,t);
    } else {
      PbAtShell(prng_, event_, 15,0.,0.,t);
    }
    ////    label_23400  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 98.13) goto label_23401;
    goto label_23402;
  label_23401  :
    Egamma=1.770;
    cK=3.51e-3;
    cL=0.49e-3;
    cM=0.13e-3;
    cp=2.5e-4;
    p=prng_()*(cg+cK+cL+cM+cp);
    if (p <= cg) {
      decay0_gamma(prng_, event_, Egamma,tclev,thlev,tdlev);
    }
    else if (p <= cg+cK) {
      decay0_electron(prng_, event_, Egamma-EbindK,tclev,thlev,tdlev);
      PbAtShell(prng_, event_, 88,0.,0.,tdlev);
    }
    else if (p <= cg+cK+cL) {
      decay0_electron(prng_, event_, Egamma-EbindL,tclev,thlev,tdlev);
      PbAtShell(prng_, event_, 15,0.,0.,tdlev);
    }
    else if (p <= cg+cK+cL+cM) {
      decay0_electron(prng_, event_, Egamma-EbindM,tclev,thlev,tdlev);
      PbAtShell(prng_, event_, 3,0.,0.,tdlev);
    } else {
      decay0_pair(prng_, event_, Egamma-1.022,tclev,thlev,tdlev);
    }
    goto label_57000;
  label_23402  :
    Egamma=1.442;
    cK=2.7e-3;
    cL=0.4e-3;
    cM=0.1e-3;
    cp=0.2e-4;
    p=prng_()*(cg+cK+cL+cM+cp);
    if (p <= cg) {
      decay0_gamma(prng_, event_, Egamma,tclev,thlev,tdlev);
    }
    else if (p <= cg+cK) {
      decay0_electron(prng_, event_, Egamma-EbindK,tclev,thlev,tdlev);
      PbAtShell(prng_, event_, 88,0.,0.,tdlev);
    }
    else if (p <= cg+cK+cL) {
      decay0_electron(prng_, event_, Egamma-EbindL,tclev,thlev,tdlev);
      PbAtShell(prng_, event_, 15,0.,0.,tdlev);
    }
    else if (p <= cg+cK+cL+cM) {
      decay0_electron(prng_, event_, Egamma-EbindM,tclev,thlev,tdlev);
      PbAtShell(prng_, event_, 3,0.,0.,tdlev);
    } else {
      decay0_pair(prng_, event_, Egamma-1.022,tclev,thlev,tdlev);
    }
    goto label_89800;
  label_1633  :
    p=prng_();
    if (p <= 0.733) {  // 73.3% EC from K shell
      PbAtShell(prng_, event_, 88,0.,0.,t);
    }
    else if (p <= 0.931) {  // 19.8% EC from L shell
      PbAtShell(prng_, event_, 15,0.,0.,t);
    }
    else { // 6.9% EC from M shell
      PbAtShell(prng_, event_, 3,0.,0.,t);
    }
    ////    label_16330  :
    thlev=0.80;
    Egamma=1.064;
    cK=9.42e-2;
    cL=2.47e-2;
    cM=0.73e-2;
    p=prng_()*(cg+cK+cL+cM);
    if (p <= cg) {
      decay0_gamma(prng_, event_, Egamma, tclev, thlev, tdlev);
      ipg1064 = &event_.grab_last_particle(); 
    }
    else if (p <= cg+cK) {
      decay0_electron(prng_, event_, Egamma-EbindK, tclev, thlev, tdlev);
      ipe1064 = &event_.grab_last_particle(); 
      PbAtShell(prng_, event_, 88,0.,0.,tdlev);
    }
    else if (p <= cg+cK+cL) {
      decay0_electron(prng_, event_, Egamma-EbindL,tclev,thlev,tdlev);
      ipe1064 = &event_.grab_last_particle(); 
      PbAtShell(prng_, event_, 15,0.,0.,tdlev);
    } else {
      decay0_electron(prng_, event_, Egamma-EbindM,tclev,thlev,tdlev);
      ipe1064 = &event_.grab_last_particle(); 
      PbAtShell(prng_, event_, 3,0.,0.,tdlev);
    }
    goto label_57000;
  label_89800  :
    thlev=0.;
    p=100.*prng_();
    if (p <= 99.245) goto label_89801;
    goto label_89802;
  label_89801  :
    Egamma=0.898;
    cK=2.01e-2;
    cL=0.34e-2;
    p=prng_()*(cg+cK+cL);
    if (p <= cg) {
      decay0_gamma(prng_, event_, Egamma,tclev,thlev,tdlev);
    }
    else if (p <= cg+cK) {
      decay0_electron(prng_, event_, Egamma-EbindK,tclev,thlev,tdlev);
      PbAtShell(prng_, event_, 88,0.,0.,tdlev);
    } else {
      decay0_electron(prng_, event_, Egamma-EbindL,tclev,thlev,tdlev);
      PbAtShell(prng_, event_, 15,0.,0.,tdlev);
    }
    return;
  label_89802  :
    Egamma=0.328;
    cK=0.2850;
    cL=0.0486;
    cM=0.0151;
    p=prng_()*(cg+cK+cL+cM);
    if (p <= cg) {
      decay0_gamma(prng_, event_, Egamma,tclev,thlev,tdlev);
    }
    else if (p <= cg+cK) {
      decay0_electron(prng_, event_, Egamma-EbindK,tclev,thlev,tdlev);
      PbAtShell(prng_, event_, 88,0.,0.,tdlev);
    }
    else if (p <= cg+cK+cL) {
      decay0_electron(prng_, event_, Egamma-EbindL,tclev,thlev,tdlev);
      PbAtShell(prng_, event_, 15,0.,0.,tdlev);
    } else {
      decay0_electron(prng_, event_, Egamma-EbindM,tclev,thlev,tdlev);
      PbAtShell(prng_, event_, 3,0.,0.,tdlev);
    };
    goto label_57000;
  label_570  :
    p=prng_();
    if (p <= 0.7965) {
      PbAtShell(prng_, event_, 88,0.,0.,t);
    }
    else if (p <= 0.9466) {
      PbAtShell(prng_, event_, 15,0.,0.,t);
    } else {
      PbAtShell(prng_, event_, 3,0.,0.,t);
    }
  label_57000  :
    thlev=130.5e-12;
    Egamma=0.570;
    cK=1.55e-2;
    cL=0.45e-2;
    cM=0.15e-2;
    p=prng_()*(cg+cK+cL+cM);
    if (p <= cg) {
      decay0_gamma(prng_, event_, Egamma,tclev,thlev,tdlev);
      ipg570 = &event_.grab_last_particle(); 
    }
    else if (p <= cg+cK) {
      decay0_electron(prng_, event_, Egamma-EbindK,tclev,thlev,tdlev);
      ipe570 = &event_.grab_last_particle(); 
      PbAtShell(prng_, event_, 88,0.,0.,tdlev);
    }
    else if (p <= cg+cK+cL) {
      decay0_electron(prng_, event_, Egamma-EbindL,tclev,thlev,tdlev);
      ipe570 = &event_.grab_last_particle(); 
      PbAtShell(prng_, event_, 15,0.,0.,tdlev);
    }
    else {
      decay0_electron(prng_, event_, Egamma-EbindM,tclev,thlev,tdlev);
      ipe570 = &event_.grab_last_particle(); 
      PbAtShell(prng_, event_, 3,0.,0.,tdlev);
    }
    // Angular correlation between gammas and conversion electrons of 1064 and
    // 570 keV
    // et al., Nucl. Phys. A 93(1967)63. For K, L and M electrons the same
    // coefficients are used.
    // Thanks to V.Vasilyev for correcting formula in previous DECAY0 version
    // for case of two conversion electrons emitted.
    if (ipg1064 != 0 && ipg570 != 0) {
      a2=0.231;
      a4=-0.023;
      ip1064=ipg1064;
      ip570=ipg570;
    }
    else if (ipe1064 != 0 && ipg570 != 0) {
      a2=0.223;
      a4=-0.020;
      ip1064=ipe1064;
      ip570=ipg570;
    }
    else if (ipg1064 != 0 && ipe570 != 0) {
      a2=0.275;
      a4=-0.012;
      ip1064=ipg1064;
      ip570=ipe570;
    }
    else if (ipe1064 != 0 && ipe570 != 0) {
      a2=0.271;
      a4=-0.010;
      ip1064=ipe1064;
      ip570=ipe570;
    } else {
      return;
    }
    p1064 = ip1064->get_p();
    p570  = ip570->get_p();
    // Rejection method :
  label_3  :
    phi1=twopi*prng_();
    ctet1=1.-2.*prng_();
    stet1=std::sqrt(1.-ctet1*ctet1);
    phi2=twopi*prng_();
    ctet2=1.-2.*prng_();
    stet2=std::sqrt(1.-ctet2*ctet2);
    ctet=ctet1*ctet2+stet1*stet2*cos(phi1-phi2);
    p2=(3.*gsl_pow_2(ctet)-1.)/2.;
    p4=(35.*gsl_pow_4(ctet)-30.*gsl_pow_2(ctet)+3.)/8.;
    if (prng_()*(1.+std::abs(a2)+std::abs(a4)) > 1.+a2*p2+a4*p4) {
      goto label_3;
    }
    ip1064->set_momentum(p1064 * stet1 * std::cos (phi1),
			 p1064 * stet1 * std::sin (phi1),
			 p1064 * ctet1);
    ip570->set_momentum(p570 * stet2 * std::cos (phi2),
			 p570 * stet2 * std::sin (phi2),
			 p570 * ctet2);
    return;
  }
  // end of Bi207.f

} // end of namespace bxdecay0

// end of Bi207.cc
// Local Variables: --
// mode: c++ --
// End: --
