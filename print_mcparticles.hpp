#include <vector>

#ifndef PRINT_MCPARTICLES_HPP
#define PRINT_MCPARTICLES_HPP

namespace simb
{
  class MCParticle;
}

namespace examples
{
  //Algorithm that prints the contents of simb::MCParticles and returns the number of MCParticles in this data cell.
  int print_mcparticles(std::vector<simb::MCParticle> const& particles);
}

#endif //PRINT_MCPARTICLES_HPP
