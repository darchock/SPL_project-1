#include "SelectionPolicy.h"
#include "Simulation.h"

#include <vector>
using std::vector;


/*
------MandatesSelectionPolicy class
*/

//virtual select() func
int MandatesSelectionPolicy::select(vector<int>& partiesToOffer, Simulation &s, int pId) {

/*
in current implementation if party mandates isn't unique it'll take the party with the lower Id
*/

	int maxMandates = -1;
	int selectedPartyId = -1;
	int toRemove = -1;
	for (unsigned int i = 0; i < partiesToOffer.size(); ++i) {
		int p = partiesToOffer.at(i);
		if (s.getParty(p).getMandates() > maxMandates) {
			maxMandates = s.getParty(p).getMandates();
			selectedPartyId = p;
			toRemove = i;
		}
	}

    // remove partyId of selected party from partiesToOffer vector
    partiesToOffer.erase(partiesToOffer.begin() + toRemove);

	return selectedPartyId;
}

//virtutal clone() func
SelectionPolicy* MandatesSelectionPolicy::clone() const
{
	return new MandatesSelectionPolicy();
}


/*
------EdgeWeightSelectionPolicy class
*/

//virtual select() func
int EdgeWeightSelectionPolicy::select(vector<int>& partiesToOffer, Simulation &s,int pId) {

/*
in current implementation if party mandates isn't unique it'll take the party with the lower Id
*/

	int maxEdge = -1;
	int selectedPartyId = -1;
    int toRemove = -1;
    for (unsigned int i = 0; i < partiesToOffer.size(); ++i) {
        int p = partiesToOffer.at(i);
        if (s.getGraph().getEdgeWeight(pId, p) > maxEdge) {
			maxEdge = s.getGraph().getEdgeWeight(pId, p);
			selectedPartyId = p;
            toRemove = i;
        }
    }

    // remove partyId of selected party from partiesToOffer vector
	partiesToOffer.erase(partiesToOffer.begin() + toRemove);

	return selectedPartyId;
}

//virtual clone() func
SelectionPolicy* EdgeWeightSelectionPolicy::clone() const
{
	return new EdgeWeightSelectionPolicy();
}
