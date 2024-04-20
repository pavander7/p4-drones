// 1761414855B69983BD8035097EFBD312EB0527F0

#ifndef FASTTSP_H
#define FASTTSP_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <cmath>
#include "vertex.h"

class FASTTSP
{
public:
    FASTTSP(std::vector<Vertex> &data);
    friend std::ostream &operator<<(std::ostream &os, const FASTTSP &elt);
    ~FASTTSP();
private:
    class Node;
    Node *root;
    double total_C;
    size_t numNodes;
};

class FASTTSP::Node
{
public:
    Node(Vertex vtx_in, uint64_t C_in) : vtx(vtx_in), C(C_in), E(nullptr), prev(nullptr) {}
    Node(Vertex vtx_in, uint64_t C_in, Node *next) : vtx(vtx_in), C(C_in), E(next), prev(nullptr) {next->prev = this;}
    void reassign(Node *next)
    {
        E = next;
        next->prev = E;
        C = vtx.pow_dist(next->vtx);
    }
    /* std::uint64_t swap_cost(Node* other); */
    /* void twoopt(Node* other); */
    uint64_t dist() const {return vtx.pow_dist(E->vtx);}
    Node *encorporate(Vertex &elt);
    Node *next() { return this->E; }
    Node *previous() { return this->prev; }
    friend class FASTTSP;
    friend std::ostream &operator<<(std::ostream &os, const Node &elt)
    {
        os << elt.vtx.i;
        return os;
    }

private:
    Vertex vtx;
    uint64_t C;
    FASTTSP::Node *E;
    FASTTSP::Node *prev;
};

#endif