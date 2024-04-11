//1761414855B69983BD8035097EFBD312EB0527F0

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <cmath>
#include <set>

struct Vertex {
    int x, y;
    std::size_t i;
    int area();
    bool operator== (Vertex const &other) {return (this->i == other.i);}
    bool operator!= (Vertex const &other) {return (this->i != other.i);}
    int pow_dist (Vertex &other);
};

class MST {
private:
    class Node;
    class NodeComp;
    double total_C;
    std::deque<Node*> F;
public:
    MST(std::vector<Vertex> &data);
    double dist() {return sqrt(double(total_C));}
    friend std::ostream& operator<<(std::ostream& os, const MST& elt);
};

class MST::Node {
public:
    Node(Vertex &v_in, int C_in, Vertex E_in) : vtx(v_in), C(C_in), E(E_in) {}
    int area() {return vtx.area();}
    int pow_dist(Node &other) {this->vtx.pow_dist(other.vtx);}
    int pow_dist(Vertex &other) {this->vtx.pow_dist(other);}
    friend class MST;
    friend struct NodeComp;
    friend std::ostream& operator<<(std::ostream& os, const Node& elt) {
        os << elt.vtx.i << ' ' << elt.E.i;
        return os;
    }
private:
    Vertex vtx;
    int C;
    Vertex E;
};

struct MST::NodeComp {
    bool operator() (const Node &a, const Node &b) const {
        if (a.C == b.C) return true;
        else return (a.C < b.C);
    } bool operator() (const Node* a, const Node* b) const {
        if (a->C == b->C) return true;
        else return (a->C < b->C);
    }
};

struct VertexComp {
    bool operator() (const Vertex &a, const Vertex &b) const {
        if (a.i == b.i) return true;
        else if (a.x == b.x) {
            if (a.y == b.y) return true;
            else return (a.y < b.y);
        } else return (a.x < b.x);
    }
};

class TSP {
public:
    TSP(std::vector<Vertex> &data);
private:
    std::set<Vertex, VertexComp> Q;
    std::vector<Vertex> F;
};