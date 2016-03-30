/**
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Contains declarations of system-independant (universal size) integers
 * and float types, shortened type names for some commonly used types, and
 * enumerations.
 */

#ifndef definitions_H
#define definitions_H

#include <complex>

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
 * A structure containing the calculated results from processing the audio
 * recordings.
 */
typedef struct {

} DataParams;

/**
 * A structure containing information needed in the process() thread.
 */
typedef struct {

} ProcData;

/**
 * This namespace contains all code related to this project.
 */
namespace vaso {
	/**
	 * The side of the head to which a recording pertains.
	 */
	enum class Side { Left, Right };
}

#endif
