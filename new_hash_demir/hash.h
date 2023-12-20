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

class hashT{
public:
	hashT();
	size_t quadProb(size_t originalIndex, int i) const;
	size_t FirstHashIndex(const string& logName) const;
	string read_logs(string linex);
	void insert();
	void printTopTen();
	

private:
	pair<string, int>* HTable; //pointer to the hash table
	ifstream logfile;

};