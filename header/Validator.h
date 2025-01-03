#ifndef VALIDATOR
#define VALIDATOR

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Validator
{
public:
    // data members
    vector<vector<float>> data;
    vector<int> features;

    // functions

    // takes in file name, populates data with the stuff from filename
    // should also do z score normalization on the data
    //  -> (find mean of whole data set, find std dev, use to change every element)
    Validator(string fileName);

    void normalizeData();
    // float calcMean();
    // float calcStdDev(float mean);
    float calcMean(int feature_index);
    float calcStdDev(float mean, int feature_index);

    void min_max_normalize();

    // pass in a FeatureNode, updates validator's vector of features to FeatureNode's vector
    void update_features(vector<int> ft);

    // takes in testSample, trainSample, and calcs distance using the features listed in FeatureNode features
    float euclidean_distance(vector<float> testSample, vector<float> trainSample);

    // returns accuracy of the classifier, given features store in class Validator
    double NN_classifier();
};

#endif