/**
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @author Nicholas K. Nolan
 * @brief contains the functions necessary to perform the mathematical
 * operations required by this program
 * */

#ifndef sigmath_H
#define sigmath_H

#include <complex>
#include <initializer_list>

#include "definitions.hpp"

namespace vaso {
	// PROTOTYPES

	/**
	 * Takes the average of all elements in an array
	 *
	 * @param data the array from which to compute the average
	 *
	 * @param size the number of elements in the data array
	 *
	 * @return the computed average
	 */
	float32 average(float32* data, uint32 size);

	/**
	 * Element-wise averaging along the first dimension of a two-dimensional
	 * array.
	 *
	 * @param data the two-dimensional array containing [count] number of arrays
	 * in the first dimension and [size] number of each elements in the second
	 * dimension
	 *
	 * @param avg the array of size [size] containing the averaged values of
	 * each element
	 *
	 * @param count the number of arrays in the first dimension of data and will
	 * likely be a constant value of 3 in this program
	 *
	 * @param size the number of elements in the second dimension of data
	 */
	void average(float32* data, float32* avg, uint8 count, uint32 size);

	/**
	 * Computes the left-handed first derivative of a discrete signal. The first
	 * element will be 0.
	 *
	 * @param data an array containing the discrete signal data
	 *
	 * @param size the number of elements in data
	 */
	void diff(float32* data, uint32 size);

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

	/**
	 * Computes the magitude of an array of complex numbers.
	 *
	 * @param orig the array of complex numbers
	 *
	 * @param newmags an array to which the magitudes are to be written
	 *
	 * @param size the number of elements in orig and newmags
	 */
	void mag(cfloat32* orig, float32* newmags, uint32 size);

	/**
	 * Finds the maximum value in an array.
	 *
	 * @param data the array whose maximum value is to be found
	 *
	 * @param uint32 size the number of elements in the data array
	 */
	void max(float32* data, uint32 size);

	/**
	 * Applies an nth-order moving-average filter to a discrete signal.
	 *
	 * @param data the array containing the signal to which the filter should be
	 * applied
	 *
	 * @param size the number of elements in the data array
	 *
	 * @param order the order of the filter
	 */
	void smooth(float32* data, uint32 size, uint16 order);

	// DEFINITIONS

	float32 average(float32* data, uint32 size) {

	}

	void average(float32* data, float32* avg, uint8 count, uint32 size) {
		// data is an array. Access like so: data[index]
	}

	void diff(float32* data, uint32 size) {

	}

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

	void mag(cfloat32* orig, float32* newmags, uint32 size) {

	}

	void max(float32* data, uint32 size) {

	}

	void smooth(float32* data, uint32 size, uint16 order) {

	}
}

#endif
