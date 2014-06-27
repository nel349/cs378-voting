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
// voting_solve
// ------------

/**
 * Reads the input and generates the correct result
 * @param r is a std::istream
 * @param w is a std::ostream
 * @return void
 */
void voting_solve (std::istream&, std::ostream&);


// ------
// Vote
// ------

/**
 * A Vote class. Contains a deque with each voter's preference of
 * candidates.
 */
class Vote {
	public:
		deque<int> votes; /**< a deque to hold the numbers */

		/** 
        * A Vote constructor that is initialized with
        * voters choices
        */
		Vote(string);
		/** 
        * A Vote constructor that is initialized with
        * voters choices
        */
		Vote(const Vote&);
		
		/** 
        * Removes first item from the deck of votes 
        */
		int removeVote();
		
		/**
        * Gets the size of the ballot
        */
		int getSize();
		
		/** 
        * return first item from the deck of votes 
        */
		int getFrontElement();
		
		/** 
        * returns string Vote according to the voter's preferences 
        */
		
		string printVote();};

// ---------
// Candidate
// ---------

/**
 * Candidate class. Each candidate contains a  deque<Vote>
 */
class Candidate{
	public:	
		deque<Vote> ballots;	/**< a deque to hold the Vote objects */
		string name; 			/** Candidate Name*/
		int numVotes;			/** Number of votes per candidate */
		bool valid;				/** is candidate still in the run? */

		/**
     	* Initializes Candidate object with a name
     	*/
		Candidate(string);

		/**
     	* Gets how many ballots this candidate has
     	*/
		int getNumVotes();

		/**
     	* Add ballot to this candidate's list of votes
     	*/
		void addVote(Vote);};

// ---------
// Election
// ---------

/**
 * Election class. Each elections has a list with candates
 */
class Election{
	public:
		int numCandidates;				/**< Number of Candidates in this election */							
		deque<Candidate> candidates;	/**< a deque to hold the Candidate objects */
		int totalVotes;					/**< Total number of votes for this election */

		/**
     	* Initializes List<Candidate> object with a name
     	*/
		Election(deque<string>);
		
		/**
     	* prints candidates
     	*/
		void printCandidates();
		
		/**
     	* @param list of votes to distribute amoung the candidates
     	*/
		void addBallots(deque<Vote>);
		
		/**
     	* Prints state
     	*/
		void state();
		
		/**
     	* Analysis teh votes and determines winner(s)
     	*/
		void runElection(std::ostream&);
		
		/**
     	* @return weather is a tir ot not
     	*/
		bool isTie();
		
		/**
     	* @return index of the candidate with most votes
     	* 
     	*/
		int mostVotesIndex();

		/**
     	* Number of votes of the candidate with the least amount of votes
     	* @return int with least amount of votes 
     	*/
		int leastVotes();
		
		/**
     	* Ballot distribution
     	* @param deque<Votes> distribute votes to the appropiate candidate
     	*/
		bool distributeBallots(deque<Vote>);};

// ------------
// read_votes
// ------------

/**
 * Reads the votes per election
 * @param r is a std::istream
 * @return deque<Vote>
 */
deque<Vote> read_votes(std::istream&);

// ------------
// read_candidates
// ------------

/**
 * Reads candidates from the input and returns a deque
 * @param r is a std::istream
 * @return deque<string>
 */
deque<string> read_candidates(std::istream&);



#endif // Voting_h
