
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

string RSN(string HHH) { // RSN = read and return site name

	int start, end;
	start = HHH.find("GET") + 4;
	end = HHH.find("HTTP", start) - 1;
	return HHH.substr(start, end - start);

}



int main(){

	ifstream log("access_log.txt");          // This is our way to open the text file [line 42]

	string check                             // "check" is to get site names, since it is used multiple times, it's been made equal to a value [line 43 to 45]
		  ,line;                             // "line" is to get the lines of the text file [line 42 and 43]

	unordered_map<string, int> STK;           // STK = string to keyvalue / this is used to store the amount of visits and names of each site [line 43]
	unordered_map<int , vector<string> > KTS; // KTS = keyvalue to string / this is used to order the values 

	int xc =0                                 // xc is used to find the biggest value, only print out 10 numbers (our break condition) [line 48 to 82] 
	   ,kc=0								  // kc is there to check all values in our map [line 48 to 82]
	   ,x=0                                   // x is there so we don't check more times that line in our text file (less than 10 sites) [line 45,49,80]
	   ,a=0;                                  // a is used to ensure that the same site names are not printed, since we store all names from 1 to n for each site [line 59,63,71]

	string checkA[10];                        // this array is used to ensure that the same site names are not printed, since all names are stored from 1 to n for each site [line 57 and 66]

	high_resolution_clock::time_point time1 = high_resolution_clock::now(); // this is for taking the time
	   
		while (getline(log, line)) {         // this while is to put the values to the unordered maps
			check = RSN(line);
			STK[check]++;
			KTS[STK[check]].push_back(check);
			x++;
	    }                                     
		
		while (1) {                           // this while is for printing top 10 visited sites
			if (kc == x ) {					 
				std::cout << "theres less than 10 sites"<<endl;
				break;
			}
			else if  (KTS[kc + 1].size() == xc) { 

				for (int i = 0; i <= 10; i++) {  
					for (int j = 0; j < 10; j++) {
						if (KTS[kc][i] == checkA[j])
						{
							a++;
						}
					}

					if(a==0)
					{
						std::cout << KTS[kc][i] << " " << kc << " of total visits" << endl;
						checkA[xc]= KTS[kc][i];
						xc++;
						kc = 0;
						break;
					}
					a = 0;
				}

				
			}
			
			kc++;
			if (xc == 10)
			break;
			x++;
			
		}
		
		high_resolution_clock::time_point time2 = high_resolution_clock::now(); // to check time
		duration<double> time_span = duration_cast<duration<double>>(time2 - time1); // to check time
		std::cout<<endl<< "Total Elapsed Time : " << time_span.count()<<"Seconds"<<endl; // to print time
		return 0;
}
