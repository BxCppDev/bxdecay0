// fermi.cc

// Ourselves:
#include <bxdecay0/fermi.h>

// Standard library:
#include <iostream>
#include <sstream>
#include <cmath>
#include <stdexcept>

// Third party:
// - GSL:
#include <gsl/gsl_sf.h>
// #include <CLHEP/Units/SystemOfUnits.h>

// This project:
#include <bxdecay0/particle.h>
#include <bxdecay0/particle_utils.h>

namespace bxdecay0 {

  double decay0_a_from_z(double z_)
  {
    return 0.0075 * z_ * z_ + 1.9 * z_ + 0.25;
  }

  double decay0_fermi_func_nr_approx(double z_, double e_)
  {
    double e = e_;
    if (e_ < 50.e-6) e = 50.e-6;
    double z = z_;
    static double emass = decay0_emass(); // MeV
    double alpha = 1.0 / 137.036;
    //double me    = emass;
    double w     = e / emass + 1.;
    double p     = std::sqrt(w * w - 1.);
    double beta  = p / w;
    double t     = 2. * M_PI * alpha * z / beta;
    return (t / (1. - std::exp(-t)));
  }

  double decay0_fermi_func_orig(double z_, double e_)
  {
    double e = e_;
    double z = z_;
    if (e < 50.e-6) e = 50.e-6;
    double alfaz = z / 137.036;
    double w = e / 0.510998910 + 1.;
    double p = std::sqrt(w * w - 1.);
    double y = alfaz * w / p;
    double g = std::sqrt(1. - alfaz * alfaz);
    gsl_sf_result res_lnr, res_arg;
    int status = gsl_sf_lngamma_complex_e(g, y, &res_lnr, &res_arg);
    if (status != GSL_SUCCESS) {
      std::cerr << "genbb_help::decay0_fermi_func_orig: GSL error: "
                << gsl_strerror(status) << std::endl;
      throw std::logic_error("genbb_help::decay0_fermi_func_orig: GSL error at 'gsl_sf_lngamma_complex_e' invocation!");
    }
    double lnr = res_lnr.val;
    double res = std::pow(p, 2. * g - 2.) * std::exp(M_PI * y + 2. * lnr);
    return res;
  }

  double decay0_fermi_func(double z_, double e_, bool use_l0_)
  {
    using namespace std;
    double e = e_;
    if (e_ < 50.e-6) e = 50.e-6;
    double z = z_;
    static double emass = decay0_emass(); // MeV
    double alpha = 1.0 / 137.036;
    double hbarc = 197.3269631; // MeV.fm
    double r0    = 1.2; // fm
    double me    = emass; // MeV
    double we    = e / emass + 1.;
    double pe    = std::sqrt(we * we - 1.);
    //double beta  = pe / we;
    double aZ     = alpha * z;
    double gamma1 = std::sqrt(1. - aZ * aZ);
    double y      = aZ * we / pe;
    double a      = decay0_a_from_z (z);
    double R      = r0 * std::exp(std::log(a) / 3.) * me / hbarc;
    double F0 = 4. * std::exp(2. * (gamma1 - 1.) * std::log(2. * pe * R))
      * std::exp (M_PI * y);
    double g2 = gsl_sf_gamma (2. * gamma1 + 1.);
    gsl_sf_result res_lnr, res_arg;
    int status = gsl_sf_lngamma_complex_e(gamma1, y, &res_lnr, &res_arg);
    if (status != GSL_SUCCESS)
      {
        std::ostringstream message;
        message << "genbb::decay0::decay0_fermi_func: "
                << "GSL error at 'gsl_sf_lngamma_complex_e' invocation: "
                << gsl_strerror(status) << std::endl;
        throw std::logic_error(message.str());
      }
    double lnr = res_lnr.val;
    double g1 = std::exp(lnr);
    F0 *= (g1 * g1);
    F0 /= (g2 * g2);
    double L0 = 1.0;
    if(use_l0_)
      {
        double term = 1. - aZ * (we * R - 7. * aZ / 15.)
          - 0.5 * gamma1 * aZ * R / we;
        L0 = 0.5 * (1. + gamma1) * term;
      }
    return (F0 * L0);
  }


  double decay0_fermi_func_shape_only(double z_, double e_)
  {
    double e = e_;
    if (e_ < 50.e-6) e = 50.e-6;
    double z = z_;
    static double emass = decay0_emass();
    double alpha = 1.0 / 137.036;
    double aZ     = alpha * z;
    double we = e / emass + 1.;
    double pe = std::sqrt(we * we - 1.);
    //double beta  = pe / we;
    double y = aZ * we / pe;
    double gamma1 = std::sqrt(1. - aZ * aZ);
    gsl_sf_result res;
    //int err = gsl_sf_lngamma_complex_e (gamma1, y, &res, &arg);
    double lnr     = res.val;
    //double lnr_err = res.err;
    //double zarg     = arg.val;
    //double zarg_err = arg.err;
    return std::exp(2. * (gamma1 - 1.) * std::log(pe))
      * std::exp(M_PI * y + 2. * lnr);
  }

  double decay0_fermi(double z_, double e_)
  {
    return decay0_fermi_func_orig(z_, e_);
  }

} // end of namespace bxdecay0
