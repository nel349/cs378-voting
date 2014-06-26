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

deque<Candidate> candidatos;

int numCandidates = 0;

deque<string> read_candidates(std::istream& r){
    deque<string> listCandidates;
    numCandidates = 0;
    r >> numCandidates;
    // cout << "Numero de Candidatos: " << candidateCount << endl;

    string name = "";
    getline(r, name);

    if(!r)
        return listCandidates;

    // Collect Candidate Names
    for(int i = 0; i < numCandidates; ++i){
        getline(r, name);
        listCandidates.push_back(name);
        // cout << names << endl;
    }

    return listCandidates;
}

deque<Vote> read_votes(std::istream& r){
    deque<Vote> listVotes;

    // read ballots
    string ballot = "";
    // getline(r, ballot);
    bool endTestCase = false;

    while( r && !endTestCase){
        
        getline(r, ballot);

        if(!ballot.empty() && r){
            // cout << ballot << endl;
            Vote v (ballot);
            listVotes.push_back(v);
        }
        else{
            endTestCase = true;}
    }

    // cout << "Number of ballot : " << (int) listVotes.size() << endl;
    return listVotes;
}


// -------------
// Voting_print
// -------------

void voting_print (std::ostream& w) {
    w  << endl;}

// -------------
// Voting_solve
// -------------

void voting_solve (std::istream& r, std::ostream& w) {
    
	int testNum = 1;
    int numElections = 0;

    r >>  numElections;
    string line = "";
    
    while(testNum <= numElections){ 
        
        string endVotes = "";
        deque<string> candidates = read_candidates(r);
        Election election(candidates);
        
        deque<Vote> ballots = read_votes(r);

        election.addBallots(ballots);
        election.runElection(w);

        if(testNum + 1 == numElections)
            w << "\n";
        testNum++;
    }

    voting_print(w);
}
        


Vote::Vote(std::string ballot){

    stringstream lineVotes;
    lineVotes << ballot;
    int n;
    for(int i = 0; i < numCandidates; ++i){
        lineVotes >> n;
        if(n != 0)
            votes.push_back(n);  
    }
}

Vote::Vote(const Vote &obj){
    votes = obj.votes;}


int Vote::getSize(){
    return (int) votes.size();
}
void Vote::printVote(){
    for(int i = 0; i < (int) votes.size(); ++i)
        cout << votes[i] << " ";    
    cout << endl;
}

int Vote::removeVote(){
    int v = votes.front();
    votes.pop_front();
    return v;
}

int Vote::getFrontElement(){
    if((int)votes.size() == 0){
        return -1;
    }

    int v = votes.front();
    votes.pop_front();
    return v;
}


Candidate::Candidate(string n){
    name = n;
    valid = true;
}

void Candidate::addVote(Vote v){
    ballots.push_back(v);
}

int Candidate::getNumVotes(){
    return (int) ballots.size();
 }

Election::Election(deque<string> names){
    numCandidates = (int) names.size();
    for(int i = 0; i < numCandidates; ++i){
        Candidate c(names[i]);
        candidates.push_back(c);
    }
}
void Election::printCandidates(){
    for(int i = 0; i < numCandidates; ++i)
        cout << candidates[i].name << endl;

}

void Election::addBallots(deque<Vote> list){
    totalVotes  = (int) list.size();
    for(int i = 0; i < totalVotes; ++i){
        Vote ballot = list[i];
        int canName = ballot.removeVote() - 1;
        candidates[canName].addVote(ballot);
    }
}

void Election::state(){
    for(int i = 0; i < (int) candidates.size(); ++i)
        cout << candidates[i].name << " : " << candidates[i].getNumVotes() << endl;
}

bool Election::isTie(){

    int numVotes = -1;
    bool isTie = true;
    int i = 0;
    
    // Find first valid candidate
    for( ; i < numCandidates; ++i)
        if(candidates[i].valid ){
            numVotes = candidates[i].getNumVotes();
            break;
        }

    // Find if all candidates tie
    for( ; (i < numCandidates) && isTie; ++i)
        if(candidates[i].valid && numVotes != candidates[i].getNumVotes()){
            isTie = false;
        }
            
    return isTie;
}


int Election::mostVotesIndex(){

    int maxIndex = -1;
    int maxVotes = -1;

    for(int i = 0  ; (i < numCandidates); ++i)
        if(candidates[i].valid && maxVotes < candidates[i].getNumVotes()){
            maxIndex = i;
            maxVotes = candidates[i].getNumVotes();
        }            
    return maxIndex;
}

int Election::leastVotes(){

    int leastVotes = 2147483647;

    for(int i = 0 ; i < numCandidates; i++)
        if(candidates[i].valid && leastVotes > candidates[i].getNumVotes()){
            leastVotes = candidates[i].getNumVotes();
        }
    return leastVotes;
}

bool Election::distributeBallots(deque<Vote> list){
    bool distributed = false;

    for(int i = 0; i < (int) list.size(); ++i){
        Vote v  = list.front();
        list.pop_front();
    
        bool donated = false;
        while(!donated && v.getSize() != 0){
            int nextBestChice = v.removeVote() - 1;
            if(candidates[nextBestChice].valid){
                candidates[nextBestChice].addVote(v);
                donated = true;
            }
        }
    }

    return distributed;
}

void Election::runElection(std::ostream& w){
    int winner = mostVotesIndex();
    bool tie = isTie();

    bool isNaturalWinner = (candidates[winner].getNumVotes() / (double) totalVotes)  > 0.5;

    if(isNaturalWinner){
        w << candidates[winner].name << endl;
        return;
    }
    
    while(!isNaturalWinner){
        int l = leastVotes();
        deque<int> lossers;
        // distribute votes
        for(int i = 0; i < numCandidates; ++i){
            if( candidates[i].valid && l == candidates[i].getNumVotes()){
                candidates[i].valid = false;
                lossers.push_back(i);
            }
        }

        for(int i = 0; i < (int) lossers.size(); ++i)
                distributeBallots(candidates[lossers[i]].ballots);

        winner = mostVotesIndex();
        isNaturalWinner = (candidates[winner].getNumVotes() / (double) totalVotes)  > 0.5;
        tie = isTie();

        int winnerVotes = candidates[winner].getNumVotes();

        if(tie){
            for(int i = 0; i < numCandidates; ++i){
                if(candidates[i].valid && winnerVotes == candidates[i].getNumVotes())
                    w << "\n"<< candidates[i].name;
            }
            return;
        }
        if(isNaturalWinner){
            w << candidates[winner].name ;
            return;
        }
    }    

}

