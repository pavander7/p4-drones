// 1761414855B69983BD8035097EFBD312EB0527F0

#include "OPTTSP.h"
#include <iomanip>
#include "MST.h"
#include "FASTTSP.h"

//https://www.geeksforgeeks.org/traveling-salesman-problem-using-branch-and-bound-2/

using namespace std;

void OPTTSP::genPerms(vector<Vertex> &path, size_t permLength)
{
    /* //cerr << "genPerms on [";
    bool first = true;
    for (auto vtx : path) {
        if (!first) cout << ", ";
        else first = false;
        cout << vtx.i;
    } //cerr << "] with permLength " << permLength << endl; */
    if (permLength == path.size())
    {
        // Do something with the path
        double cost = calcPath(path);
        if (cost < bestCost) {
            bestPath = path;
            bestCost = cost;
            /* std::cerr << "New best cost acheived: " << bestCost << '\n'; */
        }
        return;
    } // if ..complete path

    if (!promising(path, permLength))
    {
        return;
    } // if ..not promising

    for (size_t i = permLength; i < path.size(); ++i)
    {
        swap(path[permLength], path[i]);
        genPerms(path, permLength + 1);
        swap(path[permLength], path[i]);
    } // for ..unpermuted elements
} // genPerms()

bool OPTTSP::promising(vector<Vertex> &path, size_t permLength)
{
    //calculate lower bound
    vector<Vertex> setPortion(path.begin(), path.begin() + int(permLength));
    if (setPortion.empty() || permLength == size_t(0)) return true;
    double setCost = 0;
    for (size_t i = 0; i < setPortion.size() - size_t(1); i++) setCost += sqrt(setPortion[i].pow_dist(setPortion[i+size_t(1)]));
    if (setCost > bestCost) {/* std::cerr << "early abort.\n"; */ return false;}
    else if (path.size() > permLength) {
        vector<Vertex> unsetPortion(path.begin() + int(permLength), path.end());
        //find minimum edges
        //special case: path[permLength]
        double arm1Len = 0;
        double arm2Len = 0;
        {
            uint64_t arm1temp = 0;
            uint64_t arm2temp = 0;
            for (auto m : unsetPortion) {
                uint64_t cost1 = path[0].pow_dist(m);
                uint64_t cost2 = path[permLength - size_t(1)].pow_dist(m);
                if (arm1temp == 0 || cost1 < arm1temp) arm1temp = cost1;
                if (arm2temp == 0 || cost2 < arm2temp) arm2temp = cost2;
            }
            arm1Len = sqrt(arm1temp);
            arm2Len = sqrt(arm2temp);
        } 
        double mstCost = 0;
        {
            uMST mst(unsetPortion);
            mstCost = mst.dist();
        }
        double lowerbound = setCost + arm1Len + arm2Len + mstCost;
        /* for (size_t i = 0; i < path.size(); ++i)
            std::cerr << setw(2) << path[i].i << ' ';
        std::cerr << setw(4) << permLength << setw(10) << setCost;
        std::cerr << setw(10) << arm1Len << setw(10) << arm2Len;
        std::cerr << setw(10) << mstCost << setw(10) << lowerbound << "  " << (lowerbound < bestCost) << '\n'; */
        return (lowerbound < bestCost);
    }
    return true;
}

// OPTTSP functions
OPTTSP::OPTTSP(std::vector<Vertex> &data) : rawData(data), bestPath(data)
{
    {
        FASTTSP estGraph(data);
        bestCost = estGraph.cost();
    }
    //std::cerr << "Best path length = " << bestCost << '\n';
    //std::cerr << "Current path =";
    for (auto her : bestPath) std::cerr << ' ' << her.i;
    //std::cerr << "\n\n" << "Path                               PL   curCost     arm 1     arm 2       MST     Total  Promising?\n";
    genPerms(rawData, size_t(1));
}
double OPTTSP::calcPath(std::vector<Vertex> &path) {
    double cost = 0;
    for (size_t n = 0; n < path.size(); n++) {
        size_t m = (n + size_t(1)) % path.size();
        cost += sqrt(path[n].pow_dist(path[m]));
    } return cost;
}
ostream &operator<<(std::ostream &os, const OPTTSP &elt) {
    os << elt.bestCost << endl;
    for (auto vtx : elt.bestPath) {
        os << vtx.i << ' ';
    } os << endl;
    return os;
}
// OPTTSP functions
