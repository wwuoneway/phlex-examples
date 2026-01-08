//A track_cheater interprets MCParticles directly as Tracks as a quick-to-develop stand-in for real reconstruction

#ifndef TRACK_CHEATER_HPP
#define TRACK_CHEATER_HPP

#include <vector>
#include <map>

namespace simb {
  class MCParticle;
}

namespace examples {
  class track;

  class track_cheater {
    public:
      track_cheater(std::map<int, double> const& energy_thresholds);
      std::vector<track> reconstruct(std::vector<simb::MCParticle> const& particles);

    private:
      std::map<int, double> m_energy_thresholds; //Map from PDG code to energy threshold.  A particle with energy below
                                                 //its PDG code's threshold will not be reconstructed.  Defaults to 0.
  };
}

#endif //TRACK_CHEATER_HPP
