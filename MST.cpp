//1761414855B69983BD8035097EFBD312EB0527F0

#include "MST.h"

using namespace std;

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
vector<Vertex> MST::out() {
    vector<Vertex> output;
    for (auto step : F) {
        output.push_back(step->vtx);
    } return output;
}
//MST functions