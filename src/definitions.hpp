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
 * 
 */
const uint8 DURATION = 6;

/**
 *
 */
const sint8 ERROR = -1;

/**
 * 
 */
const uint8 REC_COUNT = 6;

/**
 * 
 */
const uint32 SAMPLE_COUNT = 262144;

/**
 * 
 */
const uint16 SAMPLE_FREQ = 48000;

/**
 * 
 */
const std::string TEMP_FILE = ".temp";

/**
 *
 */
const uint32 BUFFER_SIZE = SAMPLE_COUNT * sizeof(float32);

// Objective/structural type definitions

/**
 * Defines a type for complex float32's.
 */
typedef std::complex<float32> cfloat32;

/**
 * Contains the calculated results from processing the audio recordings.
 */
typedef struct {
	float32 freq = 0;
	float32 noise = 0;
} DataParams;

/**
 * Contains the maximum value found in an array and the value's index in that
 * array.
 */
typedef struct {
	float32 value = 0;
	uint32 index = 0;
} Maximum;

/**
 * This namespace contains all code related to this project.
 */
namespace vaso {
	/**
	 * The side of the head to which a recording pertains.
	 */
	enum class Side { Left, Right };
}

/**
 * Contains the information needed by the thread that executes the Process()
 * function.
 */
typedef struct {
	float32** data;
	uint8 recCount;
	uint32 sampleCount;
	uint32 sampleFreq;
	uint8* counter;
	std::map<vaso::Side, DataParams> results;
} ThreadParams;

#endif
