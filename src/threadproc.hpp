/**
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief contains functions related to the program's threaded processing of
 * audio data
 */

#ifndef threadproc_H
#define threadproc_H

#include <pthread.h>

#include "definitions.hpp"

namespace vaso {	
	// PROTOTYPES
	
	/**
	 * Computes recording parameters in a separate thread in a thread-safe
	 * manner. Automatically waits for each recording to finish before
	 * processing it. This file is meant to be called ONLY from the
	 * StartProcessing() function.
	 *
	 * @param procdata a struct containing the values necessary to processing
	 * the audio
	 *
	 * @return a (void) pointer to a DataParams struct containing the computed
	 * parameters for a patient
	 */
	void* process(void* procdata);

	/**
	 * Begins processing the recorded data. Should be called before or
	 * immediately after the first recording.
	 *
	 * @param proxdata a struct containing the values necessary to processing
	 * the audio
	 */
	void StartProcessing(ProcData procdata);

	// DEFINITIONS
	
	void* process(void* procdata) {

	}

	void StartProcessing(ProcData procdata) {

	}
}

#endif
