#include <assert.h>

#include "undirected_graph.h"

using namespace std;

// explicit
Graph::Graph(int numVertices)
    : numVertices_(numVertices) {
  for (int v = 0; v < numVertices; ++v) {
    adjacencyLists_.push_back(set<int>());
  }
}

Graph::~Graph() {
}

int Graph::numVertices() const {
  return numVertices_;
}

int Graph::numEdges() const {
  int edgeCount = 0;
  for (vector<set<int> >::const_iterator it = adjacencyLists_.begin();
       it != adjacencyLists_.end(); ++it) {
    edgeCount += (*it).size();
  }
  return edgeCount / 2;
}

void Graph::addEdge(int fromVertex, int toVertex) {
  assert(fromVertex >= 0 && fromVertex < numVertices_);
  assert(toVertex >= 0 && toVertex < numVertices_);
  adjacencyLists_[fromVertex].insert(toVertex);
  adjacencyLists_[toVertex].insert(fromVertex);
}

set<int>::const_iterator Graph::adjacencyList(int vertex) const {
  assert(vertex >= 0 && vertex < numVertices_);
  return adjacencyLists_[vertex].begin();
}

ostream& operator<<(ostream& ostr, const Graph& gr) {
  ostr << "Graph - numVertices: " << gr.numVertices_ << ", ";
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
