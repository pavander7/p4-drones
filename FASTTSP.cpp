//1761414855B69983BD8035097EFBD312EB0527F0

#include "FASTTSP.h"

using namespace std;

//FASTTSP functions
/* FASTTSP::FASTTSP(std::vector<Vertex> &data) : total_C(0) { //nearest neighbor heuristic
    unordered_set<Vertex> Q;
    for (auto datum : data) {Q.insert(datum);}
    auto him = data.front();
    Node* prev = nullptr;
    while (!Q.empty()) {
        Q.erase(him);
        int c = 0;
        Vertex next;
        for (Vertex her : Q) {
            if (c == 0 || him.pow_dist(her) < c) {
                next = her;
                c = him.pow_dist(her);
            }
        } Node* temp = new Node(him, c);
        if (prev == nullptr) root = temp;
        else prev->reassign(temp);
        total_C += c;
        prev = temp;
        him = next;
    } root->reassign(prev);
} */
FASTTSP::FASTTSP(std::vector<Vertex> &data) : total_C(0) { //nearest insertion heuristic
    unordered_set<size_t> Q;
    unordered_map<size_t, Node*> F;
    for (size_t I = 0; I < data.size(); I++) {Q.insert(I);}
    {
        auto vtx1 = data[0];
        auto vtx2 = data[1];
        auto node1 = new Node(vtx1, vtx1.pow_dist(vtx2));
        auto node2 = new Node(vtx2, vtx2.pow_dist(vtx1), node1);
        node1->reassign(node2);
        F.emplace(size_t(0), node1);
        F.emplace(size_t(1), node2);
        root = node1;
    }
    while (!Q.empty()) {
        int c = 0;
        Vertex to_add = {0,0,0}; //default
        Node* before = nullptr;
        for (auto elt : F) {
            for (auto n : Q) {
                Vertex candidate = data[n];
                int can_dist = candidate.pow_dist(data[elt.first]);
                if (c == 0 || can_dist < c) {
                    to_add = candidate;
                    c = can_dist;
                    before = elt.second;
                } 
            }
        } total_C += before->insert_dist(to_add);
        Q.erase(to_add.i);
        F.emplace(to_add.i, before->encorporate(to_add));
    }
}
int FASTTSP::Node::insert_dist (Vertex &elt) {
    return elt.insert_dist(vtx, E->vtx);
}
FASTTSP::Node* FASTTSP::Node::encorporate (Vertex &elt) {
    Node* ptr = new Node (elt, elt.pow_dist(this->E->vtx), this->E);
    this->reassign(ptr);
    return ptr;
}
std::ostream& operator<<(std::ostream& os, const FASTTSP& elt) {
    os << elt.total_C << endl;
    FASTTSP::Node* current = elt.root;
    while (current->next() != elt.root) {
        os << current << ' ';
        current = current->next();
    } return os;
}
//FASTTSP functions