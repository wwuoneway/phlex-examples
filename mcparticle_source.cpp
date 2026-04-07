#include "phlex/configuration.hpp"
#include "phlex/model/data_cell_index.hpp"
#include "phlex/source.hpp"

#include "read_mcparticles_from_art.cpp"

using namespace phlex;

//Can I keep data_cell_index separate from ToyMCAlg?
namespace
{
  template <class ALG>
  struct wrapper: public ALG
  {
    template <class ...ARGS>
    wrapper(ARGS... args): ALG(args...) {}

    auto phlex_callback(data_cell_index const& id) { return ALG::operator ()(id.number()); }
  };
}

PHLEX_REGISTER_PROVIDERS(m, config)
{
  auto const art_module = config.get<std::string>("art_module");
  auto const art_label = config.get<std::string>("art_label");
  auto const art_job = config.get<std::string>("art_job");

  auto const art_file_name = config.get<std::string>("art_file_name");

  auto part_maker = m.make<wrapper<ToyMCAlg>>(art_file_name, "simb::MCParticles_" + art_module + "_" + art_label + "_" + art_job + ".obj");
  part_maker.provide("read_mcparticles", &wrapper<ToyMCAlg>::phlex_callback).output_product(product_query{.creator = "largeant", .layer = "event"});
}
