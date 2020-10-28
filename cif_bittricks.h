/* 
 * File:   cif_bittricks.h
 * Author: comeillfoo
 */

#ifndef CIF_BITTRICKS_H
#define CIF_BITTRICKS_H

/**
 * The function that encapsulates the bit trick which resets one particular bit in 32-bit integer
 *
 * @param bitmask sequence of bits in 32-bit integer word which one bit must be cleared in
 * @param cleared_bit the number of bit in bit mask that must be cleared
 * @return new bit mask with the cleared bit on the special position
 */
uint32_t clear_kth_bit(uint32_t bitmask, uint32_t cleared_bit);

/**
 * The function that encapsulates the bit trick which sets one particular bit in 32-bit integer
 *
 * @param bitmask sequence of bits in 32-bit integer word which one of them must be cleared in
 * @param set_bit the number of bit in bitmask (0-31) that must be set
 * @return new bit mask with the set bit on the special position
 */
uint32_t set_kth_bit(uint32_t bitmask, uint32_t set_bit);

/**
 * The function that encapsulates the bit trick which toggles one particular bit (from 1->0 or 0->1) in 32-bit integer
 *
 * @param bitmask sequence of bits in 32-bit integer word which one of them must be toggled in
 * @param toggled_bit the number of bit in bitmask (0-31) that must be toggled
 * @return new bit mask with the toggled bit on the special position
 */
uint32_t flipped_kth_bit(uint32_t bitmask, uint32_t toggled_bit);

#endif /* CIF_BITTRICKS_H */

