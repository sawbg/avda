/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @author Nicholas K. Nolan
 * @brief 
 */

#include <iostream>
#include <string>
#include <unistd.h>

#include "definitions.hpp"

#define COUNT 80

using namespace std;
using namespace vaso;

/**
 * 
 * 
 */
int main(int argc, char** argv) {
	char text1[COUNT];
	char text2[COUNT];

	cout << "Enter text to ignore: ";
	cout.flush();
	read(STDIN_FILENO, &text1, COUNT);
	fflush(stdin);
	cout << endl << "Enter text to print: ";
	cout.flush();
	read(STDIN_FILENO, &text2, COUNT);
	cout << endl << "In buffer: " << text2 << endl;
}
