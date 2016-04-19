/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @author Nicholas K. Nolan
 * @brief contains the main program
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
using namespace vaso;

/**
 * The main program for this project. It will detect vasospasms over a period
 * of days.
 */
int main(int argc, char** argv) {
	const string recCommand = string("arecord -t raw -d ")
		+ to_string(DURATION) + string(" -D plughw:1,0 -f FLOAT -q -r ")
		 + to_string(SAMPLE_FREQ) + string(" ") + TEMP_FILE;
	DataParams params[REC_COUNT];

	string filename = "wizmack, sammy andy.csv";//PatientName();  // generate name for patient's file

	// Recorded audio buffer
	float32* buffer = (float32*)std::malloc(BUFFER_SIZE);

	// Start recording
	for(uint8 i = 0; i < REC_COUNT; i++) {
		cout << "Press [ ENTER ] to begin analysis for the "
			<< (i < REC_COUNT / 2 ? "left" : "right") << " side, depth #"
			<< (((i >= REC_COUNT / 2) ? (i - REC_COUNT / 2) : i) + 1)
			<< "...";
		fflush(stdin);
		getchar();  // wait for ENTER to be pressed
		cout << "Recording..." << endl;

		system(recCommand.c_str());
		sleep(DURATION + 1);

		int file = open(TEMP_FILE.c_str(), O_RDONLY);
		int retRead = read(file, buffer, BUFFER_SIZE);
		close(file);
		remove(TEMP_FILE.c_str());

		if(file < 0 || retRead < BUFFER_SIZE) {
			cerr << "An error occurred reading the doppler audio! "
				"The program will now exit." << endl;
			return ERROR;
		}

		params[i] = process(buffer, SAMPLE_COUNT, SAMPLE_FREQ);
		cout << "The analysis is complete." << endl << endl;
	}

	free(buffer);
	map<Side, DataParams> results;
	results[Side::Left] = average(params, REC_COUNT / 2);
	results[Side::Right] = average(&params[REC_COUNT / 2], REC_COUNT / 2);

	cout << "Analysis is complete." << endl << endl;

	for(int i = 0; i < 2; i++) {
		Side side = (Side)i;
		cout << (side == Side::Left ? "[LEFT]" : "[RIGHT]") << endl;
		cout << "Drop-off frequency: " << (uint16)(results[side].freq + 0.5)
			<< " Hz" << endl;
		cout << "Average relative noiseband power: "
			<< (sint16)(results[side].noise - 0.5) << " dB" << endl <<endl;
	}

	try {
		map<Side, DataParams> baseParams = ReadParams(filename);
		// TODO: Print results & probable diagnosis

	} catch(exception ex) {
		
		// TODO: Write all results to file
	}
	
}
