#include <assert.h>

#include "digraph.h"

using namespace std;

// explicit
Digraph::Digraph(int numVertices)
    : numVertices_(numVertices) {
  for (int v = 0; v < numVertices; ++v) {
    adjacencyLists_.push_back(set<int>());
  }
}

Digraph::~Digraph() {
}

int Digraph::numVertices() const {
  return numVertices_;
}

int Digraph::numEdges() const {
  return numEdges_;
}

void Digraph::addEdge(int fromVertex, int toVertex) {
  assert(fromVertex >= 0 && fromVertex < numVertices_);
  assert(toVertex >= 0 && toVertex < numVertices_);
  adjacencyLists_[fromVertex].insert(toVertex);
  ++numEdges_;
}

set<int> Digraph::adjacencyList(int vertex) const {
  assert(vertex >= 0 && vertex < numVertices_);
  set<int> adjList = adjacencyLists_[vertex];
  return adjList;
}

ostream& operator<<(ostream& ostr, const Digraph& gr) {
  ostr << "Digraph - numVertices: " << gr.numVertices_ << ", ";
  ostr << "numEdges: " << gr.numEdges() << endl;

  for (int v = 0; v < gr.numVertices(); ++v) {
    ostr << v << ": ";
    for (set<int>::const_iterator it = gr.adjacencyLists_[v].begin();
         it != gr.adjacencyLists_[v].end(); ++it) {
      ostr << *it << " ";
    }
    ostr << endl;
  }
  return ostr;
}
