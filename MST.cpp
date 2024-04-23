// 1761414855B69983BD8035097EFBD312EB0527F0

#include "MST.h"
//#include <unordered_set>

using namespace std;

// MST functions
MST::MST(const vector<Vertex> &data, bool restrict_in) : restrict(restrict_in)
{ // Prim's Algorithm
    unordered_map<size_t, size_t> Q;
    F.reserve(data.size());
    total_C = 0;
    Vertex v = data.front();
    for (size_t w_i = 1; w_i < data.size(); w_i++)
    {
        //Vertex w = data[w_i];
        if (!(this->valid(v,data[w_i])))
            Q.emplace(w_i, data.size());
        else Q.emplace(w_i, 0);
    }
    while (!Q.empty())
    {
        //cerr << "Remaining Vertices: " << Q.size() << '\n';
        size_t bestopt = data.size();
        uint64_t bestcost = 0;
        for (auto [key, elt] : Q) {
            if (elt != data.size()) {
                uint64_t cost = data[key].pow_dist(data[elt]);
                if (bestcost == 0 || cost < bestcost) {
                    bestcost = cost;
                    bestopt = key;
                }
            }
        }
        if (bestopt == data.size()) {
            cerr << "Cannot construct MST";
            exit(1);
        }
        mst_edge* her = new mst_edge(bestopt, Q[bestopt]);
        {
            Q.erase(bestopt);
            F.push_back(her);
            total_C += sqrt(her->cost(data));
            for (auto [w_i, v_i] : Q)
            {
                if (this->valid(her->vtx_a(data), data[w_i]))
                {
                    if (Q[w_i] == data.size()) Q[w_i] = her->a;
                    else {
                        uint64_t incumbent = data[v_i].pow_dist(data[w_i]);
                        uint64_t proposed = data[her->a].pow_dist(data[w_i]);
                        if (incumbent > proposed) Q[w_i] = her->a;
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
        auto hold = F.back();
        F.pop_back();
        delete hold;
    }
}
// MST functions