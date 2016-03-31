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
	// Constants declared
	const uint8 REC_COUNT = 6;
	const uint32 SAMPLE_COUNT = pow(2, 18);
	const uint32 SAMPLE_FREQ = 48000;

	// generate name for patient's file
	string filename = "";//PatientName();

	// TODO: Load all of patient's parameters

	// Record doppler audio
	uint8 counter = 0;  // number of current recording
	float32** buffer;

	for(uint8 i = 0; i < REC_COUNT; i++) {
		buffer[i] = (float32*)malloc(SAMPLE_COUNT * sizeof(float32));
	}
	
	ThreadParams p;
	p.data = buffer;
	p.recCount = REC_COUNT;
	p.sampleCount = SAMPLE_COUNT;
	p.sampleFreq = SAMPLE_FREQ;
	p.counter = &counter;

	pthread_t procThread;
	int retThread = pthread_create(&procThread, NULL, Process, &p);

	if(retThread != 0) {
		cerr << "An error occurred creating the processing thread. "
			"The program will now exit." << endl;
		return ERROR;
	}

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

		counter++;
	}

	// wait for processing thread to finish, then get results
	pthread_join(procThread, NULL);

	// TODO: Print results & probable diagnosis

	// TODO: Write all results to file
	
	// Free all malloc'd memory
	for(uint8 i = 0; i < REC_COUNT; i++) {
		free(buffer[i]);
	}
}
