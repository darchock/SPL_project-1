#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

class JoinPolicy;
class Simulation;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); 

    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;

    //added methods
    int getCoalitionId(); // #1
    void setCoalitionId(int coalitionId); // #2
    void submitOffer(int agentId); // #3
    vector<int> getOffers(); //#4
    //bool isInOffers(int partyId); //#5 

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;

    //added fields
    int mCoalitionId;
    vector<int> offers; //offers vec contains agentId of agents who submitted an offer
    int timer;
    // for (int id : offersId)
    // {
    //     int i = getParty(offersId(id)).coalitionId 
    //     int mandates = s.coalitionsMandates(i) 
    // }
};
