#pragma once

#include <vector>
using std::vector;

class Simulation;

class SelectionPolicy {
    public:
        virtual int select(vector<int>& partiesToOffer, Simulation &s, int pId) = 0;
        virtual ~SelectionPolicy() = default;
        virtual SelectionPolicy* clone() const = 0;
 };

class MandatesSelectionPolicy: public SelectionPolicy{ 
    public:
        int select(vector<int>& partiesToOffer, Simulation &s, int pId) override;
        //~MandatesSelectionPolicy();
        SelectionPolicy* clone() const override;
};

class EdgeWeightSelectionPolicy: public SelectionPolicy{ 
    public:
        int select(vector<int>& partiesToOffer, Simulation &s, int pId) override;
        //~EdgeWeightSelectionPolicy();
        SelectionPolicy* clone() const override;
};