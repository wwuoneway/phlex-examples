//Hack to read MCParticles from an ART file by event
#include "MCParticle.h"

#include "TFile.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"

#include <vector>

//A ToyMCAlg acts like a program that reads from an event generator or runs GEANT!
//But it really reads from an art-root file.
class ToyMCAlg {
  static constexpr auto artTreeName = "Events";
  //static constexpr auto artBranchName = "simb::MCParticles_largeant__G4.obj";

public:
  ToyMCAlg(std::string const& inFileName, std::string const& artBranchName) :
    m_artFile(TFile::Open(inFileName.c_str())),
    m_treeReader(artTreeName, m_artFile.get()),
    m_particles(m_treeReader, artBranchName.c_str())
  {
    if (!m_artFile) {
      throw std::runtime_error("ToyMCAlg could not open a file named " + inFileName);
    }
  }

  std::vector<simb::MCParticle> operator()(int64_t const eventID)
  {
    m_treeReader.SetEntry(eventID);
    if (!m_treeReader.Next())
      throw std::runtime_error("No entry " + std::to_string(eventID) + " in ART-ROOT file " + m_artFile->GetName());

    std::vector<simb::MCParticle> result(
      m_particles.begin(),
      m_particles
        .end());

    return result;
  }

private:
  std::unique_ptr<TFile> m_artFile;
  TTreeReader
    m_treeReader; //Use TTreeReader instead of just TBranch + TTree because it was easier to get it to pick members out of art::Wrapper<> without a dictionary for art::Wrapper<>.  I'm not sure why it's any easier.
  TTreeReaderArray<simb::MCParticle> m_particles;
};
