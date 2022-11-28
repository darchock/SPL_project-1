#include <iostream>
#include <iomanip>
#include "Simulation.h"

using std::cout;
using std::endl;

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents), coalitions(), coalitionsMandates() {

    // You can change the implementation of the constructor, but not the signature!
    coalitions.resize(mAgents.size());
	coalitionsMandates.resize(mAgents.size());

	for (Agent& agent : mAgents) {
		addToCoalition(agent.getId(), agent.getPartyId());
        // change original agent's coalitionId to their agentId
        agent.buildSet(mGraph);
    }
}


void Simulation::step()
{
    for (int i = 0; i < mGraph.getNumVertices(); ++i)
		getParty(i).step(*this);

	for (Agent& agent : mAgents)
		agent.step(*this);
}

bool Simulation::shouldTerminate() const {    
    // TODO implement this method

    bool allJoined = true;

	for (int mandates : coalitionsMandates)
		if (mandates > 60)
			return true;

	for (int i = 0; i < mGraph.getNumVertices(); ++i)
		if (getParty(i).getState() != State::Joined)
			allJoined = false;

	return allJoined;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

// #1
Graph &Simulation::getGraph()
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

// #2
Party &Simulation::getParty(int partyId)
{
    return mGraph.getParty(partyId);
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    // TODO: you MUST implement this method for getting proper output, read the documentation above.
    //return vector<vector<int>>();
    return coalitions;
}

// #3
void Simulation::addToCoalition(int coalitionId, int partyId)
{
    //Select party that an original agent represents and change their coalitionId to their agentId
    //Update agent.coalitionId to their agentId (only the original agents)
    // change party of agent to State::Joined
    // add to coalitionsMandates vector & update num of mandates
    // add partyId to coalitions vector

    getParty(partyId).setCoalitionId(coalitionId);
    getParty(partyId).setState(State::Joined);
    coalitionsMandates[coalitionId] += getParty(partyId).getMandates();
    coalitions[coalitionId].push_back(partyId);

}

// #4
void Simulation::addAgent(const Agent& agent)
{
    mAgents.push_back(agent);
}

// #5
const Agent& Simulation::getAgent(int agentId) const
{
    return mAgents[agentId];
}

// #6
int Simulation::getCoalitionMandates(int coalitionId) const
{
    return coalitionsMandates[coalitionId];
}
