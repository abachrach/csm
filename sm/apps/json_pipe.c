#include "../csm/csm_all.h"
#include <csm_options/csm_options.h>

int main(int argc, const char * argv[]) {
	sm_set_program_name(argv[0]);
	
	int n;
	
	struct csm_option* ops = csm_options_allocate(3);
	csm_options_int(ops, "n", &n, 1, "Number of copies");
	if(!csm_options_parse_args(ops, argc, argv)) {
		sm_info("%s : reads a JSON stream and copies it multiplied by n."
			"\n\ncsm_options:\n", (char*)argv[0]);
		csm_options_print_help(ops, stderr);
		return -1;
	}
	
	
	while(1) { 
		JO jo = json_read_stream(stdin);
		if(!jo) {
			if(feof(stdin)) break;
			sm_error("Malformed JSON\n");
			return -1;
		}
		
		const char * s = json_object_to_json_string(jo);
		int i; for(i=0;i<n;i++) {
			puts(s); puts("\n");
		}
		jo_free(jo);
	}
	
	return 0;
}
