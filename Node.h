#ifndef NODE_H
#define NODE_H

class Node
{
    public:
        Node(double xCoordinate, double yCoordinate, int i);
        ~Node();
        void setX(double xCoordinate);
        void setY(double yCoordinate);
        void setIdentity(int i);
        double getX() const;
        double getY() const;
        int getIdentity() const;
        void print() const;
    
    private:
        double x;
        double y;
        int identity;

};

#endif