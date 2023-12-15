#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include "hashT.h"

using namespace std;
using namespace std::chrono;


string extractSiteName(string linex) { // RSN = read and return site names

	int start, end;
	start = linex.find("GET ") + 4;
	end = linex.find(" HTTP", start);
	return linex.substr(start, end - start);

}

int main() {

    high_resolution_clock::time_point time1 = high_resolution_clock::now(); // This is used for taking the time
    hashT visitCounts(25013); // Adjust the size as needed
    ifstream file("access_log");
    string line;
    // int lineCount = 0; // Counter for debugging

    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    while (getline(file, line)) {
        // cout << "Line " << ++lineCount << ": " << line << endl; // Debugging: print each line
        string pageName = extractSiteName(line);
        // cout << "Inserting: " << pageName << endl; // Debugging statement
        visitCounts.insert(pageName);
    }

    file.close();

    // Collect data from hashT and sort
    vector<pair<string, int>> visitVector;
    for (int i = 0; i < visitCounts.getHTSize(); i++) {
        string pageName;
        int count;
        visitCounts.retrieve(i, pageName, count);
        if (!pageName.empty()) {
            // cout << "Retrieved: " << pageName << " - " << count << endl; // Debugging statement
            visitVector.emplace_back(pageName, count);
        }
    }

    sort(visitVector.begin(), visitVector.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });

    // Print the top 10 most visited pages
    cout << "Top 10 most visited pages:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << visitVector[i].first << " was visited " << visitVector[i].second << " times." << endl;
    }

    high_resolution_clock::time_point time2 = high_resolution_clock::now(); 			// This is here to check time
    duration<double> time_span = duration_cast<duration<double>>(time2 - time1); 		// This is here to check time
    std::cout<<endl<< "Total Elapsed Time: " << time_span.count()<<"Seconds"<<endl; 	// This is here to print time

    return 0;
}
