//Hack to read one data product from an ART file by event
#include "TFile.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"

#include <vector>

//An ArtReader reads one type of data product from an art-root file.
template <class PROD>
class ArtReader {
  static constexpr auto artTreeName = "Events";
  //static constexpr auto artBranchName = "simb::MCParticles_largeant__G4.obj";

public:
  ArtReader(std::string const& inFileName, std::string const& artBranchName) :
    m_artFile(TFile::Open(inFileName.c_str())),
    m_treeReader(artTreeName, m_artFile.get()),
    m_prods(m_treeReader, artBranchName.c_str())
  {
    if (!m_artFile) {
      throw std::runtime_error("ToyMCAlg could not open a file named " + inFileName);
    }
  }

  std::vector<PROD> operator()(int64_t const eventID)
  {
    m_treeReader.SetEntry(eventID);
    if (!m_treeReader.Next())
      throw std::runtime_error("No entry " + std::to_string(eventID) + " in ART-ROOT file " + m_artFile->GetName());

    std::vector<PROD> result(
      m_prods.begin(),
      m_prods
        .end());

    return result;
  }

private:
  std::unique_ptr<TFile> m_artFile;
  TTreeReader
    m_treeReader; //Use TTreeReader instead of just TBranch + TTree because it was easier to get it to pick members out of art::Wrapper<> without a dictionary for art::Wrapper<>.  I'm not sure why it's any easier.
  TTreeReaderArray<PROD> m_prods;
};
