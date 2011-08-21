#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include <math.h>
#include <libgen.h>

#include <csm_options/csm_options.h>
#include "../csm/csm_all.h"

void purify(LDP ld, double threshold_min, double threshold_max);


struct ld_purify_params {
	double threshold_min, threshold_max;
	const char* file_input;
	const char* file_output;
};


int main(int argc, const char * argv[]) {
	sm_set_program_name(argv[0]);
	
	
	csm_options_banner("ld_purify: Makes sure that the file format is valid. \n * Sets valid=0 if reading is outside interval ");
	
	struct ld_purify_params p;
	
	struct csm_option* ops = csm_options_allocate(20);
	csm_options_double(ops, "threshold_min", &p.threshold_min, 0.01, 
		"Sets valid=0 if readings are less than this threshold.");
	csm_options_double(ops, "threshold_max", &p.threshold_max, 79.0, 
		"Sets valid=0 if readings are more than this threshold.");
	
	csm_options_string(ops, "in", &p.file_input, "stdin", "Input file ");
	csm_options_string(ops, "out", &p.file_output, "stdout", "Output file ");
		
		
	if(!csm_options_parse_args(ops, argc, argv)) {
		csm_options_print_help(ops, stderr);
		return -1;
	}

	FILE * in = open_file_for_reading(p.file_input);
	if(!in) return -3;

	FILE * out = open_file_for_writing(p.file_output);
	if(!out) return -2;



	LDP ld; int count = -1;
	while( (ld = ld_from_json_stream(in))) {
		
		purify(ld, p.threshold_min, p.threshold_max);
		
		if(!ld_valid_fields(ld))  {
			sm_error("Wait, we didn't purify enough  (#%d in file)\n", count);
			continue;
		}
		
		ld_write_as_json(ld, out);
		ld_free(ld);
	}
	
	return 0;
}



void purify(LDP ld, double threshold_min, double threshold_max) {
	for(int i=0;i<ld->nrays;i++) {
		if(!ld->valid[i]) continue;
		
		double rho = ld->readings[i];
		if( is_nan(rho) | (rho < threshold_min) | (rho > threshold_max) ) {
			ld->readings[i] = GSL_NAN;
			ld->valid[i] = 0;
			ld->alpha[i] = GSL_NAN;
			ld->alpha_valid[i] = 0;
		}
		
	}
	
}



