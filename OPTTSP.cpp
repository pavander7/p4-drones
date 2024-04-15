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
}
//OPTTSP functions