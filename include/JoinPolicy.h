#pragma once

class JoinPolicy {
    public:
        virtual int join(vector<int> &offers, Simulation &s);
};

class MandatesJoinPolicy : public JoinPolicy {
    public:
        virtual int join(vector<int> &offers, Simulation &s);
};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
        virtual int join(vector<int> &offers, Simulation &s);
};