// 1761414855B69983BD8035097EFBD312EB0527F0

#include "MST.h"
//#include <unordered_set>

using namespace std;

// MST functions
MST::MST(const vector<Vertex> &data, bool restrict_in) : restrict(restrict_in)
{ // Prim's Algorithm
    unordered_map<size_t, size_t> Q;
    //priority_queue<mst_edge *, vector<mst_edge *>, NodeComp> poss;
    //vector<size_t> poss(data.size(), 0);
    F.reserve(data.size());
    total_C = 0;
    /* for (size_t I = 1; I < data.size(); I++)
    {
        Q.emplace(I);
    } */
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
        //NodeComp comp(data);
        //priority_queue<mst_edge*, vector<mst_edge*>, NodeComp> opts(comp);
        size_t bestopt = 0;
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
        if (bestcost == 0) {
            cerr << "Cannot construct MST";
            exit(1);
        }
        mst_edge* her = new mst_edge(bestopt, Q[bestopt]);
        //poss[her->b] = data.size();
        {
            Q.erase(bestopt);
            F.push_back(her);
            total_C += sqrt(her->cost(data));
            for (auto [w_i, v_i] : Q)
            {
                //Vertex w = data[w_i];
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
/* MST::MST(vector<Vertex> &data, bool restrict_in) : restrict(restrict_in)
{ // Kruskal's Algorithm
    mst_tree *final_tree = nullptr;
    {
        unordered_map<size_t, mst_edge*> forest;
        unordered_map<size_t, mst_tree*> M;
        unordered_set<mst_tree*> T;
        forest.reserve(data.size());
        total_C = 0;
        for (size_t t = 0; t < data.size(); t++) {
            auto temp = new mst_tree(t);
            T.insert(temp);
            M[t] = temp;
        }
        for (size_t o = 0; o < data.size(); o++) {
            for (size_t i = o + size_t(1); i < data.size(); i++) {
                size_t l = 0, h = 0;
                if (i < o) {l = i; h = o;}
                else {l = o; h = i;}
                if (valid(data[l], data[h]) && ((forest.count(l) == 0) || (data[l].pow_dist(data[h]) < forest.at(l)->cost(data)))) {
                    if (forest.count(l) != 0) {
                        auto temp = forest.at(l);
                        forest.at(l) = new mst_edge(l, h);
                        delete temp;
                    } else {
                        auto temp = new mst_edge(l, h);
                        forest.emplace(l, temp);
                    }
                }
            }
        }
        while (T.size() > 1) {
            mst_tree* bestopt = nullptr;
            mst_edge* best_e = nullptr;
            uint64_t bestcost = 0;
            for (auto [t, e] : forest) {
                if (bestcost == 0 || e->cost(data) < bestcost) {
                    bestopt = M[t];
                    bestcost = e->cost(data);
                    best_e = e;
                }
            } if (bestopt == nullptr) {
                cerr << "Cannot construct MST";
                exit(1);
            } else {
                auto victim = M[best_e->b];
                bestopt->encorporate(*victim, best_e);
                for (auto i : victim->Q) {
                    M[i] = bestopt;
                }
                T.erase(victim);
                delete victim;
                size_t p = best_e->a;
                forest.erase(p);
                vector<size_t> O = {p};
                for (size_t i = 0; i < data.size(); i++) {
                    if (M[p] == M[i]) {
                        forest.erase(i);
                        O.push_back(i);
                    }
                }
                for (auto o : O) {
                    for (size_t i = o + size_t(1); i < data.size(); i++) { 
                        size_t l = 0, h = 0;
                        if (i < o) {l = i; h = o;}
                        else {l = o; h = i;}
                        if ((M[l] != M[h]) && valid(data[l], data[h]) && (((forest.count(l)) == 0) || data[l].pow_dist(data[h]) < forest.at(l)->cost(data))) {
                            if (forest.count(l) != 0) {
                                auto temp = forest.at(l);
                                forest.at(l) = new mst_edge(l, h);
                                delete temp;
                            } else {
                                auto temp = new mst_edge(l, h);
                                forest.emplace(l, temp);
                            }
                        }
                    }
                }
            }
        }
        final_tree = M[0];
        while (!final_tree->E.empty()) {
            auto temp = final_tree->E.back();
            F.push_back(temp);
            final_tree->E.pop_back();
            total_C += sqrt(temp->cost(data));
        }
    }
} */
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

// mst-tree functions
/* void MST::mst_tree::encorporate(MST::mst_tree &other, MST::mst_edge* connection) {
    //if (connected(connection) && other.connected(connection)) {
        this->E.push_back(connection);
        for (auto e : other.E) this->E.push_back(e);
        for (auto v_i : other.Q) this->Q.insert(v_i);
    //}
}
bool MST::mst_tree::connected(MST::mst_edge &elt) {
    return ((Q.count(elt.a) != 0) || (Q.count(elt.b) != 0));
} */
// mst-tree functions