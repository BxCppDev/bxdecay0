#ifndef BXDECAY0_FERMI_H
#define BXDECAY0_FERMI_H 1

namespace bxdecay0 {

  /// Compute an approximation of A from Z (acceptable for most nuclei)
  /// \param z_ Z of the daughter nucleus
  double decay0_a_from_z(double z_);

  /// Compute the Fermi function for given Z and kinetic energy
  /// using the non-relativistic approcimation
  double decay0_fermi_func_nr_approx(double z_, double e_);

  double decay0_fermi_func_orig(double z_, double e_);

  double decay0_fermi_func(double z_, double e_, bool use_l0_ = false);

  double decay0_fermi_func_shape_only(double z_, double e_);

  /// Compute the Fermi function for given Z and kinetic energy
  /// \param z_ Z of the daughter nucleus
  /// \param e_ Kinetic energy in MeV
  double decay0_fermi(double z_, double e_);

} // end of namespace bxdecay0

#endif // BXDECAY0_FERMI_H

// Local Variables: --
// mode: c++ --
// End: --
