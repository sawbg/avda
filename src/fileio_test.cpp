/**
*@author Samuel Andrew Wisner
*@author Nicholas K. Nolan
*@brief
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "definitions.hpp"
#include "fileio.hpp"
#include "process.hpp"
#include <time.h>

using namespace std;
using namespace vaso;

int main() {
	map<Side, DataParams> laMap = ReadParams(PatientName());
	cout <<  laMap[Side::Left].freq << endl;
}
