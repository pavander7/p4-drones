//1761414855B69983BD8035097EFBD312EB0527F0

#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <cmath>

struct Vertex {
    int x, y;
    std::size_t i;
    int area();
    bool operator== (Vertex const &other) const;
    bool operator!= (Vertex const &other) const;
    bool operator< (Vertex const &other) const;
    int pow_dist (Vertex const &other) const;
    int insert_dist (Vertex const &before, Vertex const &after) const;
};

struct VertexComp {
    bool operator() (const Vertex &a, const Vertex &b) const;
};

#endif