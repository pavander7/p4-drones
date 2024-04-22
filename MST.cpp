// 1761414855B69983BD8035097EFBD312EB0527F0

#include "MST.h"

using namespace std;

// MST functions
MST::MST(vector<Vertex> &data, bool restrict_in) : restrict(restrict_in)
{
    unordered_map<size_t, Vertex> Q;
    //priority_queue<mNode *, vector<mNode *>, NodeComp> poss;
    unordered_map<size_t, mNode*> poss;
    total_C = 0;
    for (size_t I = 0; I < data.size(); I++)
    {
        Q.emplace(data[I].i, data[I]);
    }
    Vertex v = data.front();
    Q.erase(v.i);
    for (auto [n, w] : Q)
    {
        //Vertex w = data[n];
        if (this->valid(v,w))
        {
            mNode *W = new mNode(v, v.pow_dist(w), w);
            poss.emplace(n, W);
        }
    }
    while (!Q.empty())
    {
        priority_queue<mNode *, vector<mNode *>, NodeComp> opts;
        for (auto [key, elt] : poss) {opts.push(elt);}
        if (opts.empty()) {
            cerr << "Cannot construct MST";
            exit(1);
        }
        mNode *her = opts.top();
        poss.erase(her->E.i);
        //if (Q.count(her->E.i) != 0)
        {
            Q.erase(her->E.i);
            F.push_back(her);
            total_C += sqrt(her->C);
            for (auto [n, w] : Q)
            {
                //Vertex w = data[n];
                if (this->valid(her->E,w))
                {
                    mNode *W = new mNode(her->E, her->E.pow_dist(w), w);
                    //if ((poss.count(n) != 0) && (poss[n]->C > W->C)) poss[n] = W;
                    if (poss.count(n) == 0) poss.emplace(n, W);
                }
            }
        }
    } 
}
std::ostream &operator<<(std::ostream &os, const MST &elt)
{
    os << elt.total_C << endl;
    for (auto n : elt.F)
        os << *n << endl;
    return os;
}
MST::~MST() {
    while (!F.empty()) {
        auto temp = F.front();
        F.pop_front();
        delete temp;
    }
}
bool MST::valid(Vertex v, Vertex w) {
    if (restrict) return (v.area() == 1 || w.area() == 1 || w.area() == v.area());
    else return true;
}
// MST functions



/* for each unadded value, 
store exactly one vertex that is the cheapest way to get there, 
dynamically populating and updating as the program runs.
problem: how do i find the lowest value
idea: store the first value, refuse to store more expenive options */