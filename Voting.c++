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
    
    string name = "";
    getline(r, name);

    if(!r)
        return listCandidates;

    // Collect Candidate Names
    for(int i = 0; i < numCandidates; ++i){
        getline(r, name);
        listCandidates.push_back(name);
    }
    return listCandidates;
}

deque<Vote> read_votes(std::istream& r){
    deque<Vote> listVotes;

    // read ballots
    string ballot = "";
    bool endTestCase = false;

    while( r && !endTestCase){
        getline(r, ballot);

        if(!ballot.empty() && r){
            Vote v (ballot);
            listVotes.push_back(v);
        }
        else{
            endTestCase = true;}
    }
    return listVotes;
}

// -------------
// Voting_solve
// -------------

void voting_solve (std::istream& r, std::ostream& w) {
    
	int testNum = 1;
    int numElections = 0;

    r >>  numElections;
    string line = "";
    bool end = false;
    
    while(testNum <= numElections){ 
        
        string endVotes = "";
        deque<string> candidates = read_candidates(r);
        Election election(candidates);
        
        deque<Vote> ballots = read_votes(r);

        election.addBallots(ballots);
        election.runElection(w);

        if(testNum == numElections)
            end = true;
        
        if(!end)
            w  << endl;
        
        testNum++;
    }
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
string Vote::printVote(){
    string result = "";
    for(int i = 0; i < (int) votes.size(); ++i)
        if(i + 1 == (int) votes.size() ){
             result += to_string(votes[i]);
        }
        else{
            result += to_string(votes[i]) + " ";
        }
    return result;
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
        if(candidates[i].valid)
            cout << candidates[i].name << " : " << candidates[i].getNumVotes() << endl;
}

bool Election::isTie(){

    int numVotes = -1;
    bool isTie = true;
    int i = 0;
    
    bool ff = false;
    // Find first valid candidate
    for( ; i < numCandidates && !ff; ++i){
        if(candidates[i].valid ){
            numVotes = candidates[i].getNumVotes();
            ff= true;
        }
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
    int numLossers = (int) list.size();

    for(int i = 0; i < numLossers; ++i){
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
    int maxVotesIndex = mostVotesIndex();
    bool tie = isTie();
    int winnerVotes = candidates[maxVotesIndex].getNumVotes();
    bool isNaturalWinner = (candidates[maxVotesIndex].getNumVotes() / (double) totalVotes)  > 0.5;

    if(isNaturalWinner){
        w << candidates[maxVotesIndex].name << endl;
        return;}

    if(tie){
        for(int i = 0; i < numCandidates; ++i){
            if(candidates[i].valid && winnerVotes == candidates[i].getNumVotes())
                w << candidates[i].name << endl;
        }
        return;}
   
    
    while(!isNaturalWinner && !tie){
        
        int leastV = leastVotes();
        deque<int> lossers;
        
        // collect lossers
        for(int i = 0; i < numCandidates; ++i){
            if( candidates[i].valid && leastV == candidates[i].getNumVotes()){
                candidates[i].valid = false;
                lossers.push_back(i);
            }
        }

        // distribute votes
        for(int i = 0; i < (int) lossers.size(); ++i)
                distributeBallots(candidates[lossers[i]].ballots);

        maxVotesIndex = mostVotesIndex();
        isNaturalWinner = (candidates[maxVotesIndex].getNumVotes() / (double) totalVotes)  > 0.5;
        tie = isTie();

        winnerVotes = candidates[maxVotesIndex].getNumVotes();

        if(isNaturalWinner){
            w << candidates[maxVotesIndex].name << endl;
            return;}

        if(tie){
            for(int i = 0; i < numCandidates; ++i){
                if(candidates[i].valid && winnerVotes == candidates[i].getNumVotes())
                    w << candidates[i].name << endl;
            }
            return;}
    }    
}