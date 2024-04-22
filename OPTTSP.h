// 1761414855B69983BD8035097EFBD312EB0527F0

#ifndef OPTTSP_H
#define OPTTSP_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <cmath>
#include "MST.h"
#include "vertex.h"

class OPTTSP 
{
public:
    explicit OPTTSP(std::vector<Vertex> &data);
    friend std::ostream &operator<<(std::ostream &os, const OPTTSP &elt);

private:
    std::vector<size_t> bestPath;
    double bestCost;
    class uMST;

    void genPerms(std::vector<size_t> &path, std::size_t permLength, std::vector<Vertex> &data);
    bool promising(std::vector<size_t> &path, std::size_t permLength, std::vector<Vertex> &data);
    double calcPath(std::vector<size_t> &path, std::vector<Vertex> &data);
};

class OPTTSP::uMST : public MST 
{
public:
    explicit uMST(std::vector<Vertex> &data) : MST(data, false) {}
};

#endif