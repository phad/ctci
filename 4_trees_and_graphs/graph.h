#ifndef GRAPH_H
#define GRAPH_H

#include <set>

class GraphInterface {
 public:
  virtual ~GraphInterface() {}

  virtual int numVertices() const = 0;
  virtual int numEdges() const = 0;

  virtual void addEdge(int fromVertex, int toVertex) = 0;
  virtual std::set<int> adjacencyList(int vertex) const = 0;
};

#endif
