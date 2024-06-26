// 1761414855B69983BD8035097EFBD312EB0527F0

#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <cmath>

struct Vertex 
{
    int x, y;
    int area();
    bool operator==(Vertex const &other) const;
    bool operator!=(Vertex const &other) const;
    bool operator<(Vertex const &other) const;
    uint64_t pow_dist(Vertex const &other) const;
};

#endif