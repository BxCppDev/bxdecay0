// Ourselves:
#include "bxdecay0_g4/unique_point_vertex_generator_messenger.hh"

// Standard library:
#include <string>
#include <sstream>

// BxDecay0:
#include <bxdecay0/decay0_generator.h>
#include <bxdecay0/bb_utils.h>

// Geant4:
#include <G4Tokenizer.hh>
#include <G4UIcommand.hh>

// CLHEP:
#include <CLHEP/Units/SystemOfUnits.h>

namespace bxdecay0_g4 {

  UniquePointVertexGeneratorMessenger::UniquePointVertexGeneratorMessenger(UniquePointVertexGenerator * upvg_)
    : G4UImessenger()
  {
    _upvg_ = upvg_;

    // // Directory /bxdecay0/
    // _top_directory_ = new G4UIdirectory("/bxdecay0/");
    // _top_directory_->SetGuidance(" BxDecay0 comands.");

    // Directory /bxdecay0/upvg/
    _upvg_directory_ = new G4UIdirectory("/bxdecay0/upvg/");
    _upvg_directory_->SetGuidance(" BxDecay0 unique point vertex generator commands.");

    {
      // Command /bxdecay0/upvg/vertex
      _upvg_vertex_cmd_ = new G4UIcommand("/bxdecay0/upvg/vertex", this);
      _upvg_vertex_cmd_->SetGuidance("Set the coordinates of the point-like source");

      {
        // X parameter: 
        G4UIparameter * xParam = new G4UIparameter("x", 'd', false);
        xParam->SetGuidance("the X coordinate of the point-like source vertex (mm)");
        _upvg_vertex_cmd_->SetParameter(xParam);
      }

      {
        // Y parameter: 
        G4UIparameter * yParam = new G4UIparameter("y", 'd', false);
        yParam->SetGuidance("the Y coordinate of the point-like source vertex (mm)");
        _upvg_vertex_cmd_->SetParameter(yParam);
      }

      {
        // Z parameter: 
        G4UIparameter * zParam = new G4UIparameter("z", 'd', false);
        zParam->SetGuidance("the Z coordinate of the point-like source vertex (mm)");
        _upvg_vertex_cmd_->SetParameter(zParam);
      }

      {
        // Unit parameter: 
        G4UIparameter * unitParam = new G4UIparameter("unit", 's', true);
        unitParam->SetGuidance("the length unit (default: mm)");
        unitParam->SetDefaultValue("mm");
        _upvg_vertex_cmd_->SetParameter(unitParam);
      }
 
    }
    
    _upvg_vertex_cmd_->AvailableForStates(G4State_PreInit, G4State_Idle);
    
    return;
  }

  UniquePointVertexGeneratorMessenger::~UniquePointVertexGeneratorMessenger()
  {
    delete _upvg_vertex_cmd_;
    delete _upvg_directory_;
    return;
  }

  G4String UniquePointVertexGeneratorMessenger::GetCurrentValue(G4UIcommand * command_)
  {
    G4String curValue;
    if (command_ == _upvg_vertex_cmd_) {
      G4ThreeVector source = _upvg_->GetSourcePosition();
      std::ostringstream sCurValue;
      sCurValue << source.x() / CLHEP::mm << ' ';
      sCurValue << source.y() / CLHEP::mm << ' ';
      sCurValue << source.z() / CLHEP::mm << ' ';
      sCurValue << "mm";
      curValue = sCurValue.str();
    }
    return curValue;
  }
    
  void UniquePointVertexGeneratorMessenger::SetNewValue(G4UIcommand * command_, G4String new_value_)
  {
    
    if (command_ == _upvg_vertex_cmd_) {
      // Temporary parsing variables:
      G4double x    = 0.0;  // 0
      G4double y    = 0.0;  // 1
      G4double z    = 0.0;  // 2
      G4double lengthUnit = CLHEP::mm; // 3
      G4Tokenizer next(new_value_);
      G4String xRepr = next();
      x = StoD(xRepr);
      G4String yRepr = next();
      y = StoD(yRepr);
      G4String zRepr = next();
      z = StoD(zRepr);
      G4String unitRepr = next();
      if (! unitRepr.isNull()) {
        if (unitRepr == "mm") {
          lengthUnit = CLHEP::mm;
        } else if (unitRepr == "cm") {
          lengthUnit = CLHEP::cm;
        } else if (unitRepr == "m") {
          lengthUnit = CLHEP::m;
        } else if (unitRepr == "micrometer") {
          lengthUnit = CLHEP::micrometer;
        }
      }
      x *= lengthUnit;
      y *= lengthUnit;
      z *= lengthUnit;
      G4ThreeVector newSource(x, y, z);
       _upvg_->SetSourcePosition(newSource);
    }

    return;
  }
  
} // end of namespace bxdecay0_g4 
