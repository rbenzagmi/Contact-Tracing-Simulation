#include "../include/Tree.h"
#include "../include/Session.h"
#include <vector>

using namespace std;

//constructor
Tree::Tree(int rootLable) : node(rootLable), children() {}

//copy constructor
Tree::Tree(const Tree &other) : node(other.node), children() {
    for (auto i : other.children) {
        children.push_back(i->clone());
    }
}

//clear
void Tree::clear() {
    for (auto &child: children) {
        delete child;
    }
    children.clear();
}

//destructor
Tree::~Tree() {
    clear();
}

//copy assignment operator
Tree &Tree::operator=(const Tree &other) {
    if (this != &other) {
        clear();
        node = other.node;
        for (auto i : other.children) {
            addChild(*i);
        }
    }
    return *this;
}

//move constructor
Tree::Tree(Tree &&other) : node(other.node), children(move(other.children)) {}

//move assignment operator
Tree &Tree::operator=(Tree &&other) {
    if (this != &other) {
        node = other.node;
        children.swap(other.children);
    }
    return *this;
}

//constructor
RootTree::RootTree(int rootLable) : Tree(rootLable) {}

Tree* RootTree::clone() const {
    return new RootTree(*this);
}

int RootTree::traceTree() {
    return getRootLabel();
}

//constructor
MaxRankTree::MaxRankTree(int rootLable) : Tree(rootLable) {}

Tree* MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}

//return the node with the max rank in the tree
int MaxRankTree::traceTree() {
    int node = -1;
    int maxRank = -1;
    Tree* currTree;
    queue<Tree*> queue;
    queue.push(this);
    while (!queue.empty()) {
        currTree = queue.front();
        queue.pop();
        size_t currSize = currTree->getChildren().size();
        int currSizeInt = currSize;
        //if the rank of the currTree node is bigger than maxRank so this is the node with tha max rank
        if (currSizeInt > maxRank) {
            maxRank = currSizeInt;
            node = currTree->getRootLabel();
        }
        //pushing all the childrens to the queue because we need to check the rank of all the nodes in
        //the tree
        for (int i = 0; i < currSizeInt; ++i) {
            queue.push(currTree->getChildren()[i]);
        }
    }
    return node;
}

//constructor
CycleTree::CycleTree(int rootLable, int currCycle) : Tree(rootLable), currCycle(currCycle) {}

Tree* CycleTree::clone() const {
    return new CycleTree(*this);
}

int CycleTree::traceTree() {
    queue<Tree*> childes;
    childes.push(this);
    //when currCycle=0 we end and we will return the first node that now is in the queue
    while(currCycle>0)
    {
        Tree* cycleT = childes.front();
        //if he has no children so we can stop and return him
        if (!cycleT->getChildren().empty())
        {
            childes.pop();
            childes.push(cycleT->getChildren()[0]);
        }
        currCycle--;
    }
    return childes.front()->getRootLabel();
}

Tree* Tree::createTree(const Session &session, int rootLabel) {
    //checking what is the type of the tree
    TreeType type = session.getTreeType();
    //just because it will enter anytime to the switch
    Tree* root = nullptr;
    switch (type) {
        case Root:
            root = new RootTree(rootLabel);
            break;
        case MaxRank:
            root = new MaxRankTree(rootLabel);
            break;
        case Cycle:
            root = new CycleTree(rootLabel, session.getCycle());
            break;
    }
    return root;
}

void Tree::addChild(const Tree& child) {
    Tree* copy = child.clone();
    children.push_back(copy);
}

void Tree::addChild(Tree* child) {
    children.push_back(child);
}

int Tree::getRootLabel() const {
    return node;
}

vector<Tree*> Tree::getChildren() {
    return children;
}
