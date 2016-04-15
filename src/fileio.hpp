/**
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
	 * creates a file (if necessary) in which all of a patient's data can
	 * be saved.
	 *
	 * Must warn a user if the patient folder does not already exist in order to
	 * prevent missaving data.
	 *
	 * @return the file under which all patient data is saved
	 */
	std::string PatientName() {
		using namespace std;

		string fname = "";
		string mname = "";
		string lname = "";
		string patfil = "";
		string patientname = "";
		uint32 track1 = 0;
		uint32 track2 = 0;
		ofstream file;

		do {
			cout << "Please enter the patients name." << endl;
			cout << "First name: ";
			getline(cin, fname);
		        cout << "Middle name: ";
		        getline(cin, mname);
			cout << "Last name: ";
			getline(cin, lname);

			patientname = PATIENT_PATH + lname + ", " + fname + " " + mname + ".csv";	//creates new string with path to patient file
			cout << patientname << endl;	//prints out patientname. shows user the path to the patient file
			cout << endl;

			if (!ifstream(patientname)) { //compares patientname to existing files and lets user know if the file does not exist
				do {		//do while statment to continue asking user about the file if their input is not acceptable
					cout << "Patient file does not exist, would you like to create file or re-enter their name?" << endl;
					cout << "  *Type 'create' and press enter key to create the patient file." << endl;
					cout << "  *Type 'reenter' and press enter key to re-enter the patients name." << endl;
					cout << endl;
					getline (cin, patfil);

					if(patfil == "create") {//patfil equals create, track1 and 2  will increase escaping both do while loops
						track1 = 1;
						track2 = 1;
						file.open(patientname);
						file.close();
					}

					else if(patfil == "reenter") {
                               			track1 = 0;
						track2 = 1;
					}

					else {
						cout << endl;
						cout << "Your input is not acceptable." << endl;
						cout << endl;
					}
				}while(track2 == 0);
			}
		}while (track1 = 0);

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
