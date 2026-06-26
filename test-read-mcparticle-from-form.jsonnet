{
  driver: {
    cpp: 'generate_layers',
    layers: {
      event: { parent: 'job', total: 5, starting_number: 0 },
    },
  },
  sources: {
    mcparticles_from_form: {
      cpp: 'form_source',
      input_file: 'output.root',
      algorithm: 'print_mcparticles',
      plugin: 'mcparticle_printer',
      //creator: 'read_mcparticles_from_form',
      creator: 'mcparticle_printer',
      products: ['mcparticles'],
    },
  },
  modules: {
    register_form_source_extra_types: {
      cpp: 'form_source_test_types',
    },
    mcparticle_printer: {
      cpp: 'mcparticles_form_readback_module',
    },
    output: {
      cpp: 'form_module',
      output_file: 'form_mcparticle_readback.root',
      products: ['mcparticles'],
    },
  },
}
