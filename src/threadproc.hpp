/**
 * @author Samuel Andrew Wisner, awisne94@gmail.com
 * @brief 
 */

#ifndef threadproc_H
#define threadproc_H

#include <pthread.h>

#include "definitions.hpp"

namespace vaso {	
	// PROTOTYPES
	
	/**
	 *
	 */
	void* process(void* procdata);

	/**
	 *
	 */
	void StartProcessing(ProcData procdata);

	// DEFINITIONS
	
	void* processing(void* procdata) {

	}

	void StartProcessing(ProcData procdata) {

	}
}

#endif
