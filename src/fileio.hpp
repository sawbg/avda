/**
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief contains functions related to the file I/O use in this program
 */

#ifndef fileio_H
#define fileio_H

#include <iostream>
#include <string>

#include "definitions.hpp"

namespace vaso {
	/**
	 * Absolute path to the folder containing the patients' data
	 */
	const std::string PATIENT_PATH = "/home/pi/patients/";

	/**
	 * Gets a data-based name to which  the file(s) created in a session to be
	 * saved.
	 *
	 * @return a partial (?) filename for the current session
	 */
	std::string CurrentDataName() {

	}

	/**
	 * Finds the filename of the oldest (i.e., baseline) data is saved.
	 *
	 * @param dir the directory which contains all patient data
	 *
	 * @return the base (?) filename to which all baseline data was saved
	 */
	std::string InitialDataName(auto dir) {

	}

	/**
	 * Prompts a user to enter a first, middle, and last name for a patients and
	 * creates a directory (if necessary) in which all of a patient's data can
	 * be saved.
	 *
	 * Must warn a user if the patient folder does not already exist in order to
	 * prevent missaving data.
	 *
	 * @return the directory under which all patient data is saved
	 */
	std::string PatientName() {

	}

	/**
	 * Reads the previously computated parameters found in the specified
	 * file.
	 *
	 * @param filename the absolute or relative path to the file containing the
	 * patient data to read
	 *
	 * @return the patient parameters read
	 */
	DataParams ReadParams(auto filename) {

	}

	/**
	 * Writes the parameters to the specified file.
	 *
	 * @param params
	 */
	std::string WriteParams(DataParams params, auto filename) {

	}
}

#endif
