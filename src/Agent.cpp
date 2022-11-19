#include <iostream>
#include <iomanip>
#include "Agent.h"
#include "Simulation.h"
#include "SelectionPolicy.h"

using std::cout;
using std::endl;

// Initialization list
Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy), partiesToOffer()
{
    // You can change the implementation of the constructor, but not the signature!
    

}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::step(Simulation &sim)
{
    // TODO: implement this method
    cout << "agent.step()" << std::endl;

    updateSet(sim);
    // agent preform step() only if he has parties to submit an offer to in current step:
    if (partiesToOffer.size() > 0) {

        // inside select() 'selectedPartyId' it's been removed from partiesToOffer vector
        int selectedPartyId = mSelectionPolicy->select(partiesToOffer, sim, mPartyId);
        sim.getParty(selectedPartyId).submitOffer(mAgentId);

    }
    // else: no parties left to offer to
 
}

void Agent::buildSet(Graph &g)
{

    for (int i = 0; i < g.getNumVertices(); ++i) {

        //we add every neighbor of our represented party according to the edges matrix: whomever we have a connection with && whomever that isn't already joined 
        if (g.getEdgeWeight(mPartyId,i) != 0 && g.getParty(i).getState() != State::Joined)
            partiesToOffer.push_back(i);

    }

}

void Agent::updateSet(Simulation &sim)
{

    for (int i = 0; i < partiesToOffer.size(); ++i) {
        int p = partiesToOffer.at(i);
        if (sim.getParty(p).getState() == State::Joined || sim.getParty(p).getCoalitionId() == sim.getParty(mPartyId).getCoalitionId())
            partiesToOffer.erase(partiesToOffer.begin()+i);
    }

}


