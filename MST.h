// 1761414855B69983BD8035097EFBD312EB0527F0

#ifndef MST_H
#define MST_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <cmath>
#include "vertex.h"

class MST
{
public:
    class mNode;
    MST(std::vector<Vertex> &data, bool restrict_in);
    double dist() { return double(total_C); }
    friend std::ostream &operator<<(std::ostream &os, const MST &elt);
    bool valid(Vertex v, Vertex w);
    ~MST();
private:
    class NodeComp;
    double total_C;
    bool restrict;
    std::deque<mNode *> F;
};

class MST::mNode
{
public:
    mNode(Vertex &v_in, uint64_t C_in, Vertex E_in) : vtx(v_in), C(C_in), E(E_in) {}
    int area() { return vtx.area(); }
    uint64_t pow_dist(mNode &other) { return this->vtx.pow_dist(other.vtx); }
    uint64_t pow_dist(Vertex &other) { return this->vtx.pow_dist(other); }
    uint64_t cost() {return C;}
    friend class MST;
    friend class NodeComp;
    friend std::ostream &operator<<(std::ostream &os, const mNode &elt)
    {
        if (elt.vtx.i < elt.E.i) {
            os << elt.vtx.i << ' ' << elt.E.i;
        } else os << elt.E.i << ' ' << elt.vtx.i;
        return os;
    }

private:
    Vertex vtx;
    uint64_t C;
    Vertex E;
};

class MST::NodeComp
{
public:
    bool operator()(const mNode &a, const mNode &b) const
    {
        if (a.C == b.C)
            return true;
        else
            return (a.C > b.C);
    }
    bool operator()(const mNode *a, const mNode *b) const
    {
        if (a->C == b->C)
            return true;
        else
            return (a->C > b->C);
    }
};

#endif