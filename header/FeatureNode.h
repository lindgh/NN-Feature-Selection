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

    FeatureNode(int numFeatures); // 1. constructor. takes in # of features to be considered
    void accuracyEvaluation();    // 2. evaluation function on a FeatureNode modifies accuracy
};

#endif