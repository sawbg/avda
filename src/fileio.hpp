/**PatientName()
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief contains functions related to the file I/O use in this program
 */

#ifndef fileio_H
#define fileio_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "definitions.hpp"
#include <time.h>

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
		uint32 track3 = 0;

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

			if (file.good()) {
				track1 = 1;
			}

			/*
			 * Compares patientname to existing files and lets user know
			 * if the file does not exist.
			 */
			else if (!file.good()) {
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
						std::ofstream createfile(patientname.c_str());
						track1 = 1;
						track2 = 1;
						track3 = 1;
						createfile << CSV_HEADER << std::endl;
						createfile.flush();
						createfile.close();
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
		} while (track1 == 0);

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
		std::map<Side, DataParams> myMap;
		DataParams leftparams;
		DataParams rightparams;

		std::ifstream file(filename.c_str());
		std::string leftline;
		std::string rightline;
		std::string leftsearch = "Left";
		std::string rightsearch = "Right";
		std::string paramstring;
		std::string lfreqstr;
		std::string lnoisestr;
		std::string rfreqstr;
		std::string rnoisestr;
		uint32 lcnt;
		uint32 rcnt;
		float32 lfreqval;
		float32 lnoiseval;
		float32 rfreqval;
		float32 rnoiseval;

		//if statement which uses ifstream function to open patient file (filename)
		if(file.is_open()) {
			//While statement to find the first Left line and save to leftline as string.
			while (getline(file, leftline)) {
				if(leftline.find(leftsearch, 0) != std::string::npos) {
					break;
				}

			}

			//While statement to find first right line and save to rightline as string.
			while (getline(file,rightline)) {
				if(rightline.find(rightsearch, 0) != std::string::npos) {
					break;
				}
			}

			//Code to break leftline and rightline into its parts
			std::stringstream lss(leftline);
			std::stringstream rss(rightline);

			while(getline(lss,paramstring, ',')) {
				lcnt++;

				if(lcnt == 3) {
					lfreqstr = paramstring;
				}

				else if(lcnt == 4) {
					lnoisestr = paramstring;
				}
			}

			while(getline(rss,paramstring, ',')) {
				rcnt++;

				if(rcnt == 3) {
					rfreqstr = paramstring;
				}

				else if(rcnt == 4) {
					rnoisestr = paramstring;
				}
			}

			//Statement to convert lfreq, lnoise, rfreq, and rnoise from strings to floats.
			lfreqval = atof(lfreqstr.c_str());
			lnoiseval = atof(lnoisestr.c_str());
			rfreqval = atof(rfreqstr.c_str());
			rnoiseval = atof(rnoisestr.c_str());

			file.close();
		}

		else {
			std::cout << "The patient file could not be opened." << std::endl;
		}

		leftparams.freq = lfreqval;
		leftparams.noise = lnoiseval;
		rightparams.freq = rfreqval;
		rightparams.noise = rnoiseval;

		myMap[Side::Left] = leftparams;
		myMap[Side::Right] = rightparams;

		return myMap;
	}

	/**
	 * Writes the parameters to the specified file.
	 *
	 * @param params
	 */
	std::string WriteParams(std::map<Side, DataParams>, auto filename) {
		std::ofstream file(filename.c_str());
		time_t measurementtime;	//Gives pointer measurementtime a data type of time_t.
		time(&measurementtime);	//Gets the current time.
		std::map<Side, DataParams> myMap;	//Creating new instance of the map object.

		//if statement to print the Left side parameters to the patient file.
		if(file.is_open()) {
			file << std::string(ctime(&measurementtime)) + "," + "Left" + "," + std::to_string(myMap[Side::Left].freq) 
				+ ", " + std::to_string(myMap[Side::Left].noise) << std::endl;
			file.close();
		}

		//if statement to print the Right side parameters to the patient file.
		if(file.is_open()) {
			file << std::string(ctime(&measurementtime)) + "," + "Right" + "," + std::to_string(myMap[Side::Right].freq) 
				+ ", " + std::to_string(myMap[Side::Right].noise) << std::endl;
			file.close();
		}

		else {
			std::cout << "Patient file can not be opened!" << std::endl;
		}
	}
}

#endif


