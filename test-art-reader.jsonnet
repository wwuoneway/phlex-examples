{
  driver: {
    cpp: 'generate_layers',
    layers: {
      spill: { parent: 'job', total: 10, starting_number: 1 },
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
}
