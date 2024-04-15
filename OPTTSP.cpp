//1761414855B69983BD8035097EFBD312EB0527F0

#include "OPTTSP.h"

using namespace std;

template <typename T>
void genPerms(vector<T> &path, size_t permLength) {
  if (permLength == path.size()) {
  // Do something with the path
    return;
  }  // if ..complete path

  if (!promising(path, permLength)) {
    return;
  }  // if ..not promising

  for (size_t i = permLength; i < path.size(); ++i) {
    swap(path[permLength], path[i]);
    genPerms(path, permLength + 1);
    swap(path[permLength], path[i]);
  }  // for ..unpermuted elements
}  // genPerms()

//OPTTSP functions
OPTTSP::OPTTSP(std::vector<Vertex> &data) : total_C(0) {
    unordered_set<Vertex> Q;
    unordered_map<Vertex, Node*> F;
    for (auto datum : data) {Q.insert(datum);}
    {
        auto vtx1 = data[0];
        auto vtx2 = data[1];
        auto node1 = new Node(vtx1, vtx1.pow_dist(vtx2));
        auto node2 = new Node(vtx2, vtx2.pow_dist(vtx1), node1);
        node1->reassign(node2);
        F.emplace(vtx1, node1);
        F.emplace(vtx2, node2);
        root = node1;
    }
}
//OPTTSP functions