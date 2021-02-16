#include "../include/Agent.h"
using namespace std;

//constructor
Agent::Agent() {}

//destructor
Agent::~Agent() {}

//constructor
ContactTracer::ContactTracer() : Agent() {}

Agent* ContactTracer::clone() const {
    return new ContactTracer(*this);
}

void ContactTracer::act(Session &session) {
    if (!session.isEmptyQueue()) {
        int infectedNode = session.dequeueInfected();
        //we create a BFS tree that his root is infectedNode
        Tree* BFSTree = session.getGraph().BFSScan(session, infectedNode);
        //according to the type of the tree we will check who is the node that the contact tracer need to
        //remove his neighbours
        int toRemove = BFSTree->traceTree();
        Graph &updatedGraph = session.getGraph();
        updatedGraph.removeNeighbours(toRemove);
        //we dont need the BFSTree anymore
        delete BFSTree;
    }
}

//constructor
Virus::Virus(int nodeInd) : Agent(), nodeInd(nodeInd) {}

Agent* Virus::clone() const {
    return new Virus(*this);
}

void Virus::act(Session &session) {
    Graph &g = session.getGraph();
    if (!g.isInfected(nodeInd)) {
        g.infectNode(nodeInd);
        session.enqueueInfected(nodeInd);
    }
    std::vector<int> neighbours = g.getNeighbours(nodeInd);
    int k = 0;
    for (size_t i = 0; i < neighbours.size(); ++i) {
        if (neighbours[i] == 1) {
            //if we didnt visit this neighbour so we will visit him and make a virus for him
            if (!session.getVisited()[i]) {
                session.visit(k);
                Virus tempVirus(k);
                session.addAgent(tempVirus);
                break;
            }
        }
        k++;
    }
}