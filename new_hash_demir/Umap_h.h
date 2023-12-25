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

class UMap{  // class for Unordered_Map Solution (Hash map class� a��ld�ktan sonra inherit edilebilir).
public:
    UMap(); // Definition of default constructor.
    string read_logs(string linex); // Definition of the function that reads the file names from "acces_log.txt". 
    void to_map();
    void t_print();
    void print_topten();
    // void one_cycle();
    unordered_map<string, int> getCount();
private:
    ifstream logfile; // this will be our access_log
    vector<pair<int, string>> visitVector; // this will be the vector to get sorted at the end.
    unordered_map<string, int> visitCounts; // this will hold the information about which log visited how many times.
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
    logfile.close();
}

void UMap::t_print() {
    // Transfer to a vector for sorting
    for (const pair<string, int>& pair : visitCounts) {
        visitVector.emplace_back(pair.second, pair.first);
    }
    // Sort in descending order of visit count
    sort(visitVector.begin(), visitVector.end(), [](const pair<int, string>& a, const pair<int, string>& b) {
        return a.first > b.first;
    });
    cout << "Top 10 most visited pages:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << visitVector[i].second << " was visited " << visitVector[i].first << " times." << endl;
    }
}

// void UMap::one_cycle() {
//     to_map();
//     t_print();
// }
