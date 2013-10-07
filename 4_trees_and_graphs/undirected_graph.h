#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H

#include <iostream>
#include <set>
#include <string>
#include <vector>

class Graph {
 public:
  explicit Graph(int numVertices);
  ~Graph();

  int numVertices() const;
  int numEdges() const;

  void addEdge(int fromVertex, int toVertex);
  std::set<int>::const_iterator adjacencyList(int vertex) const;

 private:
  Graph(const Graph&);
  Graph& operator=(const Graph&);

  const int numVertices_;
  int numEdges_;
  std::vector<std::set<int> > adjacencyLists_;
  friend std::ostream& operator<<(std::ostream& ostr, const Graph& Graph);
};

std::ostream& operator<<(std::ostream& ostr, const Graph& Graph);

#endif
