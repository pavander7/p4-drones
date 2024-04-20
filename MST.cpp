// 1761414855B69983BD8035097EFBD312EB0527F0

#include "MST.h"

using namespace std;

// MST functions
MST::MST(vector<Vertex> &data)
{
    unordered_set<size_t> Q;
    //priority_queue<Node *, vector<Node *>, NodeComp> poss;
    unordered_map<size_t, Node*> poss;
    total_C = 0;
    for (size_t I = 0; I < data.size(); I++)
    {
        Q.insert(I);
    }
    Vertex v = data.front();
    Q.erase(v.i);
    for (size_t n : Q)
    {
        Vertex w = data[n];
        if (v.area() == 1 || w.area() == 1 || w.area() == v.area())
        {
            Node *W = new Node(v, v.pow_dist(w), w);
            if (poss.count(w.i) != 0 && poss[w.i]->C > W->C) poss[w.i] = W;
            else if (poss.count(w.i) == 0) poss.emplace(w.i, W);
        }
    }
    while (!Q.empty())
    {
        priority_queue<Node *, vector<Node *>, NodeComp> opts;
        for (auto [key, elt] : poss) {opts.push(elt);}
        Node *her = opts.top();
        poss.erase(her->E.i);
        //if (Q.count(her->E.i) != 0)
        {
            Q.erase(her->E.i);
            F.push_back(her);
            total_C += sqrt(her->C);
            for (size_t n : Q)
            {
                Vertex w = data[n];
                if (her->E.area() == 1 || w.area() == 1 || w.area() == her->E.area())
                {
                    Node *W = new Node(her->E, her->E.pow_dist(w), w);
                    if (poss.count(w.i) != 0 && poss[w.i]->C > W->C) poss[w.i] = W;
                    else if (poss.count(w.i) == 0) poss.emplace(w.i, W);
                }
            }
        }
        /* priority_queue<Node *, vector<Node *>, NodeComp> temp;
        while (!poss.empty()) {
            Node* t = poss.top();
            poss.pop();
            if (Q.count(t->E.i) != 0) temp.push(t);
        }
        swap(temp, poss); */
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
// MST functions



/* for each unadded value, 
store exactly one vertex that is the cheapest way to get there, 
dynamically populating and updating as the program runs.
problem: how do i find the lowest value
idea: store the first value, refuse to store more expenive options */