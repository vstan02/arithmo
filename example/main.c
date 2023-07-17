#include <stdio.h>

#include "arithmo.h"

static int eval(artm_calc_t* calc, const char* expression);

extern int main(void) {
  artm_calc_t* calc = artm_calc_init(5);
  eval(calc, "$t = 2 + 5");
  eval(calc, "t");
  eval(calc, "$x = 3 + 5 - 29");
  eval(calc, "x");
  eval(calc, "t * (y - 1)");
  eval(calc, "t * (x - 1)");
  artm_calc_free(calc);
  return 0;
}

static int eval(artm_calc_t* calc, const char* expression) {
  artm_result_t result = artm_calc_eval(calc, expression);

  const artm_token_t* token = &result.as.token;
  switch (result.status) {
    case ARTM_NULL_CALC:
      return printf("[ERROR] NULL_CALC\n");
    case ARTM_NULL_EXPR:
      return printf("[ERROR] NULL_EXPR\n");
    case ARTM_ALLOC_ERR:
      return printf("[ERROR] ALLOC_ERR\n");
    case ARTM_INV_TOKEN:
      return printf("[ERROR] INV_TOKEN -> '%.*s'\n", (int) token->size, token->target);
    case ARTM_UNDEF_VAR:
      return printf("[ERROR] UNDEF_VAR -> '%.*s'\n", (int) token->size, token->target);
    default:
      return printf("[SUCCESS] %s = %g\n", expression, result.as.value);
  }
}
