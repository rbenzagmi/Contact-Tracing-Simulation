#include <vector>
#include <fstream>
#include "../include/json.hpp"
#include "../include/Session.h"
#include "../include/Agent.h"

using json=nlohmann::json;
using namespace std;

//constructor
Session::Session(const std::string &path) : g({}), treeType(), agents(), infectedQueue(), visited(), cycleNum(0) {
    ifstream i(path);
    json j;
    i >> j;
    g = Graph(j["graph"]);
    std::string tree = j["tree"];
    for (size_t i1 = 0; i1 < g.numOfVertices(); i1++) {
        visited.push_back(false);
    }
    for (auto &elem: j["agents"]) {
        if (elem[0] == "V") {
            addAgent(Virus(elem[1]));
            visit(elem[1]);
        } else
            addAgent(ContactTracer());
    }
    if (j["tree"] == "M")
        treeType = TreeType::MaxRank;
    else if (j["tree"] == "C")
        treeType = TreeType::Cycle;
    else
        treeType = TreeType::Root;
}

//copy constructor
Session::Session(const Session &other) : g(other.g), treeType(other.treeType), agents(),
                                         infectedQueue(other.infectedQueue), visited(other.visited),
                                         cycleNum(other.cycleNum) {
    for (auto agent : other.agents) {
        agents.push_back(agent->clone());
    }
}

//clear
void Session::clear() {
    for (auto &agent: agents) {
        delete (agent);
    }
    agents.clear();
}

//destructor
Session::~Session() {
    clear();
}

//copy assignment operator
Session &Session::operator=(const Session &other) {
    if (this != &other) {
        clear();
        g = other.g;
        treeType = other.treeType;
        for (Agent *agent:other.agents) {
            addAgent(*agent);
        }
        infectedQueue = other.infectedQueue;
        visited = other.visited;
        cycleNum = other.cycleNum;
    }
    return *this;
}

//move constructor
Session::Session(Session &&other) :
        g(other.g),
        treeType(other.treeType),
        agents(move(other.agents)),
        infectedQueue(other.infectedQueue),
        visited(other.visited),
        cycleNum(other.cycleNum) {}

//move assignment operator
Session &Session::operator=(Session &&other) {
    if (this != &other) {
        g = other.g;
        treeType = other.getTreeType();
        this->agents.swap(other.agents);
        infectedQueue = other.infectedQueue;
        visited = other.visited;
        cycleNum = other.cycleNum;
    }
    return *this;
}

void Session::simulate() {
    cycleNum = 0;
    size_t numOfAgents = 0;
    while (numOfAgents != agents.size() && g.getCountVirus() != g.numOfVertices()) {
        numOfAgents = agents.size();
        //all the for is one iteration that pass all over tha agents and each agent need to do his act
        for (size_t i = 0; i < numOfAgents; ++i) {
            agents[i]->act(*this);
        }
        //when we finish the iteration (the for loop) we move for the next cycleNum
        cycleNum++;
    }

    vector<int> infNodesList;
    vector<bool> infNodes = g.getInfectedNodes();
    int k = 0;
    //making a vector with the nodes that infected (vector with int numbers)
    for (size_t i = 0; i < infNodes.size(); ++i) {
        if (infNodes[i]) {
            infNodesList.push_back(k);
        }
        k++;
    }
    //now we will make the output file
    json j;
    j["graph"] = g.getEdges();
    j["infected"] = infNodesList;
    ofstream o("./output.json");
    o << j;
    o.close();
}

void Session::setGraph(const Graph &graph) {
    g = graph;
}

Graph& Session::getGraph() {
    return g;
}

void Session::enqueueInfected(int node) {
    infectedQueue.push(node);
}

int Session::dequeueInfected() {
    int infected = infectedQueue.front();
    infectedQueue.pop();
    return infected;
}

TreeType Session::getTreeType() const {
    return treeType;
}

void Session::addAgent(const Agent &agent) {
    Agent* clone = agent.clone();
    agents.push_back(clone);
}

int Session::getCycle() const {
    return cycleNum;
}

std::vector<bool> Session::getVisited() {
    return visited;
}

void Session::visit(int node) {
    visited[node] = true;
}

bool Session::isEmptyQueue() {
    return infectedQueue.empty();
}