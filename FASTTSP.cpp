// 1761414855B69983BD8035097EFBD312EB0527F0

#include "FASTTSP.h"
#include <list>

using namespace std;

// FASTTSP functions
/* FASTTSP::FASTTSP(std::vector<Vertex> &data) : total_C(0) { //nearest neighbor heuristic
    unordered_set<Vertex> Q;
    fast_node* root;
    size_t numNodes = 1;
    for (auto datum : data) {Q.insert(datum);}
    auto him = data.front();
    fast_node* prev = nullptr;
    while (!Q.empty()) {
        Q.erase(him);
        int c = 0;
        Vertex next;
        for (Vertex her : Q) {
            if (c == 0 || him.pow_dist(her) < c) {
                next = her;
                c = him.pow_dist(her);
            }
        } fast_node* temp = new fast_node(him, c);
        if (prev == nullptr) root = temp;
        else prev->reassign(temp);
        total_C += c;
        prev = temp;
        him = next;
        numNodes++;
    } root->reassign(prev);
 */
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
    //unordered_map<size_t, fast_node *> F; // maps created nodes to their starting index for later random access, F.A. elt € F, elt € T_e
    vector<size_t> Q; // Q = D - !T_v : set of the indices of all vertices not yet in DLL
    for (size_t I = 2; I < data.size(); I++) { Q.push_back(I); } // add all vertices to Q, 0 & 1 are ommitted since they would be immediately removed in 1.2
    total_C = size_t(2) * sqrt(data[0].pow_dist(data[1]));
    //cerr << "1.2: initialize DLL\n";
    //cerr << "1.2.1: initialize basic member variables\n";
    //fast_node* root; // constant time access pointer into DLL at arbitrary posiiton
    /* size_t numNodes = 2; // tracks number of nodes, for later deconstruction, starts as 2
    {
        //cerr << "1.2.2: identify starting vertices\n";
        //auto vtx1 = data[0]; // a
        //auto vtx2 = data[1]; // b
        //cerr << "1.2.3: construct edges without pointers\n";
        auto node1 = new fast_node(0); // ab
        auto node2 = new fast_node(1); // ba
        //cerr << "1.2.4: connect edges by initializing pointers\n";
        node1->reassign(node2);
        node2->reassign(node1); 
        //cerr << "1.2.5: enter edges into F for tracking\n";
        F.emplace(size_t(0), node1);
        F.emplace(size_t(1), node2);
        //cerr << "1.2.6: assign access point\n";
        root = node1;
    } */


    //cerr << "1.3: execute CIH\n";
    while (!Q.empty()) // true as long as there are unconnected points
    {
        //cerr << "Remaining Vertices: " << Q.size() << '\n';
        //cerr << "1.3.1: define variables\n";
        double c = 0; // cost w(c) of best insertion c, where c is an insertion of the form ab -> axb, where a, b € T_v && x € Q
        size_t to_add = data.size(); // best vertex c_x to include (initialized to arbitrary default value)
        auto after = tour.begin();
        //fast_node *before = nullptr; // pointer to the edge c_ab that will be affected by insertion
        size_t w = Q.back();
        Q.pop_back();
        //cerr << "1.3.2: loop through every edge in DLL\n";  
        auto it = tour.begin();
        auto next = ++tour.begin();
        while (it != tour.end())
        {
            size_t v = *it;
            size_t u = *next;
            // let ab be the edge defined by elt
            // ab € T_e, a, b € T_v
            //cerr << "1.3.3: loop through every unconnected vertex\n";
        
            // let x be the candidate vertex
            //cerr << "1.3.3.1: define & analyze x\n";
            Vertex candidate = data[w]; // x
            Vertex a = data[v];
            Vertex b = data[u];

            double left_leg = sqrt(candidate.pow_dist(a)); // w(ax)
            double right_leg = sqrt(candidate.pow_dist(b)); // w(xb)
            double curr_dist = sqrt(a.pow_dist(b)); // w(ab)
            double can_dist = (left_leg + right_leg) - curr_dist; // w(axb) == w(ax) + w(xb) - w(ab): increase to total cost of the path if x is inserted between a & b
            
            //double can_dist = sqrt(candidate.pow_dist(a));

            //cerr << "1.3.3.1: evaluate insertion (ab -> axb)\n";
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

        //cerr << "1.3.3: execute best insertion c\n";
        if (to_add < data.size()) { // only execute if c is defined
            //Q.erase(to_add); // remove c_x from Q
            /* auto left = after; if (after == tour.begin()) left = tour.end(); left--;
            auto right = after; right++; if (after == tour.end()) left = tour.begin();
            uint64_t lDist = data[*left].pow_dist(data[to_add]);
            uint64_t rDist = data[*right].pow_dist(data[to_add]);
            if (rDist < lDist) ++after; */
            if (*after == tour.back()) tour.push_back(to_add);
            else tour.insert(++after, to_add);
            total_C += c;
            //F.emplace(to_add, before->encorporate(to_add)); // encorporate performs the insertion, adds the resulting node to F
            //numNodes++; // updates node count
        }
    } 

    //cerr << "stage 2: 2-opt heuristic\n";

    //cerr << "2.1: convert T from DLL to vector\n";
    /* fast_node* current = root; // pointer to act as iterator on DLL
    while (numNodes != 0) { // exectutes deletion exactly as many times as construction
        fast_edge *currEdge = nullptr; // ab defined dynamically to account for special case
        if (numNodes == 1) currEdge = new fast_edge(current->v_i, finalPath[0].a_i); // special case: accounts for loop
        else currEdge = new fast_edge(current->v_i, current->E->v_i); // default case
        this->finalPath.push_back(*currEdge); // adds ab to new representation of T
        fast_node* temp = current; // pop node
        current = current->next(); // current++
        delete temp; // delete now useless node
        delete currEdge; // delete dynamically allocated edge
        numNodes--;
    } */
    finalPath = vector<size_t>(tour.begin(), tour.end());
    //cerr << "2.2: loop through edges in T\n";
    twoopt(finalPath, data);
    //twoopt(finalPath, data);
    //cerr << "stage 3: report results\n";
    /* for (size_t i = 0; i < finalPath.size(); i++) {
        auto a = data[finalPath[i]];
        auto b = data[finalPath[(i + size_t(1)) % tour.size()]];
        total_C += sqrt(a.pow_dist(b)); // sums total cost of T by iterating through each edge
    } */
}

/* FASTTSP::fast_node *FASTTSP::fast_node::encorporate(size_t i)
{
    fast_node *ptr = new fast_node(i, this->E); // construct xb
    this->reassign(ptr); // change ab to ax
    return ptr;
} */
std::ostream &operator<<(std::ostream &os, const FASTTSP &elt)
{
    os << elt.total_C << endl;
    for (auto v : elt.finalPath) { os << v << ' '; }
    os << '\n';
    return os;
}
void FASTTSP::swapEdge(vector<size_t> &path, size_t x, size_t y) {
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
/* std::vector<size_t> FASTTSP::givePath() const {
    vector<size_t> goodPath;
    goodPath.reserve(finalPath.size());
    for (auto e : finalPath) goodPath.push_back(e.a_i);
    return goodPath;
} */
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
}
// FASTTSP functions