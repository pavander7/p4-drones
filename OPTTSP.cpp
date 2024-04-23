// 1761414855B69983BD8035097EFBD312EB0527F0

#include "OPTTSP.h"
#include <iomanip>
#include "MST.h"
#include "FASTTSP.h"

//https://www.geeksforgeeks.org/traveling-salesman-problem-using-branch-and-bound-2/

using namespace std;

void OPTTSP::genPerms(vector<size_t> &path, size_t permLength, const std::vector<Vertex> &data)
{
    if (permLength == path.size())
    {
        // Do something with the path
        double cost = calcPath(path, data);
        if (cost < bestCost) {
            bestPath = path;
            bestCost = cost;
            //std::cerr << "New best cost acheived: " << bestCost << '\n';
        }
        return;
    } // if ..complete path

    if (!promising(path, permLength, data))
    {
        return;
    } // if ..not promising

    for (size_t i = permLength; i < path.size(); ++i)
    {
        swap(path[permLength], path[i]);
        genPerms(path, permLength + 1, data);
        swap(path[permLength], path[i]);
    } // for ..unpermuted elements
} // genPerms()

bool OPTTSP::promising(vector<size_t> &path, size_t permLength, const std::vector<Vertex> &data)
{
    if (path.size() - permLength < 5) return true;
    //calculate lower bound
    if (permLength <= size_t(1)) return true;
    double setCost = 0;
    for (size_t i = 0; i < permLength - size_t(1); i++) setCost += sqrt(data[path[i]].pow_dist(data[path[i+size_t(1)]]));
    if (setCost > bestCost) {/* std::cerr << "early abort.\n"; */ return false;}
    if (path.size() > permLength) {
        vector<size_t> unsetPortion(path.begin() + int(permLength), path.end());

        double mstCost = this->estimate(unsetPortion, data);
        if ((setCost + mstCost) > bestCost) return false;

        double arm1Len = 0;
        double arm2Len = 0;
        {
            uint64_t arm1temp = 0;
            uint64_t arm2temp = 0;
            for (auto m : unsetPortion) {
                uint64_t cost1 = data[path[0]].pow_dist(data[m]);
                uint64_t cost2 = data[path[permLength - size_t(1)]].pow_dist(data[m]);
                if (arm1temp == 0 || cost1 < arm1temp) arm1temp = cost1;
                if (arm2temp == 0 || cost2 < arm2temp) arm2temp = cost2;
            }
            arm1Len = sqrt(arm1temp);
            arm2Len = sqrt(arm2temp);
        } 
        double lowerbound = setCost + arm1Len + arm2Len + mstCost;
        /* for (size_t i = 0; i < path.size(); ++i)
            std::cerr << setw(2) << path[i] << ' ';
        std::cerr << setw(4) << permLength << setw(10) << setCost;
        std::cerr << setw(10) << arm1Len << setw(10) << arm2Len;
        std::cerr << setw(10) << mstCost << setw(10) << lowerbound << "  " << (lowerbound < bestCost) << '\n'; */
        return (lowerbound < bestCost);
    }
    return true;
}

// OPTTSP functions
OPTTSP::OPTTSP(const std::vector<Vertex> &data)
{
    bestPath.resize(data.size());
    {
        FASTTSP estGraph(data);
        bestCost = estGraph.cost();
        bestPath = estGraph.givePath();
    }
    //std::cerr << "Best path length = " << bestCost << '\n';
    //for (size_t n = 0; n < data.size(); n++) bestPath[n] = n;
    /* std::cerr << "Current path =";
    for (auto her : bestPath) std::cerr << ' ' << her;
    std::cerr << "\n\n" << "Path                               PL   curCost     arm 1     arm 2       MST     Total  Promising?\n"; */
    auto currPath = bestPath;
    genPerms(currPath, size_t(1), data);
}
double OPTTSP::calcPath(std::vector<size_t> &path, const std::vector<Vertex> &data) {
    double cost = 0;
    for (size_t n = 0; n < path.size(); n++) {
        size_t m = (n + size_t(1)) % path.size();
        cost += sqrt(data[path[n]].pow_dist(data[path[m]]));
    } return cost;
}
ostream &operator<<(std::ostream &os, const OPTTSP &elt) {
    os << elt.bestCost << endl;
    for (auto i : elt.bestPath) {
        os << i << ' ';
    } os << endl;
    return os;
}
double OPTTSP::estimate(const std::vector<size_t> &path, const std::vector<Vertex> &data) {
    vector<Vertex> vtxPath;
    vtxPath.reserve(path.size());
    for (auto i : path) vtxPath.push_back(data[i]);
    uMST mst(vtxPath);
    return mst.dist();
}
// OPTTSP functions
