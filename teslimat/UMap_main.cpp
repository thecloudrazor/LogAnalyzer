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

int main(){
    UMap unordered_map; // Create an instance of the UMap class
    high_resolution_clock::time_point time1 = high_resolution_clock::now(); // Record the start time
    
    unordered_map.to_map(); // Calling the to_map() function implemented in Unordered_map_h.h
    unordered_map.t_print(); // Calling the t_print() function implemented in Unodered_map_h.h

    high_resolution_clock::time_point time2 = high_resolution_clock::now(); // Record the end time
    duration<double> time_span = duration_cast<duration<double>>(time2 - time1); // Calculate the elapsed time

    cout << endl << "Total Elapsed Time: " << time_span.count() << " Seconds" << endl; // Print the total elapsed time
    return 0;
}
