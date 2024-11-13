#ifndef FEATURENODE_H
#define FEATURENODE_H

#include <iostream>
#include <vector>
using namespace std;

class FeatureNode
{
public:
    // DATA MEMBERS

    vector<int> features; // 1. the state representation, ie, the features (maybe vector?)
    double accuracy;      // 2. the accuracy of the state representation
    int featureLimit;     // 3. maybe number of features total? aka our limit.

    // FUNCTIONS

    FeatureNode();
    FeatureNode(int numFeatures); // 1. constructor. takes in # of features to be considered
    void accuracyEvaluation();    // 2. evaluation function on a FeatureNode modifies accuracy
    // 3. copy constructor
    // 4. bool contains(int):  checks if a node's feature vector contains an int i.
    // edge case for when node.features.size() == 0. if its feature vector is empty, return false
    // otherwise, loop through features vector, return true if i is there
};

#endif