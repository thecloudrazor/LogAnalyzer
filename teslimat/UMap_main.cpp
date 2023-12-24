#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cassert>
#include "Umap_h.h"

using namespace std;
using namespace std::chrono;

int main()
{
    UMap obj;
    high_resolution_clock::time_point time1 = high_resolution_clock::now(); // This is used for taking the time
    obj.to_map();
    obj.t_print();
    high_resolution_clock::time_point time2 = high_resolution_clock::now(); 			// This is here to check time
    duration<double> time_span = duration_cast<duration<double>>(time2 - time1); 		// This is here to check time
    std::cout << endl << "Total Elapsed Time: " << time_span.count() << " Seconds" << endl; 	// This is here to print time
    return 0;
}
