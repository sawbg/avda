/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @author Nicholas K. Nolan
 * @brief Contains a program to test clearing the stdin buffer. 
 */

#include <iostream>
#include <string>
#include <unistd.h>

#include "definitions.hpp"

#define COUNT 80

using namespace std;
using namespace avda;

/**
 * Tests the ability to clear the stdin buffer. 
 */
int main(int argc, char** argv) {
	char text1[COUNT];
	char text2[COUNT];

	cout << "Enter text to ignore: ";
	cout.flush();
	read(STDIN_FILENO, &text1, COUNT);
//	fflush(stdin);
	cout << endl << "Enter text to print: ";
	cout.flush();
	read(STDIN_FILENO, &text2, COUNT);
	cout << endl << "In buffer: " << text2 << endl;
}
