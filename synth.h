#include <stdint.h>
void synth_init(void);

/** Outputs a tone point-by-point.
 * Uses internal state for storage, in classic embedded fasion
 */
int8_t synth(void);

/** Computes the next step in the circle
 * assumes x and y range between -120 and 120.
 * Works best when dx is at least 2.
 */
int8_t minsky(int8_t *x, int8_t *y, int8_t dt);

/** Creates a triangle wave rather than a sine wave
 */
int8_t triangle(int8_t *x, int8_t *y, int8_t dt);

/** Multiplies two 8-bit integers as if they were 1.7 fixed-point
 */ 
int8_t mul8(int8_t a, int8_t b);
