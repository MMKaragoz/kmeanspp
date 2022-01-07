#include "Clustering.h"
#include "Node.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

Clustering::Clustering()
{
    readFile("50.txt");
    // readFile("20.txt");
    cout << "Clustering is called.\n";
    chooseK();
}

Clustering::~Clustering()
{
    cout << "Clustering is destroyed.\n";
}

void Clustering::readFile(string fileName)
{
	/**
    * reads a file with location of file  
    */
	cout << setprecision(13);

	ifstream fs;
	fs.open(fileName.c_str(), ofstream::in);
	if (fs.is_open()){	
		int count = 1;
		double cX = 0.0;
		double cY = 0.0;
		while (!fs.eof())
		{
			fs >> cX >> cY;
			Node n(cX, cY, count);
			n.print();
			nodes.push_back(n);
			count+=1;	
		}	
		fs.close();
	} else {
		cout << "Got error while opening " << fileName.c_str() << " file\n";
	}
}

void Clustering::chooseK()
{
	/**
    * asks the interface k value.  
    */
    int K;
    
    cout << "Enter the center number:\n";
    cin >> K;
    setK(K);
    printNodes();
}

void Clustering::setK(int K)
{
	/**
    * sets k which means total number of centroids.  
    */
    k = K;
}

int Clustering::getK() const
{
	/**
    * gets k.  
    */
    return k;
}	

vector<Node> &Clustering::getNodes()
{
	/**
    *   gets all nodes which got from file.
    */
	return nodes;
}

void Clustering::print() const
{
	/*
	*	prints k.
	*/
    cout << "K is " << getK() << ".\n";
}

void Clustering::printNodes()
{
	/**
	*	prints all nodes.
	*/
	for(vector<Node>::const_iterator it = getNodes().begin(); it != getNodes().end(); it++){
        cout << "Node " << (*it).getIdentity() << "\t" << (*it).getX() << "\t" << (*it).getY() << endl;
	}
}	