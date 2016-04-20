/**
 * @file
 * @author Samuel Andrew Wisner
 * @brief Contains program that tests some functions in fileio.hpp.
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>

#include "definitions.hpp"
#include "fileio.hpp"
#include "process.hpp"

using namespace std;
using namespace avda;

/**
 * Tests the functions in fileio.hpp.
 */
int main() {
	string path = PATIENT_PATH + "wizmack, sammy andy.csv";
	map<Side, DataParams> laMap = ReadParams(path);
	cout <<  laMap[Side::Right].freq << endl;
	cout << laMap[Side::Right].noise << endl;

	WriteParams(laMap, path);
}
