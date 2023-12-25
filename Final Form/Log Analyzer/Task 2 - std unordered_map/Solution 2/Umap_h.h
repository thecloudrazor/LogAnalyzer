#pragma once
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cassert>

using namespace std;

class UMap{ 
public:
    UMap(); // Definition of the default constructor.

    string read_logs(string linex); // Definition of the function that reads the file names from the access log. 
    
    void to_map(); // Function to populate the unordered_map with log file entries and their visit counts.
    
    void t_print(); // Function to print the top 10 most visited pages.
    
    unordered_map<string, int> getCount(); // Function to get the visit counts as an unordered_map.

private:
    ifstream logfile; // Input file stream representing the the access log.
    
    vector<pair<int, string>> visitVector; // Vector for sorting log entries based on visit counts.
    
    unordered_map<string, int> visitCounts; // Map to store visit counts for each log entry.
};

    // Default constructor
UMap::UMap() : logfile("access_log") {}

    // Function to read file names from the access log.
string UMap::read_logs(string linex) { 
    int start, end;
    start = linex.find("GET ") + 4;
    end = linex.find(" ", start);
    return linex.substr(start, end - start);
}
    // Function to populate the unordered_map with log file entries and their visit counts.
void UMap::to_map() {
    // Variable to hold the file names.
    string line;
    // Assert function to check if logfile is opened properly. If not, this part gets executed.
    assert(logfile.is_open());
    
    while (getline(logfile, line)) {
        string pageName = read_logs(line);
        visitCounts[pageName]++;
    }
    logfile.close();
}

void UMap::t_print() {
    // Transfer to a vector for sorting
    for (const pair<string, int> pair : visitCounts) {
        visitVector.emplace_back(pair.second, pair.first);
    }
    // Time Complexity of this std::sort() function is O(Nlog(N)).
	// This std::sort() uses a lambda function to sort the numbers by decending order.
    sort(visitVector.begin(), visitVector.end(), [](const pair<int, string>& a, const pair<int, string>& b) {
        return a.first > b.first;
    });
    cout << "Top 10 most visited pages:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << i+1 << ") " << visitVector[i].second << " Count: " << visitVector[i].first << endl;
    }
}

