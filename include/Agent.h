#pragma once

#include <vector>
//#include "Simulation.h"
class Graph; // maybe it'll help in error of "Graph has not been declared in "void buildSet(Graph &g)" "
class SelectionPolicy;
class Simulation;
using std::vector;


class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);

    //rule of 5 methods
    ~Agent(); // destructor
    Agent& operator=(const Agent& other); // assignment operator
    Agent(const Agent& other); // copy constructor
    Agent(Agent&& other); // move constructor
    Agent& operator=(Agent&& other); // move assignment operator
    
    int getId() const;
    int getPartyId() const;
    void step(Simulation &sim);

    //added methods
    //#1
    void buildSet(Graph &g);
    //#2
    void updateSet(Simulation &sim);
    //#3
    SelectionPolicy* clone() const;
    //#4
    void removePartyFromOffers(int toRemoveId);
    //#5
    bool existOfferFromMyCoalition(vector<int> &coalitionsOffers, int myCoalitionId);

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;

    //added fields
    vector<int> partiesToOffer;

};
