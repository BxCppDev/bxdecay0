#ifndef BXDECAY0_BB_H
#define BXDECAY0_BB_H

// Standard library:
#include <string>
#include <fstream>

// This project:
#include <bxdecay0/bb_utils.h>

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
    int irndmst;        ///< (unused)
    int iwrfile;        ///< (unused)
    std::string chfile; ///< Output file name (unused)
    int icurrent;       ///< From common/currentev/ (unused)
    std::ofstream fout; ///< Output file stream (unused)

    /// Default constructor
    genbbpar();

    /// Reset
    void reset();

  protected:

    void _set_defaults();

  };

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

    /// Dump
    void dump(std::ostream & out_, const std::string & indent_ = "") const;

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
