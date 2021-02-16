#ifndef ASS1_TREE_H_
#define ASS1_TREE_H_

#include <vector>

class Session;

class Tree {
public:
    Tree(int rootLabel); //constructor
    Tree(const Tree &other); //copy constructor
    virtual ~Tree(); //destructor
    Tree &operator=(const Tree &other); //copy assignment operator
    Tree(Tree &&other); //move constructor
    Tree &operator=(Tree &&other); //move assignment operator

    void addChild(const Tree& child);
    void addChild(Tree* child);

    static Tree* createTree(const Session &session, int rootLabel);
    virtual int traceTree() = 0;

    std::vector<Tree*> getChildren();
    int getRootLabel() const;
    virtual Tree* clone() const = 0;
private:
    int node;
    std::vector<Tree*> children;
    void clear();
};

class CycleTree : public Tree {
public:
    //constructor
    CycleTree(int rootLabel, int currCycle);
    //return the node that we need now according to the type of the tree (now its a cycle)
    virtual int traceTree();

    virtual Tree* clone() const;
private:
    int currCycle;
};

class MaxRankTree : public Tree {
public:
    //constructor
    MaxRankTree(int rootLabel);
    //return the node that we need now according to the type of the tree (now its a cycle)
    virtual int traceTree();

    virtual Tree* clone() const;
};

class RootTree : public Tree {
public:
    //constructor
    RootTree(int rootLabel);
    //return the node that we need now according to the type of the tree (now its a cycle)
    virtual int traceTree();

    virtual Tree* clone() const;
};

#endif
