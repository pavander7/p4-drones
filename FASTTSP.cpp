// 1761414855B69983BD8035097EFBD312EB0527F0

#include "FASTTSP.h"

using namespace std;

// FASTTSP functions
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
FASTTSP::FASTTSP(std::vector<Vertex> &data) : total_C(0), numNodes(0)
{ // nearest insertion heuristic
    unordered_set<size_t> Q;
    unordered_map<size_t, Node *> F;
    for (size_t I = 2; I < data.size(); I++)
    {
        Q.insert(I);
    }
    {
        auto vtx1 = data[0];
        auto vtx2 = data[1];
        auto node1 = new Node(vtx1, vtx1.pow_dist(vtx2));
        auto node2 = new Node(vtx2, vtx2.pow_dist(vtx1), node1);
        node1->reassign(node2);
        node2->reassign(node1);
        F.emplace(size_t(0), node1);
        F.emplace(size_t(1), node2);
        root = node1;
    }
    while (!Q.empty())
    {
        double c = 0;
        Vertex to_add = {0, 0, 0}; // default
        Node *before = nullptr;
        bool foundValidOpt = false;
        for (auto elt : F)
        {
            for (auto n : Q)
            {
                Vertex candidate = data[n];
                double can_dist = (sqrt(candidate.pow_dist(elt.second->vtx)) + sqrt(candidate.pow_dist(elt.second->E->vtx))) - sqrt(elt.second->vtx.pow_dist(elt.second->E->vtx));
                if (c == 0 || can_dist < c)
                {
                    to_add = candidate;
                    c = can_dist;
                    foundValidOpt = true;
                    before = elt.second;
                    /* if (candidate.pow_dist(elt.second->E->vtx) < candidate.pow_dist(elt.second->prev->vtx)) before = elt.second;
                    else before = elt.second->prev; */
                }
            }
        }
        //total_C += before->insert_dist(to_add);
        if (foundValidOpt) {
            Q.erase(to_add.i);
            F.emplace(to_add.i, before->encorporate(to_add));
        } 
    } 
    Node* current = root;
    total_C += sqrt(current->dist());
    numNodes++;
    while (current->next() != root) {
        current = current->next();
        total_C += sqrt(current->dist());
        numNodes++;
    }
}

FASTTSP::Node *FASTTSP::Node::encorporate(Vertex &elt)
{
    Node *ptr = new Node(elt, elt.pow_dist(this->E->vtx), this->E);
    this->reassign(ptr);
    return ptr;
}
std::ostream &operator<<(std::ostream &os, const FASTTSP &elt)
{
    os << elt.total_C << endl;
    FASTTSP::Node *current = elt.root;
    os << *current << ' ';
    while (current->next() != elt.root)
    {
        current = current->next();
        os << *current << ' ';
    } os << endl;
    return os;
}
FASTTSP::~FASTTSP() {
    auto ptr = root;
    while (numNodes != 0) {
        auto curr = ptr;
        ptr = ptr->next();
        delete curr;
        numNodes--;
    }
}
/* uint64_t FASTTSP::Node::swap_cost(FASTTSP::Node* other) {
    uint64_t current_cost = this->C + other->C;
    uint64_t swap_cost_a = this->vtx.pow_dist(other->E->vtx);
    uint64_t swap_cost_b = other->vtx.pow_dist(this->E->vtx);
    uint64_t swap_cost_total = swap_cost_a + swap_cost_b;
    if (swap_cost_total < current_cost) return current_cost - swap_cost_total;
    else return 0;
}
void FASTTSP::Node::twoopt(FASTTSP::Node* other) {
    Node* temp = this->E;
    this->reassign(other->E);
    other->reassign(temp);
} */
// FASTTSP functions