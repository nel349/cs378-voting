// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2014
// Glenn P. Downing
// --------------------------------

/*
Google Test Libraries:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

To compile the test:
    % g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Voting.c++ TestVoting.c++ -o TestVoting -lgtest -lgtest_main -lpthread

To run the test:
    % valgrind TestVoting

To obtain coverage of the test:
	% gcov-4.7 -b Voting.c++ TestVoting.c++
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <utility>  // make_pair, pair

#include "gtest/gtest.h"
#include <deque>


#include "Voting.h"

// -----------
// TestVoting
// -----------

// ----
// read candidates
// ----
// 
TEST(Voting,  read_candidates_1) {
    std::istringstream r("3\nJames Franco\nCameron Diaz\nTom Hanks\n");
    string expected[] ={"James Franco", "Cameron Diaz", "Tom Hanks"};
    deque<string> p = read_candidates(r);
    deque<string> q ;
    q.assign(expected, expected + 3);
    assert( p == q);   
}

TEST(Voting,  read_candidates_2) {
    std::istringstream r("6\nA\nB\nC\nD\nE\nF\n");
    string expected[] ={"A", "B", "C", "D", "E", "F"};
    deque<string> p = read_candidates(r);
    deque<string> q ;
    q.assign(expected, expected + 6);
    assert( p == q);   
}

TEST(Voting,  read_candidates_3) {
    std::istringstream r("10\nA\nB\nC\nD\nE\nF\nG\nH\nI\nJ\n");
    string expected[] ={"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    deque<string> p = read_candidates(r);
    deque<string> q ;
    q.assign(expected, expected + 10);
    assert( p == q);    
}


// ----
// read votes
// ----
// 

TEST(Voting,  read_votes) {
    std::istringstream r("1 2 3\n4 5 6\n7 8 9\n");
    // cout << r.str();
    Vote expected[] ={Vote("1 2 3"), Vote("4 5 6"), Vote("7 8 9")};
    deque<Vote> p = read_votes(r);
    deque<Vote> q ;
    q.assign(expected, expected+1);
    Vote x = p.front();
    // for( int i = 0 ; i< 3; ++i){
    //     x.printVote();
    // }
    // assert( p == q);   
}



TEST(Voting,  voting_solve_1) {
    std::istringstream r("1\n\n3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n");
    std::ostringstream w;
    voting_solve(r, w);
    ASSERT_EQ( "John Doe\n", w.str());
}
TEST(Voting,  voting_solve_2) {
    std::istringstream r("1\n\n1\nalpha\n1\n");
    std::ostringstream w;
    voting_solve(r, w);
    // cout << w.str();
    ASSERT_EQ( "alpha\n", w.str());
}
TEST(Voting,  voting_solve_3) {
    std::istringstream r("1\n\n3\nA\nB\nC\n1 2 3\n1 2 3\n1 2 3\n");
    std::ostringstream w;
    voting_solve(r, w);
    // cout << w.str();
    ASSERT_EQ( "A\n", w.str());
}


//****************************************
// VOTE
//****************************************

// ----
// Vote::getSize
// ----
// 
TEST(Voting, getSize_1){
    deque<string> candidates;
    string expected[] = {"James Franco", "Cameron Diaz", "Tom Hanks"};
    candidates.assign(expected, expected + 3);

    Vote v("1 2 3");
    Vote w("2 3 1");
    Vote y("1 5 3");
    Vote vs[] = {v, w, y};
    deque<Vote> votes;
    votes.assign(vs, vs + 3);


    Election e (candidates);
    e.addBallots(votes);

    ASSERT_EQ(2 ,e.candidates[0].ballots[1].getSize());
}

TEST(Voting, getSize_2){
    deque<string> candidates;
    string expected[] = {"James Franco", "Cameron Diaz", "Tom Hanks"};
    candidates.assign(expected, expected + 3);

    Vote v("1 2 3 4");
    Vote w("2 3 1 4");
    Vote y("1 5 3 4");
    Vote z("1 5 3 4");
    Vote vs[] = {v, w, y, z};
    deque<Vote> votes;
    votes.assign(vs, vs + 4);

    Election e (candidates);
    e.candidates[0].addVote(v);
    e.candidates[0].addVote(w);
    e.candidates[0].addVote(y);
    e.candidates[0].addVote(z);

    e.addBallots(votes);

    ASSERT_EQ(3 ,e.candidates[0].ballots[1].getSize());
}


// ----
// Vote::printVote
// ----
// 
TEST(Voting, printVote_1){
    deque<string> candidates;
    string expected[] = {"James Franco", "Cameron Diaz", "Tom Hanks"};
    candidates.assign(expected, expected + 3);

    Vote v("1 2 3");
    Vote w("2 3 1");
    Vote y("1 5 3");

    ASSERT_EQ("1 2 3", v.printVote());
}

TEST(Voting, printVote_2){
    deque<string> candidates;
    string expected[] = {"James Franco", "Cameron Diaz", "Tom Hanks"};
    candidates.assign(expected, expected + 3);

    Vote v("1 2 3");
    Vote w("2 3 1");
    Vote y("1 5 3");

    ASSERT_EQ("1 2 3", v.printVote());
}


TEST(Voting, printVote_3){
    deque<string> candidates;
    string expected[] = {"James Franco", "Cameron Diaz", "Tom Hanks"};
    candidates.assign(expected, expected + 3);

    Vote v("1 2 3");
    Vote w("2 3 1");
    Vote y("1 5 3");

    ASSERT_EQ("1 2 3", v.printVote());
}

// ----
// Vote::removeVote
// ----
// 

TEST(Voting, removeVote){
    deque<string> candidates;
    string expected[] = {"James Franco", "Cameron Diaz", "Tom Hanks"};
    candidates.assign(expected, expected + 3);

    Vote v("1 2 3");
    Vote w("2 3 1");
    Vote y("1 5 3");
    Vote z("1 5 3");
    Vote vs[] = {v, w, y, z};
    deque<Vote> votes;
    votes.assign(vs, vs + 4);

    Election e (candidates);
    e.candidates[0].addVote(v);
    e.candidates[0].addVote(w);
    e.candidates[0].addVote(y);
    e.candidates[0].addVote(z);

    assert("1 2 3" == e.candidates[0].ballots[0].printVote() );

    e.candidates[0].ballots[0].removeVote();

    assert("1 2 3" != e.candidates[0].ballots[0].printVote() );
}



// ----
// Vote::getFrontElement
// ----
// 
TEST(Voting, getFrontElement){
    deque<string> candidates;
    string expected[] = {"James Franco", "Cameron Diaz", "Tom Hanks"};
    candidates.assign(expected, expected + 3);

    Vote v("1 2 3");
    Vote w("2 3 1");
    Vote y("1 5 3");
    Vote z("1 5 3");
    Vote vs[] = {v, w, y, z};
    deque<Vote> votes;
    votes.assign(vs, vs + 4);

    Election e (candidates);
    e.candidates[0].addVote(v);
    e.candidates[0].addVote(w);
    e.candidates[0].addVote(y);
    e.candidates[0].addVote(z);
    ASSERT_EQ(1,e.candidates[0].ballots[0].getFrontElement() );
}

//****************************************
// Candidate
//****************************************

// ----
// Candidate::addVote
// ----
// 
TEST(Voting, addVote_1){
    Candidate a("John");
    Vote v("1 2 3");
    a.addVote(v);
    string actual = a.ballots[0].printVote();
    ASSERT_EQ(actual, "1 2 3");
}
TEST(Voting, addVote_2){
    Candidate a("Tim");
    Vote v("324324 234 334");
    a.addVote(v);
    string actual = a.ballots[0].printVote();
    ASSERT_EQ(actual, "324324 234 334");
}
TEST(Voting, addVote_3){
    Candidate a("Mark");
    Vote v("12 2 31");
    a.addVote(v);
    string actual = a.ballots[0].printVote();
    ASSERT_EQ(actual, "12 2 31");
}

// ----
// Candidate::getNumVotes
// ----
// 
TEST(Voting, getNumVotes_1){
    Candidate a("Mark");
    Vote v("12 2 31");
    a.addVote(v);
    int actual = a.getNumVotes();
    ASSERT_EQ(1, actual);
}
TEST(Voting, getNumVotes_2){
    Candidate a("Mark");
    Vote v("12 2 31");
    Vote w("12 2 31");
    a.addVote(v);
    a.addVote(w);
   
    int actual = a.getNumVotes();
    ASSERT_EQ(2, actual);
}
TEST(Voting, getNumVotes_3){
    Candidate a("Mark");
    Vote v("12 2 31");
    Vote w("12 2 31");
    Vote y("12 2 31");
    a.addVote(v);
    a.addVote(w);
    a.addVote(y);
    int actual = a.getNumVotes();
    ASSERT_EQ(3, actual);
}




//****************************************
// Election
//****************************************


// ----
// Election::addBallots
// ----
// 
TEST(Voting, addBallots_1){
    deque<string> candidates;
    string expected[] = {"James Franco", "Cameron Diaz", "Tom Hanks"};
    candidates.assign(expected, expected + 3);

    Vote v("1 2 3");
    Vote w("2 3 1");
    Vote y("1 3 2");
    Vote vs[] = {v, w, y};
    deque<Vote> votes;
    votes.assign(vs, vs + 3);

    Election e (candidates);
 
    e.addBallots(votes);

    ASSERT_EQ(e.candidates[0].ballots[0].printVote(), "2 3");
    ASSERT_EQ(e.candidates[0].ballots[1].printVote(), "3 2");
    
    ASSERT_EQ(e.candidates[1].ballots[0].printVote(), "3 1");

}
TEST(Voting, addBallots_2){
    deque<string> candidates;
    string expected[] = {"James Franco", "Cameron Diaz", "Tom Hanks"};
    candidates.assign(expected, expected + 3);

    Vote v("1 2 3");
    Vote w("2 3 1");
    Vote y("1 3 2");
    Vote vs[] = {v, w, y};
    deque<Vote> votes;
    votes.assign(vs, vs + 3);

    Election e (candidates);
 
    e.addBallots(votes);

    ASSERT_EQ(e.candidates[0].ballots[0].printVote(), "2 3");
    ASSERT_EQ(e.candidates[0].ballots[1].printVote(), "3 2"); 
    ASSERT_EQ(e.candidates[1].ballots[0].printVote(), "3 1");

}

TEST(Voting, addBallots_3){
    deque<string> candidates;
    string expected[] = {"James Franco", "Cameron Diaz", "Tom Hanks"};
    candidates.assign(expected, expected + 3);

    Vote v("1 2 3");
    Vote w("2 3 1");
    Vote y("1 5 3");
    Vote vs[] = {v, w, y};
    deque<Vote> votes;
    votes.assign(vs, vs + 3);
    Election e (candidates);
 
    e.addBallots(votes);
    ASSERT_EQ(e.candidates[0].ballots[0].printVote(), "2 3");
    ASSERT_EQ(e.candidates[0].ballots[1].printVote(), "5 3");
    
    ASSERT_EQ(e.candidates[1].ballots[0].printVote(), "3 1");

}


TEST(Voting, state){
    
}


// ----
// Election::isTie
// ----
// 
TEST(Voting, isTie_1){
    deque<string> candidates;
    string expected[] = {"James Franco", "Cameron Diaz", "Tom Hanks"};
    candidates.assign(expected, expected + 3);

    Vote v("1 2 3");
    Vote w("2 3 1");
    Vote y("1 5 3");
    Vote vs[] = {v, w, y};
    deque<Vote> votes;
    votes.assign(vs, vs + 3);
    Election e (candidates);
 
    e.addBallots(votes);
    assert(!e.isTie());
}

TEST(Voting, isTie_2){
    deque<string> candidates;
    string expected[] = {"James Franco", "Cameron Diaz", "Tom Hanks"};
    candidates.assign(expected, expected + 3);

    Vote v("1");
    Vote w("2");
    Vote y("2");
    Vote z("1");
    Vote vs[] = {v, w, y, z};
    deque<Vote> votes;
    votes.assign(vs, vs + 1);
    Election e (candidates);
 
    e.addBallots(votes);
    // cout << e.
    assert(!e.isTie());
}



TEST(Voting, isTie_3){
    deque<string> candidates;
    string expected[] = {"James Franco", "Cameron Diaz", "Tom Hanks"};
    candidates.assign(expected, expected + 3);

    Vote v("3 2 1");
    Vote w("1 3 2");
    Vote y("1 2 3");
    Vote vs[] = {v, w, y};
    deque<Vote> votes;
    votes.assign(vs, vs + 3);
    Election e (candidates);
    e.addBallots(votes);
    assert(!e.isTie());
}


// ----
// Election::mostVotesIndex
// ----
// 
TEST(Voting, mostVotesIndex_1){
    deque<string> candidates;
    string expected[] = {"James Franco", "Cameron Diaz", "Tom Hanks"};
    candidates.assign(expected, expected + 3);

    Vote v("1 2 3");
    Vote w("2 3 1");
    Vote y("1 5 3");
    Vote vs[] = {v, w, y};
    deque<Vote> votes;
    votes.assign(vs, vs + 3);
    Election e (candidates);
 
    e.addBallots(votes);
    assert ( e.mostVotesIndex()  == 0);
}


TEST(Voting, mostVotesIndex_2){
    deque<string> candidates;
    string expected[] = {"James Franco", "Cameron Diaz", "Tom Hanks"};
    candidates.assign(expected, expected + 3);

    Vote v("2 1 3");
    Vote w("2 3 1");
    Vote y("1 5 3");
    Vote vs[] = {v, w, y};
    deque<Vote> votes;
    votes.assign(vs, vs + 3);
    Election e (candidates);
    e.addBallots(votes);
    assert ( e.mostVotesIndex()  == 1);

}

TEST(Voting, mostVotesIndex_3){
    deque<string> candidates;
    string expected[] = {"James Franco", "Cameron Diaz", "Tom Hanks"};
    candidates.assign(expected, expected + 3);

    Vote v("3 1 2");
    Vote w("3 2 1");
    Vote y("1 2 3");
    Vote vs[] = {v, w, y};
    deque<Vote> votes;
    votes.assign(vs, vs + 3);
    Election e (candidates);
    e.addBallots(votes);
    assert ( e.mostVotesIndex()  == 2);

}

// ----
// Election::leastvotes
// ----
// 
TEST(Voting, leastVotes_1){
    deque<string> candidates;
    string expected[] = {"James Franco", "Cameron Diaz", "Tom Hanks"};
    candidates.assign(expected, expected + 3);

    Vote v("3 1 2");
    Vote w("3 2 1");
    Vote y("1 2 3");
    Vote vs[] = {v, w, y};
    deque<Vote> votes;
    votes.assign(vs, vs + 3);
    Election e (candidates);
    e.addBallots(votes);
    assert ( e.leastVotes()  == 0);
}

TEST(Voting, leastVotes_2){
    deque<string> candidates;
    string expected[] = {"James Franco", "Cameron Diaz", "Tom Hanks"};
    candidates.assign(expected, expected + 3);

    Vote v("1 3 2");
    Vote w("2 3 1");
    Vote y("1 2 3");
    Vote vs[] = {v, w, y};
    deque<Vote> votes;
    votes.assign(vs, vs + 3);
    Election e (candidates);
    e.addBallots(votes);
    ASSERT_EQ( 0 , e.leastVotes());
}

TEST(Voting, leastVotes_3){
    deque<string> candidates;
    string expected[] = {"James Franco", "Cameron Diaz", "Tom Hanks"};
    candidates.assign(expected, expected + 3);

    Vote v("1 3 2");
    Vote w("2 3 1");
    Vote y("3 2 1");
    Vote z("2 3 1");
    Vote a("1 2 3");

    Vote vs[] = {v, w, y, z, a};
    deque<Vote> votes;
    votes.assign(vs, vs + 5);
    Election e (candidates);
    e.addBallots(votes);
    ASSERT_EQ( 1 , e.leastVotes());
}


// ----
// Election::distribute Ballots
// ----
//
TEST(Voting, distributeBallots_1){
    deque<string> candidates;
    string expected[] = {"James Franco", "Cameron Diaz", "Tom Hanks"};
    candidates.assign(expected, expected + 3);

    Vote v("1 3 2");
    Vote w("2 3 1");
    Vote y("3 2 1");
    Vote z("2 3 1");
    Vote a("1 2 3");

    Vote vs[] = {v, w, y, z, a};
    deque<Vote> votes;
    votes.assign(vs, vs + 5);
    Election e (candidates);
    assert ( !e.distributeBallots(votes));

}

TEST(Voting, distributeBallots_2){
    deque<string> candidates;
    string expected[] = {"James Franco", "Cameron Diaz", "Tom Hanks"};
    candidates.assign(expected, expected + 3);

    Vote v("1 3 2");
    Vote w("2 3 1");
    Vote y("1 2 3");
    Vote vs[] = {v, w, y};
    deque<Vote> votes;
    votes.assign(vs, vs + 3);
    Election e (candidates);
    assert ( !e.distributeBallots(votes));
}

TEST(Voting, distributeBallots_3){
    deque<string> candidates;
    string expected[] = {"James Franco", "Cameron Diaz", "Tom Hanks"};
    candidates.assign(expected, expected + 3);

    Vote v("3 1 2");
    Vote w("3 2 1");
    Vote y("1 2 3");
    Vote vs[] = {v, w, y};
    deque<Vote> votes;
    votes.assign(vs, vs + 3);
    Election e (candidates);
    assert ( !e.distributeBallots(votes));
}

// ----
// Election::run election
// ----
//
TEST(Voting, runElection_1){
    assert(true);
}
