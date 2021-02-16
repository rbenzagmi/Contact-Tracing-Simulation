#ifndef ASS1_SESSION_H_
#define ASS1_SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"

#include <queue>

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const std::string& path); //constructor
    Session(const Session& other); //copy constructor
    virtual ~Session(); //destructor
    Session& operator=(const Session& other); //copy assignment operator
    Session(Session&& other); //move constructor
    Session& operator=(Session&& other); //move assignment operator

    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);

    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;

    bool isEmptyQueue();
    int getCycle() const;
    std::vector<bool> getVisited();
    void visit (int);
    Graph& getGraph();

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;
    std::queue<int> infectedQueue;
    std::vector<bool> visited;
    int cycleNum;
    void clear();
};

#endif
