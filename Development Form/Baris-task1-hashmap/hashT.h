#ifndef H_Htable
#define H_Htable

#include <iostream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

class hashT {
public:
    // Constructor with a default size of 30013. We use a prime number for better hash distribution.
    hashT(int size = 30013);
    // Destructor to deallocate memory
    ~hashT();
    // Function to insert a page name into the hash table
    void insert(const string& pageName);
    // Function to retrieve the count of a page name at a given hash index
    void retrieve(int hashIndex, string& pageName, int& count) const;
    // Function to get the size of the hash table
    int getHTSize() const;

private:
     // Structure to represent an item in the hash table
     struct HashItem {
        string pageName; // The key (page name)
        int count;      // The value (count of visits)
        int status;     // 0 = empty, 1 = occupied, -1 = deleted
    };

    HashItem *HTable; // Pointer to the array of hash items
    int HTSize;       // Size of the hash table
    // Hash function to compute the index for a given key
    int hashFunc(const string& key) const;
};

// Constructor implementation
hashT::hashT(int size) : HTSize(size) {
    HTable = new HashItem[size]; // Allocate memory for the hash table
    for (int i = 0; i < size; i++) {
        HTable[i].status = 0; // Initialize all hash items as empty
        HTable[i].count = 0;
    }
}

// Destructor implementation
hashT::~hashT() {
    delete[] HTable;
}

// Hash function implementation
int hashT::hashFunc(const string& key) const {
    unsigned long hashVal = 0;
    for (char ch : key) {
        hashVal = 37 * hashVal + ch; // Compute the hash value
    }
    return hashVal % HTSize; // Return the index within the table size using modulus operator
}

// Insert function implementation
void hashT::insert(const string& pageName) {
    int hashIndex = hashFunc(pageName); // Compute the initial hash index
    int originalIndex = hashIndex;
    int i = 1;

    // Quadratic probing in case of collision
    while (HTable[hashIndex].status == 1 && HTable[hashIndex].pageName != pageName) {
        hashIndex = (originalIndex + i * i) % HTSize; // // Compute the new index with Quadratic probing
        i++;
        if (i == HTSize) {
            cerr << "Error: Hash table is full." << endl;
            return; // Exit if the table is full
        }
    }

    // Insert or update the hash item
    if (HTable[hashIndex].status != 1) {
        HTable[hashIndex].pageName = pageName;
        HTable[hashIndex].status = 1;
    }
    HTable[hashIndex].count++;
}

// Retrieve function implementation
void hashT::retrieve(int hashIndex, string& pageName, int& count) const {
    if (HTable[hashIndex].status == 1) {
        pageName = HTable[hashIndex].pageName; // Retrieve the page name
        count = HTable[hashIndex].count;       // Retrieve the count

    } else {
        pageName = ""; // Return empty string if the item is not found
        count = 0;
    }
}

// Function to get the size of the hash table
int hashT::getHTSize() const {
    return HTSize;
}
#endif