#ifndef BXDECAY0_PLOG69_H
#define BXDECAY0_PLOG69_H 1

namespace bxdecay0 {

  // Values of natural logarithm of the standard values of momentum
  // (in units m_e*c) from:
  // H.Behrens, J.Janecke, "Numerical tables for beta-decay and
  // electron capture", Berlin, Springer-Verlag, 1969.
  // Range of momenta correspond to kinetic energy range from 2.55 keV to 25.0 MeV.
  struct BJ69
  {
    static const double plog69[48];
  };

} // end of namespace bxdecay0

#endif // BXDECAY0_PLOG69_H

// Local Variables: --
// mode: c++ --
// End: --
