#ifndef BXDECAY0_GDROT_H
#define BXDECAY0_GDROT_H 1

namespace bxdecay0 {

  /// \brief Rotates vector from one reference system into another.
  // Theta and phi are anti-clockwise Eulerian angles between the
  // two systems.
  // M.Hansroul, G.Patrick (GEANT).
  void decay0_gdrot(double * p_,
                    const double costh_, const double sinth_,
                    const double cosph_, const double sinph_);

} // end of namespace bxdecay0

#endif // BXDECAY0_GDROT_H

// Local Variables: --
// mode: c++ --
// End: --
