#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

string RSN(string linex) { // RSN = read and return site names

	int start, end;
	start = linex.find("GET") + 4;
	end = linex.find(" ", start);
	return linex.substr(start, end - start);
}

int main(){

	ifstream log("access_log");          // This is our way to open the text file [line 42]

	string checkS                            // "checkS" is to get site names (it's been made equal to a value since it is utilized multiple times by the program) [line 43 to 45]
		  ,line;                             // "line" is to get the lines of the text file [line 42 and 43]

	unordered_map<string, int> STK;           // STK = string to keyvalue / this is used to store the amount of visits and names of each site [line 43]
	unordered_map<int , vector<string> > KTS; // KTS = keyvalue to string / this is used to order the values 

	int tenCounter=0                          // "tenCounter" is used to find the biggest value, only print out 10 numbers (the break condition) [line 48 to 82] 
	   ,counter=0							  // "counter" is used to check all values in our map [line 48 to 82]
	   ,checkI=0                              // "checkI" is used to ensure checking is not done than more times the amount of lines in our text file (less than 10 sites) [line 45,49,80]
	   ,ensurer=0;                            // "ensurer" is used to ensure that the same site names are not printed, since all names are stored from 1 to n for each site [line 59,63,71]

	string checkA[10];                        // This array is used to ensure that the same site names are not printed, since all names are stored from 1 to n for each site [line 57 and 66]

	high_resolution_clock::time_point time1 = high_resolution_clock::now(); // This is used for taking the time
	   
		while (getline(log, line)) {         // This while loop is used to put the values to the unordered maps 
			checkS = RSN(line);
			STK[checkS]++;
			KTS[STK[checkS]].push_back(checkS);
			checkI++;
	    }                                     
		
		while (1) {                           // This while loop is used to print top 10 visited sites
			if (counter == checkI ) {					 
				std::cout << "There's less than 10 sites"<<endl;
				break;
			}
			else if  (KTS[counter + 1].size() == tenCounter) { 

				for (int i = 0; i <= 10; i++) {  
					for (int j = 0; j < 10; j++) {
						if (KTS[counter][i] == checkA[j])
						{
							ensurer++;
						}
					}

					if(ensurer==0)
					{
						std::cout << KTS[counter][i] << " " << counter << " of total visits" << endl;
						checkA[tenCounter]= KTS[counter][i];
						tenCounter++;
						counter = 0;
						break;
					}
					ensurer = 0;
				}

			}
			
			counter++;
			if (tenCounter == 10)
			break;
			
		}
		
		high_resolution_clock::time_point time2 = high_resolution_clock::now(); 			// This is here to check time
		duration<double> time_span = duration_cast<duration<double>>(time2 - time1); 		// This is here to check time
		std::cout<<endl<< "Total Elapsed Time: " << time_span.count()<<"Seconds"<<endl; 	// This is here to print time
		return 0;
}
