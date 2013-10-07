#ifndef DIGRAPH_H
#define DIGRAPH_H

#include <iostream>
#include <set>
#include <vector>

#include "graph.h"

class Digraph : public GraphInterface {
 public:
  explicit Digraph(int numVertices);
  virtual ~Digraph();

  virtual int numVertices() const;
  virtual int numEdges() const;

  virtual void addEdge(int fromVertex, int toVertex);
  virtual std::set<int> adjacencyList(int vertex) const;

 private:
  Digraph(const Digraph&);
  Digraph& operator=(const Digraph&);

  const int numVertices_;
  int numEdges_;
  std::vector<std::set<int> > adjacencyLists_;
  friend std::ostream& operator<<(std::ostream& ostr, const Digraph& graph);
};

std::ostream& operator<<(std::ostream& ostr, const Digraph& graph);

#endif
