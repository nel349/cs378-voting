

#include <iostream> // istream, ostream
#include <utility>  
#include <deque>
#include <string>


#include <cassert>  // assert
#include <sstream>
#include <vector>

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif




using namespace std;

void voting_solve (std::istream&, std::ostream&);

void voting_print (std::ostream&, bool);


class Vote {

    public:
        deque<int> votes;

        Vote(string);
        Vote(const Vote&);
        // Vote& operator = (Vote other){
        //  votes = other.votes;
        //  return *this;
        // };
        int removeVote();
        int getSize();
        int getFrontElement();
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

void voting_print (std::ostream& w, bool end) {
    
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
    // state();
    // Find if all candidates tie
    for( ; (i < numCandidates) && isTie; ++i)
        if(candidates[i].valid && numVotes != candidates[i].getNumVotes()){
            isTie = false;
        }
            
    // cout << "Is tie: " << isTie << endl;
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



    // cout << "\tNumber of Ballots to distribute: " <<  list.size() << endl;
    // for(int i = 0; i < (int) list.size(); ++i){
    //     list[i].printVote();
    // }
    int numLossers = (int) list.size();

    for(int i = 0; i < numLossers; ++i){

        Vote v  = list.front();
        list.pop_front();
        // v.printVote();
        bool donated = false;
        
        while(!donated && v.getSize() != 0){
            int nextBestChice = v.removeVote() - 1;
            // cout << "\t\tNext Best Choice: " << nextBestChice << endl;
            if(candidates[nextBestChice].valid){
                candidates[nextBestChice].addVote(v);
                donated = true;
                // cout << "\tVoted given to : " << candidates[nextBestChice].name << endl;
                // state();
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
        return;
    }

    // cout << "TIE?  " << tie<< endl; 
    if(tie){
        for(int i = 0; i < numCandidates; ++i){
            if(candidates[i].valid && winnerVotes == candidates[i].getNumVotes())
                w << candidates[i].name << endl;
        }
        return;
    }
   
    // cout << "Running Election..." << endl;
    int roundNum = 1;
    
    while(!isNaturalWinner && !tie){
        // cout << "\nRound of elimination # " << roundNum++ << endl;
        
        // cout << "Before distribution: " << endl;
        // state();
        int leastV = leastVotes();
        // cout << "\tLeast Votes: " << leastV << endl;
        deque<int> lossers;
        
        // distribute votes
        for(int i = 0; i < numCandidates; ++i){
            if( candidates[i].valid && leastV == candidates[i].getNumVotes()){
                candidates[i].valid = false;
                lossers.push_back(i);
            }
        }

        // cout << "\tNumber of loser : " << lossers.size() << endl;
        for(int i = 0; i < (int) lossers.size(); ++i)
                distributeBallots(candidates[lossers[i]].ballots);

        maxVotesIndex = mostVotesIndex();
        isNaturalWinner = (candidates[maxVotesIndex].getNumVotes() / (double) totalVotes)  > 0.5;
        tie = isTie();

        winnerVotes = candidates[maxVotesIndex].getNumVotes();

        if(isNaturalWinner){
            w << candidates[maxVotesIndex].name << endl;
            return;
        }
        if(tie){
            for(int i = 0; i < numCandidates; ++i){
                if(candidates[i].valid && winnerVotes == candidates[i].getNumVotes())
                    w << candidates[i].name << endl;
            }
            return;
        }
    }    

}



int main () {
    using namespace std;
    voting_solve(cin, cout);
    return 0;}