#ifndef BXDECAY0_FE2_MODS_H
#define BXDECAY0_FE2_MODS_H

namespace bxdecay0 {

  /// \brief Probability distribution for energy of first e-/e+ for modebb=4
  ///        (2nu2b, 0+ -> 0+, 2n mechanism)
  double decay0_fe2_mod4(double e2_, void * params_);

  /// \brief Probability distribution for energy of first e-/e+ for modebb=5
  ///        (0nu2b with Gelmini-Roncadelli Majoron (spectral index = 1),
  ///        0+ -> 0+, 2n mechanism)
  double decay0_fe2_mod5(double e2_, void * params_);

  /// \brief Probability distribution for energy of second e-/e+ for modebb=6
  ///        (0nu2b with massive vector etc. Majoron (spectral index = 3),
  ///        0+ -> 0+, 2n mechanism)
  double decay0_fe2_mod6(double e2_, void * params_);

  /// \brief Probability distribution for energy of second e-/e+ for modebb=8
  ///        (2nu2b, 0+ -> 2+, 2n or N* mechanism)
  double decay0_fe2_mod8(double e2_, void * params_);

  /// \brief Probability distribution for energy of second e-/e+ for modebb=13
  ///        (0nu2b with Majoron with spectral index = 7, 0+ -> 0+, 2n mechanism)
  double decay0_fe2_mod13(double e2_, void * params_);

  /// \brief Probability distribution for energy of second e-/e+ for modebb=14
  ///        (0nu2b with Mohapatra Majoron with spectral index = 2, 0+ -> 0+, 2n mechanism)
  double decay0_fe2_mod14(double e2_, void * params_);

  /// \brief Probability distribution for energy of second e-/e+ for modebb=15
  double decay0_fe2_mod15(double e2_, void * params_);

  /// \brief Probability distribution for energy of second e-/e+ for modebb=16
  double decay0_fe2_mod16(double e2_, void * params_);

} // end of namespace bxdecay0

#endif // BXDECAY0_FE2_MODS_H

// Local Variables: --
// mode: c++ --
// End: --
