#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

class JoinPolicy;
class SelectionPolicy;
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

    //rule of 5 methods
    virtual ~Party(); // destructor
    Party& operator=(const Party& other); // assignment operator
    Party(const Party& other); // Copy CTR
    Party(Party&& other); // Move CTR
    Party& operator=(Party&& other);

    State getState() const;
    void setState(State state);
    int getMandates() const;
    const string &getName() const;
    void step(Simulation &s);

    //added methods
    int getCoalitionId(); // #1
    void setCoalitionId(int coalitionId); // #2
    void submitOffer(int agentId, int agentsCoalitionId); // #3
    vector<int>& getOffers(); //#4
    void setTimer(); //#5
    void removeOffer(int agentId); //#6
    int getId(); //#7
    void cloneAgent(Simulation& sim, SelectionPolicy *selectionPolicy); //#8
    int getOffersCoalitionId(int offerId); //#9
    vector<int>& getOffersCoalitionVec(); //#10

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;

    //added fields
    int mCoalitionId;
    vector<int> offers; //offers vec contains agentId of agents who submitted an offer
    vector<int> coalitionOfOfferingAgent;
    int timer;
};
