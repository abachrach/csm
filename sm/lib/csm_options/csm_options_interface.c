#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

/* Cavillo (non impatta la portabilità. */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <string.h>
#include "csm_options.h"

/** User-friendly interface */


struct csm_option* csm_options_allocate(int n) {
	n += 2; /* better safe than sorry */
	struct csm_option* ops = malloc(sizeof(struct csm_option)*n);
	int i; for(i=0;i<n;i++) {
		ops[i].name = 0;
		ops[i].type = (enum option_type) 0xbeef;
		ops[i].desc = 0;
		ops[i].value_pointer = 0;
		ops[i].set_pointer = 0;
	}
	return ops;
}

/* Find next empty slot in the array. XXX farlo meglio */
struct csm_option* csm_options_next_empty(struct csm_option*ops) {
	int i; for(i=0;;i++) {
		if(ops[i].name == 0)
		 return ops+i;
	}
}

char * strdup_(const char *s);

void csm_options_int(struct csm_option*ops, const char* name, int *p, int def_value, const char*desc) {
	struct csm_option* o =  csm_options_next_empty(ops);
	o->name = strdup_(name);
	o->value_pointer = p;
	o->set_pointer = 0;
	o->desc = strdup_(desc);
	o->type = OPTION_INT;
	*p = def_value;
}

void csm_options_alternative(struct csm_option*ops, const char*name, struct csm_option_alternative* alt,
 	int*value, const char*desc) {
	struct csm_option* o =  csm_options_next_empty(ops);
	o->name = strdup_(name);
	o->value_pointer = value;
	o->set_pointer = 0;
	o->desc = strdup_(desc);
	o->type = OPTION_ALTERNATIVE;
	o->alternative = alt;
	*value = alt[0].value;
}


void csm_options_double (struct csm_option*ops, const char* name, double *p, double def_value, const char*desc){
	struct csm_option* o =  csm_options_next_empty(ops);
	o->name = strdup_(name);
	o->value_pointer = p;
	o->set_pointer = 0;
	o->desc = strdup_(desc);
	o->type = OPTION_DOUBLE;
	*p = def_value;
}

void csm_options_string (struct csm_option*ops, const char* name, const char** p,const char*def_value,const char*desc){
	struct csm_option* o =  csm_options_next_empty(ops);
	o->name = strdup_(name);
	o->value_pointer = p;
	o->set_pointer = 0;
	o->desc = strdup_(desc);
	o->type = OPTION_STRING;
	*p = def_value;
}
