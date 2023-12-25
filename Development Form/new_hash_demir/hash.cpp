#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <cassert>
#include "hash.h"

using namespace std;
using namespace std::chrono;

int main() {
	hashT hash_map;	// Create an instance of the hashT class
	high_resolution_clock::time_point time1 = high_resolution_clock::now();	// Record the start time
	
	hash_map.insert(); // Calling the insert() function implemented in hash.h
	hash_map.print(); // Calling the print() function implemented in hash.h
	
	high_resolution_clock::time_point time2 = high_resolution_clock::now(); // Record the end time
    duration<double> time_span = duration_cast<duration<double>>(time2 - time1); // Calculate the elapsed time
    
	cout<<endl<< "Total Elapsed Time: " << time_span.count()<<"Seconds"<<endl;	// Print the total elapsed time

	return 0;
}

