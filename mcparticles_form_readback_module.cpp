#include "phlex/module.hpp"
#include "MCParticle.h"

using namespace phlex;

namespace {
  std::vector<simb::MCParticle> passthrough(std::vector<simb::MCParticle> const& particles)
  {
    return particles;
  }
}

PHLEX_REGISTER_ALGORITHMS(m, config)
{
  (void)config;

  m.transform("passthrough_mcparticles", passthrough)
    .input_family(product_selector{.creator = "mcparticle_printer",
                                   .layer = "event",
                                   .suffix = "mcparticles",
                                   .type = experimental::make_type_id<std::vector<simb::MCParticle>>()})
    .output_product_suffixes("mcparticles");
}
