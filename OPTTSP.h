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
    OPTTSP(std::vector<Vertex> &data);
    friend std::ostream &operator<<(std::ostream &os, const OPTTSP &elt);

private:
    std::vector<Vertex> rawData;
    std::vector<Vertex> bestPath;
    double bestCost;
    class uMST;

    void genPerms(std::vector<Vertex> &path, std::size_t permLength);
    bool promising(std::vector<Vertex> &path, std::size_t permLength, double &lowerbound);
    double calcPath(std::vector<Vertex> &path);

};

class OPTTSP::uMST : public MST
{
public:
    uMST(std::vector<Vertex> &data) : MST(data) {}
    bool valid(Vertex v, Vertex w) {return (v != w);}
};

#endif