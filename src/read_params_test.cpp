/**
 * @file
 * @author Samuel Andrew Wisner, awisner94@gmail.com
 * @brief Contains a program test the PatientName() function.
 */

#include <string>

#include "fileio.hpp"

using namespace std;
using namespace avda;

/**
 * Tests the PatientName() function in fileio.hpp.
 */
int main(int argc, char** argv) {
	string filename = PatientName();
	cout << filename;
}
