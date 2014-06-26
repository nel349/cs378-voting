// --------------------------
// projects/Voting/Voting.h
// Copyright (C) 2014
// Glenn P. Downing
// --------------------------

#ifndef Voting_h
#define Voting_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <utility>  
#include <deque>
#include <string>

using namespace std;



// ------------
// Voting_eval
// ------------

/**
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length in the range [i, j]
 */
void voting_eval ();

void voting_solve (std::istream&, std::ostream&);


class Vote {

	public:
		deque<int> votes;
		Vote(string);
		int removeVote();
		int getSize();
		void printVote();};

class Candidate{

	public:	
		deque<Vote> ballots;
		string name;
		int numVotes;
		bool valid;
		Candidate(string);
		int getNumVotes();
		void addVote(Vote);
		// Vote removeVote();

};

class Election{
	public:
		int numCandidates;
		deque<Candidate> candidates;
		int totalVotes;
		Election(deque<string>);
		void printCandidates();
		void addBallots(deque<Vote>);
		void state();
		void runElection(std::ostream&);
		bool isTie();
		int mostVotesIndex();

		int leastVotes();
		bool distributeBallots(deque<Vote>);

};

deque<Vote> read_votes(std::istream&);

deque<string> read_candidates(std::istream&);



#endif // Voting_h
