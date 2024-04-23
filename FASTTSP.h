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
    //void swapEdge(std::vector<size_t> &path, std::size_t x, std::size_t y);
    //void twoopt(std::vector<size_t> &path, const std::vector<Vertex> &data);
};

#endif