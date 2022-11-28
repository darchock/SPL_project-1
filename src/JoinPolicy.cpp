#include "JoinPolicy.h"
#include "Simulation.h"

#include <vector>
using std::vector;

/*
------MandatesJoinPolicy class
*/

// CTR
//MandatesJoinPolicy::MandatesJoinPolicy() { }

//virtual join() func
int MandatesJoinPolicy::join(vector<int>& offers, Simulation& s) {

	int maxMandates = -1;
	int partyIdOfferingAgent = -1;
	int offeringAgentId = -1;
	for (int i : offers) {
		partyIdOfferingAgent = s.getAgent(i).getPartyId();
		int cId = s.getParty(partyIdOfferingAgent).getCoalitionId();
		if (s.getCoalitionMandates(cId) > maxMandates) {
			offeringAgentId = i;
			maxMandates = s.getCoalitionMandates(cId);
		}
	}

	return offeringAgentId;
}

//Destructor
//MandatesJoinPolicy::~MandatesJoinPolicy() = default;

//virtual clone() func
JoinPolicy* MandatesJoinPolicy::clone() const
{
	return new MandatesJoinPolicy();
}

/*
------LastOfferJoinPolicy class
*/

// CTR
//LastOfferJoinPolicy::LastOfferJoinPolicy() { }

//virtual join() func
int LastOfferJoinPolicy::join(vector<int>& offers, Simulation& s) {
	return offers.at(offers.size()-1);
}

//Destructor
//LastOfferJoinPolicy::~LastOfferJoinPolicy() = default;

//virtual clone() func
JoinPolicy* LastOfferJoinPolicy::clone() const
{
	return new LastOfferJoinPolicy();
}

