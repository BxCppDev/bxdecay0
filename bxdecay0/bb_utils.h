#ifndef BXDECAY0_BB_UTILS_H
#define BXDECAY0_BB_UTILS_H

// Standard library:
#include <string>
#include <map>
#include <set>

namespace bxdecay0 {

  /// Return the set of supported DBD isotopes
  const std::set<std::string> & dbd_isotopes();

  /// Return the set of supported "background" isotopes
  const std::set<std::string> & background_isotopes();

  /// \brief Mode of double beta decay (DBD) used inside BxDecay0 (bb- or bb+)
  ///
  /// This type  has been introduced to  ensure backward compatibility
  /// with  the so-called  'modebb' index  used in  the legacy  Decay0
  /// program which  has changed from  versions to another  making the
  /// BxDecay0 interface  unstable.  A  mapping system is  provided to
  /// guarantee the proper association between the BxDecay0's DBD mode
  /// and the Decay0 modebb values.
  enum dbd_mode_type {
    DBDMODE_UNDEF = 0, ///< Undefined
    
    DBDMODE_0NUBB_MN_0_2N = 1,  
    DBDMODE_1 = DBDMODE_0NUBB_MN_0_2N,

    DBDMODE_0NUBB_RHC_LAMBDA_0_2N = 2, 
    DBDMODE_2 = DBDMODE_0NUBB_RHC_LAMBDA_0_2N,

    DBDMODE_0NUBB_RHC_LAMBDA_02_N = 3, 
    DBDMODE_3 = DBDMODE_0NUBB_RHC_LAMBDA_02_N,

    DBDMODE_2NUBB_0_2N = 4, 
    DBDMODE_4 = DBDMODE_2NUBB_0_2N,

    DBDMODE_0NUBB_M1_0_2N = 5, 
    DBDMODE_5 = DBDMODE_0NUBB_M1_0_2N,

    DBDMODE_0NUBB_M3_0_2N  = 6, 
    DBDMODE_6 = DBDMODE_0NUBB_M3_0_2N,

    DBDMODE_0NUBB_RHC_LAMBDA_2_2N = 7,  
    DBDMODE_7 = DBDMODE_0NUBB_RHC_LAMBDA_2_2N,

    DBDMODE_2NUBB_2_2N = 8, 
    DBDMODE_8 = DBDMODE_2NUBB_2_2N,

    DBDMODE_0NUKB_02 = 9, 
    DBDMODE_9 = DBDMODE_0NUKB_02,

    DBDMODE_2NUKB_02 = 10,
    DBDMODE_10 = DBDMODE_2NUKB_02,

    DBDMODE_0NU2K_02 = 11, 
    DBDMODE_11 = DBDMODE_0NU2K_02,

    DBDMODE_2NU2K_02 = 12, 
    DBDMODE_12 = DBDMODE_2NU2K_02,

    DBDMODE_0NUBB_M7_0_2N = 13,
    DBDMODE_13 = DBDMODE_0NUBB_M7_0_2N,

    DBDMODE_0NUBB_M2_0_2N = 14,
    DBDMODE_14 = DBDMODE_0NUBB_M2_0_2N,

    DBDMODE_2NUBB_BOSONIC_0  = 15, 
    DBDMODE_15 = DBDMODE_2NUBB_BOSONIC_0,

    DBDMODE_2NUBB_BOSONIC_2  = 16, 
    DBDMODE_16 = DBDMODE_2NUBB_BOSONIC_2,

    DBDMODE_0NUBB_RHC_ETA_S_0 = 17,
    DBDMODE_17 = DBDMODE_0NUBB_RHC_ETA_S_0,

    DBDMODE_0NUBB_RHC_ETA_NMES_0 = 18,
    DBDMODE_18 = DBDMODE_0NUBB_RHC_ETA_NMES_0,

    DBDMODE_2NUBB_LV_0 = 19,
    DBDMODE_19 = DBDMODE_2NUBB_LV_0,

    // Neutrinoless quadruple beta decay, possible only for Zr96, Xe136, Nd150
    DBDMODE_0NU4B_0 = 20, 
    DBDMODE_20 = DBDMODE_0NU4B_0,

    // Double beta decay with gA process (g0) only for Se82, Mo100, Cd116, Nd150
    DBDMODE_2NUBB_GA_G0 = 21, 
    DBDMODE_21 = DBDMODE_2NUBB_GA_G0,

    // Double beta decay with gA process (g2) only for Se82, Mo100, Cd116, Nd150
    DBDMODE_2NUBB_GA_G2 = 22, 
    DBDMODE_22 = DBDMODE_2NUBB_GA_G2,

    // Double beta decay with gA process (g22) only for Se82, Mo100, Cd116, Nd150
    DBDMODE_2NUBB_GA_G22 = 23, 
    DBDMODE_23 = DBDMODE_2NUBB_GA_G22,

    // Double beta decay with gA process (g4) only for Se82, Mo100, Cd116, Nd150
    DBDMODE_2NUBB_GA_G4 = 24, 
    DBDMODE_24 = DBDMODE_2NUBB_GA_G4,

    DBDMODE_MIN = DBDMODE_1,
    DBDMODE_MAX = DBDMODE_20
  };

  /// \brief The legacy values used for the BB mode in the Fortran Decay0 program
  enum legacy_modebb_type {
    LEGACY_MODEBB_UNDEF = 0, ///< Undefined
    LEGACY_MODEBB_1 = 1, 
    LEGACY_MODEBB_2 = 2, 
    LEGACY_MODEBB_3 = 3, 
    LEGACY_MODEBB_4 = 4, 
    LEGACY_MODEBB_5 = 5, 
    LEGACY_MODEBB_6 = 6, 
    LEGACY_MODEBB_7 = 7, 
    LEGACY_MODEBB_8 = 8, 
    LEGACY_MODEBB_9 = 9, 
    LEGACY_MODEBB_10 = 10, 
    LEGACY_MODEBB_11 = 11, 
    LEGACY_MODEBB_12 = 12, 
    LEGACY_MODEBB_13 = 13, 
    LEGACY_MODEBB_14 = 14, 
    LEGACY_MODEBB_15 = 15, 
    LEGACY_MODEBB_16 = 16, 
    LEGACY_MODEBB_17 = 17, 
    LEGACY_MODEBB_18 = 18, 
    LEGACY_MODEBB_19 = 19, 
    LEGACY_MODEBB_20 = 20,
    LEGACY_MODEBB_MIN = 1,
    LEGACY_MODEBB_MAX = 20,
    LEGACY_MODEBB_NA  = -1 ///< Unsupported by legacy decay0
  };

  /// \brief DBD mode record
  struct dbd_record {
    dbd_mode_type      dbd_mode = DBDMODE_UNDEF; ///< BxDecay0 DBD mode
    std::string        unique_label; ///< Unique label identifying the DBD mode
    legacy_modebb_type legacy_modebb = LEGACY_MODEBB_UNDEF; ///< Associated legacy Decay0 mode
    std::string        description; ///< Description string of the DBD mode
  };

  /// Return the set of DBD modes with description
  const std::map<dbd_mode_type, dbd_record> & dbd_modes();

  /// Return the DBD mode associated to a given label
  dbd_mode_type dbd_mode_from_label(const std::string & label_);

  /// Return the DBD mode associated to a given label
  dbd_mode_type dbd_mode_from_legacy_modebb(const legacy_modebb_type legacy_modebb_);

  /// Return the label associated to a given DBD mode
  std::string dbd_mode_label(const dbd_mode_type dbd_mode_);
  
  /// Return the label associated to a given DBD mode
  std::string dbd_mode_description(const dbd_mode_type dbd_mode_);

  /// Return the BB Decay0 legacy mode assocated to the given DBD mode
  legacy_modebb_type dbd_legacy_mode(const dbd_mode_type dbd_mode_);

  /// Return the set of DBD modes with support for energy sum range
  const std::set<dbd_mode_type> & dbd_modes_with_esum_range();

  /// Check if a given DBD mode has support for energy sum range
  bool dbd_supports_esum_range(const dbd_mode_type dbd_mode_);
  
} // end of namespace bxdecay0

#endif // BXDECAY0_BB_UTILS_H

// Local Variables: --
// mode: c++ --
// End: --
