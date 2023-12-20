#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cassert>
#include "hash.h"

using namespace std;
using namespace std::chrono;

const static int array_size = 30000; // eğer bunun çözümünü bulursak sorun yok bu sayıyı sallama giriyorum

hashT::hashT() : logfile("access_log") { // constructor
	HTable = new pair<string, int>[array_size];
}

size_t hashT::FirstHashIndex(const string& logName) const { // stringleri ascii kodlarından index'e çeviriyor.
	size_t hash = 0;
	for (char c : logName) { // burdaki 27 sayısı değiştirlebilir. Kodun hızında değişiklik yapıcaktır 27 de 0.81sn
		hash = 27 * hash + c;
	}
	return hash % array_size;
}

string hashT::read_logs(string linex) { // string return
	int start, end;
	start = linex.find("GET ") + 4;
	end = linex.find(" ", start); // burda "HTTP" yerine " " kullandım
	return linex.substr(start, end - start);
}

size_t hashT::quadProb(size_t indexX, int probIteration) const { // quadratic probing le farklı string aynı index li elemana farklı index veriyor
	return (indexX + probIteration * probIteration) % array_size;
}

void hashT::insert() { 
	string line;
	size_t index;
	assert(logfile.is_open());

	while (getline(logfile, line)) {  
        string pageName = read_logs(line);
        index = FirstHashIndex(pageName);
        int probeIteration = 1;  

        while (HTable[index].first != pageName && !HTable[index].first.empty()) {  //eğer farklı string aynı index girerse bu o stringe boş olan bir index buluyor
            index = quadProb(index, probeIteration);
            probeIteration++;  
        }

        HTable[index].first = pageName;
        HTable[index].second++;
    }
}

 void hashT::printTopTen() { //gpt den aldım değiştirelim yapabiliyorsak
	sort(HTable, HTable + array_size, [](const auto& a, const auto& b) {
		return a.second > b.second; // Sort in descending order
	});
	cout << "Top 10 elements:" << endl;
	for (int i = 0; i < min(10, array_size); i++) {
		cout << "String: " << HTable[i].first << ", Count: " << HTable[i].second << endl;
	}

	delete[] HTable;
 }

int main() {
	hashT denemeOBJ;
	high_resolution_clock::time_point time1 = high_resolution_clock::now(); // This is used for taking the time
	denemeOBJ.insert();
	denemeOBJ.printTopTen();
	high_resolution_clock::time_point time2 = high_resolution_clock::now(); 			// This is here to check time
    duration<double> time_span = duration_cast<duration<double>>(time2 - time1); 		// This is here to check time
    cout<<endl<< "Total Elapsed Time: " << time_span.count()<<"Seconds"<<endl; 	// This is here to print time

	 return 0;
}

