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