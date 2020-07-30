#ifndef BXDECAY0_GFANG_H
#define BXDECAY0_GFANG_H 1

namespace bxdecay0 {

  /// \brief  Finds theta-phi angles for a particle with momentum P.
  // The logical flag ROTATE indicates whether the director
  // cosines are along the Z axis (.FALSE.) or not (.TRUE.).
  // F.Carminati (GEANT).
  void decay0_gfang(const double * p_,
                    double & costh_,
                    double & sinth_,
                    double & cosph_,
                    double & sinph_,
                    bool & rotate_);

} // end of namespace bxdecay0

#endif // BXDECAY0_GFANG_H

// Local Variables: --
// mode: c++ --
// End: --
