#include "../header/Validator.h"

// takes in file name, populates data with the stuff from filename
// should also do z score normalization on the data
//  -> (find mean of whole data set, find std dev, use to change every element)
Validator::Validator(string fileName)
{
}

// pass in a FeatureNode, updates validator's vector of features to FeatureNode's vector
void Validator::update_features(FeatureNode ft)
{
}

// takes in testSample, trainSample, and calcs distance using the features listed in FeatureNode features
float Validator::euclidean_distance(vector<float> testSample, vector<float> trainSample)
{

    return 0.0f;
}

// returns accuracy of the classifier, given features store in class Validator
double Validator::NN_classifier()
{

    return 0.0;
}