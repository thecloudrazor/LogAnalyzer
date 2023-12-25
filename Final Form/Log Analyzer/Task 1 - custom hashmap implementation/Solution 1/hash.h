#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <cassert>
#include <algorithm>

using namespace std;

class hashT {
public:
	hashT(int size); // Constructor with size input. That has a default value aswell.
	
	int quadProb(int originalIndex, int i); // Function for quadratic probing. 
	
	int FirstHashIndex(const string& logName); // Function that generates an index for the given string.
	
	string read_logs(string linex);  // Function that extracts and returns the logs from the access log.
	
	void insert(); // Function for inserting the log entries into the hash function.
	
	void print(); // Prints the top 10 most visited logs.
private:
	vector<pair<string, int>> HTable; // Hash table storing pairs of strings and their counts.
	
	ifstream logfile; // Input file stream for reading log entries.

	int array_size; // Variable that represents the size of the array.
};
   
	// Constructor with size input.
	// We know that we dont't need a default size this big but
	// -in the class we learned that making the size close to 
	// -double the size of the actual size might be more efficient.
hashT::hashT(int size = 30013) : logfile("access_log") { 
	array_size = size;
	HTable.resize(array_size);
}

	// Initial hash function that generates index from a string.
int hashT::FirstHashIndex(const string& logName) { 
	// This will generate an index by adding up the ASCII numbers
	// -and multiplying with a prime number.
	int hash = 0;
	for (char a : logName) {
		hash = 13 * hash + a; 
	}
	return hash % HTable.size();
}

	// Extracts the page name from a log entry.
string hashT::read_logs(string linex) { 
	int start, end;
	start = linex.find("GET ") + 4;
	end = linex.find(" ", start);
	return linex.substr(start, end - start);
}

	// Quadratic probing function.
int hashT::quadProb(int indexX, int probIteration) {
	return (indexX + probIteration * probIteration) % HTable.size();
}
	// Inserts log entries into the hash table using quadratic probing.
void hashT::insert() {
	// Variable to hold the file names.
	string line;
	// Variables for counting the unique file names and holding the index's of strings.
	int index;
	long long unsigned int logCount = 0;
	// int logCount = 0;
	// Assert function to check if logfile opened properly. If not execute program.
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
			logCount++;
		}
		HTable[index].second++;
		if(logCount == HTable.size()){
			cout << "===========================" << endl;
			cout << "ERROR Hash Table is Full." << endl;
			cout << "===========================" << endl;
			return;
		}
	}
	cout << "Unique elements in the hash table: " << logCount << endl;
	cout << "=========================================" << endl;
}

	// Prints the top 10 elements in the hash table.
void hashT::print() {
	// Time Complexity of this std::sort() function is O(Nlog(N)).
	// This std::sort() uses a lambda function to sort the numbers by decending order.
	sort(HTable.begin(), HTable.end(), [](pair<string, int>& a, pair<string, int>& b) { 
		return a.second > b.second;
	});
	// Print the most visited 10 files.
	cout << "Top 10 elements:" << endl;
	for (int i = 0; i < 10; i++) {
		cout << i+1 << ") " << HTable[i].first  << "	" << HTable[i].second << " total visits"<< endl;
	}
}