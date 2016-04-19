/**
 * @file
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
 * The main program for this project. It will detect vasospasms over a period
 * of days.
 */
int main(int argc, char** argv) {
	// generate name for patient's file
	string filename = PatientName();
	DataParams params[REC_COUNT];

	// Record doppler audio
	float32* buffer = (float32*)std::malloc(SAMPLE_COUNT * sizeof(float32));

	for(uint8 i = 0; i < REC_COUNT; i++) {
		cout << "Press [ ENTER ] to begin recording for the "
			<< (i < REC_COUNT / 2 ? "left" : "right") << " side, depth #"
			<< (((i >= REC_COUNT / 2) ? (i - REC_COUNT / 2) : i) + 1)
			<< endl;

		system((string("arecord -t raw -d ") << DURATION
				<< " -D plughw:1,0 -f FLOAT -r " << SAMPLE_RATE
				<< " " << TEMP).c_str());
		sleep(DURATION + 1);

		int file = open(TEMP, O_RDONLY);
		int retRead = read(file, &buffer, SAMPLE_COUNT * sizeof(float32));

		if(file != 0 || retRead < SAMPLE_COUNT) {
			cerr << "An error occurred reading the doppler audio! "
				"The program will now exit." << endl;
			return ERROR;
		}

		params[i] = process(buffer, SAMPLE_COUNT, SAMPLE_FREQ);
		cout << "The recording is complete." << endl << endl;
	}

	free(buffer);
	map<Side, DataParams> results;
	results[Side::Left] = average(params, REC_COUNT / 2);
	resutls[Side::Right] = average(&params[REC_COUNT / 2], REC_COUNT / 2);

	cout << "Analysis is complete." << endl << endl;

	for(int i = 0; i < 2; i++) {
		Side side = (Side)i;
		cout << (side == Side::Left ? "[LEFT]" : "[RIGHT]") << endl;
		cout << "Drop-off frequency: " << (uint16)(results[side].freq + 0.5)
			<< " Hz" << endl;
		cout << "Average relative noiseband power: "
			<< (uint16)(results[side].noise + 0.5) << " dB" << endl;
	}

	try {
		DataParams baseParams = ReadParams(filename);
		// TODO: Print results & probable diagnosis

	} catch(exception ex) {
		
		// TODO: Write all results to file
	}
	
}
