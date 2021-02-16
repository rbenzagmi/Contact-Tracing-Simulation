#ifndef ASS1_AGENT_H_
#define ASS1_AGENT_H_

#include <vector>
#include "Session.h"

class Agent{
public:
    Agent(); //constructor

    virtual void act(Session& session)=0;

    virtual ~Agent(); //destructor
    virtual Agent* clone() const=0;
};

class ContactTracer: public Agent{
public:
    ContactTracer(); //constructor

    virtual void act(Session& session);

    virtual Agent* clone() const;
};


class Virus: public Agent{
public:
    Virus(int nodeInd); //constructor

    virtual void act(Session& session);

    virtual Agent* clone() const;
private:
    const int nodeInd;
};

#endif
