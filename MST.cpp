//1761414855B69983BD8035097EFBD312EB0527F0

#include "MST.h"

using namespace std;

//vertex functions
int Vertex::area() {
    if (x < 0 && y < 0) return 2;
    else if ((x == 0 && y < 0)||(y == 0 && x < 0)) return 1;
    else return 0;
}

int Vertex::pow_dist (Vertex &other) {
    int X = this->x - other.x;
    int Y = this->y - other.y;
    return ((X*X)+(Y*Y));
}
//vertex functions

//MST functions
MST::MST (vector<Vertex> &data) {
    unordered_set<Vertex> Q;
    priority_queue<Node*,vector<Node*>,NodeComp> poss;
    total_C = 0;
    for (auto her : data) {Q.insert(her);}
    Vertex v = data.front();
    Q.erase(v);
    for (Vertex w : Q) {
        if (v.area() == 2 || w.area() == 2 || w.area() == v.area()) {
            Node* W = new Node(v, v.pow_dist(w), w);
            poss.push(W);
        }
    }
    while (!Q.empty()) {
        Node* her = poss.top();
        poss.pop();
        if (Q.count(her->E) != 0) {
            Q.erase(her->E);
            F.push_back(her);
            total_C += her->C;
            for (Vertex w : Q) {
                if (v.area() == 2 || w.area() == 2 || w.area() == v.area()) {
                    Node* W = new Node(v, v.pow_dist(w), w);
                    poss.push(W);
                }
            }
        }
    }
}
std::ostream& operator<<(std::ostream& os, const MST& elt) {
    os << elt.total_C << endl;
    for (auto n : elt.F) os << n << endl;
    return os;
}
//MST functions

//TSP functions
TSP::TSP(std::vector<Vertex> &data) {
    for (auto datum : data) {Q.insert(datum);}
    F.reserve(data.size());
    auto her = data.front();
    Q.erase(her);
    
}
//TSP functions