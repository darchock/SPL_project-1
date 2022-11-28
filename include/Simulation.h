#pragma once
#include <vector>

#include "Graph.h"
class Agent;
class Party;

using std::string;
using std::vector;

class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);

    void step();
    bool shouldTerminate() const;

    const Graph &getGraph() const;
    //getGraph non-const #1
    Graph &getGraph();

    const vector<Agent> &getAgents() const;
    const Party &getParty(int partyId) const;
    //getParty non-const #2
    Party& getParty(int partyId);

    const vector<vector<int>> getPartiesByCoalitions() const;

    //added methods:
    void addToCoalition(int coalitionId, int partyId); // #3
    void addAgent(const Agent& agent); // #4
    const Agent& getAgent(int agentId) const; // #5
    
    //vector<vector<int>> getPartiesByCoalitions() const;
    int getCoalitionMandates(int coalitionId) const; // #6

private:
    Graph mGraph;
    vector<Agent> mAgents;
    vector<vector<int>> coalitions;
    vector<int> coalitionsMandates;
};
