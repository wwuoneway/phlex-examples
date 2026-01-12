//A track_cheater_per_tpc interprets MCParticles directly as Tracks as a quick-to-develop stand-in for real reconstruction
//This version UNFOLDS MCParticles into a collection of Tracks per "TPC".

#ifndef TRACK_CHEATER_PER_TPC_HPP
#define TRACK_CHEATER_PER_TPC_HPP

#include <vector>
#include <map>

namespace simb {
  class MCParticle;
}

namespace examples {
  class track;

  class track_cheater_per_tpc {
    public:
      using particles_t = std::vector<simb::MCParticle>;
      using next_t = particles_t::const_iterator;

      //Constructed once per input family cell according to https://framework-r-d.github.io/phlex-design/ch_conceptual_design/hofs/partitioned_unfolds.html#partitioned-unfolds
      track_cheater_per_tpc(/*double const tpc_size, std::map<int, double> const& energy_thresholds,*/ particles_t const& particles);
      std::pair<next_t, std::vector<track>> make_tracks(next_t next);
      bool keep_going(next_t const next) const;

    private:
      double m_tpc_size; //Model a TPC as a cube for the sake of demonstration
      std::map<int, double> m_energy_thresholds; //Map from PDG code to energy threshold.  A particle with energy below
                                                 //its PDG code's threshold will not be reconstructed.  Defaults to 0.
      next_t m_end;
  };
}

#endif //TRACK_CHEATER_PER_TPC_HPP
