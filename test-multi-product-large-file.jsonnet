{
  driver: {
    cpp: 'generate_layers',
    layers: {
      event: { parent: 'job', total: 25, starting_number: 0 },
    },
  },
  sources: {
    mcparticle_source: {
      cpp: 'mcparticle_source',
      layer: 'event',
      art_module: 'largeant',
      art_label: '',
      art_job: 'G4',
      art_file_name: '/exp/dune/data/users/aolivier/rntuple/largeProductionFilesForRNTuple/anu_dune10kt_1x2x6_1375_448_20230824T071604Z_gen_g4_detsim_hitreco__20240221T063407Z_reco2.root',
    },
  },
  modules: {
    track_cheater: {
      cpp: 'track_cheater_module',
    },
    mcparticle_printer: {
      cpp: 'mcparticles_module',
    },
    output: {
      cpp: 'form_module',
      products: ['cheater_tracks', 'mcparticles',],
    },
  },
}
