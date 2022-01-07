#ifndef KMEANSPP_H
#define KMEANSPP_H

#include "Clustering.h"
#include <map>

class KMeansPP : public Clustering
{
    public:
        KMeansPP();
        ~KMeansPP();
        std::vector<Node> &getCentroids();
        std::map<int, std::vector<Node>> &getClusters();
        void printCentroids();
        void printClusters();
        void apply();

    private:
        void initializeFirstCentroid();
        void initializeRestCentroids();
        void findDistances();
        void iteration();
        double findTotalDistance();
        Node findClosestNode(const double, const double);
        double calculateEuclidean(const double, const double, const double, const double);
        std::vector<Node> centroids;
        std::map<int, std::vector<Node>> clusters;
};

#endif