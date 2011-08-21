#include "csm_options.h"



struct params {
	int a_int;
	double a_double;
	const char * file;
	int algo;
};


struct csm_option_alternative alt[4] = { 
   {"PLICP", 3, "a new algorithm"}, 
   {"ICP",   4, "the standard"}, 
   {"MbICP", 5, "good for rotations"}, {0,0,0}
};

int main(int argc, const char*argv[]) {
	csm_options_banner("This is a test program for the csm_options library.");
	
	struct params p;
	
	struct csm_option* ops = csm_options_allocate(3);
	csm_options_int    (ops, "i", &p.a_int,  42, "An int parameter");
	csm_options_double (ops, "d", &p.a_double,  0.42, "A double parameter");
	csm_options_string (ops, "s", &p.file ,  "Hello", "A file parameter");
	csm_options_alternative(ops, "algorith", alt, &p.algo, "which algorithm to use" );
	
	
	if(!csm_options_parse_args(ops, argc, argv)) {
		printf("A simple program.\n\nUsage:\n");
		csm_options_print_help(ops, stderr);
		return -1;
	}
	
	printf("i: %d \n", p.a_int);
	printf("d: %g \n", p.a_double);
	printf("s: %s \n", p.file);
	
	return 0;
}
