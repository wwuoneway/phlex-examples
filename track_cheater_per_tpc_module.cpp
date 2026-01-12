#include "phlex/module.hpp"
#include "track_cheater_per_tpc.hpp"
#include "track.hpp"
#include "MCParticle.h"

using namespace phlex;

PHLEX_REGISTER_ALGORITHMS(m, config)
{
  m.unfold<examples::track_cheater_per_tpc>("track_cheater_per_tpc",
                                            &examples::track_cheater_per_tpc::keep_going,
                                            &examples::track_cheater_per_tpc::make_tracks)
    .input_family("largeant"_in("event"))
    .output_products("cheater_tracks"_in("tpc")/*_in("event")*/);
}
