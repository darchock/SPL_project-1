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

//Rule of 5 Methods

//Destructor
Agent::~Agent()
{
    if(mSelectionPolicy) delete mSelectionPolicy;
}

//Copy Assignment Operator
Agent& Agent::operator=(const Agent& other)
{
    if (&other != this) {
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        if (mSelectionPolicy) delete mSelectionPolicy;
        mSelectionPolicy = other.mSelectionPolicy->clone(); // is there a need to allocate a pointer to a new obj type JoinPolicy??? and how would i know which one is it??
        for(int p: other.partiesToOffer)
            partiesToOffer.push_back(p);
    }

    return *this;
}

//Copy CTR
Agent::Agent(const Agent &other)
    : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy->clone()), partiesToOffer(other.partiesToOffer) 
{

}

//Move CTR
Agent::Agent(Agent &&other) 
    : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy->clone()), partiesToOffer(other.partiesToOffer)
{
    delete other.mSelectionPolicy;
    other.mSelectionPolicy = nullptr;
}

// Move Assignment Operator
Agent& Agent::operator=(Agent &&other)
{

    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;

    mSelectionPolicy = other.mSelectionPolicy;
    delete other.mSelectionPolicy;
    other.mSelectionPolicy = nullptr;

    for(int p: other.partiesToOffer)
        partiesToOffer.push_back(p);
    
    return *this;
}


//Getters
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

    updateSet(sim);
    // agent preform step() only if he has parties to submit an offer to in current step:
    if (partiesToOffer.size() > 0) {

        // inside select() 'selectedPartyId' is been removed from partiesToOffer vector
        int selectedPartyId = mSelectionPolicy->select(partiesToOffer, sim, mPartyId);
        int toSubmitCoalitionId = sim.getParty(getPartyId()).getCoalitionId();
        //changing party.mState to State::CollectingOffers && initializing party.timer (if this is the first offer submitted to this party) -- is happening in party.step()
        sim.getParty(selectedPartyId).submitOffer(mAgentId, toSubmitCoalitionId); //submitOffer() takes: agentId and the coalitionId that he represents

    }
    // else: no parties left to offer to
}

//#1
void Agent::buildSet(Graph &g)
{
    for (int i = 0; i < g.getNumVertices(); ++i) {
        //we add every neighbor of our represented party according to the edges matrix: whomever we have a connection with && whomever that isn't already joined 
        if (g.getEdgeWeight(mPartyId,i) != 0 && g.getParty(i).getState() != State::Joined)
            partiesToOffer.push_back(i);
    }
}

//#2
void Agent::updateSet(Simulation &sim)
{
    for (unsigned int i = 0; i < partiesToOffer.size(); ++i) {
        int p = partiesToOffer.at(i);
        //1. get my coalitionId
        int myCoalitionId = sim.getParty(getPartyId()).getCoalitionId();
        //2. get the coalition id's of offering agent for party p
        vector<int> pCoalitionsOffers = sim.getParty(p).getOffersCoalitionVec();

        //1) if party p is already joined (accpeted some offer)
        //2) if there is an offer in party p offers vec from an agent that represents the same coalition as i am
        // -->> it means we need to erase that offer from party offers vec
        if (sim.getParty(p).getState() == State::Joined || existOfferFromMyCoalition(pCoalitionsOffers, myCoalitionId))
            partiesToOffer.erase(partiesToOffer.begin()+i);
    }
}

//#3
SelectionPolicy* Agent::clone() const
{
    return mSelectionPolicy;
}

//#4
void Agent::removePartyFromOffers(int toRemoveId)
{
    for (unsigned int i = 0; i < partiesToOffer.size(); ++i) {
        int p = partiesToOffer.at(i);
        if (p == toRemoveId)
            partiesToOffer.erase(partiesToOffer.begin()+i);
    }
}

//#5
bool Agent::existOfferFromMyCoalition(vector<int> &coalitionsOffers, int myCoalitionId)
{
    if (coalitionsOffers.size() == 0)
        return false;

    for (int otherCoalitionId : coalitionsOffers) {
        if (otherCoalitionId == myCoalitionId)
            return true;
    }
    return false;
}