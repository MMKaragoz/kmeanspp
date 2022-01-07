#ifndef CLUSTERING_H
#define CLUSTERING_H

#include "Node.h"
#include <string>
#include <vector>

class Clustering
{
    public:
        Clustering();
        ~Clustering();
        void readFile(std::string fileName);
        void chooseK();
        void setK(int K);
        int getK() const;
        std::vector<Node> &getNodes();
        void print() const;
        void printNodes() ;

    private:
        int k; /// number of clusters
        std::vector<Node> nodes;

        
};


#endif  