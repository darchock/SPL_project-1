#pragma once

class SelectionPolicy {
    public:
        virtual int select(vector<int> partiesToOffer, Simulation &s, int pId);
 };

class MandatesSelectionPolicy: public SelectionPolicy{ 
    public:
        virtual int select(vector<int> partiesToOffer, Simulation &s, int pId);
};

class EdgeWeightSelectionPolicy: public SelectionPolicy{ 
    public:
        virtual int select(vector<int> partiesToOffer, Simulation &s, int pId);
};