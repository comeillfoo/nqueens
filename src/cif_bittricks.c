#include <stdint.h>

uint32_t clear_kth_bit(uint32_t bitmask, uint32_t cleared_bit) {
  return bitmask & ~(1 << cleared_bit);
}

uint32_t set_kth_bit(uint32_t bitmask, uint32_t set_bit) {
  return bitmask | (1 << set_bit);
}

uint32_t flipped_kth_bit(uint32_t bitmask, uint32_t toggled_bit) {
  return bitmask ^ (1 << toggled_bit);
}
