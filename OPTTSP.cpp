// 1761414855B69983BD8035097EFBD312EB0527F0

#include "OPTTSP.h"
#include "iomanip"
#include "MST.h"

//https://www.geeksforgeeks.org/traveling-salesman-problem-using-branch-and-bound-2/

using namespace std;

void OPTTSP::genPerms(vector<Vertex> &path, size_t permLength)
{
    //cerr << "genPerms on [";
    bool first = true;
    for (auto vtx : path) {
        if (!first) cout << ", ";
        else first = false;
        cout << vtx.i;
    } //cerr << "] with permLength " << permLength << endl;
    if (permLength == path.size())
    {
        // Do something with the path
        double cost = calcPath(path);
        if (cost < bestCost) bestPath = path;
        return;
    } // if ..complete path

    double curCost = 0;
    if (!promising(path, permLength, curCost))
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

bool OPTTSP::promising(vector<Vertex> &path, size_t permLength, double &lowerbound)
{
    //calculate lower bound
    vector<Vertex> setPortion(path.begin(), path.begin() + int(permLength));
    double setCost = 0;
    if (!setPortion.empty()) calcPath(setPortion);
    if (setCost > bestCost) {return false; cerr << "early abort.\n";}
    else if (path.size() > permLength) {
        vector<Vertex> unsetPortion(path.begin() + int(permLength), path.end());
        OPTTSP::uMST mst(unsetPortion);
        double mstCost = mst.dist();
        lowerbound = setCost + mstCost;
        for (size_t i = 0; i < path.size(); ++i)
            cerr << setw(2) << path[i].i << ' ';
        cerr << setw(4) << permLength << setw(10) << lowerbound;
        // cerr << setw(10) << arm1Len << setw(10) << arm2Len;
        cerr << setw(10) << mstCost << setw(10) << lowerbound << "  " << (lowerbound < bestCost) << '\n';
        return (lowerbound < bestCost);
    }
    return true;
}

// OPTTSP functions
OPTTSP::OPTTSP(std::vector<Vertex> &data) : rawData(data), bestPath(data), bestCost(calcPath(data))
{
    genPerms(rawData, size_t(0));
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