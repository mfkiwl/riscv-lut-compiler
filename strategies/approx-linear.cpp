#include "../strategies.h"

static void _execute(
  LookupTable *lut, WeightsTable *weights, options_t &options) {
  
  // todo: implement

}

namespace approx_strategy {
  const record_t LINEAR {
    .execute=_execute
  };

};