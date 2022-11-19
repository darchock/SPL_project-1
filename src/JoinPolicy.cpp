#include "JoinPolicy.h"
#include "Simulation.h"
#include <vector>
using std::vector;

class joinPolicy {
	public:
		virtual int join(vector<int>& offers, Simulation& s);
};

class mandatesJoinPolicy: joinPolicy {

	// CTR
	mandatesJoinPolicy::mandatesJoinPolicy() { }
	
	public:
		virtual int join(vector<int>& offers, Simulation& s) {

			int maxMandates = -1;
			int partyIdOfferingAgent = -1;
			int offeringAgentId = -1;
			for (int i : offers) {
				int partyIdOfferingAgent = s.getAgent(i).getPartyId();
				int cId = s.getParty(partyIdOfferingAgent).getCoalitionId();
				if (s.getCoalitionMandates(cId) > maxMandates) {
					offeringAgentId = i;
					maxMandates = s.getCoalitionMandates(cId);
				}
			}
			return offeringAgentId;
		}
};

class LastOfferJoinPolicy : joinPolicy {

	// CTR
	LastOfferJoinPolicy::LastOfferJoinPolicy() { }

	public:
		virtual int join(vector<int>& offers, Simulation& s) {
			return offers.at(offers.size()-1);
		}
};  
