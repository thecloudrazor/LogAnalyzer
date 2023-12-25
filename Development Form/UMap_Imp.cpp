
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cassert>
#include "UMap_deneme.h"

using namespace std;
using namespace std::chrono;

UMap::UMap() : logfile("access_log") {} // Implementation of default constructor that assigns the logfile to "access_log.txt" on the object.

string UMap::read_logs(string linex) {  // Implementation of read_logs function that will take the file names from "acces_log.txt".
    int start, end;
    start = linex.find("GET ") + 4;
    end = linex.find(" HTTP", start);
    return linex.substr(start, end - start);
}

void UMap::to_map() {
    string line;

    assert(logfile.is_open()); // bunun yerine if kullan�labilir. (sonradan kald�r) 

    while (getline(logfile, line)) {
        string pageName = read_logs(line);
        visitCounts[pageName]++;
    }

    cout << "Unique Items: " << visitCounts.size() << endl; // Remove later, used to know the Hashmap size

    logfile.close();
}

void UMap::transfer_sort() {
    // Transfer to a vector for sorting
    for (const pair<string, int>& pair : visitCounts) {
        visitVector.emplace_back(pair.second, pair.first);
    }

    // Sort in descending order of visit count
    sort(visitVector.begin(), visitVector.end(), [](const pair<int, string>& a, const pair<int, string>& b) {
        return a.first > b.first;
        });
}

void UMap::print_topten() {    // Print the top 10 most visited pages
    std::cout << "Top 10 most visited pages:" << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << visitVector[i].second << " was visited " << visitVector[i].first << " times." << std::endl;
    }
}

void UMap::one_cycle() {
    high_resolution_clock::time_point time1 = high_resolution_clock::now(); // This is used for taking the time

    to_map();
    transfer_sort();
    print_topten();

    high_resolution_clock::time_point time2 = high_resolution_clock::now(); 			// This is here to check time
    duration<double> time_span = duration_cast<duration<double>>(time2 - time1); 		// This is here to check time
    std::cout << endl << "Total Elapsed Time: " << time_span.count() << " Seconds" << endl; 	// This is here to print time
}
