/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Contains a program to test the process() function.
 */

#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <unistd.h>

#include "definitions.hpp"
#include "process.hpp"

#define COUNT 131072

using namespace std;
using namespace avda;

/**
 * Tests the process() function from process.hpp.
 */
int main(int argc, char** argv) {
	int file = open("/home/pi/avda/etc/audio/test.raw", O_RDONLY);

	if(file < 0) {
		cerr << "File unreadable!" << endl;
		return -1;
	}

	float32* buffer = (float32*)malloc(COUNT * sizeof(float32));
	int charRead = read(file, buffer, COUNT * sizeof(float32));

	if(charRead < COUNT) {
		cerr << "Too few bytes read!" << endl;
		return -1;
	}

	close(file);

	DataParams params = process(buffer, COUNT, SAMPLE_FREQ);
	free(buffer);
	cout << "Cutoff: " << params.freq << endl;
	cout << "Noise: " << params.noise << endl;
}
