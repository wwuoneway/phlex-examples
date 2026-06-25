#include "phlex/module.hpp"
#include "print_mcparticles.hpp"
#include "MCParticle.h"

using namespace phlex;

PHLEX_REGISTER_ALGORITHMS(m, config)
{
  auto const layer = "event"; //hard-coded in ART reader source for now

  m.transform("print_mcparticles", examples::print_mcparticles)
    .input_family(product_selector{.creator = "read_mcparticles", .layer = layer, .suffix = "largeant"})
    .output_product_suffixes("mcparticles");
}
