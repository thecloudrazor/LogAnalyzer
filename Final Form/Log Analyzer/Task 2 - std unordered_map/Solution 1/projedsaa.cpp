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

	ifstream log("access_log");		// Open the access log file for reading.

	string checkS                            // Variables for storing site names and lines from the log file.
		  ,line;

	unordered_map<string, int> STK;           // Map to store the count of visits for each site.
	unordered_map<int , vector<string> > KTS; // Map to order site names based on visit count.

	long long unsigned int tenCounter=0       // Counter for printing only the top 10 sites. 
	   ,counter=0							  // Counter to iterate through all values in the map. 
	   ,checkI=0                              // Counter to ensure checking is not done more times than the number of lines in the text file. 
	   ,ensurer=0;                            // Counter to ensure the same site names are not printed multiple times. 

	string checkA[10];                        // Array to store site names already printed.

	high_resolution_clock::time_point time1 = high_resolution_clock::now(); // Record the start time.
	   
		while (getline(log, line)) {         // Iterate through each line in the log file.
			checkS = RSN(line);
			STK[checkS]++;
			KTS[STK[checkS]].push_back(checkS);
			checkI++;
	    }                                     
		
		while (1) {                           // Iterate to print the top 10 visited sites.
			if (counter == checkI ) {					 // Check if all sites have been processed.
				std::cout << "There's less than 10 sites"<<endl;
				break;
			}
			else if  (KTS[counter + 1].size() == tenCounter) { // Check if the current count matches the desired count for printing.

				for (int i = 0; i <= 10; i++) {  
					for (int j = 0; j < 10; j++) {
						if (KTS[counter][i] == checkA[j])
						{
							ensurer++;
						}
					}

					if(ensurer==0) // If the site name hasn't been printed before, print it.
					{
						std::cout << KTS[counter][i] << " " << counter << " of total visits" << endl;
						checkA[tenCounter]= KTS[counter][i];
						tenCounter++;
						counter = 0; // Reset counters for the next iteration.
						break;
					}
					ensurer = 0; // Reset the ensurer for the next iteration.
				}

			}
			
			counter++;
			if (tenCounter == 10)
			break;
			
		}
		
		high_resolution_clock::time_point time2 = high_resolution_clock::now(); 			// Record the end time.
		duration<double> time_span = duration_cast<duration<double>>(time2 - time1); 		// Calculate elapsed time.
		std::cout<<endl<< "Total Elapsed Time: " << time_span.count()<<"Seconds"<<endl; 	// Print elapsed time.
		return 0;
}
