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

class UMap {  // class for Unordered_Map Solution (Hash map class� a��ld�ktan sonra inherit edilebilir).
public:
    UMap(); // Definition of default constructor.
    string read_logs(string linex); // Definition of the function that reads the file names from "acces_log.txt". 
    void to_map();
    void transfer_sort();
    void print_topten();
    void one_cycle();
private:
    ifstream logfile; // this will be our access_log
    unordered_map<string, int> visitCounts; // this will hold the information about which log visited how many times.
    vector<pair<int, string>> visitVector; // this will be the vector to get sorted at the end.
};

UMap::UMap() : logfile("access_log") {} // Implementation of default constructor that assigns the logfile to "access_log.txt" on the object.

string UMap::read_logs(string linex) {  // Implementation of read_logs function that will take the file names from "acces_log.txt".
    int start, end;
    start = linex.find("GET ") + 4;
    end = linex.find(" ", start);
    return linex.substr(start, end - start);
}

void UMap::to_map() {
    string line;

    assert(logfile.is_open());

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
    to_map();
    transfer_sort();
    print_topten();
}
