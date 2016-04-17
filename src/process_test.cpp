/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @author Nicholas K. Nolan
 * @brief 
 */

#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <unistd.h>

#include "definitions.hpp"
#include "process.hpp"

#define COUNT 524228

using namespace std;
using namespace vaso;

/**
 * 
 */
int main(int argc, char** argv) {
	int file = open("/home/pi/etc/audio/test.raw", O_RDONLY);
	float32* buffer = (float32*)malloc(COUNT * sizeof(float32));
	read(file, &buffer, COUNT);
	close(file);

	DataParams params = process(buffer, COUNT, SAMPLE_FREQ);
	free(buffer);
}
