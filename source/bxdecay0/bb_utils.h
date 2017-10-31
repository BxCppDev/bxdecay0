#ifndef BXDECAY0_BB_UTILS_H
#define BXDECAY0_BB_UTILS_H

// Standard library:
#include <string>
#include <map>
#include <set>

namespace bxdecay0 {

  /// \brief Mode of double beta (- or +) decay:
  // [SI - spectral index]
  enum modebb_type {
    MODEBB_UNDEF            = 0,  ///< Undefined
    MODEBB_0NUBB_0_2N       = 1,  ///< 0nubb with neutrino mass, 0+ -> 0+,      2n
    MODEBB_1                = MODEBB_0NUBB_0_2N,
    MODEBB_0NUBB_RHCL_0_2N  = 2,  ///< 0nubb with rhc-lambda,    0+ -> 0+,      2n
    MODEBB_2                = MODEBB_0NUBB_RHCL_0_2N,
    MODEBB_0NUBB_RHCL_02_N  = 3,  ///< 0nubb with rhc-lambda,    0+ -> 0+, 2+,  N*
    MODEBB_3                = MODEBB_0NUBB_RHCL_02_N,
    MODEBB_2NUBB_0_2N       = 4,  ///< 2nubb,                    0+ -> 0+,      2n
    MODEBB_4                = MODEBB_2NUBB_0_2N,
    MODEBB_0NUBB_MAJ1_0_2N  = 5,  ///< 0nuM1bb (Majoron, SI=1),  0+ -> 0+,      2n
    MODEBB_5                = MODEBB_0NUBB_MAJ1_0_2N,
    MODEBB_0NUBB_MAJ3_0_2N  = 6,  ///< 0nuM3bb (Majoron, SI=3),  0+ -> 0+,      2n
    MODEBB_6                = MODEBB_0NUBB_MAJ3_0_2N,
    MODEBB_0NUBB_RHCL_2_2N  = 7,  ///< 0nubb with rhc-lambda,    0+ -> 2+,      2n
    MODEBB_7                = MODEBB_0NUBB_RHCL_2_2N,
    MODEBB_2NUBB_2_2N       = 8,  ///< 2nubb,                    0+ -> 2+,      2n, N*
    MODEBB_8                = MODEBB_2NUBB_2_2N,
    MODEBB_0NUKB_02         = 9,  ///< 0nuKb+                    0+ -> 0+, 2+
    MODEBB_9                = MODEBB_0NUKB_02,
    MODEBB_2NUKB_02         = 10, ///< 2nuKb+                    0+ -> 0+, 2+
    MODEBB_10               = MODEBB_2NUKB_02,
    MODEBB_0NUKK_02         = 11, ///< 0nu2K                     0+ -> 0+, 2+
    MODEBB_11               = MODEBB_0NUKK_02,
    MODEBB_2NUKK_02         = 12, ///< 2nu2K                     0+ -> 0+, 2+
    MODEBB_12               = MODEBB_2NUKK_02,
    MODEBB_0NUBB_MAJ7_0_2N  = 13, ///< 0nuM7bb (Majoron, SI=7)   0+ -> 0+, 2n
    MODEBB_13               = MODEBB_0NUBB_MAJ7_0_2N,
    MODEBB_0NUBB_MAJ2_0_2N  = 14, ///< 0nuM2bb (Majoron, SI=2)   0+ -> 0+, 2n
    MODEBB_14               = MODEBB_0NUBB_MAJ2_0_2N,
    MODEBB_2NUBB_BOSE_0     = 15, ///< 2nubb with bosonic nu's   0+ -> 0+
    MODEBB_15               = MODEBB_2NUBB_BOSE_0,
    MODEBB_2NUBB_BOSE_2     = 16, ///< 2nubb with bosonic nu's   0+ -> 2+
    MODEBB_16               = MODEBB_2NUBB_BOSE_2,
    MODEBB_0NUBB_RHCE_0     = 17, ///< 0nubb with rhc-eta        0+ -> 0+, simplified expression
    MODEBB_17               = MODEBB_0NUBB_RHCE_0,
    MODEBB_0NUBB_RHCE_0_NME = 18, ///< 0nubb with rhc-eta        0+ -> 0+, with specific NMEs
    MODEBB_18               = MODEBB_0NUBB_RHCE_0_NME,
    MODEBB_2NUBB_LV_0       = 19, ///< 2nubb with LV             0+ -> 0+, with Lorentz violation
    MODEBB_19               = MODEBB_2NUBB_LV_0,
    MODEBB_0NU4B_0          = 20, ///< 0nu4b                     0+ -> 0+, quadruple beta decay
                                  ///< possible only for Zr96, Xe136, Nd150
    MODEBB_20               = MODEBB_0NU4B_0,
    MODEBB_MIN              = MODEBB_1,
    MODEBB_MAX              = MODEBB_20
  };

  // Return the dictionary of DBD modes
  struct dbd_record {
    modebb_type modebb;
    // bool        esum_range = false;
    std::string description;
  };

  /// Return the set of DBD modes with description
  const std::map<modebb_type,dbd_record> & decay0_dbd_modes();

  /// Return the label associated to a DBD mode
  std::string decay0_dbd_mode_description(const modebb_type modebb_);

  /// Return the set of DBD modes with support for energy sum range
  const std::set<modebb_type> & decay0_dbd_modes_with_esum_range();

  /// Check if a DBD mode has support for energy sum range
  bool decay0_supports_esum_range(const modebb_type modebb_);

} // end of namespace bxdecay0

#endif // BXDECAY0_BB_UTILS_H

// Local Variables: --
// mode: c++ --
// End: --
