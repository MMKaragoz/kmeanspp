#include "KMeansPP.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

KMeansPP::KMeansPP()
:
    Clustering()
{
    apply();
    // cout << "KMeansPP is called.\n";
}

KMeansPP::~KMeansPP()
{
    // cout << "KMeansPP is destroyed.\n";
}

void KMeansPP::apply()
{
    /**
	*   applies KMeans++ algorithm.
	*/
    int itr = 0;
    initializeFirstCentroid();
    initializeRestCentroids();
    cout << "Enter the iteration number:\n";
    cin >> itr;

    for (int i = 0; i < itr; i++) {
        cout << i + 1 << ". iteration\n\n";
        findDistances();
        iteration();
    }
}
void KMeansPP::initializeFirstCentroid() 
{
    /**
	* initializes first centroid randomly.
	*/
    srand(time(0));
    int random = rand() % getNodes().size();
    centroids.push_back(getNodes().at(random - 1));
}

void KMeansPP::initializeRestCentroids()
{
    /**
	* initializes the rest of centroids based on probability which is in the article.
	*/
    double totalDistance = 0.0;
    double dists = 0.0;
    totalDistance = findTotalDistance();
    vector<double> distances;
    vector<double> probs;
    vector<double> distances_all;
    double  a = 0.0;

    for(vector<Node>::iterator n = getNodes().begin(); n != getNodes().end(); n++) {
        for(vector<Node>::iterator n2 = getNodes().begin(); n2 != getNodes().end(); n2++) {
            if ((*n).getX() == (*n2).getX() && (*n).getX() == (*n2).getX()) {
                continue;        
            } else {
                dists = pow(calculateEuclidean((*n2).getX(), (*n2).getY(), (*n).getX(), (*n).getY()), 2);
            }
        }  
        if (a != dists / totalDistance) {
            probs.push_back(dists / totalDistance);
        }
        a = dists / totalDistance;
    }
    
    int count = 1;
    while (getK() != count) {   
        count += 1;
        int minElementIndex = min_element(probs.begin(), probs.end())-probs.begin();
        int maxElementIndex = max_element(probs.begin(), probs.end()) - probs.begin();
        centroids.push_back(getNodes().at(maxElementIndex));
        probs[minElementIndex] = 1; 
    }
}

void KMeansPP::printCentroids()
{
    /**
	*   prints all centroids we got from the file.
	*/
    for(vector<Node>::const_iterator it = getCentroids().begin(); it != getCentroids().end(); it++)
        cout << "Centroid is " << (*it).getIdentity() << " " << (*it).getX() << " " << (*it).getY() << "\n";
}

vector<Node> &KMeansPP::getCentroids()
{
    /**
	*   gets centroids.
	*/
    return centroids;
}

double KMeansPP::findTotalDistance()
{
    /**
	*   finds total distance between nodes and centroids and then returns double.
	*/
    double totalDistance = 0.0;

    for(vector<Node>::iterator n = getNodes().begin(); n != getNodes().end(); n++) {
        for(vector<Node>::iterator it = getCentroids().begin(); it!=getCentroids().end(); it++) {
            totalDistance += pow(calculateEuclidean((*it).getX(), (*it).getY(), (*n).getX(), (*n).getY()), 2);
        }
    }
    return totalDistance;
}
double KMeansPP::calculateEuclidean(const double x1, const double y1, const double x2, const double y2)
{
    /**
	*   calculates euclidean and returns double.
	*/
    double result = 0.0;
    result = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
    return result;
}

void KMeansPP::findDistances()
{
    /**
	*   finds distance between all nodes and all centroids.
	*/
    // cout << "findDistances is run.\n";
    vector<double> distances;
    double distance = 0.0;

    for(int j = 0; j < getNodes().size(); j++) {
        for(int it = 0; it < getK(); it++) {
            distance = calculateEuclidean(getCentroids()[it].getX(), getCentroids()[it].getY(), getNodes()[j].getX(), getNodes()[j].getY());
            distances.push_back(distance);
        }
        int minElementIndex = min_element(distances.begin(),distances.end()) - distances.begin();
        clusters[minElementIndex].push_back(getNodes()[j]);
        distances.clear();
    }
    printClusters();
}

void KMeansPP::printClusters()
{
    /**
	*   prints clusters
	*/
    for(const auto& c : getClusters()) {
        cout << "Class No: " << c.first << "  Indentity of Nodes: [" ;
        for( Node d : c.second ) {
            cout << d.getIdentity() << " " ;
        }
        cout << "]\n" ;
    }
}

void KMeansPP::iteration()
{
    /**
	*   does an iteration when each called and obtains the x and y-axis averages of each cluster. 
    *   
	*/
    double totalX = 0.0;
    double totalY = 0.0;

    for (int i = 0; i < getK(); i++) {
        
        if(getClusters()[i].size() > 0) {
            for(int j = 0; j < getClusters()[i].size(); j++) {
                // cout << "(x, y) - (" << getClusters()[i][j].getX() << ", " << getClusters()[i][j].getY() << ")\n";
                totalX += getClusters()[i][j].getX();
                totalY += getClusters()[i][j].getY();
            }
            // cout << "(TotalX, TotalY) - (" << totalX << ", " << totalY << ")\n";
            double sumX = totalX / getClusters()[i].size();
            double sumY = totalY / getClusters()[i].size();
            // cout << "(SumX, SumY) - (" << sumX << ", " << sumY << ")\n";
            totalX = 0.0;
            totalY = 0.0;
            Node closestNode = findClosestNode(sumX, sumY);
            getCentroids()[i] = closestNode;
        }
    }

    getClusters().clear();
    printCentroids();
}

Node KMeansPP::findClosestNode(const double X, const double Y)
{
    /**
	* finds closest node according to x and y-axis.
	*/
    vector<double> distances;

    for (int i = 0; i < getNodes().size(); i++) {
        distances.push_back(calculateEuclidean(X, Y, getNodes()[i].getX(), getNodes()[i].getY()));
    }
    int minElementIndex = min_element(distances.begin(),distances.end()) - distances.begin();
    return getNodes()[minElementIndex];
}

std::map<int, std::vector<Node>> &KMeansPP::getClusters()
{
    /*
    *   get clusters
    */
    return clusters;
}
