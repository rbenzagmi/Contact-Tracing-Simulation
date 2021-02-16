#include "../include/Graph.h"
#include "../include/Session.h"

#include <queue>

using namespace std;

//constructor
Graph::Graph(vector<std::vector<int>> matrix) : edges(matrix), infectedNodes(), countVirus(0) {
    size_t size = matrix.size();
    for (size_t i = 0; i < size; ++i) {
        infectedNodes.push_back(false);
    }
}

//destructor
Graph::~Graph() {}

vector<int> Graph::getNeighbours(int node) const {
    return edges[node];
}

void Graph::infectNode(int nodeInd) {
    infectedNodes[nodeInd] = true;
    countVirus++;
}

bool Graph::isInfected(int nodeInd) {
    return infectedNodes[nodeInd];
}

//return a BFS tree that his root is nodeInd
Tree* Graph::BFSScan(Session &session, int nodeInd) {
    Tree* currTree = Tree::createTree(session, nodeInd);
    int numOfVertices = session.getGraph().edges.size();
    vector<bool> visited(numOfVertices, false);
    queue<Tree*> q; //queue of pointers to trees
    q.push(currTree);
    Tree* currNode;
    visited[nodeInd] = true;
    while (!q.empty()) {
        currNode = q.front();
        q.pop();
        int k = 0;
        vector<int> neighbours = session.getGraph().getNeighbours(currNode->getRootLabel());
        //now we will pass all over the neighbours of currNode and check if each one is visited already -
        //if not - we will create from each one tree and add it to the BFS tree as a childes
        for (size_t j = 0; j < neighbours.size(); ++j) {
            if (neighbours[j] == 1) {
                if (!visited[j]) {
                    Tree* currNodeTree = Tree::createTree(session, k);
                    currNode->addChild(currNodeTree);
                    q.push(currNodeTree);
                    visited[j] = true;
                }
            }
            k++;
        }
    }
    return currTree;
}

size_t Graph::numOfVertices() {
    return edges.size();
}

std::vector<std::vector<int>> Graph::getEdges() {
    return edges;
}

void Graph::removeNeighbours(int nodeInd) {
    for (size_t i = 0; i < edges.size(); i++) {
        edges[nodeInd][i] = 0;
        edges[i][nodeInd] = 0;
    }
}

std::vector<bool> Graph::getInfectedNodes() {
    return infectedNodes;
}

size_t Graph::getCountVirus() const {
    return countVirus;
}