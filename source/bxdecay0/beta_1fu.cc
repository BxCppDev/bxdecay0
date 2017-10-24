// Ourselves:
#include <bxdecay0/beta_1fu.h>

// Standard library:
#include <cmath>

// Third party:
// - GSL:
#include <gsl/gsl_math.h>

// This project:
#include <bxdecay0/i_random.h>
#include <bxdecay0/event.h>
#include <bxdecay0/particle.h>
#include <bxdecay0/particle_utils.h>
#include <bxdecay0/tgold.h>
#include <bxdecay0/funbeta_1fu.h>
#include <bxdecay0/plog69.h>

namespace bxdecay0 {

  void decay0_beta_1fu(i_random & prng_, event & event_,
                       double Qbeta_, double Zdtr_,
                       double tcnuc_, double thnuc_, double & tdnuc_,
                       double c1_, double c2_, double c3_, double c4_)
  {
    bj69sl2 parssl2;
    parssl2.Zdtr  = Zdtr_;
    parssl2.Qbeta = Qbeta_;
    parssl2.c1    = c1_;
    parssl2.c2    = c2_;
    parssl2.c3    = c3_;
    parssl2.c4    = c4_;
    //i in [0:48[ parssl2.sl2[i] = 0.0;
    decay0_beta_1fu(prng_, event_, tcnuc_, thnuc_, tdnuc_, &parssl2);
    return;
  }

  void decay0_beta_1fu(i_random & prng_, event & event_,
                       double tcnuc_, double thnuc_,  double & tdnuc_,
                       void * params_)
  {
    // Parameters for function 'decay0_funbeta_1fu'
    bj69sl2 * parssl2 = static_cast<bj69sl2 *>(params_);
    const double & Zdtr  = parssl2->Zdtr;
    const double & Qbeta = parssl2->Qbeta;
    //const double & c1    = parssl2->c1;
    //const double & c2    = parssl2->c2;
    //const double & c3    = parssl2->c3;
    //const double & c4    = parssl2->c4;
    double *       sl2   = parssl2->sl2;

    // Values of the "lambda2" Coulomb function for some Zdtr values from:
    // H.Behrens, J.Janecke, "Numerical tables for beta-decay and electron
    // capture", Berlin, Springer-Verlag, 1969.
    // Values are calculated as product between unscreened lambda2 (Table II of BJ'1969)
    // and screened corrections (Table III), and are given for "standard" values of
    // momentum (0.1-50.0 in units of m_e*c). (Log values of these momenta are in array
    // plog69.)
    for (int i = 1; i <= 48; i++) {
      sl2[i-1] = 1.;
    }
    if ((int)Zdtr == 19) {
      // 39-Ar, Q_beta=0.565
      sl2[ 1-1] = 2.0929;               // p = 0.1
      sl2[ 2-1] = 1.2337;               // p = 0.2
      sl2[ 3-1] = 1.0747;               // p = 0.3
      sl2[ 4-1] = 1.0234;               // p = 0.4
      sl2[ 5-1] = 0.99977;              // p = 0.5
      sl2[ 6-1] = 0.98728;              // p = 0.6
      sl2[ 7-1] = 0.98024;              // p = 0.7
      sl2[ 8-1] = 0.97624;              // p = 0.8
      sl2[ 9-1] = 0.97445;              // p = 0.9
      sl2[10-1] = 0.97377;              // p = 1.0
      sl2[11-1] = 0.97406;              // p = 1.2
      sl2[12-1] = 0.97549;              // p = 1.4
      sl2[13-1] = 0.9757;               // p = 1.6
      sl2[14-1] = 0.9754;               // p = 1.8
      sl2[15-1] = 0.9754;               // p = 2.0
      sl2[16-1] = 0.9756;               // p = 2.2
      sl2[17-1] = 0.9760;               // p = 2.4, E=0.818
    }
    else if((int)Zdtr == 20) {
      // 42-Ar, Q_beta=0.600 + 42-K, Q_beta=3.525
      sl2[ 1-1] = 2.2248;               // p = 0.1
      sl2[ 2-1] = 1.2634;               // p = 0.2
      sl2[ 3-1] = 1.0851;               // p = 0.3
      sl2[ 4-1] = 1.0275;               // p = 0.4
      sl2[ 5-1] = 1.0008;               // p = 0.5
      sl2[ 6-1] = 0.98693;              // p = 0.6
      sl2[ 7-1] = 0.97884;              // p = 0.7
      sl2[ 8-1] = 0.97426;              // p = 0.8
      sl2[ 9-1] = 0.97213;              // p = 0.9
      sl2[10-1] = 0.97128;              // p = 1.0
      sl2[11-1] = 0.97138;              // p = 1.2
      sl2[12-1] = 0.97276;              // p = 1.4
      sl2[13-1] = 0.9731;               // p = 1.6
      sl2[14-1] = 0.9728;               // p = 1.8
      sl2[15-1] = 0.9728;               // p = 2.0
      sl2[16-1] = 0.9731;               // p = 2.2
      sl2[17-1] = 0.9735;               // p = 2.4
      sl2[18-1] = 0.9740;               // p = 2.6
      sl2[19-1] = 0.9745;               // p = 2.8
      sl2[20-1] = 0.9750;               // p = 3.0
      sl2[21-1] = 0.9756;               // p = 3.2
      sl2[22-1] = 0.9762;               // p = 3.4
      sl2[23-1] = 0.9768;               // p = 3.6
      sl2[24-1] = 0.9774;               // p = 3.8
      sl2[25-1] = 0.9780;               // p = 4.0
      sl2[26-1] = 0.9794;               // p = 4.5
      sl2[27-1] = 0.9808;               // p = 5.0
      sl2[28-1] = 0.9821;               // p = 5.5
      sl2[29-1] = 0.9834;               // p = 6.0
      sl2[30-1] = 0.9846;               // p = 6.5
      sl2[31-1] = 0.9859;               // p = 7.0
      sl2[32-1] = 0.9870;               // p = 7.5
      sl2[33-1] = 0.9882;               // p = 8.0
      sl2[34-1] = 0.9903;               // p = 9.0
      sl2[35-1] = 0.9924;               // p = 10.0, E=4.625
    }
    else if((int)Zdtr == 39) {
      // 90-Sr, Q_beta=0.546
      sl2[ 1-1] = 5.6836;               // p = 0.1
      sl2[ 2-1] = 2.0435;               // p = 0.2
      sl2[ 3-1] = 1.3704;               // p = 0.3
      sl2[ 4-1] = 1.1386;               // p = 0.4
      sl2[ 5-1] = 1.0327;               // p = 0.5
      sl2[ 6-1] = 0.97761;              // p = 0.6
      sl2[ 7-1] = 0.94571;              // p = 0.7
      sl2[ 8-1] = 0.92621;              // p = 0.8
      sl2[ 9-1] = 0.91383;              // p = 0.9
      sl2[10-1] = 0.90577;              // p = 1.0
      sl2[11-1] = 0.89708;              // p = 1.2
      sl2[12-1] = 0.89379;              // p = 1.4
      sl2[13-1] = 0.89354;              // p = 1.6
      sl2[14-1] = 0.89479;              // p = 1.8
      sl2[15-1] = 0.89695;              // p = 2.0
      sl2[16-1] = 0.89953;              // p = 2.2
      sl2[17-1] = 0.90229;              // p = 2.4, E=0.818
    }
    else if((int)Zdtr == 40) {
      // 90-Y, Q_beta=2.228
      sl2[ 1-1] = 5.8992;               // p = 0.1
      sl2[ 2-1] = 2.0922;               // p = 0.2
      sl2[ 3-1] = 1.3883;               // p = 0.3
      sl2[ 4-1] = 1.1454;               // p = 0.4
      sl2[ 5-1] = 1.0345;               // p = 0.5
      sl2[ 6-1] = 0.97692;              // p = 0.6
      sl2[ 7-1] = 0.94344;              // p = 0.7
      sl2[ 8-1] = 0.92294;              // p = 0.8
      sl2[ 9-1] = 0.90998;              // p = 0.9
      sl2[10-1] = 0.90153;              // p = 1.0
      sl2[11-1] = 0.89243;              // p = 1.2
      sl2[12-1] = 0.88892;              // p = 1.4
      sl2[13-1] = 0.88848;              // p = 1.6
      sl2[14-1] = 0.88970;              // p = 1.8
      sl2[15-1] = 0.89186;              // p = 2.0
      sl2[16-1] = 0.89454;              // p = 2.2
      sl2[17-1] = 0.89739;              // p = 2.4
      sl2[18-1] = 0.90037;              // p = 2.6
      sl2[19-1] = 0.90330;              // p = 2.8
      sl2[20-1] = 0.90631;              // p = 3.0
      sl2[21-1] = 0.90931;              // p = 3.2
      sl2[22-1] = 0.91223;              // p = 3.4
      sl2[23-1] = 0.91507;              // p = 3.6
      sl2[24-1] = 0.9174;               // p = 3.8
      sl2[25-1] = 0.9195;               // p = 4.0
      sl2[26-1] = 0.9246;               // p = 4.5
      sl2[27-1] = 0.9295;               // p = 5.0
      sl2[28-1] = 0.9343;               // p = 5.5
      sl2[29-1] = 0.9388;               // p = 6.0
      sl2[30-1] = 0.9432;               // p = 6.5, E=2.850
    }
    else if((int)Zdtr == 56) {
      // 137-Cs, Q_beta=0.514 (to level 0.662)
      sl2[ 1-1] = 9.3262;               // p = 0.1
      sl2[ 2-1] = 2.8592;               // p = 0.2
      sl2[ 3-1] = 1.6650;               // p = 0.3
      sl2[ 4-1] = 1.2481;               // p = 0.4
      sl2[ 5-1] = 1.0580;               // p = 0.5
      sl2[ 6-1] = 0.95794;              // p = 0.6
      sl2[ 7-1] = 0.89948;              // p = 0.7
      sl2[ 8-1] = 0.86350;              // p = 0.8
      sl2[ 9-1] = 0.84043;              // p = 0.9
      sl2[10-1] = 0.82535;              // p = 1.0
      sl2[11-1] = 0.80875;              // p = 1.2
      sl2[12-1] = 0.80209;              // p = 1.4
      sl2[13-1] = 0.80046;              // p = 1.6
      sl2[14-1] = 0.80152;              // p = 1.8
      sl2[15-1] = 0.80409;              // p = 2.0
      sl2[16-1] = 0.80752;              // p = 2.2
      sl2[17-1] = 0.81167;              // p = 2.4, E=0.818
    }

    double em, fm;
    decay0_tgold(50.e-6, 0.5 * Qbeta, Qbeta,
                 decay0_funbeta_1fu, 0.001 * Qbeta, 2,
                 em, fm, params_);
    // Rejection method:
    double f, fe, E;
    do {
      E = 50.e-6 + (Qbeta - 50.e-6) * prng_();
      fe = decay0_funbeta_1fu(E, params_);
      f = fm * prng_();
    } while (f > fe);
    bxdecay0::particle_code np;
    if (Zdtr >= 0.) np = ELECTRON;
    if (Zdtr < 0.) np = POSITRON;
    // isotropical emission of beta particle is supposed
    decay0_particle(prng_, event_,
                    np, E, E, 0., M_PI, 0., 2.*M_PI,
                    tcnuc_, thnuc_, tdnuc_);
    return;
  }

} // end of namespace bxdecay0
