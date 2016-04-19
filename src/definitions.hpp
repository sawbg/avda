/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Contains declarations of system-independant (universal size) integers
 * and float types, shortened type names for some commonly used types, and
 * enumerations.
 */

#ifndef definitions_H
#define definitions_H

#include <complex>
#include <map>
#include <string>

#define ENUM signed char

// Type definitions

typedef unsigned char byte;
typedef unsigned char uint8;
typedef signed char sint8;

typedef unsigned short uint16;
typedef signed short sint16;

typedef unsigned int uint32;
typedef signed int sint32;

typedef unsigned long long uint64;
typedef signed long long sint64;

typedef float float32;
typedef double float64;


// Constants

/**
 * Threshold for the differential-parameters product to be considered indicative
 * of a vasospasm.
 */
const uint16 DET_THRESH = 5000;

/**
 * Duration of recording in seconds.
 */
const uint8 DURATION = 6;

/**
 * Error integer returned when the program must exit with an error.
 */
const sint8 ERROR = -1;

/**
 * Maximum drop-off frequency considered valid.
 */
const uint16 MAX_DROP_FREQ = 7000;

/**
 * Number of recordings (both left and right) to make.
 */
const uint8 REC_COUNT = 6;

/**
 * Number of samples to use in processing the recordings. Must be a power of
 * two. SAMPLE_COUNT / SAMPLE_FREQ < DURATION must be true.
 */
const uint32 SAMPLE_COUNT = 131072;//262144;

/**
 * Recording sampling rate in Hz (NOT kHz).
 */
const uint16 SAMPLE_FREQ = 24000;

/**
 * Filename of the temporary recording file.
 */
const std::string TEMP_FILE = ".temp";

/**
 * Size of the sample buffer.
 */
const uint32 BUFFER_SIZE = SAMPLE_COUNT * sizeof(float32);


// Objective/structural type definitions

/**
 * Complex float32's.
 */
typedef std::complex<float32> cfloat32;

/**
 * Calculated results from processing the audio recordings.
 */
typedef struct {
	float32 freq = 0;
	float32 noise = 0;
} DataParams;

/**
 * Maximum value found in an array and the value's index in that
 * array.
 */
typedef struct {
	float32 value = 0;
	uint32 index = 0;
} Maximum;


// Enumerations

/**
 * This namespace contains all code related to this project.
 */
namespace avda {
	/**
	 * Side of the head to which a recording pertains.
	 */
	enum class Side { Left, Right };
}


// Doxygen documentation for other files.

/**
 * @file makefile
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Contains recipes for building the test applications, the main
 * application, and the documentation.
 */

/**
 * @file README.md
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Contains the readme text as markdown, which also doubles as the main
 * page.
 */

/**
 * @file doxygen.config
 * @author Samnuel Andrew Wisner, awisner94@gmail.com
 * @brief Contains Doxygen configuration settings.
 */

#endif
