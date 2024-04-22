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
    explicit FASTTSP(std::vector<Vertex> &data);
    friend std::ostream &operator<<(std::ostream &os, const FASTTSP &elt);
    double cost() {return total_C;}
private:
    class fNode;
    class Edge;
    double total_C;
    std::vector<Edge> finalPath;
    void swapEdge(std::vector<Edge> &path, std::size_t x, std::size_t y);
};

class FASTTSP::fNode
{
public:
    fNode(Vertex vtx_in, uint64_t C_in) : vtx(vtx_in), C(C_in), E(nullptr), prev(nullptr) {}
    fNode(Vertex vtx_in, uint64_t C_in, fNode *next) : vtx(vtx_in), C(C_in), E(next), prev(nullptr) {next->prev = this;}
    void reassign(fNode *next)
    {
        E = next;
        next->prev = E;
        C = vtx.pow_dist(next->vtx);
    }
    /* std::uint64_t swap_cost(Node* other); */
    /* void twoopt(Node* other); */
    uint64_t dist() const {return vtx.pow_dist(E->vtx);}
    fNode *encorporate(const Vertex &elt);
    fNode *next() { return this->E; }
    friend class FASTTSP;
    friend std::ostream &operator<<(std::ostream &os, const fNode &elt)
    {
        os << elt.vtx.i;
        return os;
    }

private:
    Vertex vtx;
    uint64_t C;
    FASTTSP::fNode *E;
    FASTTSP::fNode *prev;
};

class FASTTSP::Edge {
public:
    Edge(Vertex &a_in, Vertex &b_in) : a(a_in), b(b_in) {}
    friend class FASTTSP;
    size_t first() {return a.i;}
    uint64_t cost() {return a.pow_dist(b);}
private:
    Vertex a;
    Vertex b;
};

#endif