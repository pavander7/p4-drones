//1761414855B69983BD8035097EFBD312EB0527F0

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <cmath>

struct Vertex {
    int x, y;
    std::size_t i;
    int area();
    bool operator== (Vertex const &other) {return (this->i == other.i);}
    bool operator!= (Vertex const &other) {return (this->i != other.i);}
    int pow_dist (Vertex const &other) const;
    int insert_dist (Vertex const &before, Vertex const &after) const;
};

int Vertex::area() {
    if (x < 0 && y < 0) return 2;
    else if ((x == 0 && y < 0)||(y == 0 && x < 0)) return 1;
    else return 0;
}
int Vertex::pow_dist (Vertex const &other) const {
    int X = this->x - other.x;
    int Y = this->y - other.y;
    return ((X*X)+(Y*Y));
}
int Vertex::insert_dist (Vertex const &before, Vertex const &after) const {
    int dist1 = before.pow_dist(after);
    int dist2 = this->pow_dist(before) + this->pow_dist(after);
    return (dist2 - dist1);
}

struct VertexComp {
    bool operator() (const Vertex &a, const Vertex &b) const {
        if (a.i == b.i) return true;
        else if (a.x == b.x) {
            if (a.y == b.y) return true;
            else return (a.y < b.y);
        } else return (a.x < b.x);
    }
};