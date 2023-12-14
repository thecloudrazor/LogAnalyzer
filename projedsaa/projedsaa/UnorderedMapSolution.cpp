#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cassert>

using namespace std;
using namespace std::chrono;

string extractSites(string linex) { // read file and return site names

	int start, end;
	start = linex.find("GET ") + 4;
	end = linex.find(" HTTP", start);
	return linex.substr(start, end - start);

}

// bool compareVisitCount(const std::pair<int, std::string>& a, const std::pair<int, std::string>& b) {
//     return a.first > b.first;
// }

int main()
{
    high_resolution_clock::time_point time1 = high_resolution_clock::now(); // This is used for taking the time

    ifstream logfile("access_log"); // Demir: bende acces logu görmemesinin sebebi bilgisayarımda .txt ye çevirmemden kaynaklıymış. Eğer .txt yoksa size kendinize göre değiştirin bu satırı. 
    unordered_map<string, int> visitCounts;
    
    string line;

    /*if (!logfile.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }*/
    
    assert(logfile.is_open()); // if yerine bu kullanılabilir.

    while (getline(logfile, line)) {
        string pageName = extractSites(line);
        visitCounts[pageName]++;    
    }

    cout << "Unique Items: " << visitCounts.size() << endl; // Remove later, used to know the Hashmap size

    logfile.close(); // we don't need to use the log file after reading the unique logs and their count.
      // Transfer to a vector for sorting
    vector<pair<int, string>> visitVector;
    
    // vector<pair<string, int>> visitVector;   // belki kullanılabilir kullanımayacaksa kaldır.
    //for (const auto& pair : visitCounts) { 
    for (const pair<string, int>& pair : visitCounts) {    
        visitVector.emplace_back(pair.second, pair.first); //emplaces the number of times that site visited to first pair, names to second pair. 
    }

    // Sort in descending order of visit count
    // std::sort(visitVector.begin(), visitVector.end(), [](const auto& a, const auto& b) {   // belki kullanılabilir kullanımayacaksa kaldır.
    sort(visitVector.begin(), visitVector.end(), [](const pair<int, string>& a, const pair<int, string>& b) {
        return a.first > b.first;
    });

    //std::sort(visitVector.begin(), visitVector.end(), compareVisitCount);


    // Print the top 10 most visited pages
    std::cout << "Top 10 most visited pages:" << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << visitVector[i].second << " was visited " << visitVector[i].first << " times." << std::endl;
    }

    high_resolution_clock::time_point time2 = high_resolution_clock::now(); 			// This is here to check time
    duration<double> time_span = duration_cast<duration<double>>(time2 - time1); 		// This is here to check time
    std::cout<<endl<< "Total Elapsed Time: " << time_span.count()<<" Seconds"<<endl; 	// This is here to print time
}