/**
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief 
 * */

#ifndef sigmath_H
#define sigmath_H

#include <complex>

#include "definitions.hpp"

namespace vaso {

	/**
	 * Replaces the values of an array of cfloat32's with the array's DFT using
	 * a decimation-in-frequency algorithm.
	 *
	 * This code is based on code from
	 * http://rosettacode.org/wiki/Fast_Fourier_transform#C.2B.2B.
	 *
	 * @param data the array whose values should be replaced with its DFT
	 *
	 * @param size the number of elements in the data array
	 */
	void fft(cfloat32* data, uint32 size);

	void fft(cfloat32* data, uint32 size) {
		// DFT
		uint32 k = size;
		uint32 n;
		float32 thetaT = M_PI / size;
		cfloat32 phiT(cos(thetaT), sin(thetaT));
		cfloat32 T;

		while(k > 1) {
			n = k;
			k >>= 1;
			phiT = phiT * phiT;
			T = 1.0L;

			for(uint32 l = 0; l < k; l++) {
				for(uint32 a = l; a < size; a += n) {
					uint32 b = a + k;
					cfloat32 t = data[a] -data[b];
					data[a] +=data[b];
					data[b] = t * T;
				}

				T *= phiT;
			}
		}

		// Decimate
		uint32 m = (uint32)log2(size);

		for(uint32 a = 0; a < size; a++) {
			uint32 b = a;

			// Reverse bits
			b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
			b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
			b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
			b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
			b = ((b >> 16) | (b << 16)) >> (32 - m);

			if (b > a)
			{
				cfloat32 t = data[a];
				data[a] =data[b];
				data[b] = t;
			}
		}
	}
}

#endif
