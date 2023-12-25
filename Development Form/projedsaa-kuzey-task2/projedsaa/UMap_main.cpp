#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cassert>
#include "Umap_h.h"
#include "Umap_imp.cpp"

using namespace std;
using namespace std::chrono;

int main()
{
    UMap obj;
    obj.one_cycle();
    return 0;
}
// Taslak olarak böyle yaptım, en basit versiyon bu kullanılabilir hash map header'ı geldiğinde onu inherit yaptırabiliriz kısalır biraz daha. 
