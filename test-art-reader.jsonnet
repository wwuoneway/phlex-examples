{
  driver: {
    cpp: 'generate_layers',
    layers: {
      event: { parent: 'job', total: 5, starting_number: 0 },
    },
  },
  sources: {
    mcparticle_source: {
      cpp: 'mcparticle_source',
      layer: 'event',
      art_module: 'largeant',
      art_label: '',
      art_job: 'G4',
      art_file_name: '/cvmfs/dune.osgstorage.org/pnfs/fnal.gov/usr/dune/persistent/stash/ContinuousIntegration/DUNEFD/g4/prodgenie_nue_dune10kt_1x2x6_g4_10events_20200727.root',
    },
  },
  modules: {
    print_mcparticles: {
      cpp: 'mcparticles_module',
      layer: 'event',
    },
    output: {
      cpp: 'form_module',
      products: ['n_mcparticles'],
    },
  },
}
