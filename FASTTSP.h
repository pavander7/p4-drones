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
    explicit FASTTSP(const std::vector<Vertex> &data);
    friend std::ostream &operator<<(std::ostream &os, const FASTTSP &elt);
    double cost() {return total_C;}
    std::vector<size_t> givePath() const {return finalPath;}
private:
    class fast_node;
    class fast_edge;
    double total_C;
    std::vector<size_t> finalPath;
    void swapEdge(std::vector<size_t> &path, std::size_t x, std::size_t y);
    void twoopt(std::vector<size_t> &path, const std::vector<Vertex> &data);
};

/* class FASTTSP::fast_node 
{
public:
    explicit fast_node(size_t vtx_in) : v_i(vtx_in), E(nullptr), prev(nullptr) {}
    fast_node(size_t vtx_in, fast_node *next) : v_i(vtx_in), E(next), prev(nullptr) {next->prev = this;}
    void reassign(fast_node *next)
    {
        E = next;
        next->prev = E;
    }
    Vertex vtx(const std::vector<Vertex> &data) const {return data[v_i];}
    uint64_t dist(const std::vector<Vertex> &data) const {return vtx(data).pow_dist(E->vtx(data));}
    fast_node *encorporate(size_t i);
    fast_node *next() { return this->E; }
    friend class FASTTSP;
    friend std::ostream &operator<<(std::ostream &os, const fast_node &elt)
    {
        os << elt.v_i;
        return os;
    }

private:
    size_t v_i;
    FASTTSP::fast_node *E;
    FASTTSP::fast_node *prev;
};

class FASTTSP::fast_edge 
{
public:
    fast_edge(const size_t &a_in, const size_t &b_in) : a_i(a_in), b_i(b_in) {}
    friend class FASTTSP;
    size_t first() {return a_i;}
    uint64_t cost(const std::vector<Vertex> &data) {return data[a_i].pow_dist(data[b_i]);}
private:
    size_t a_i;
    size_t b_i;
}; */

#endif