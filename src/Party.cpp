#include <iostream>
#include <iomanip>
#include "Party.h"
#include "Simulation.h"
#include "JoinPolicy.h"


using std::cout;
using std::endl;

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting), mCoalitionId(-1), offers(), timer(0) 
{
    // You can change the implementation of the constructor, but not the signature!

    // ADD PRIVATE TIMER ACCORDING TO THE FIRST OFFER RECIVED
    // ADD 'MAIL BOX' OF OFFERS FROM AGENTS:
    /*
    MAIL BOX:
        fields of an object Offer()
    
    */
}

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

void Party::step(Simulation &s)
{
    // TODO: implement this method
    cout << "praty.step()" << std::endl;
    
    if (this->mState != State::Joined) {
        
        if (this->mState == State::Waiting) {

            if (offers.size() > 0) {
                timer += 1;
                mState = State::CollectingOffers;
            }
            //else there was no offers last iteration

        }
        else { // means mState == State::CollectingOffers
            
            timer += 1;
            if (timer == 3) {
                
                // 1. choose offer to accpet according to JoinPolicy: method that will return a pointer of the choosen agent from offers vec
                // 2. addToCoalition() (changes inside party's State to Joined)
                // 3. clone agent that we got the accepted offer from
                // 4. vec offers: {1,4} -- agentId of agent who submitted an offer

                //mJoinPolicy.join(offers, s);
                int aId = mJoinPolicy->join(offers, s);
                const Agent& toClone = s.getAgents().at(aId);
                int cId = s.getParty(toClone.getPartyId()).getCoalitionId();
                s.addToCoalition(cId, toClone.getPartyId());
                // clone agent toClone and add him to s.mAgents with fields: agentId = mAgents.size()


                /*
                1. choose from offers vec
                int aId = mJoinPolicy.join(offers, s);
                int pId = s.getAgent(aId).getPartyId();
                int cId = s.getParty(pId).getCoalitionId();
                2. add to the existing coalition
                s.addToCoalition(cId, pId);
                3. clone the agent from whom we got the accepted offer
                4. add the cloned agent to mAgents in simulation class 

                */

                // #1
                //int coalitionToJoin = mJoinPolicy.join(*this); option 1
                //Agent toClone = mJoinPolicy.join(offers, s);
                // #2
                //s.addToCoalition(toClone.coalitionId, mId);
                // #3

            }
                
        }        
    }

}

const string & Party::getName() const
{
    return mName;
}

//added methods
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
void Party::submitOffer(int agentId)
{
    offers.push_back(agentId);
}

//#4
vector<int> Party::getOffers()
{
    return offers;
}

