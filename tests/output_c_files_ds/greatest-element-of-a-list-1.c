#include <assert.h>

float max(unsigned int count, float values[]) {
     assert(count > 0);
     unsigned int idx;
     float themax = values[0];
     for(idx = 1; i < count; ++idx) {
          themax = values[idx] > themax ? values[idx] : themax;
     }
     return themax;
}
