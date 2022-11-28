#pragma once

#include <vector>
using std::vector;

class Simulation;


class JoinPolicy {
    public:
        virtual int join(vector<int> &offers, Simulation &s) = 0;
        virtual ~JoinPolicy() = default; 
        virtual JoinPolicy* clone() const = 0;
};

class MandatesJoinPolicy : public JoinPolicy {
    public:
        int join(vector<int> &offers, Simulation &s) override;
        //~MandatesJoinPolicy();
        JoinPolicy* clone() const override;
};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
        int join(vector<int> &offers, Simulation &s) override;
        //~LastOfferJoinPolicy();
        JoinPolicy* clone() const override;
};