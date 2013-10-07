#include <assert.h>
#include <map>

#include "../digraph.h"
#include "../undirected_graph.h"

using namespace std;

enum ETraverseState {
  ENotVisited,
  EVisiting,
  EVisited
};

bool pathExists(const GraphInterface& g, int n1, int n2) {
  map<int, ETraverseState> traversal;
  vector<int> toVisitList;
  for (int n = 0; n < g.numVertices(); ++n) {
    traversal[n] = ENotVisited;
  }
  toVisitList.push_back(n1);
  bool exhausted = false;
  while (!exhausted && !toVisitList.empty()) {
    int nextVertex = toVisitList.back();
    toVisitList.pop_back();
    traversal[nextVertex] = EVisiting;
    set<int> adjList = g.adjacencyList(nextVertex);
    for (set<int>::iterator it = adjList.begin(); it != adjList.end(); ++it) {
      if (traversal[*it] == ENotVisited) {
        if (*it == n2) {
          return true;
        }
        toVisitList.push_back(*it);
      }
    }
    traversal[nextVertex] = EVisited;

    exhausted = true;
    for (map<int, ETraverseState>::iterator it = traversal.begin();
         it != traversal.end(); ++it) {
      exhausted &= (it->second == EVisited);
    }
  }
  return false;
}

void testUndirectedGraph() {
  UndirectedGraph* g = new UndirectedGraph(8);
  g->addEdge(0, 1);
  g->addEdge(0, 2);
  g->addEdge(0, 3);
  g->addEdge(3, 4);
  g->addEdge(4, 5);
  cout << *g << endl;

  assert(pathExists(*g, 0, 1));
  assert(pathExists(*g, 1, 0));

  assert(pathExists(*g, 0, 4));
  assert(pathExists(*g, 4, 0));

  assert(pathExists(*g, 1, 5));
  assert(pathExists(*g, 5, 1));

  assert(!pathExists(*g, 3, 6));
  assert(!pathExists(*g, 6, 7));

  delete g;
}

void testDigraph() {
  Digraph* g = new Digraph(8);
  g->addEdge(0, 1);
  g->addEdge(0, 2);
  g->addEdge(0, 3);
  g->addEdge(3, 4);
  g->addEdge(4, 5);
  cout << *g << endl;

  assert(pathExists(*g, 0, 1));
  assert(!pathExists(*g, 1, 0));

  assert(pathExists(*g, 0, 4));
  assert(!pathExists(*g, 4, 0));

  assert(!pathExists(*g, 1, 5));
  assert(!pathExists(*g, 3, 6));
  assert(!pathExists(*g, 6, 7));

  delete g;
}

int main(int argc, char **argv) {
  testUndirectedGraph();
  testDigraph();
  return 0;
}