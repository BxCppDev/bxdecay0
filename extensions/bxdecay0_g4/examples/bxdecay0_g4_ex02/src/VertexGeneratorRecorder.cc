/// \file VertexGeneratorRecorder.cc
/// \brief Implementation of the VertexGeneratorRecorder class

#include "VertexGeneratorRecorder.hh"

#include <exception>

VertexGeneratorRecorder::VertexGeneratorRecorder(bxdecay0_g4::VertexGeneratorInterface * vg_,
                                                 const std::string & outfilename_)
  : fVG(vg_)
  , fOutFilename(outfilename_)
{
  std::clog << "[log] VertexGeneratorRecorder::VertexGeneratorRecorder: Opening file '" << fOutFilename << "' for generated vertex recording...\n";
  fFileOut.reset(new std::ofstream(fOutFilename.c_str()));
  if (!fFileOut) throw std::runtime_error("No output file is defined!");
  if (!*fFileOut) throw std::runtime_error("Output file is not valid!");
}

VertexGeneratorRecorder::~VertexGeneratorRecorder()
{
  if (fFileOut.get()) {
    std::clog << "[log] VertexGeneratorRecorder::VertexGeneratorRecorder: Closing generated vertex file '" << fOutFilename << "'...\n";
    fFileOut->close();
    fFileOut.reset();
  } 
}
 
bool VertexGeneratorRecorder::HasNextVertex() const
{
  return fVG->HasNextVertex();
}

void VertexGeneratorRecorder::ShootVertex(G4ThreeVector & vertex_)
{
  fVG->ShootVertex(vertex_);
  *fFileOut << vertex_.x() / CLHEP::mm << ' ' << vertex_.y() / CLHEP::mm  << ' ' << vertex_.z() / CLHEP::mm  << " mm\n";
}


