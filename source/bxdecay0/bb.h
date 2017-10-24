#ifndef BXDECAY0_BB_H
#define BXDECAY0_BB_H

// Standard library:
#include <string>
#include <fstream>

namespace bxdecay0 {

  /// \brief Energy range information for DBD generation
  struct enrange
  {
    double      ebb1; ///< Left E sum limit for modes with continuous distribution of sum of e-/e+ energies (4,5,6,8,10 and 13), in which events will be generated (MeV)
    double      ebb2; ///< Right E sum limit for modes with continuous distribution of sum of e-/e+ energies (4,5,6,8,10 and 13), in which events will be generated (MeV)
    /** Coefficient to calculate the corresponding
     *  number of bb events in full range of energies:
     *  full_number=generated_number*toallevents
     *  (for modes 4,5,6,8,10 and 13).
     */
    double      toallevents;
    int         levelE;      ///< keV (unused)
    int         itrans02;    ///< Flag for spin (unused)
    std::string chdspin;     ///< Spin string (unused)

    /// Default constructor
    enrange();

    /// Reset
    void reset();

  protected:

    void _set_defaults();

  };

  /// \brief Parameters used to run the genbb application
  struct genbbpar
  {
    int nevents;        ///< Number of events
    int ievstart;       ///< Number of the first generated event
    int irndmst;        ///<
    int iwrfile;        ///<
    std::string chfile; ///< Output file name
    int icurrent;       ///< From common/currentev/
    std::ofstream fout; ///< Output file stream

    /// Default constructor
    genbbpar();

    /// Reset
    void reset();

  protected:

    void _set_defaults();

  };

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
      MODEBB_0NUBB_MAJ7_0_2N  = 13, ///< 0nuM7bb (Majoron, SI=7)   0+ -> 0+,      2n
      MODEBB_13               = MODEBB_0NUBB_MAJ7_0_2N,
      MODEBB_0NUBB_MAJ2_0_2N  = 14, ///< 0nuM2bb (Majoron, SI=2)   0+ -> 0+,      2n
      MODEBB_14               = MODEBB_0NUBB_MAJ2_0_2N,
      MODEBB_2NUBB_BOSE_0     = 15, ///< 2nubb with bosonic nu's   0+ -> 0+
      MODEBB_15               = MODEBB_2NUBB_BOSE_0,
      MODEBB_2NUBB_BOSE_2     = 16, ///< 2nubb with bosonic nu's   0+ -> 2+
      MODEBB_16               = MODEBB_2NUBB_BOSE_2,
      MODEBB_0NUBB_RHCE_0     = 17, ///< 0nubb with rhc-eta        0+ -> 0+       simplified expression
      MODEBB_17               = MODEBB_0NUBB_RHCE_0,
      MODEBB_0NUBB_RHCE_0_NME = 18, ///< 0nubb with rhc-eta        0+ -> 0+       with specific NMEs
      MODEBB_18               = MODEBB_0NUBB_RHCE_0_NME,
      MODEBB_MIN              = MODEBB_1,
      MODEBB_MAX              = MODEBB_18
    };

  /// Return the label associated to a DBD mode
  std::string decay0_dbd_mode_label(int);

  /// Check if a DBD mode supports limits set on generated energy sum
  bool decay0_supports_esum_limits(int modebb_);

  /// \brief Internal working data:
  struct denrange
  {
    double dens;
    double denf;
    int    mode;

    /// Default constructor
    denrange();

    /// Reset
    void reset();

  protected:

    void _set_defaults();

  };

  /// \brief Internal working data:
  struct helpbb
  {
    double Zd; // unused
    double Ad; // unused
    double e0;
    double e1;

    /// Default constructor
    helpbb();

    /// Reset
    void reset();

  protected:

    void _set_defaults();

  };

  /// \brief Parameters for MODE_18:
  struct eta_nme
  {
    double chi_GTw;
    double chi_Fw;
    double chip_GT;
    double chip_F;
    double chip_T;
    double chip_P;
    double chip_R;

    /// Default constructor
    eta_nme();

    /// Reset
    void reset();

  protected:

    void _set_defaults();

  };

  /// \brief DBD parameters
  struct bbpars
    : public enrange
    , public denrange
    , public helpbb
    , public eta_nme
  {
    static const unsigned int SPSIZE = 4300;
    int    modebb;   ///< Mode of double beta (- or +) decay (from 1 to 18)
    double Qbb;      ///< Energy release in double beta process: difference between masses of parent and daughter atoms (MeV);
    double Edlevel;  ///< Energy of level of daughter nucleus to which transition occured (MeV);
    double EK;       ///< Binding energy of electron on K shell of parent atom (MeV) (for modebb=10 and 11);
    double Zdbb;     ///< Atomic number of daughter nucleus (Z>0 for b-b- and Z<0 for b+b+ and eb+ processes);
    double Adbb;     ///< Mass number of daughter nucleus
    int    istartbb; ///< Initialization flag must be =0 for first call of bb for a given mode;
    double spthe1[SPSIZE];
    double spthe2[SPSIZE];
    double spmax;

    /// Default constructor
    bbpars();

    /// Reset
    void reset();

  protected:

    void _set_defaults();

  };

  class i_random;
  class event;

  /// \brief Subroutine for sampling the energies and angles of electrons in various modes of double beta decay without Primakoff-Rosen approximation.
  //
  // Output: - time of event's start (sec) (as supposed, =0 here);
  //         - time shift from previous time to calculate
  //           when particle was emitted (sec)
  //           (as supposed, =0 here);
  //         - toallevents
  // V.I.Tretyak, 26.11.1995; 17.02.2009.
  void decay0_bb(i_random & prng_, event & event_, void * params_);

} // end of namespace bxdecay0

#endif // BXDECAY0_BB_H

// Local Variables: --
// mode: c++ --
// End: --
