/// \file VertexPoolLoader.cc
/// \brief Implementation of the VertexPoolLoader class

#include "VertexPoolLoader.hh"

#include <cmath>
#include <limits>
#include <exception>

VertexPoolLoader::VertexPoolLoader(const std::string & infilename_)
  : fInFilename(infilename_)
{
  std::clog << "[log] VertexPoolLoader::VertexPoolLoader: Opening file '" << fInFilename << "' for loading stored vertexes...\n";
  fFileIn.reset(new std::ifstream(fInFilename.c_str()));
  if (!fFileIn) throw std::runtime_error("No input file is defined!");
  if (!*fFileIn) throw std::runtime_error("Input file is not valid!");
}

VertexPoolLoader::~VertexPoolLoader()
{
  if (fFileIn.get()) { 
    std::clog << "[log] VertexPoolLoader::VertexPoolLoader: Closing stored vertex file '" << fInFilename << "' after " << fCounter << " records...\n";
    fFileIn->close();
    fFileIn.reset();
  } 
}
 
bool VertexPoolLoader::HasNextVertex() const
{
  return ! std::isnan(fNextVertex.x());
}

void VertexPoolLoader::LoadNextVertex()
{
  fNextVertex.setX(std::numeric_limits<double>::quiet_NaN());
  fNextVertex.setY(std::numeric_limits<double>::quiet_NaN());
  fNextVertex.setZ(std::numeric_limits<double>::quiet_NaN());
  if (! fFileIn->eof()) {
    double x, y, z;
    *fFileIn >> x >> y >> z >> std::ws;
    fCounter++;
    if (!*fFileIn) {
      throw std::runtime_error("VertexPoolLoader::LoadNextVertex: Invalid vertex format (counter=" + std::to_string(fCounter) + ")!");
    }
    x *= CLHEP::mm;
    y *= CLHEP::mm;
    z *= CLHEP::mm;
    fNextVertex.set(x, y, z);
  }
}

void VertexPoolLoader::ShootVertex(G4ThreeVector & vertex_)
{
  vertex_ = fNextVertex;
  LoadNextVertex();
}

