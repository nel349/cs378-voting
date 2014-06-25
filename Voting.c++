// ----------------------------
// projects/Voting/Voting.c++
// Copyright (C) 2014
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <utility>  // make_pair, pair
#include <string>
#include <sstream>
#include <deque>
#include <vector>

#include "Voting.h"

using namespace std;
deque<string> canditate_names(20, "");
int numCandidates = 0;

// deque<vector> candidates;



// ------------
// Voting_read
// ------------
void voting_read (std::istream& r) {
	
	r >> numCandidates;
	cout << "Numero de Candidatos: " << numCandidates << endl;

	string names = "";
	getline(r, names);


	if(!r)
		return;

	// Collect Candidate Names
	for(int i = 0; i < numCandidates; ++i){
		getline(r, names);
		canditate_names.push_back(names);
		// cout << names << endl;
	}
	print_candidates();

	string ballot = "";
	getline(r, ballot);
	
    bool endTestCase = false;



    while( r && !endTestCase){
        
        getline(r, ballot);
        if(!ballot.empty()){

            cout << ballot << endl;
            Vote v (ballot);
      
        }
        else{
            endTestCase = true;

           
        }
    }


}

// ------------
// Voting_eval
// ------------
void voting_eval () {
    
}


// -------------
// Voting_print
// -------------

void voting_print (std::ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << std::endl;}

// -------------
// Voting_solve
// -------------

void voting_solve (std::istream& r, std::ostream& w) {
    
	int testNum = 1;
    int numElections = 0;

    r >>  numElections;
    string line = "";
    getline(r, line); 


    while(testNum <= numElections)
    { 
        cout << "*******************Starting new Test " << testNum << endl;     
        canditate_names.clear();
        voting_read(r); 
        voting_eval();
        cout << "\n";
        testNum++;
    }
    

}
        
void print_candidates(){

    for(std::string & x: canditate_names){
        if(x != "")
            cout << x << endl;   
    }
}

void reset(){
    canditate_names.clear();
    numCandidates = 0;

}

Vote::Vote(std::string ballot){

    stringstream lineVotes;
    lineVotes << ballot;
    int n;
    for(int i = 0; i < numCandidates; ++i){
        lineVotes >> n;
        // cout << n << endl;
        if(n != 0){
            votes.push_back(n);
        }
    }

}
// string temp = "";

    

    // int numTestCases = 0;
    // getline(r, temp);

   

    // stringstream(temp) >> numTestCases;
    // // temp >> numTestCases;
    // // r >> numTestCases;
    // cout << "Number Of Test: " << numTestCases << endl; 
    
    // int line;
    // getline(r, temp);

    // while(numTestCases > 0){



    //     getline(r, temp);
    //     stringstream(temp) >> numCandidates;
    //     cout << "Number Of candidates: " << numCandidates << endl; 


    //     do{
    //         if(!r)
    //             return;
            

    //         getline(r, temp);

    //         // cout << temp << endl;

    //         if(numCandidates > 0){
    //            canditate_names.push_back(temp);     
    //         }
    //         --numCandidates;
    //     }while(!temp.empty() );

    //     print_candidates();
    //     reset();
    //     numTestCases--;
    // }
