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
  /// Description of the `/bxdecay0/generator/` commands' parameters:
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

  };
  
} // end of namespace bxdecay0_g4 

#endif // BXDECAY0G4_PRIMARY_GENERATOR_ACTION_MESSENGER_HH
