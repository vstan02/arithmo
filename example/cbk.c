#include <stdio.h>

#include "arithmo.h"

static void error_cbk(const artm_result_t*, void*);

extern int main(void) {
  artm_calc_t* calc = artm_calc_init(5);

  const char* expression = "$t = 3 + 5";
  double result = artm_calc_cbk_eval(calc, expression, ARTM_CBK(error_cbk, NULL));
  printf("%s = %g\n", expression, result);

  artm_calc_free(calc);
  return 0;
}

static void error_cbk(const artm_result_t* result, __attribute_maybe_unused__ void* payload) {
  const artm_token_t* token = &result->as.token;
  switch (result->status) {
    case ARTM_NULL_CALC:
      printf("[ERROR] NULL_CALC\n");
      break;
    case ARTM_NULL_EXPR:
      printf("[ERROR] NULL_EXPR\n");
      break;
    case ARTM_ALLOC_ERR:
      printf("[ERROR] ALLOC_ERR\n");
      break;
    case ARTM_INV_TOKEN:
      printf("[ERROR] INV_TOKEN -> '%.*s'\n", (int) token->size, token->target);
      break;
    case ARTM_UNDEF_VAR:
      printf("[ERROR] UNDEF_VAR -> '%.*s'\n", (int) token->size, token->target);
      break;
    default: break;
  }
}
