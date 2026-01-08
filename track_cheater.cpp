#include "track_cheater.hpp"
#include "MCParticle.h"
#include "track.hpp"

#include "TDatabasePDG.h"
//#include "TSystem.h" //TODO: Remove me

#include <cmath>

namespace examples {
  track_cheater::track_cheater(std::map<int, double> const& energy_thresholds):
    m_energy_thresholds(energy_thresholds)
  {
    //N.B.: Calling TClass::GetClass("examples::Track") to even check for a dictionary causes this class (but not the vector version) to show up in the dictionary list later when it didn't before.
    /*std::cout << "Loading library manually..." << std::endl;
    int const result = gSystem->Load("libform_test_data_products.so");
    gSystem->LoadAllLibraries();
    std::cout << "Result of library load: " << result << std::endl;*/
  }

  std::vector<track> track_cheater::reconstruct(std::vector<simb::MCParticle> const& particles)
  {
    std::vector<track> tracks;

    for(auto const& part: particles)
    {
      auto partInfo = TDatabasePDG::Instance()->GetParticle(part.PdgCode());
      /*if(!partInfo) {
        std::cerr << "No information in ROOT for particle with PDG code " << part.PdgCode()
                  << std::endl << "Skipping..." << std::endl;
      }*/
      if(partInfo && //exclude particles for which ROOT has no database entry.  Very low momentum nuclei are a common example.
         fabs(partInfo->Charge()) > 0.2 && //exclude neutral particles
         part.Momentum().E() - part.Momentum().M() > m_energy_thresholds[part.PdgCode()]) //energy threshold per PDG code
        tracks.emplace_back(part.Position(), part.EndPosition());
    }

    return tracks;
  }
}
