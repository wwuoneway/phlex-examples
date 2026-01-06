#include "print_mcparticles.hpp"
#include "MCParticle.h"

#include <iostream> //TODO: Use Phlex's printing facilities

namespace examples
{
  std::vector<simb::MCParticle> print_mcparticles(std::vector<simb::MCParticle> const& particles)
  {
    std::cout << "[" << std::endl;
    for(auto const& part: particles) std::cout << part << std::endl;
    std::cout << "]" << std::endl;

    return particles;
  }
} //namespace examples
