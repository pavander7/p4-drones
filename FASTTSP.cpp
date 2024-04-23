// 1761414855B69983BD8035097EFBD312EB0527F0

#include "FASTTSP.h"
#include <list>

using namespace std;

// FASTTSP functions
FASTTSP::FASTTSP(const std::vector<Vertex> &data) : total_C(0) // total_C initialized as 0 for later incrementation
{ 
    //cerr << "Beginning FASTTSP on dataset of size: " << data.size() << '\n';
    //NOTATION:

    // let u(X,Y) be the union of sets X and Y
    // let i(X,Y) be the intersection of sets X and Y
    // let !X be the inverse set of X
    // let a € X mean that value a is a member of set X

    // let D be the set of vertices in data.
    // let G be the graph of D
    // let T be a path on G
    // let T_e be the subset of T containing the edges
    // let T_v be the subset of V containing the vertices

    // let xy be the edge from vertex x to vertex y with weight w(ab), where x, y € D
    
    //cerr << "stage 1: cheapest insertion heuristic (CIH)\n";

    //cerr << "1.1: import dataset\n";
    list<size_t> tour {0, 1};
    vector<size_t> Q; // Q = D - !T_v : set of the indices of all vertices not yet in DLL
    for (size_t I = 2; I < data.size(); I++) { Q.push_back(I); } // add all vertices to Q, 0 & 1 are ommitted since they would be immediately removed in 1.2
    //total_C = size_t(2) * sqrt(data[0].pow_dist(data[1]));

    //cerr << "1.2: execute CIH or NIH\n";
    while (!Q.empty()) // true as long as there are unconnected points
    {
        //cerr << "Remaining Vertices: " << Q.size() << '\n';
        //cerr << "1.2.1: define variables\n";
        double c = 0; // cost w(c) of best insertion c, where c is an insertion of the form ab -> axb, where a, b € T_v && x € Q
        size_t to_add = data.size(); // best vertex c_x to include (initialized to arbitrary default value)
        auto after = tour.begin(); // pointer to the edge c_ab that will be affected by insertion
        size_t w = Q.back();
        Q.pop_back();

        //cerr << "1.2.2: loop through every edge in DLL\n";  
        auto it = tour.begin();
        auto next = ++tour.begin();
        while (it != tour.end())
        {
            size_t v = *it;
            size_t u = *next;
            // let ab be the edge defined by elt
            // ab € T_e, a, b € T_v
        
            // let x be the candidate vertex
            //cerr << "1.2.3: define & analyze x\n";
            Vertex candidate = data[w]; // x
            Vertex a = data[v];
            Vertex b = data[u];

            // CIH version
            double left_leg = sqrt(candidate.pow_dist(a)); // w(ax)
            double right_leg = sqrt(candidate.pow_dist(b)); // w(xb)
            double curr_dist = sqrt(a.pow_dist(b)); // w(ab)
            double can_dist = (left_leg + right_leg) - curr_dist; // w(axb) == w(ax) + w(xb) - w(ab): increase to total cost of the path if x is inserted between a & b
            
            // NIH version
            //double can_dist = sqrt(candidate.pow_dist(a));

            //cerr << "1.3.4: evaluate insertion (ab -> axb)\n";
            if (c == 0 || can_dist < c) // if w(c) == 0, c is undefined
            {                           // if (w(axb) < c), c should be disregarded in favor of axb
                to_add = w; // c_x = x
                c = can_dist; // w(c) = w(axb)
                after = it;
                //before = elt; // c_ab = ab
            } 
            
            ++it; ++next;
            if (next == tour.end()) next = tour.begin();
        }

        //cerr << "1.4: execute best insertion c\n";
        if (to_add < data.size()) { // only execute if c is defined

            // NIH version
            /* auto left = after; if (after == tour.begin()) left = tour.end(); left--;
            auto right = after; right++; if (after == tour.end()) left = tour.begin();
            uint64_t lDist = data[*left].pow_dist(data[to_add]);
            uint64_t rDist = data[*right].pow_dist(data[to_add]);
            if (rDist < lDist) ++after; */

            if (*after == tour.back()) tour.push_back(to_add);
            else tour.insert(++after, to_add);
            //total_C += c;
        }
    } 

    //cerr << "stage 2: 2-opt heuristic\n";

    //cerr << "2.1: convert T from DLL to vector\n";
    finalPath = vector<size_t>(tour.begin(), tour.end());
    //cerr << "2.2: loop through edges in T\n";
    //twoopt(finalPath, data);
    //twoopt(finalPath, data);

    //cerr << "stage 3: report results\n";
    for (size_t i = 0; i < finalPath.size(); i++) {
        auto a = data[finalPath[i]];
        auto b = data[finalPath[(i + size_t(1)) % tour.size()]];
        total_C += sqrt(a.pow_dist(b)); // sums total cost of T by iterating through each edge
    }
}
std::ostream &operator<<(std::ostream &os, const FASTTSP &elt)
{
    os << elt.total_C << endl;
    for (auto v : elt.finalPath) { os << v << ' '; }
    os << '\n';
    return os;
}
/* void FASTTSP::swapEdge(vector<size_t> &path, size_t x, size_t y) {
    // let xa...by define the path between x and y such that xa and by are edges, and ... is a valid subpath between a and b
    if (x == y) return; // if x = y, nothing left to swap
    size_t x_next = (x + size_t(1) % path.size()); // a
    size_t y_prev = size_t(y + path.size() - 1) % path.size(); // b
    // perform preliminary swap
    size_t temp_i = path[x];
    path[x] = path[y];
    path[y] = temp_i;
    if ((x == y_prev) || (y == x_next)) return; // if x and y are consecutive, swap needn't be "passed", path is complete
    else { // "pass" swap to next pair of edges
        swapEdge(path, x_next, y_prev); // recursively call swapEdge to reverse remaining inner path "..."
    }
} 
void FASTTSP::twoopt(std::vector<size_t> &path, const std::vector<Vertex> &data) {
    for (size_t x = 0; x < path.size() - size_t(2); x++) {
        //cerr << "2.2.1: identify first candidate edge ab\n";
        size_t a = path[x];
        size_t b = path[(x + size_t(1)) % path.size()];
        double cost_ab = sqrt((data[a].pow_dist(data[b])));
        //cerr << "2.3: loop though edges in T that do not overlap ab\n";
        for (size_t y = x + size_t(2); y < path.size(); y++) {
            //cerr << "2.3.1: indentify second candidate edge cd\n";
            size_t c = path[y];
            size_t d = path[(y + size_t(1)) % path.size()];
            double currCost = cost_ab + sqrt((data[c].pow_dist(data[d]))); // w(ab) + w(cd)
            double possCost = sqrt((data[a].pow_dist(data[c]))) + sqrt((data[b].pow_dist(data[d]))); // w(ac) + w(bd)
            //cerr << "swap on (" << X.a.i << ", " << X.b.i << ") and (" << Y.a.i << ", " << Y.b.i << "): "
            //     << "Current: " << currCost << " Possible: " << possCost << '\n';
            if (possCost < currCost) { // if w(ac) + w(bd) < w(ab) + w(cd), swap
                //cerr << "swap made.\n";
                swapEdge(path, (x + size_t(1)) % path.size(), y); // swaps ab...cd, including reversing path b..c
            }
        }
        //cerr << (x + size_t(1)) << " edges processed.\n";
    }
} */
// FASTTSP functions