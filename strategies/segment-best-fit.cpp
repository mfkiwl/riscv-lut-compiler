#include "../strategies.h"

static uint32_t _subdivide_main(
  LookupTable *lut, WeightsTable *weights, 
  const options_t &options, uint32_t first, uint32_t last,
  uint32_t max_count) {
  
  // todo: implement

  return 0;
}

namespace segment_strategy {
  const record_t BEST_FIT {
    .subdivide=_subdivide_main
  };

};
