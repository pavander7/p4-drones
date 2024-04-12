//1761414855B69983BD8035097EFBD312EB0527F0

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <cmath>
#include "MST.h"

class FASTTSP {
public:
    FASTTSP(std::vector<Vertex> &data);
    friend std::ostream& operator<<(std::ostream& os, const FASTTSP& elt);
private:
    class Node;
    Node *root;
    int total_C;
};

class FASTTSP::Node {
public: 
    FASTTSP::Node::Node(Vertex vtx_in, int C_in) : vtx(vtx_in), C(C_in), E(nullptr) {}
    FASTTSP::Node::Node(Vertex vtx_in, int C_in, Node* next) : vtx(vtx_in), C(C_in), E(next) {}
    void reassign(Node* next) {E = next; C = vtx.pow_dist(next->vtx);}
    int insert_dist (Vertex &elt);
    Node* encorporate (Vertex &elt);
    Node* next() {return this->E;}
    friend std::ostream& operator<<(std::ostream& os, const Node& elt) {
        os << elt.vtx.i;
        return os;
    }
private:
    Vertex vtx;
    int C;
    FASTTSP::Node* E;
};