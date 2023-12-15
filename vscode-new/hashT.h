#ifndef H_Htable
#define H_Htable


#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;



// class hashT {
// public:
//     void insert(const string& pageName);
//     void retrieve(int hashIndex, string& pageName, int& count) const;
// 	int getHTSize() const;

//     hashT(int size = 101);
//     ~hashT();

// private:
//     struct HashItem {
//         string pageName;
//         int count;
//         int status; // 0 = empty, 1 = occupied, -1 = deleted
//     };

//     HashItem *HTable;
//     int HTSize;
// 	int hashFunc(const string& key) const;

//     int findIndex(const string& pageName) const;
// };

// hashT::hashT(int size) : HTSize(size) {
//     HTable = new HashItem[size];
//     for (int i = 0; i < size; i++) {
//         HTable[i].status = 0;
//         HTable[i].count = 0;
//     }
// }

// hashT::~hashT() {
//     delete[] HTable;
// }

// int hashT::hashFunc(const string& key) const {
//     unsigned long hashVal = 0;
//     for (char ch : key) {
//         hashVal = 37 * hashVal + ch;
//     }
//     return hashVal % HTSize;
// }

// void hashT::insert(const string& pageName) {
//     int hashIndex = hashFunc(pageName, HTSize);
//     int originalIndex = hashIndex;
//     int i = 1;

//     while (HTable[hashIndex].status == 1 && HTable[hashIndex].pageName != pageName) {
//         hashIndex = (originalIndex + i * i) % HTSize; // Quadratic probing
//         i++;
//         if (i == HTSize) { // Table is full
//             cerr << "Error: Hash table is full." << endl;
//             return;
//         }
//     }

//     if (HTable[hashIndex].status != 1) {
//         HTable[hashIndex].pageName = pageName;
//         HTable[hashIndex].status = 1;
//     }
//     HTable[hashIndex].count++;
// }

// void hashT::retrieve(int hashIndex, string& pageName, int& count) const {
//     if (HTable[hashIndex].status == 1) {
//         pageName = HTable[hashIndex].pageName;
//         count = HTable[hashIndex].count;
//     } else {
//         pageName = "";
//         count = 0;
//     }
// }


// int hashT::findIndex(const string& pageName) const {
//     int hashIndex = hashFunc(pageName, HTSize);
//     int originalIndex = hashIndex;
//     int i = 1;

//     while (HTable[hashIndex].status != 0 && HTable[hashIndex].pageName != pageName) {
//         hashIndex = (originalIndex + i * i) % HTSize; // Quadratic probing
//         i++;
//         if (i == HTSize) {
//             return -1; // Not found
//         }
//     }

//     if (HTable[hashIndex].status == 1) {
//         return hashIndex;
//     } else {
//         return -1; // Not found
//     }

// int hashT::getHTSize() const {
//     return HTSize;
// }

// }

class hashT {
public:
    hashT(int size = 101);
    ~hashT();

    void insert(const string& pageName);
    void retrieve(int hashIndex, string& pageName, int& count) const;
    int getHTSize() const;

private:
    struct HashItem {
        string pageName;
        int count;
        int status; // 0 = empty, 1 = occupied, -1 = deleted
    };

    HashItem *HTable;
    int HTSize;
    int hashFunc(const string& key) const;
};

hashT::hashT(int size) : HTSize(size) {
    HTable = new HashItem[size];
    for (int i = 0; i < size; i++) {
        HTable[i].status = 0;
        HTable[i].count = 0;
    }
}

hashT::~hashT() {
    delete[] HTable;
}

int hashT::hashFunc(const string& key) const {
    unsigned long hashVal = 0;
    for (char ch : key) {
        hashVal = 37 * hashVal + ch;
    }
    return hashVal % HTSize;
}

void hashT::insert(const string& pageName) {
    int hashIndex = hashFunc(pageName);
    int originalIndex = hashIndex;
    int i = 1;

    while (HTable[hashIndex].status == 1 && HTable[hashIndex].pageName != pageName) {
        hashIndex = (originalIndex + i * i) % HTSize; // Quadratic probing
        i++;
        if (i == HTSize) {
            cerr << "Error: Hash table is full." << endl;
            return;
        }
    }

    if (HTable[hashIndex].status != 1) {
        HTable[hashIndex].pageName = pageName;
        HTable[hashIndex].status = 1;
    }
    HTable[hashIndex].count++;
}
// void hashT::insert(const string& pageName) {
//     cout << "Attempting to insert: " << pageName << endl; // Debugging: Confirm method call

//     int hashIndex = hashFunc(pageName);
//     cout << "Initial hash index: " << hashIndex << endl; // Debugging: Check hash index

//     int originalIndex = hashIndex;
//     int i = 1;

//     while (HTable[hashIndex].status == 1 && HTable[hashIndex].pageName != pageName) {
//         hashIndex = (originalIndex + i * i) % HTSize; // Quadratic probing
//         i++;
//         if (i == HTSize) {
//             cerr << "Error: Hash table is full." << endl;
//             return;
//         }
//     }

//     if (HTable[hashIndex].status != 1) {
//         HTable[hashIndex].pageName = pageName;
//         HTable[hashIndex].status = 1;
//     }
//     HTable[hashIndex].count++;
//     cout << "Inserted: " << pageName << " at index " << hashIndex << endl; // Debugging
// }

void hashT::retrieve(int hashIndex, string& pageName, int& count) const {
    if (HTable[hashIndex].status == 1) {
        pageName = HTable[hashIndex].pageName;
        count = HTable[hashIndex].count;
    } else {
        pageName = "";
        count = 0;
    }
}

int hashT::getHTSize() const {
    return HTSize;
}
#endif