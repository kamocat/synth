#include <stdint.h>

/** Interpolate between points a and b.
 * If the output is fed back into a, this makes 
 * a single-pole low-pass filter
 */
int8_t interpolate(int8_t a, int8_t b, uint8_t mix);

/** Single-pole highpass and lowpass combined into band-pass.
 * y is the array of memory for the filter. Currently 2 deep.
 * x is the latest data
 * cl is the low-pass cutoff
 * ch is the high-pass cutoff
 * @returns filtered data
 */
int8_t bandpass(int8_t * y, int8_t x, uint8_t cl, uint8_t ch);
