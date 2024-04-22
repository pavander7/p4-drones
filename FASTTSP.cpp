// 1761414855B69983BD8035097EFBD312EB0527F0

#include "FASTTSP.h"

using namespace std;

// FASTTSP functions
/* FASTTSP::FASTTSP(std::vector<Vertex> &data) : total_C(0) { //nearest neighbor heuristic
    unordered_set<Vertex> Q;
    fNode* root;
    size_t numNodes = 1;
    for (auto datum : data) {Q.insert(datum);}
    auto him = data.front();
    fNode* prev = nullptr;
    while (!Q.empty()) {
        Q.erase(him);
        int c = 0;
        Vertex next;
        for (Vertex her : Q) {
            if (c == 0 || him.pow_dist(her) < c) {
                next = her;
                c = him.pow_dist(her);
            }
        } fNode* temp = new fNode(him, c);
        if (prev == nullptr) root = temp;
        else prev->reassign(temp);
        total_C += c;
        prev = temp;
        him = next;
        numNodes++;
    } root->reassign(prev);
 */
FASTTSP::FASTTSP(std::vector<Vertex> &data) : total_C(0) // total_C initialized as 0 for later incrementation
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
    unordered_map<size_t, fNode *> F; // maps created nodes to their starting index for later random access, F.A. elt € F, elt € T_e
    unordered_set<size_t> Q; // Q = D - !T_v : set of the indices of all vertices not yet in DLL
    for (size_t I = 2; I < data.size(); I++) { Q.insert(I); } // add all vertices to Q, 0 & 1 are ommitted since they would be immediately removed in 1.2

    //cerr << "1.2: initialize DLL\n";
    //cerr << "1.2.1: initialize basic member variables\n";
    fNode* root; // constant time access pointer into DLL at arbitrary posiiton
    size_t numNodes = 2; // tracks number of nodes, for later deconstruction, starts as 2
    {
        //cerr << "1.2.2: identify starting vertices\n";
        auto vtx1 = data[0]; // a
        auto vtx2 = data[1]; // b
        //cerr << "1.2.3: construct edges without pointers\n";
        auto node1 = new fNode(vtx1, vtx1.pow_dist(vtx2)); // ab
        auto node2 = new fNode(vtx2, vtx2.pow_dist(vtx1)); // ba
        //cerr << "1.2.4: connect edges by initializing pointers\n";
        node1->reassign(node2);
        node2->reassign(node1); 
        //cerr << "1.2.5: enter edges into F for tracking\n";
        F.emplace(size_t(0), node1);
        F.emplace(size_t(1), node2);
        //cerr << "1.2.6: assign access point\n";
        root = node1;
    }

    //cerr << "1.3: execute CIH\n";
    while (!Q.empty()) // true as long as there are unconnected points
    {
        //cerr << "1.3.1: define variables\n";
        double c = 0; // cost w(c) of best insertion c, where c is an insertion of the form ab -> axb, where a, b € T_v && x € Q
        Vertex to_add = {0, 0, 0}; // best vertex c_x to include (initialized to arbitrary default value)
        fNode *before = nullptr; // pointer to the edge c_ab that will be affected by insertion
        bool foundValidOpt = false; // tracks whether a valid insertion has been found

        //cerr << "1.3.2: loop through every edge in DLL\n";
        for (auto elt : F)
        {
            // let ab be the edge defined by elt
            // ab € T_e, a, b € T_v
            //cerr << "1.3.3: loop through every unconnected vertex\n";
            for (auto n : Q) // referenced by index
            {   
                // let x be the candidate vertex
                //cerr << "1.3.3.1: define & analyze x\n";
                Vertex candidate = data[n]; // x
                double left_leg = sqrt(candidate.pow_dist(elt.second->vtx)); // w(ax)
                double right_leg = sqrt(candidate.pow_dist(elt.second->E->vtx)); // w(xb)
                double curr_dist = sqrt(elt.second->vtx.pow_dist(elt.second->E->vtx)); // w(ab)
                double can_dist = (left_leg + right_leg) - curr_dist; // w(axb) == w(ax) + w(xb) - w(ab): increase to total cost of the path if x is inserted between a & b
                //cerr << "1.3.3.1: evaluate insertion (ab -> axb)\n";
                if (c == 0 || can_dist < c) // if w(c) == 0, c is undefined
                {                           // if (w(axb) < c), c should be disregarded in favor of axb
                    to_add = candidate; // c_x = x
                    c = can_dist; // w(c) = w(axb)
                    foundValidOpt = true; // register that at least one valid option has been found
                    before = elt.second; // c_ab = ab
                }
            }
        }

        //cerr << "1.3.3: execute best insertion c\n";
        if (foundValidOpt) { // only execute if c is defined
            Q.erase(to_add.i); // remove c_x from Q
            F.emplace(to_add.i, before->encorporate(to_add)); // encorporate performs the insertion, adds the resulting node to F
            numNodes++; // updates node count
        } 
    } 

    //cerr << "stage 2: 2-opt heuristic\n";

    //cerr << "2.1: convert T from DLL to vector\n";
    fNode* current = root; // pointer to act as iterator on DLL
    while (numNodes != 0) { // exectutes deletion exactly as many times as construction
        Edge *currEdge = nullptr; // ab defined dynamically to account for special case
        if (numNodes == 1) currEdge = new Edge(current->vtx, finalPath[0].a); // special case: accounts for loop
        else currEdge = new Edge(current->vtx, current->E->vtx); // default case
        this->finalPath.push_back(*currEdge); // adds ab to new representation of T
        fNode* temp = current; // pop node
        current = current->next(); // current++
        delete temp; // delete now useless node
        delete currEdge; // delete dynamically allocated edge
        numNodes--;
    }

    //cerr << "2.2: loop through edges in T\n";
    for (size_t x = 0; x < finalPath.size(); x++) {
        //cerr << "2.2.1: identify first candidate edge ab\n";
        Edge X = finalPath[x];
        //cerr << "2.3: loop though edges in T that do not overlap ab\n";
        for (size_t y = x + size_t(2); y < finalPath.size(); y++) {
            //cerr << "2.3.1: indentify second candidate edge cd\n";
            Edge Y = finalPath[y];
            double currCost = sqrt(X.cost()) + sqrt(Y.cost()); // w(ab) + w(cd)
            double possCost = sqrt(X.a.pow_dist(Y.a)) + sqrt(X.b.pow_dist(Y.b)); // w(ac) + w(bd)
            //cerr << "swap on (" << X.a.i << ", " << X.b.i << ") and (" << Y.a.i << ", " << Y.b.i << "): "
            //     << "Current: " << currCost << " Possible: " << possCost << '\n';
            if (possCost < currCost) { // if w(ac) + w(bd) < w(ab) + w(cd), swap
                //cerr << "swap made.\n";
                swapEdge(finalPath, x, y); // swaps ab...cd, including reversing path b..c
            }
        }
    }

    //cerr << "stage 3: report results\n";
    for (auto ab : finalPath) total_C += sqrt(ab.cost()); // sums total cost of T by iterating through each edge
}

FASTTSP::fNode *FASTTSP::fNode::encorporate(const Vertex &elt)
{
    fNode *ptr = new fNode(elt, elt.pow_dist(this->E->vtx), this->E); // construct xb
    this->reassign(ptr); // change ab to ax
    return ptr;
}
std::ostream &operator<<(std::ostream &os, const FASTTSP &elt)
{
    os << elt.total_C << endl;
    for (auto ab : elt.finalPath) { os << ab.first() << ' '; }
    os << '\n';
    return os;
}
void FASTTSP::swapEdge(vector<Edge> &path, size_t x, size_t y) {
    // let xa...by define the path between x and y such that xa and by are edges, and ... is a valid subpath between a and b
    if (x == y) return; // if x = y, nothing left to swap
    size_t x_next = (x + size_t(1) % path.size()); // a
    size_t y_prev = size_t(int(y) - 1 + int(path.size())) % path.size(); // b
    // perform preliminary swap
    Vertex temp_vtx = path[x].b;
    path[x].b = path[y].a;
    path[y].a = temp_vtx;
    if ((x == y_prev) || (y == x_next)) return; // if x and y are consecutive, swap needn't be "passed", path is complete
    else { // "pass" swap to next par of edges
        path[x_next].a = path[x].b; 
        path[y_prev].b = path[y].a;
        swapEdge(path, x_next, y_prev); // recursively call swapEdge to reverse remaining inner path "..."
    }
}
// FASTTSP functions