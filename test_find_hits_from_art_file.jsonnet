{
  driver: {
    cpp: 'generate_layers',
    layers: {
      event: { parent: 'job', total: 5, starting_number: 1 },
    },
  },
  sources: {
    wires_source: {
      cpp: 'wire_source',
        layer: 'event',
        art_module: 'tpcrawdecoder',
        art_label: 'dnnsp',
        art_job: 'detsim',
        art_file_name: '/exp/dune/data/users/aolivier/rntuple/largeProductionFilesForRNTuple/anu_numu2nutau_nue2numu_dunevd10kt_1x8x6_3view_30deg_27401_145_20230813T114229Z_gen_g4_detsim_hitreco__20240407T033234Z_reco2.root.dropDuneProducts.root',
    },
  },
  modules: {
    find_hits_with_gaussians_cpp: {
      cpp: 'find_hits_with_gaussians_hof',
      layer: 'event',
      // Copied in the configuration parameters that
      // I obtained from "Far Detector Simulation/Reconstruction conveners":
      // Dominic Brailsford and Laura Paulucci (in cc). See Dom and Kyle
      // 2/17/2026 on SLACK and also email around the same time. These were
      // copied out of the expanded fcl configuration. Note that the ones
      // that have different values for different planes are not used when
      // filter_hits is false.
      filter_hits: false,
      long_max_hits_vec: [1, 1, 1],
      long_pulse_width_vec: [16, 16, 16],
      max_multi_hit: 4,
      area_method: 0,
      area_norms_vec: [13.25, 13.25, 13.25],
      chi2_ndf: 50.0,
      pulse_height_cuts: [3.0,  3.0,  3.0],
      pulse_width_cuts: [2.0, 1.5, 1.0],
      pulse_ratio_cuts: [0.35, 0.40, 0.20],
      cand_hit_standard_configs: {
        CandidateHitsPlane0: {
          Plane: 0,
          roiThreshold: 6.0,
        },
        CandidateHitsPlane1: {
          Plane: 1,
          roiThreshold: 6.0,
        },
        CandidateHitsPlane2: {
          Plane: 2,
          roiThreshold: 6.0,
        },
      },
      peak_fitter_mrqdt_config: {
        min_width: 0.5,
        max_width_mult: 3.0,
        peak_range_fact: 2.0,
        peak_amp_range: 2.0,
      },
      hit_filter_alg_config: {
        min_pulse_height: [5.0, 5.0, 5.0],
        min_pulse_sigma: [1.0, 1.0, 1.0],
      },
    },
    output: {
      cpp: 'form_module',
      products: ['wires', 'hits',],
    },
  },
}
