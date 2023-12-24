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
	hashT object;
	UMap unorderedObj;

	high_resolution_clock::time_point time1 = high_resolution_clock::now();
	object.insert();
	object.printTopTen();
	high_resolution_clock::time_point time2 = high_resolution_clock::now(); 	
	unorderedObj.one_cycle();	
	high_resolution_clock::time_point time4 = high_resolution_clock::now(); 	
	duration<double> time_span = duration_cast<duration<double>>(time2 - time1);
	duration<double> time_span1 = duration_cast<duration<double>>(time4 - time1);
	cout << "*====================================================*";
	cout << endl << "Total Elapsed Time in Hash-Map is : " << time_span.count() << "Seconds"; 
	cout << endl << "Total Elapsed Time in Unordered-Map is : " << time_span1.count() << "Seconds" << endl;
	
	return 0;
}

