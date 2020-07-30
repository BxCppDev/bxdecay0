#ifndef BXDECAY0_DIVDIF_H
#define BXDECAY0_DIVDIF_H

namespace bxdecay0 {

  /// \brief Tabular interpolation using symmetrically placed argument points.
  double decay0_divdif(const double * F_, const double * A_, int NN_, double X_, int MM_);

} // end of namespace bxdecay0

#endif // BXDECAY0_DIVDIF_H

// Local Variables: --
// mode: c++ --
// End: --
