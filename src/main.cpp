/**
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @author Nicholas K. Nolan
 * @brief contains the main program
 */

#include <array>
#include <cstdlib>
#include <iostream>
#include <map>
#include <pthread.h>
#include <string>
#include <unistd.h>

#include "definitions.hpp"
#include "fileio.hpp"
#include "process.hpp"

using namespace std;
using namespace vaso;

/**
 * The main program for this progject. It will detect vasospasms over a period
 * of days.
 */
int main(int argc, char** argv) {
	// generate name for patient's file
	string filename = "";//PatientName();

	// TODO: Load all of patient's parameters

	// Record doppler audio
	float32 buffer[REC_COUNT][SAMPLE_COUNT];
	
	for(uint8 i = 0; i < REC_COUNT; i++) {
		// TODO: Prompt user to press ENTER to start recording

		int retSeek = 0;//fseek(STDIN_FILENO, 0, SEEK_END);
		int retRead = read(STDIN_FILENO, &buffer[i], SAMPLE_COUNT);

		if(retSeek != 0 || retRead < SAMPLE_COUNT) {
			cerr << "An error occurred reading the doppler audio! "
				"The program will now exit." << endl;
			return ERROR;
		}

		// TODO: Print message about recording stopped
	}

	map<Side, DataParams> results = Process(buffer);

	// TODO: Print results & probable diagnosis

	// TODO: Write all results to file
}
