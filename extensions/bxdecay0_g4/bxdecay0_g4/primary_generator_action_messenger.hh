#ifndef BXDECAY0G4_PRIMARY_GENERATOR_ACTION_MESSENGER_HH
#define BXDECAY0G4_PRIMARY_GENERATOR_ACTION_MESSENGER_HH

// Standard library:
#include <memory>

// Geant4
#include <G4UImessenger.hh>
//#include <globals.hh>

class G4UIcmdWithABool;
class G4UIcommand;

// This project:
#include <bxdecay0_g4/primary_generator_action.hh>

namespace bxdecay0_g4 {

  /// \brief BxDecay0 Geant4 primary generator messenger
  ///
  /// Description of the parameters for the `/bxdecay0/generator/background`, `/bxdecay0/generator/dbd`
  /// and `/bxdecay0/generator/dbdranged` commands:
  ///
  ///            | Parameters ||||||
  /// ---------- | ------- | -------- | -------- | --------- | -------------- | -------------- | --------
  ///            | nuclide |   seed   | dbd_mode | dbd_level | dbd_min_energy | dbd_max_energy | debug
  /// ---------- | ------- | -------- | -------- | --------- | -------------- | -------------- | --------
  /// Type       | string  |  integer | integer  | integer   | real           | real           | boolean
  /// Default    | -       |  -       | -        | -         | -              | -1.0           | false  
  /// ---------- | ------- | -------- | -------- | --------- | -------------- | -------------- | --------
  /// background | yes     |  yes     | N/A      | N/A       | N/A            | N/A            | yes
  /// Example    | "Co60"  |  314159  | N/A      | N/A       | N/A            | N/A            | false
  /// ---------- | ------- | -------- | -------- | --------- | -------------- | -------------- | --------
  /// dbd        | yes     |  yes     | yes      | yes       | N/A            | N/A            | yes
  /// Example    | "Mo100" |  951413  | 1        | 0         | -              | -              | false
  /// ---------- | ------- | -------- | -------- | --------- | -------------- | -------------- | --------
  /// dbdranged  | yes     |  yes     | yes      | yes       | yes            | yes            | yes
  /// Example    | "Se82"  |  123456  | 4        | 0         | 2.4            | 3.0            | false
  ///
  /// Geant4 macro examples:
  ///
  ///   /bxdecay0/generator/background Co60  314159 [false]
  ///   /bxdecay0/generator/dbd        Mo100 951413 1 0 [false]
  ///   /bxdecay0/generator/dbdranged  Se82  123456 4 0 2.4 3.0 [false]
  ///
  /// Special post-generation event operations:
  ///
  /// * MDL : Momentum Direction Lock, biased sampling based on a privileged direction of emission for some particle (s)
  ///
  ///   /bxdecay0/generator/mdl gamma 0 30.0 60.0 20.0 [false]
  ///
  ///  Version with rectangular cut on the emission cone aperture (required one more angular parameter) :
  ///
  ///   /bxdecay0/generator/mdlr gamma 0 30.0 60.0 20.0 10.0 [false]
  ///
  /// Description of the parameters for the `/bxdecay0/generator/mdl` command:
  ///
  ///            | Parameters |||||
  /// ---------- | ------- | -------- | --------- | ---------- | -------------- | -------------------------
  ///            | name    |   rank   | longitude | colatitude | aperture       | error_on_missing_target
  /// ---------- | ------- | -------- | --------- | ---------- | -------------- | -------------------------
  /// Type       | string  |  integer | real      | real       | real           | boolean
  /// Default    | "all"   |  -1      | 0.0       | 0.0        | 0.0            | false  
  /// ---------- | ------- | -------- | --------- | ---------- | -------------- | -------------------------
  /// Example    | "e-"    |  0       | 30.0      | 45.0       | 15.0           | true
  ///
 ///
  /// Description of the parameters for the `/bxdecay0/generator/mdlr` command (aperture rectangular cut):
  ///
  ///            | Parameters |||||
  /// ---------- | ------- | -------- | --------- | ---------- | -------------- | -------------- | -------------------------
  ///            | name    |   rank   | longitude | colatitude | aperture       | aperture2      | error_on_missing_target
  /// ---------- | ------- | -------- | --------- | ---------- | -------------- | -------------- | -------------------------
  /// Type       | string  |  integer | real      | real       | real           | real           | boolean
  /// Default    | "all"   |  -1      | 0.0       | 0.0        | 0.0            | 0.0            | false  
  /// ---------- | ------- | -------- | --------- | ---------- | -------------- | -------------- | -------------------------
  /// Example    | "e-"    |  0       | 30.0      | 45.0       | 15.0           | 5.0            | true
  ///
  ///
  /// Other commands:
  ///
  ///   Force the generator build from the configuration (last command):
  ///   /bxdecay0/generator/apply
  ///
  ///   Force the destruction of the current generator setup and clear the configuration:
  ///   /bxdecay0/generator/destroy
  ///
  /// 
  class PrimaryGeneratorActionMessenger
    : public G4UImessenger
  {
  public:

    PrimaryGeneratorActionMessenger(PrimaryGeneratorAction * );

    ~PrimaryGeneratorActionMessenger() override;

    G4String GetCurrentValue (G4UIcommand * command_) override;
    
    void SetNewValue(G4UIcommand *, G4String) override;
    
  private:

    PrimaryGeneratorAction * _pga_ = nullptr;    
    G4UIdirectory *          _pga_directory_ = nullptr;
    G4UIdirectory *          _pga_gtor_directory_ = nullptr;
    G4UIcommand *            _pga_gtor_log_cmd_ = nullptr;
    G4UIcommand *            _pga_gtor_bkgd_cmd_ = nullptr;
    G4UIcommand *            _pga_gtor_dbd_cmd_ = nullptr;
    G4UIcommand *            _pga_gtor_dbdr_cmd_ = nullptr;
    G4UIcommand *            _pga_gtor_mdl_cmd_ = nullptr;
    G4UIcommand *            _pga_gtor_mdlr_cmd_ = nullptr;
    G4UIcommand *            _pga_gtor_apply_cmd_ = nullptr;
    G4UIcommand *            _pga_gtor_destroy_cmd_ = nullptr;
    G4UIcommand *            _pga_gtor_dump_cmd_ = nullptr;
  };
  
} // end of namespace bxdecay0_g4 

#endif // BXDECAY0G4_PRIMARY_GENERATOR_ACTION_MESSENGER_HH
