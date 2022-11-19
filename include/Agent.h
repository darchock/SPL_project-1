#pragma once

#include <vector>
#include "Graph.h"
class Graph; // maybe it'll help in error of "Graph has not been declared in "void buildSet(Graph &g)" "

using std::vector;

class SelectionPolicy;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);

    int getPartyId() const;
    int getId() const;
    void step(Simulation &sim);

    //added methods
    void buildSet(Graph &g);
    void updateSet(Simulation &sim);

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;

    //added fields
    vector<int> partiesToOffer;

};
