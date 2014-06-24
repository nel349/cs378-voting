// ----------------------------
// projects/Voting/Voting.c++
// Copyright (C) 2014
// Glenn P. Downing
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

std::pair<int, int> voting_read (std::istream& r) {
	int i;
    r >> i;
    if (!r)
        return std::make_pair(0, 0);
	int j;
    r >> j;
    return std::make_pair(i, j);}

// ------------
// Voting_eval
// ------------
int voting_eval (int i, int j) {
    return 0;
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
    
    string temp = "";

    

    int numTestCases = 0;
    getline(r, temp);

   

    stringstream(temp) >> numTestCases;
    // temp >> numTestCases;
    // r >> numTestCases;
    cout << "Number Of Test: " << numTestCases << endl; 
    
    int line;
    getline(r, temp);

    while(numTestCases > 0){



        getline(r, temp);
        stringstream(temp) >> numCandidates;
        cout << "Number Of candidates: " << numCandidates << endl; 


        do{
            if(!r)
                return;
            

            getline(r, temp);

            // cout << temp << endl;

            if(numCandidates > 0){
               canditate_names.push_back(temp);     
            }
            --numCandidates;
        }while(!temp.empty() );

        print_candidates();
        reset();
        numTestCases--;
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


