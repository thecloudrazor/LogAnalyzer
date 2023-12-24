#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <cassert>
#include "Umap_h.h"

using namespace std;

int array_size;

class hashT {
public:
	hashT(int size);
	hashT();
	int quadProb(size_t originalIndex, int i);
	int FirstHashIndex(const string& logName);
	string read_logs(string linex);
	void insert();
	void print();
	vector<pair<string, int>> HTable;
private:
	ifstream logfile;
};

hashT::hashT(int size) : logfile("access_log") { // constructor
	if(size < 13000){
		size = 30013;
	}
	array_size = size;
	HTable.resize(array_size);
}

hashT::hashT() : logfile("access_log") {
	array_size = 30013;
	HTable.resize(array_size);
}

int hashT::FirstHashIndex(const string& logName) { 
	size_t hash = 0;
	for (char a : logName) {
		hash = 13 * hash + a; 
	}
	return hash % HTable.size();
}

string hashT::read_logs(string linex) { // string return
	int start, end;
	start = linex.find("GET ") + 4;
	end = linex.find(" ", start);
	return linex.substr(start, end - start);
}

int hashT::quadProb(size_t indexX, int probIteration) { // quadratic probing le farklı string aynı index li elemana farklı index veriyor
	return (indexX + probIteration * probIteration) % HTable.size();
}

void hashT::insert() {
	string line;
	int index;

	assert(logfile.is_open());

	while (getline(logfile, line)) {
		string pageName = read_logs(line);
		index = FirstHashIndex(pageName);
		int probeIteration = 1;

		while (HTable[index].first != pageName && !HTable[index].first.empty()) { 
			index = quadProb(index, probeIteration);
			probeIteration++;
		}
		if (HTable[index].first != pageName && HTable[index].first.empty()) {
			HTable[index].first = pageName;
		}
		HTable[index].second++;
	}
}

void hashT::print() {
	sort(HTable.begin(), HTable.end(), [](pair<string, int>& a, pair<string, int>& b) {
		return a.second > b.second;
	});

}