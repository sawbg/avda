/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @author Nicholas K. Nolan
 * @brief Contains the main program.
 * @bug extra newline character inserted into stdin buffer after PatientName()
 * is run
 */

#include <array>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <pthread.h>
#include <string>
#include <unistd.h>

#include "definitions.hpp"
#include "fileio.hpp"
#include "process.hpp"

using namespace std;
using namespace avda;

/**
 * The main program for this project. It will detect avdaspasms over a period
 * of days.
 */
int main(int argc, char** argv) {
	// Recorded audio buffer
	float32* buffer = (float32*)std::malloc(BUFFER_SIZE);
	bool cont = true;  // whether to continue in the recording loop
	DataParams params[REC_COUNT];  // holds DataParam's from recordings
	string filename = PatientName();  // generate name for patient's file
	map<Side, DataParams> results;  // parameters by side

	// arecord command
	const string recCommand = string("arecord -t raw -d ")
		+ to_string(DURATION) + string(" -D plughw:1,0 -f FLOAT -q -r ")
		+ to_string(SAMPLE_FREQ) + string(" ") + TEMP_FILE;

	// Recording
	while(cont) {
		for(uint8 i = 0; i < REC_COUNT; i++) {
			// prompt
			cout << "Press [ ENTER ] to begin analysis for the "
				<< (i < REC_COUNT / 2 ? "left" : "right") << " side, depth #"
				<< (((i >= REC_COUNT / 2) ? (i - REC_COUNT / 2) : i) + 1)
				<< " ";
			getchar();  // wait for ENTER to be pressed
			cout << "Analyzing..." << endl;

			system(recCommand.c_str());
			usleep(DURATION*1000000 + 1500000);  // sleep DURATION + 1.5 seconds

			int file = open(TEMP_FILE.c_str(), O_RDONLY);  // open temp file
			int retRead = read(file, buffer, BUFFER_SIZE);  // copy to buffer
			close(file);  // close temp file
			remove(TEMP_FILE.c_str());  // delete temp file

			// if something goes wrong reading the temp file, program exits
			if(file < 0 || retRead < BUFFER_SIZE) {
				cerr << "An error occurred reading the doppler audio! "
					"The program will now exit." << endl;
				return ERROR;
			}

			// process and store parameters
			params[i] = process(buffer, SAMPLE_COUNT, SAMPLE_FREQ);
			cout << "The analysis is complete." << endl << endl;
		}

		// calculate averaged parameters
		results[Side::Left] = average(params, REC_COUNT / 2);
		results[Side::Right] = average(&params[REC_COUNT / 2], REC_COUNT / 2);

		cout << "Analysis is complete." << endl << endl;

		// print averaged side analysis
		for(int i = 0; i < 2; i++) {
			Side side = (Side)i;
			cout << (side == Side::Left ? "[LEFT]" : "[RIGHT]") << endl;
			cout << "Drop-off frequency: " << (uint16)(results[side].freq + 0.5)
				<< " Hz" << endl;
			cout << "Average relative noiseband power: "
				<< (sint16)(results[side].noise - 0.5) << " dB" << endl <<endl;
		}

		cont = results[Side::Left].freq > MAX_DROP_FREQ
			|| results[Side::Right].freq > MAX_DROP_FREQ;

		if(cont) {
			cout << "An error in aquisition of the doppler audio has occurred! "
				"Ensure the connection from the doppler machine to this device "
				"is secure and the connection uninterruptable." << endl << endl;
		}
	}

	free(buffer);  // free buffer to prevent memory leak
	WriteParams(results, filename);

	// examine likelihood of avdaspasm
	try {
		map<Side, DataParams> baseParams = ReadParams(filename);
		map<Side, bool> comparison;

		for(uint8 i = 0; i < 2; i++) {
			Side side = (Side)i;
			float comp = (results[side].freq - baseParams[side].freq) 
				* (baseParams[side].noise - results[side].noise);
			comparison[side] = comp > DET_THRESH;
		}

		string which;

		if(comparison[Side::Left] && !comparison[Side::Right]) {
			which = "The left";
		} else if(!comparison[Side::Left] && comparison[Side::Right]) {
			which = "The right";
		} else if (comparison[Side::Left] && comparison[Side::Right]) {
			which = "Both";
		} else {
			which = "Neither";
		}

		cout << which << " side seems to show evidence of a vasospasm." << endl;
	} catch(runtime_error ex) {
		cout << "These values will be stored as the baseline parameters to "
			"which all future parameters are compared." << endl;
	}
}
