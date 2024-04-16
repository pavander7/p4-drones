// 1761414855B69983BD8035097EFBD312EB0527F0

#ifndef OPTTSP_H
#define OPTTSP_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <cmath>
#include "vertex.h"

/* class OPTTSP
{
public:
    OPTTSP(std::vector<Vertex> &data);
    friend std::ostream &operator<<(std::ostream &os, const OPTTSP &elt);

private:
    uint64_t total_C;
    class Node;
    Node *root;
};

class OPTTSP::Node
{
public:
    Node(Vertex vtx_in, uint64_t C_in) : vtx(vtx_in), C(C_in), E(nullptr) {}
    Node(Vertex vtx_in, uint64_t C_in, Node *next) : vtx(vtx_in), C(C_in), E(next) {}
    void reassign(Node *next)
    {
        E = next;
        C = vtx.pow_dist(next->vtx);
    }
    uint64_t insert_dist(Vertex &elt);
    Node *encorporate(Vertex &elt);
    Node *next() { return this->E; }
    friend std::ostream &operator<<(std::ostream &os, const Node &elt)
    {
        os << elt.vtx.i;
        return os;
    }

private:
    Vertex vtx;
    uint64_t C;
    OPTTSP::Node *E;
}; */

#endif