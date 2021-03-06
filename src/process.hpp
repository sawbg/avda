/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Contains functions related to the program's threaded processing of
 * audio data.
 */

#ifndef process_H
#define process_H

#include <map>
#include <stdexcept>

#include "definitions.hpp"
#include "sigmath.hpp"

namespace avda {	
	/**
	 * Analyzes a single recording to determine the drop-off frequency and
	 * average noiseband noise power.
	 *
	 * It should be noted that is algorithm is considered the intellectual
	 * property of Andrew Wisner and Nicholas Nolan. The "algorithm" is defined
	 * as the use of 1) the frequency drop-off and/or 2) a noise value from the 
	 * frequency band above the drop-off frequency in order to diagnose (with or
	 * without other factors and parameters) the presence of a avdaspasm in a
	 * patient. By faculty members and/or students in the UAB ECE department
	 * using this algorithm, they agree that the presentation of their code or
	 * project that uses this algorithm, whether verbally or in writing, will 
	 * reference the development of the initial algorithm by Andrew Wisner and
	 * Nicholas Nolan. Furthermore, a failure to meet this stipulation will
	 * warrant appropriate action by Andrew Wisner and/or Nicholas Nolan. It
	 * should be understood that the purpose of this stipulation is not to
	 * protect prioprietary rights; rather, it is to help ensure that the
	 * intellectual property of the algorithm's creators is protected and is
	 * neither misrepresented nor claimed implicitly or explicitly by another
	 * individual.
	 *
	 * @param data array containing float32 samples of audio
	 *
	 * @param size number of samples in each recording. MUST be a power of two.
	 *
	 * @param samplingRate sampling frequency in Hz or Samples/second
	 *
	 * @return cut-off frequency (Hz) and average noiseband noise power in
	 * decibels
	 */
	DataParams process(float32* data, uint32 size, float32 samplingRate) {
		if((size & (size - 1) != 0) || size < 2) {
			throw std::invalid_argument(
					"The number of samples is not a power of two!");
		}

		// declare function-scoped variables
		uint32 freqSize = size / 2;
		cfloat32* cdata = (cfloat32*)std::malloc(size * sizeof(cfloat32));
		float32* fdata = (float32*)std::malloc(freqSize * sizeof(float32));
		float32* origdata = (float32*)std::malloc(freqSize * sizeof(float32));

		// convert data to complex numbers for fft()
		for(uint32 i = 0; i < size; i++) {
			cdata[i] = data[i];
		}
	
		// find frequency spectrum in relative decibels
		fft(cdata, size);
		mag(cdata, fdata, freqSize);
		Maximum maximum = max(fdata, freqSize);

		for(uint32 i = 0; i < freqSize; i++) {
			fdata[i] /= maximum.value;
		}

		decibels(fdata, freqSize);

		for(uint32 i = 0; i < freqSize; i++) {
			origdata[i] = fdata[i];
		}

		/*
		 * Run spectrum values through moving-average filter to smooth the
		 * curve and make it easier to determine the derivative.
		 */
		smooth(fdata, freqSize, 20);

		/*
		 * Find the derivative of the smoothed spectrum. Bote that both this
		 * filter and the previous are necessary to the algorithm.
		 */
		diff(fdata, freqSize);
		smooth(fdata, freqSize, 100);
		absolute(fdata, freqSize);

		// find the parameters of this specific recording
		uint16 offset = 1000;
		absolute(&fdata[offset], freqSize - offset);
		maximum = max(&fdata[offset], freqSize - offset);
		uint32 index = maximum.index + offset;
		
		DataParams params;
		params.freq = index * (float)SAMPLE_FREQ / freqSize / 2;
		params.noise = average(&origdata[index + offset],
				freqSize - offset - index);

		free(cdata);
		free(fdata);

		return params;
	}
}

#endif
