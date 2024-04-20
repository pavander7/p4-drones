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
private:
    class Node;
    class NodeComp;
    double total_C;
    std::deque<Node *> F;
public:
    MST(std::vector<Vertex> &data);
    double dist() { return sqrt(double(total_C)); }
    friend std::ostream &operator<<(std::ostream &os, const MST &elt);
    virtual bool valid(Vertex v, Vertex w) {return (v.area() == 1 || w.area() == 1 || w.area() == v.area());}
    ~MST();
};

class MST::Node
{
public:
    Node(Vertex &v_in, uint64_t C_in, Vertex E_in) : vtx(v_in), C(C_in), E(E_in) {}
    int area() { return vtx.area(); }
    uint64_t pow_dist(Node &other) { return this->vtx.pow_dist(other.vtx); }
    uint64_t pow_dist(Vertex &other) { return this->vtx.pow_dist(other); }
    friend class MST;
    friend class NodeComp;
    friend std::ostream &operator<<(std::ostream &os, const Node &elt)
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
    bool operator()(const Node &a, const Node &b) const
    {
        if (a.C == b.C)
            return true;
        else
            return (a.C > b.C);
    }
    bool operator()(const Node *a, const Node *b) const
    {
        if (a->C == b->C)
            return true;
        else
            return (a->C > b->C);
    }
};

#endif