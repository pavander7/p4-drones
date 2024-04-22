// 1761414855B69983BD8035097EFBD312EB0527F0

#include "MST.h"

using namespace std;

// MST functions
MST::MST(vector<Vertex> &data, bool restrict_in) : restrict(restrict_in)
{
    unordered_map<size_t, Vertex> Q;
    //priority_queue<mst_edge *, vector<mst_edge *>, NodeComp> poss;
    unordered_map<size_t, size_t> poss;
    total_C = 0;
    for (size_t I = 1; I < data.size(); I++)
    {
        Q.emplace(I, data[I]);
    }
    Vertex v = data.front();
    for (auto [w_i, w] : Q)
    {
        //Vertex w = data[w_i];
        if (this->valid(v,w))
        {
            poss.emplace(w_i, 0);
        }
    }
    while (!Q.empty())
    {
        NodeComp comp(data);
        priority_queue<mst_edge*, vector<mst_edge*>, NodeComp> opts(comp);
        for (auto [key, elt] : poss) {
            mst_edge* e = new mst_edge(elt, key);
            opts.push(e);
        }
        if (opts.empty()) {
            cerr << "Cannot construct MST";
            exit(1);
        }
        mst_edge* her = opts.top();
        poss.erase(her->b);
        {
            Q.erase(her->b);
            F.push_back(her);
            total_C += sqrt(her->cost(data));
            for (auto [w_i, w] : Q)
            {
                //Vertex w = data[w_i];
                if (this->valid(her->vtx_b(data),w))
                {
                    if (poss.count(w_i) == 0) poss.emplace(w_i, her->b);
                    else {
                        mst_edge incumbent(poss[w_i], w_i);
                        mst_edge proposed(her->b, w_i);
                        if (incumbent.cost(data) > proposed.cost(data)) poss[w_i] = her->b;
                    }
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
bool MST::valid(Vertex v, Vertex w) {
    if (restrict) return (v.area() == 1 || w.area() == 1 || w.area() == v.area());
    else return true;
}
MST::~MST() {
    while (!F.empty()) {
        auto hold = F.front();
        F.pop_front();
        delete hold;
    }
}
// MST functions



/* for each unadded value, 
store exactly one vertex that is the cheapest way to get there, 
dynamically populating and updating as the program runs.
problem: how do i find the lowest value
idea: store the first value, refuse to store more expenive options */