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
	hashT object;
	high_resolution_clock::time_point time1 = high_resolution_clock::now(); // This is used for taking the time
	
	object.insert();
	object.print();
	
	high_resolution_clock::time_point time2 = high_resolution_clock::now(); 			// This is here to check time
    duration<double> time_span = duration_cast<duration<double>>(time2 - time1); 		// This is here to check time
    
	cout<<endl<< "Total Elapsed Time: " << time_span.count()<<"Seconds"<<endl; 	// This is here to print time

	return 0;
}

