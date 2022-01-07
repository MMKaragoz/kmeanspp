#include "Node.h"
#include <iostream>

using namespace std;

Node::Node(double xCoordinate, double yCoordinate, int i)
{
    setX(xCoordinate);
    setY(yCoordinate);
    setIdentity(i);
    // cout << "Node " << getIdentity() << " is called.\n";
}

Node::~Node()
{
    // cout << "Node " << getIdentity() << " is destroyed.\n";
}

void Node::setX(double xCoordinate)
{
    /**
    *  sets x coordinate.  
    */
    x = xCoordinate;
}

void Node::setY(double yCoordinate)
{
    /**
    * sets y coordinate.  
    */
    y = yCoordinate;
}

void Node::setIdentity(int i)
{
    /**
    *  sets identity of Node. 
    */
    identity = i;
}

double Node::getX() const
{
    /**
    *  gets x-axis of Node which is constant.
    */
    return x;
}

double Node::getY() const
{
    /**
    * gets y-axis of Node which is constant.  
    */
    return y;
}

int Node::getIdentity() const
{
    /**
    * gets identify of Node which is constant.  
    */
    return identity;
}

void Node::print() const
{
    /**
    * prints information about Node.
    * structure like The coordinate of node id (x, y).
    * for ex, The coordinate of node 3 (1, 1).  
    */
    cout 
    << "The coordinate of node "
    << getIdentity()
    << " (" << getX() << ", "
    << getY() << ")\n";
}