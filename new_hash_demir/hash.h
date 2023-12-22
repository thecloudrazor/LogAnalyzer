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
	int quadProb(size_t originalIndex, int i);
	int FirstHashIndex(const string& logName);
	string read_logs(string linex);
	void insert();
	void printTopTen();
	~hashT();
private:
	pair<string, int>* HTable; //pointer to the hash table
	ifstream logfile;
};

int array_size = 14000; // eğer bunun çözümünü bulursak sorun yok bu sayıyı sallama giriyorum

hashT::~hashT(){
	delete []HTable;
}

hashT::hashT() : logfile("access_log") { // constructor
	HTable = new pair<string, int>[array_size];
}

int hashT::FirstHashIndex(const string& logName) { // stringleri ascii kodlarından index'e çeviriyor. loopu gpt den aldım sayıyı değiştirdim
	size_t hash = 0;
	for (char a : logName) { // burdaki 13 sayısı değiştirlebilir. Kodun hızında değişiklik yapıcaktır asal sayı olursa unique değer bulma olasılığı daha fazla olucak 
		hash = 13 * hash + a; // bu sayede collision daha hızlı engellenicek
	}
	return hash % array_size;
}

string hashT::read_logs(string linex) { // string return
	int start, end;
	start = linex.find("GET ") + 4;
	end = linex.find(" ", start); 
	return linex.substr(start, end - start);
}

int hashT::quadProb(size_t indexX, int probIteration) { // quadratic probing le farklı string aynı index li elemana farklı index veriyor
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
		if(HTable[index].first != pageName && HTable[index].first.empty()){
			HTable[index].first = pageName;	
		}
        HTable[index].second++;
    }
}

 void hashT::printTopTen() { //gpt den aldım değiştirelim yapabiliyorsak
	sort(HTable, HTable + array_size, [](const auto& a, const auto& b) {
		return a.second > b.second; // Sort in descending order
	});
	cout << "Top 10 elements:" << endl;
	for (int i = 0; i < 10; i++) {
		cout << "String: " << HTable[i].first << " Count: " << HTable[i].second << endl;
	}
 }