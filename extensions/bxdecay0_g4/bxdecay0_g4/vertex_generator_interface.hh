#ifndef BXDECAY0G4_VERTEX_GENERATOR_INTERFACE_HH
#define BXDECAY0G4_VERTEX_GENERATOR_INTERFACE_HH

// Geant4
#include <G4ThreeVector.hh>

namespace bxdecay0_g4 {

  /// \brief Vertex generator interface
  ///
  /// It is possible to install a specific vertex generator in the BxDecay0 primary generator action class.
  /// Such an object must inherit the VertexGeneratorInterface abstract class.
  /// BxDecay0/Geant4 provides a simple UniquePointVertexGenerator class (with its own messenger)
  /// that can be directly used with the BxDecay0 generator in Geant4, or used as a model for more
  /// complex vertex generation algorithm.
  ///
  /// Finally, this interface answers only two questions:
  /// 1) HasNextVertex : Is there another available vertex from the generator ? (yes by default, but can be overridden for managing a finite tank of vertexes)
  /// 2) ShootVertex : What it the next available vertex ? 
  ///
  struct VertexGeneratorInterface
  {
    
    VertexGeneratorInterface() = default;

    virtual ~VertexGeneratorInterface() = default;

    /// Check if the generator can provide at least one more vertex (default: return true)
    virtual bool HasNextVertex() const;

    /// Return one more vertex, possibly through a randomization scheme
    ///
    /// The   management  of   some  internal random   number
    /// generator(s)  is  under  the  responsability  of  the  concrete
    /// class. This is because this  abstract interface can be used to
    /// wrap a vertex  generator algorithm which relies on
    /// its own random number  engine (C++, Boost, CLHEP/Geant4, ROOT,
    /// GSL...). So we  don't enforce people to use  a specific random
    /// engine and we don't provide/propose a default random interface.
    ///
    /// Some useful cases that do not need any randomization scheme are:
    /// - a generator which provides a sequence of vertexes from a file containing a (large) set of precomputed points,
    /// - a simple unique non-random (x,y,z) point-like source.
    ///
    virtual void ShootVertex(G4ThreeVector &  vertex_) = 0;
    
  };
  
} // end of namespace bxdecay0_g4 

#endif // BXDECAY0G4_VERTEX_GENERATOR_INTERFACE_HH
