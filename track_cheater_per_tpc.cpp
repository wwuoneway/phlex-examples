#include "track_cheater_per_tpc.hpp"
#include "MCParticle.h"
#include "track.hpp"

#include "TDatabasePDG.h"

#include <cmath>

namespace examples {
  //TODO: unfolds don't seem to support constructor arguments in this early prototype?
  track_cheater_per_tpc::track_cheater_per_tpc(/*double const tpc_size, std::map<int, double> const& energy_thresholds,*/ particles_t const& particles):
    m_tpc_size(/*tpc_size*/ 20.),
    m_energy_thresholds(/*energy_thresholds*/),
    m_end(particles.end())
  {
  }

  std::pair<track_cheater_per_tpc::next_t, std::vector<track>> track_cheater_per_tpc::make_tracks(track_cheater_per_tpc::next_t part)
  {
    std::vector<track> tracks;

    auto partInfo = TDatabasePDG::Instance()->GetParticle(part->PdgCode());
    /*if(!partInfo) {
      std::cerr << "No information in ROOT for particle with PDG code " << part->PdgCode()
                << std::endl << "Skipping..." << std::endl;
    }*/
    if(partInfo && //exclude particles for which ROOT has no database entry.  Very low momentum nuclei are a common example.
       fabs(partInfo->Charge()) > 1e-4 && //exclude neutral particles while including hypothetical millicharged particles
       part->Momentum().E() - part->Momentum().M() > m_energy_thresholds[part->PdgCode()]) //energy threshold per PDG code
    {
      //Break up MCParticle's trajectory into segements inside one TPC
      for(unsigned int which_traj_pt = 0; which_traj_pt < part->NumberTrajectoryPoints(); ++which_traj_pt) {
        auto const start = part->Position(which_traj_pt);
        int const tpc_x = start.X()/m_tpc_size,
                  tpc_y = start.Y()/m_tpc_size,
                  tpc_z = start.Z()/m_tpc_size;
        while(part->Position(which_traj_pt).X()/m_tpc_size == tpc_x
           && part->Position(which_traj_pt).Y()/m_tpc_size == tpc_y
           && part->Position(which_traj_pt).Z()/m_tpc_size == tpc_z
           && which_traj_pt < part->NumberTrajectoryPoints()) {
          ++which_traj_pt;
        }

        tracks.emplace_back(start, part->Position(--which_traj_pt));
      }
    }

    return std::make_pair(std::next(part), tracks);
  }

  bool track_cheater_per_tpc::keep_going(track_cheater_per_tpc::next_t const next) const
  {
    return next != m_end;
  }
}
