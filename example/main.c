#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "arithmo.h"

static int process(artm_calc_t* calc, const char* expression);

extern int main(void) {
  artm_calc_t* calc = artm_calc_init(5);
  process(calc, "$t = 2 + 5");
  process(calc, "t");
  process(calc, "$x = 3 + 5 - 29");
  process(calc, "x");
  process(calc, "t * (x - 1)");
  artm_calc_free(calc);
  return 0;
}

static int process(artm_calc_t* calc, const char* expression) {
  artm_result_t result = artm_calc_process(calc, expression);

  switch (result.status) {
    case ARTM_NULL_CALC:
      return printf("[ERROR] NULL_CALC\n");
    case ARTM_NULL_EXPR:
      return printf("[ERROR] NULL_EXPR\n");
    case ARTM_ALLOC_ERR:
      return printf("[ERROR] ALLOC_ERR\n");
    case ARTM_INV_TOKEN:
      return printf("[ERROR] INV_TOKEN\n");
    case ARTM_UNDEF_VAR:
      return printf("[ERROR] UNDEF_VAR\n");
    default:
      return printf("[SUCCESS] %s = %g\n", expression, result.as.value);
  }
}
