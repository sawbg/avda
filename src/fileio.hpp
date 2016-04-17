/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief contains functions related to the file I/O use in this program
 */

#ifndef fileio_H
#define fileio_H

#include <iostream>
#include <string>
#include <fstream>

#include "definitions.hpp"

namespace vaso {
	/**
	 * First line of CSV data file, which declares columns.
	 */
	const std::string CSV_HEADER = "Time,Side,Frequency,Noise Level";

	/**
	 * Absolute path to the folder containing the patients' data
	 */
	const std::string PATIENT_PATH = "/home/pi/patients/";

	/**
	 * Prompts a user to enter a first, middle, and last name for a patients and
	 * creates a file (if necessary) in which all of a patient's data can
	 * be saved.
	 *
	 * Must warn a user if the patient folder does not already exist in order to
	 * prevent missaving data.
	 *
	 * @return the file under which all patient data is saved
	 */
	std::string PatientName() {
		std::string fname = "";
		std::string mname = "";
		std::string lname = "";
		std::string patfil = "";
		std::string patientname = "";
		uint32 track1 = 0;
		uint32 track2 = 0;

		do {
			std::cout << "Please enter the patients name." << std::endl;
			std::cout << "First name: ";
			std::cin >> fname;
			std::cout << "Middle name: ";
			std::cin >> mname;
			std::cout << "Last name: ";
			std::cin >> lname;

			// creates new std::string with path to patient file
			patientname = PATIENT_PATH + lname + ", " + fname
				+ " " + mname + ".csv";

			// prints out patientname. shows user the path to the patient file
			std::cout << patientname << std::endl << std::endl;
			std::ifstream file(patientname.c_str());

			/*
			 * Compares patientname to existing files and lets user know
			 * if the file does not exist.
			 */
			if (!file.good()) {
				/* 
				 * Do while statement to continue asking user about the file
				 * if their input is not acceptable
				 */ 
				do {
					std::cout << "Patient file does not exist, would you like "
						"to create file or re-enter their name?" << std::endl;
					std::cout << "  *Type 'create' and press enter key "
						"to create the patient file." << std::endl;
					std::cout << "  *Type 'reenter' and press enter key "
						"to re-enter the patients name." << std::endl;
					std::cout << std::endl;
					std::cin >> patfil;

					/* 
					 * patfil equals create, track1 and 2 will increase
					 * escaping both do while loops
					 */
					if(patfil == "create") {
						track1 = 1;
						track2 = 1;
						file.open(patientname);
						file.close();
					}

					/*
					*patfil equals renter, track1 will remain zero allowing
					*user to reenter the patient name.
					*/
					else if(patfil == "reenter") {
						track1 = 0;
						track2 = 1;
					}

					/*
					*The users input was neither create or reenter. User
					*must enter patient name again.
					*/
					else {
						std::cout << std::endl;
						std::cout << "Your input is not acceptable." << std::endl;
						std::cout << std::endl;
					}
				}while(track2 == 0);
			}
		} while (track1 = 0);

		return patientname;	//returns the path to the patient file
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
	std::map<Side, DataParams> ReadParams(auto filename) {
		DataParams par;
		std::ifstream file(filename.c_str());
		std::string line;
		//if statement which uses ifstream function to open patient file (filename)
		if(file.is_open()) {
			std::getline(file, line);
		}

		else {
			std::cout << "The patient file could not be opened." << std::endl;
		}

		std::map<Side, DataParams> myMap;
		DataParams myParams;
		myMap[Side::Left] = myParams;

		std::par = line;
		return par;
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

