#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cassert>
#include "hash.h"
#include "UMap_h.h"

using namespace std;
using namespace std::chrono;

int main() {
	high_resolution_clock::time_point time3 = high_resolution_clock::now(); // This is used for taking the time
	UMap unorderedObj;
	unorderedObj.one_cycle();
	high_resolution_clock::time_point time4 = high_resolution_clock::now(); 			// This is here to check time
	duration<double> time_span1 = duration_cast<duration<double>>(time4 - time3); 		// This is here to check time
	cout << endl << "Total Elapsed Time in Unordered-Map is : " << time_span1.count() << "Seconds" << endl; 	// This is here to print time
	
	cout << "=============================================================" << endl;

	hashT object;
	high_resolution_clock::time_point time1 = high_resolution_clock::now(); // This is used for taking the time
	object.insert();
	object.printTopTen();
	high_resolution_clock::time_point time2 = high_resolution_clock::now(); 			// This is here to check time
	duration<double> time_span = duration_cast<duration<double>>(time2 - time1); 		// This is here to check time
	cout << endl << "Total Elapsed Time in Hash-Map is : " << time_span.count() << "Seconds" << endl; 	// This is here to print time

	return 0;
}

