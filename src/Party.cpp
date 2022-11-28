#include <iostream>
#include <iomanip>
#include "Party.h"
#include "Simulation.h"
#include "JoinPolicy.h"
#include "SelectionPolicy.h"
#include "Agent.h"


using std::cout;
using std::endl;

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting), mCoalitionId(-1), offers(), coalitionOfOfferingAgent(), timer(0) 
{
    // You can change the implementation of the constructor, but not the signature!
}

//Destructor
Party::~Party() 
{ 
    if (mJoinPolicy) delete mJoinPolicy;
}

//Copy Assignment Operator
Party& Party::operator=(const Party& other) // does assignment operator needs an initizliazation list for complexed obj as well as copy ctr?
{
    if (&other != this) {
        mId = other.mId;
        mName = other.mName;
        mMandates = other.mMandates;
        if (mJoinPolicy) delete mJoinPolicy;
        mJoinPolicy = other.mJoinPolicy->clone(); // is there a need to allocate a pointer to a new obj type JoinPolicy??? and how would i know which one is it??
        mState = other.mState;
        mCoalitionId = other.mCoalitionId;
        for (int o: other.offers)
            offers.push_back(o);
        for (int c : other.coalitionOfOfferingAgent)
            coalitionOfOfferingAgent.push_back(c);
        timer = other.timer;
    }

    return *this;
}

//Copy CTR
Party::Party(const Party& other)
    : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy->clone()), mState(other.mState), mCoalitionId(other.mCoalitionId), offers(other.offers), coalitionOfOfferingAgent(other.coalitionOfOfferingAgent), timer(other.timer)
{
    
}

 //Move CTR
Party::Party(Party&& other)
    : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy->clone()), mState(other.mState), mCoalitionId(other.mCoalitionId), offers(other.offers), coalitionOfOfferingAgent(other.coalitionOfOfferingAgent), timer(other.timer)
{
    delete other.mJoinPolicy;
    other.mJoinPolicy = nullptr;
}

 //Move Assignment Operator
Party& Party::operator=(Party&& other)
{
    
    mId = other.mId;
    mName = other.mName;
    mMandates = other.mMandates;

    mJoinPolicy = other.mJoinPolicy;
    delete other.mJoinPolicy;
    other.mJoinPolicy = nullptr;

    mState = other.mState;
    mCoalitionId = other.mCoalitionId;

    for (int o: other.offers)
        offers.push_back(o);
    for (int c : other.coalitionOfOfferingAgent)
            coalitionOfOfferingAgent.push_back(c);
    
    timer = other.timer;

    return *this;
}

// Getters
State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string & Party::getName() const
{
    return mName;
}

void Party::step(Simulation &s)
{
    // TODO: implement this method
    
    if (this->mState != State::Joined) {

        if (this->mState == State::CollectingOffers) {
            timer += 1;
            if (timer == 3) {

                // 1. choose offer to accpet according to JoinPolicy: method that will return an agentId of the choosen agent from offers vec
                int aId = mJoinPolicy->join(offers, s);
                //2. remove chosen agentId from this party.offers vec -
                // not so critical because this party is finished
                removeOffer(aId);
                //3. get the chosen Agent himself to clone him to represent this party
                const Agent& toClone = s.getAgents().at(aId);
                //4. get the coalitionId that the chosen agent is representing
                int cId = s.getParty(toClone.getPartyId()).getCoalitionId();
                //5. add this party to the chosen's agent coalition
                s.addToCoalition(cId, this->getId());
                //6. clone the chosen agent to represent this party in future steps
                cloneAgent(s, toClone.clone());

            }     
        }
        //else //mState is still in State::Waiting       
    }

}

// #1
int Party::getCoalitionId()
{
    return mCoalitionId;
}

//#2
void Party::setCoalitionId(int coalitionId)
{
    mCoalitionId = coalitionId;
}

//#3
void Party::submitOffer(int agentId, int representedCoalitionId)
{
    offers.push_back(agentId);
    coalitionOfOfferingAgent.push_back(representedCoalitionId);
    if (mState == State::Waiting)
        setState(State::CollectingOffers);
}

//#4
vector<int>& Party::getOffers()
{
    return offers;
}

//#5
void Party::setTimer()
{
    timer = 1;
}

//#6
void Party::removeOffer(int agentId)
{
    for (unsigned int i = 0; i < offers.size(); ++i) {
        int oId = offers.at(i);
        if (oId == agentId) {
            offers.erase(offers.begin()+i);
            break;
        }
    }
}

//#7
int Party::getId()
{
    return mId;
}

//#8
void Party::cloneAgent(Simulation& sim, SelectionPolicy *selectionPolicy)
{
    Agent newAgent(sim.getAgents().size(), this->getId(), selectionPolicy->clone());
    newAgent.buildSet(sim.getGraph());
    sim.addAgent(newAgent);
}

//#9
int Party::getOffersCoalitionId(int offerId)
{
    return coalitionOfOfferingAgent[offerId];
}

//#10
vector<int>& Party::getOffersCoalitionVec()
{
    return coalitionOfOfferingAgent;
}
