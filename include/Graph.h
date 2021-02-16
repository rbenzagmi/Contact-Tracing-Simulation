#ifndef ASS1_GRAPH_H_
#define ASS1_GRAPH_H_

#include <vector>
#include "Tree.h"

class Graph{
public:
    Graph(std::vector<std::vector<int>> matrix); //constructor

    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);

    virtual ~Graph(); //destructor
    static Tree* BFSScan (Session& session, int nodeInd); //return a BFS tree that his root is nodeInd
    std::vector<int> getNeighbours(int) const;
    std::vector<bool> getInfectedNodes();
    std::vector<std::vector<int>> getEdges();
    void removeNeighbours(int nodeInd);
    size_t numOfVertices();
    size_t getCountVirus() const;
private:
    std::vector<std::vector<int>> edges;
    std::vector<bool> infectedNodes;
    int countVirus;
};

#endif
