//smith.cc
//Y00794471 - Rabin Thapa

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "SmithCounter.h"

using namespace std;

//takes an integer and return it with bits high_bit_index through low_bit_index (index starts at 0)
//32 > high_bit_index >= low_bit_index >= 0
//this function is taken from Dr. Schueller's code
int maskAddress(int address, int high_bit_index, int low_bit_index) {
	int result, mask_value;
	result = (address >> low_bit_index);
	mask_value = (1 << (high_bit_index - low_bit_index + 1) - 1);
	result &= mask_value;
	
	return result;
}

int main() {
    int address;	//to strore 16-bit address
    char outcome;	//to store whether a branch (T) is taken or not taken (N)
    int numOfBranches = 0, numOfBranchesTaken = 0, numOfCorrectTakens = 0, numOfCorrectNotTakens = 0;
    const int nCounters = 32;	// number of Smith Counters
    const int num_of_bits_needed = 5;	// lg(nCounters)
    
    SmithCounter c[nCounters]; //declare an array of SmithCounters
    
    ifstream myfile ("branch_trace.dat"); //open data file
    
    if (myfile.is_open()) {	
    	myfile >> address >> outcome; // read address and outcome
    	
        while (!myfile.eof()) { 	  //read address and outcome (one at a time) till the end of file
            numOfBranches++;
			
			int index;	// stores index of SmithCounter
			index = maskAddress(address,num_of_bits_needed+1,2); // return bits indexed 2 to num_of_bits_needed+1
			
            if(outcome == 'T') {
            	numOfBranchesTaken++;
            	//hash address to the table of counters
            	//compare prediction with outcome
            	if(c[index].getPrediction() == outcome)
            		numOfCorrectTakens++;
            }
            else if(outcome == 'N') {
            	//compare prediction with outcome
            	if(c[index].getPrediction() == outcome)
            		numOfCorrectNotTakens++;
            }
            //update the state of current counter
            c[index].updateState(outcome);
            
            myfile >> address >> outcome;	// read next address and outcome
       	}
       	
        myfile.close();
	}
    else cout << "Unable to open file";

	//display the results
	cout << "Number of branches:                                " << numOfBranches << endl;
	cout << "Number of branches taken:                          " << numOfBranchesTaken << endl;
	cout << "    " << "Number taken branches correctly predicted:     " << numOfCorrectTakens << endl;
	cout << "Number of branches not taken:                      " << numOfBranches - numOfBranchesTaken << endl;
	cout << "    " << "Number not taken branches correctly predicted: " << numOfCorrectNotTakens << endl;
	cout << fixed << showpoint << setprecision(2);
	cout << "Overall rate of correct predictions:               " << 100.00*(numOfCorrectTakens+numOfCorrectNotTakens)/numOfBranches << "%" << endl;

    return 0;
}
