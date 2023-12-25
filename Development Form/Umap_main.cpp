#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cassert>
#include "UMap_deneme.h"

using namespace std;
using namespace std::chrono;

int main()
{
    UMap denemeObj;
    denemeObj.one_cycle();
    return 0;
}
// Taslak olarak böyle yaptım, en basit versiyon bu kullanılabilir hash map header'ı geldiğinde onu inherit yaptırabiliriz kısalır biraz daha. 
// Sebebini analamadım visual studiodan compile edince sorun yok burdan yapınca error alıyorum. Header ve cpp dosyalarını x64 klasörünün içine atmadım bilerek
// access logu deneme amaçlı klasör dışına çıkartıp deneyebilirsiniz. Sorunun çözümünü bulursanız düzenleme yapın.
// Error:
// :Umap_main.cpp:(.text+0x1e): undefined reference to `UMap::UMap()' 
// :Umap_main.cpp:(.text+0x2a): undefined reference to `UMap::one_cycle()'
//  collect2.exe: error: ld returned 1 exit status