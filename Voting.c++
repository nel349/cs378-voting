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
deque<Vote> election_votes;
deque<int> election_count(20,0);

int numCandidates = 0;


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
            // cout << ballot << endl;
            
            Vote v (ballot);
            election_votes.push_back(v);
            // cout << "before: " <<election_count[(v.votes[0]) - 1]; 
            election_count[(v.votes[0]) - 1] += 1;
            // cout << " after: " <<election_count[(v.votes[0]) - 1] << endl; 
            
        }

        else{
            endTestCase = true;}
    }
    print_votes();

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


    while(testNum <= numElections){ 
        cout << "*******************Starting new Test " << testNum << endl;     
        reset();
        voting_read(r); 
        //
        print_vote_count();
        // 
        voting_eval();
        cout << "\n";
        testNum++;

        cout << "election_count size() : " << (int) election_count.size() << endl;
  
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
    election_votes.clear();
    
    for(int i = 0; i < (int) election_count.size(); ++i)
        election_count[i]  = 0;

    numCandidates = 0;

}

Vote::Vote(std::string ballot){

    votes.clear();
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

void Vote::printVote(){
    for(int i = 0; i < (int) votes.size(); ++i){
        cout << votes[i] << " ";
    }
    cout << endl;
}


void print_votes(){
    for(int i = 0; i < (int) election_votes.size(); ++i){
        election_votes[i].printVote();
    }
    cout << endl;
}

void print_vote_count(){
    for(int i = 0; i < numCandidates; ++i){
        cout << canditate_names[i] << " : " << election_count[i] << endl; 
    }
    cout << endl;
}

