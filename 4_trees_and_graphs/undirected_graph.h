#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H

#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "graph.h"

class UndirectedGraph : public GraphInterface {
 public:
  explicit UndirectedGraph(int numVertices);
  virtual ~UndirectedGraph();

  virtual int numVertices() const;
  virtual int numEdges() const;

  virtual void addEdge(int fromVertex, int toVertex);
  virtual std::set<int> adjacencyList(int vertex) const;

 private:
  UndirectedGraph(const UndirectedGraph&);
  UndirectedGraph& operator=(const UndirectedGraph&);

  const int numVertices_;
  int numEdges_;
  std::vector<std::set<int> > adjacencyLists_;
  friend std::ostream& operator<<(std::ostream& ostr, const UndirectedGraph& graph);
};

std::ostream& operator<<(std::ostream& ostr, const UndirectedGraph& graph);

#endif
