#include "SelectionPolicy.h"
#include "Simulation.h"
#include <vector>
using std::vector;

class selectionPolicy {
	public:
		virtual int select(vector<int> partiesToOffer, Simulation &s, int pId);
};

class MandatesSelectionPolicy: selectionPolicy {

	// CTR
	MandatesSelectionPolicy::MandatesSelectionPolicy() { }
	
	public:
		virtual int select(vector<int> partiesToOffer, Simulation &s, int pId) {

			/*
			in current implementation if party mandates isn't unique it'll take the party with the lower Id
			*/

			int maxMandates = -1;
			int selectedPartyId = -1;
            int toRemove = -1;
            for (int i = 0; i < partiesToOffer.size(); ++i) {
                int p = partiesToOffer.at(i);
                if (s.getParty(p).getMandates() > maxMandates) {
                    selectedPartyId = p;
                    toRemove = i;
                }
            }

            // remove partyId of selected party from partiesToOffer vector
            partiesToOffer.erase(partiesToOffer.begin() + toRemove);

			return selectedPartyId;
		}
};

class EdgeWeightSelectionPolicy : selectionPolicy {

	// CTR
	EdgeWeightSelectionPolicy::EdgeWeightSelectionPolicy() { }

	public:
		virtual int select(vector<int> partiesToOffer, Simulation &s,int pId) {

			/*
			in current implementation if party mandates isn't unique it'll take the party with the lower Id
			*/

			int maxEdge = -1;
			int selectedPartyId = -1;
            int toRemove = -1;
            for (int i = 0; i < partiesToOffer.size(); ++i) {
                int p = partiesToOffer.at(i);
                if (s.getGraph().getEdgeWeight(pId, p) > maxEdge) {
					selectedPartyId = p;
                    toRemove = i;
                }
            }

            // remove partyId of selected party from partiesToOffer vector
            partiesToOffer.erase(partiesToOffer.begin() + toRemove);

			return selectedPartyId;
		}
};  