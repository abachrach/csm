#ifndef H_HSM_INTERFACE
#define H_HSM_INTERFACE

#include <csm_options/csm_options.h>

#include "hsm.h"

struct sm_params;
struct sm_result;

/* Interface of HSM for CSM */
void sm_hsm(struct sm_params* params, struct sm_result* res);

/** Adds csm_options related to HSM */
void hsm_add_csm_options(struct csm_option* ops, struct hsm_params*p);

#endif
