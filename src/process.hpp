/**
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief contains function()s related to the program's threaded processing of
 * audio data
 */

#ifndef process_H
#define process_H

#include <map>
#include <stdexcept>

#include "definitions.hpp"
#include "sigmath.hpp"

namespace vaso {	
	/**
	 * Processes the recorded audio. Meant to be run in a separate thread as the
	 * recordings are being made. This function assumes that the left-side
	 * recordings will be made first.
	 *
	 * It should be noted that is algorithm is considered the intellectual
	 * property of Andrew Wisner and Nicholas Nolan. The "algorithm" is defined
	 * as the use of 1) the frequency drop-off and/or 2) a noise value from the 
	 * frequency band above the drop-off frequency in order to diagnose (with or
	 * without other factors and parameters) the presence of a vasospasm in a
	 * patient. By faculty members and/or students in the UAB ECE department
	 * using this algorithm, they agree that the presentation of their code or
	 * project that uses this algorithm by anyone directly or indirectly related
	 * to the code or project, whether verbally or in writing, will reference
	 * the development of the initial algorithm by Andrew Wisner and Nicholas
	 * Nolan. Furthermore, a failure to meet this stipulation will warrant
	 * appropriate action by Andrew Wisner and/or Nicholas Nolan. It should be
	 * understood that the purpose of this stipulation is not to protect
	 * prioprietary rights; rather, it is to help ensure that the intellectual
	 * property of the aforementioned is protected and is neither misrepresented
	 * nor claimed implicitly or explicitly by another individual. 
	 *
	 * @return a map of the averaged left- and right-side parameters in
	 * DataParams structures
	 */
	void* Process(void* params) {
		// redeclare structure
		ThreadParams* p = (ThreadParams*)params;

		// just in case p->sampleCount isn't a power of two
		if((p->sampleCount & (p->sampleCount - 1) != 0) || p->sampleCount < 2) {
			throw std::invalid_argument(
					"The number of samples is not a power of two!");
		}

		// declare function-scoped variables
		uint32 freqSize = p->sampleCount / 2;
		cfloat32 cdata[p->recCount][p->sampleCount];
		float32 fdata[p->recCount][freqSize];
		DataParams tempParams[p->recCount];

	

		// calculate the parameters for each side to be returned
		std::map<Side, DataParams> sideParams;
		p->results[Side::Left] = average(&tempParams[0], p->recCount / 2);
		p->results[Side::Right] = average(&tempParams[p->recCount / 2],
				p->recCount / 2);
		return nullptr;
	}
}

#endif
