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
    class mst_edge;
    //class mst_tree;
    MST(const std::vector<Vertex> &data, bool restrict_in);
    double dist() { return double(total_C); }
    friend std::ostream &operator<<(std::ostream &os, const MST &elt);
    bool valid(Vertex v, Vertex w);
    bool valid(size_t v, size_t w, const std::vector<Vertex> &data) {return valid(data[v], data[w]);}
    ~MST();
private:
    class NodeComp;
    double total_C;
    bool restrict;
    std::vector<mst_edge*> F;
};

class MST::mst_edge 
{
public:
    mst_edge(size_t a_in, size_t b_in) : a(a_in), b(b_in) {}
    int area(const std::vector<Vertex> &data) { return vtx_a(data).area(); }
    //uint64_t pow_dist(const mst_edge &other, const std::vector<Vertex> &data) { return this->vtx_a(data).pow_dist(other.vtx_a(data)); }
    uint64_t pow_dist(size_t other, const std::vector<Vertex> &data) { return this->vtx_a(data).pow_dist(data[other]); }
    uint64_t cost(const std::vector<Vertex> &data) const {return vtx_a(data).pow_dist(vtx_b(data));}
    Vertex vtx_a(const std::vector<Vertex> &data) const {return data[a];}
    Vertex vtx_b(const std::vector<Vertex> &data) const {return data[b];}
    friend class MST;
    friend class NodeComp;
    friend std::ostream &operator<<(std::ostream &os, const mst_edge &elt)
    {
        if (elt.a < elt.b) {
            os << elt.a << ' ' << elt.b;
        } else os << elt.b << ' ' << elt.a;
        return os;
    }

private:
    size_t a;
    size_t b;
};

#endif