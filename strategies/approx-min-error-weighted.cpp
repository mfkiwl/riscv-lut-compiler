#include "../strategies.h"

static void _execute(
  LookupTable *lut, WeightsTable *weights, options_t &options) {


}

namespace approx_strategy {
  const record_t MIN_ERROR_WEIGHTED {
    .execute=_execute
  };

};
