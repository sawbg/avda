/**
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Contains declarations of system-independant (universal size) integers
 * and float types, shortened type names for some commonly used types, and
 * enumerations.
 */

#ifndef definitions_H
#define definitions_H

#include <complex>
#include <map>

#define ERROR -1
#define REC_COUNT 8
#define SAMPLE_COUNT 262144
#define SAMPLE_FREQ 48000
#define ENUM signed char

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

/**
 * Defines a type for complex float32's.
 */
typedef std::complex<float32> cfloat32;

/**
 * Contains the calculated results from processing the audio recordings.
 */
typedef struct {
	float32 freq;
	float32 noise;
} DataParams;

/**
 * Contains the maximum value found in an array and the value's index in that
 * array.
 */
typedef struct {
	float32 value;
	uint32 index;
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
