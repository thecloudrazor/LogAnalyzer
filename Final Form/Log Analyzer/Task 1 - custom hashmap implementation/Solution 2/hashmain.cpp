#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm> // sort function is defined in the <algorithm> header file
#include "hashT.h" // Header file for the hash table implementation

using namespace std;
using namespace std::chrono;

// Function to extract the site name from a log line
string extractSiteName(string linex) { // Read and return site names
	int start, end;
	start = linex.find("GET ") + 4;
	end = linex.find(" ", start);
    
	return linex.substr(start, end - start);
}

int main() {
    // Start a timer to measure the duration of the program
    high_resolution_clock::time_point time1 = high_resolution_clock::now();

    // Initialize the hash table with a specific size
    hashT visitCounts(30013); // Size is a prime number for better hash distribution, load factor is better than 0.5
    ifstream file("access_log"); // Open the log file
    string line;

    // Check if the file is successfully opened
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    // Read each line from the file
    while (getline(file, line)) {
        string pageName = extractSiteName(line);
        visitCounts.insert(pageName); // Insert the site name into the hash table
    }
    

    file.close();

    // Prepare a vector to store and sort the visit counts
    vector<pair<string, int>> visitVector;
    for (int i = 0; i < visitCounts.getHTSize(); i++) {
        string pageName;
        int count;
        visitCounts.retrieve(i, pageName, count); // Retrieve data from the hash table
        if (!pageName.empty()) {
            visitVector.emplace_back(pageName, count); // Add non-empty entries to the vector
        }
    }

    cout << visitVector.size() << " Unique Elements in the hash table."<< endl;
    // Time Complexity of std::sort function is O(Nlog(n))
    // lambda function is used in sort function in order to sort the elements in the vector in descending order.
    sort(visitVector.begin(), visitVector.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });

    // Print the Top 10 most visited pages:
    cout << "Top 10 most visited pages:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << visitVector[i].first << " was visited " << visitVector[i].second << " times." << endl;
    }

    // Stop the timer and calculate the elapsed time
    high_resolution_clock::time_point time2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(time2 - time1);
    std::cout<<endl<< "Total Elapsed Time: " << time_span.count()<<"Seconds"<<endl;

    return 0;
}
