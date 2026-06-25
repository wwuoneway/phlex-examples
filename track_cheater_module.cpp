#include "phlex/module.hpp"
#include "track_cheater.hpp"
#include "track.hpp"
#include "MCParticle.h"

using namespace phlex;

PHLEX_REGISTER_ALGORITHMS(m, config)
{
  auto cheater = m.make<examples::track_cheater>(config.get<std::map<int, double>>("energy_thresholds", {{}}));
  cheater.transform("track_cheater", &examples::track_cheater::reconstruct, concurrency::unlimited)
    .input_family(product_selector{.creator = "read_mcparticles", .layer = "event", .suffix = "largeant"})
    .output_product_suffixes("cheater_tracks");
}
