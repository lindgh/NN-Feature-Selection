#include "../header/Validator.h"

using namespace std;

// takes in file name, populates vector<vector<float>> data with the stuff from filename
// should then do z score normalization on the data
//  -> (find mean of whole data set, find std dev, use to change every element)
Validator::Validator(string fileName)
{
    ifstream file(fileName);

    if (!file.is_open())
    {
        cout << "Errors occured when opening the file \"" << fileName << "\"!" << endl;
    }

    string stringline;

    // read in file line by line
    cout << "Reading in data...\n"
         << endl;

    while (getline(file, stringline))
    {
        stringstream stringStream(stringline);
        float element;
        vector<float> dataRow;

        while (stringStream >> element)
        {
            dataRow.push_back(element);
        }

        data.push_back(dataRow);
    }

    // print stuff from data to make sure it was stored properly
    // for (int i = 0; i < data.size(); ++i)
    // {
    //     vector<float> temp;
    //     temp = data.at(i);
    //     for (int j = 0; j < temp.size(); ++j)
    //     {
    //         cout << temp.at(j) << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    file.close();

    cout << "Normalizing data...\n"
         << endl;

    normalizeData();
}

void Validator::normalizeData()
{
    cout << "NORMALIZE DATA UNDER CONSTRUCTION!" << endl;
}

// pass in a FeatureNode, updates validator's vector of features to FeatureNode's vector
void Validator::update_features(FeatureNode ft)
{
    features = ft.features;
}

// takes in testSample, trainSample, and calcs distance using the features listed in FeatureNode features
float Validator::euclidean_distance(vector<float> testSample, vector<float> trainSample)
{
    float sum = 0.0f;
    float dist = 0.0f;
    //only testing between these two samples
    //can be up to n features, first index is always class type 
    //testSample ex: id #0 : [class type, feature 1 (x1), feature 2 (y1), ... feature n (z1)]
    //trainSample ex: id #1 : [class type, feature 1 (x2), feature 2 (y2), ... feature n (z2)]

    //testSample.at(1) till testSample.at(testSample.size()-1)
    //i = 1 to ignore class type index
    float featureElement = 0.0f;
    for(int i = 1; i < features.size()-1; i++){
        //only test against the subset in features -> features stores the index of the datapoints, not the datapoints itself
        featureElement = features.at(i);
        //(x1-x2)
        dist =  testSample.at(featureElement) - trainSample.at(featureElement);
        //(x1-x2)^2
        dist = pow(dist,2);
        //(x1-x20^2 + )(y1-y2)^2 + ...
        sum += dist; 

    }
    //sqrt((x1-x20^2 + )(y1-y2)^2 + ...) -> euclidean dist
    sum = sqrt(sum);
    if(sum != 0.0f){
        return sum;
    }
    return 0.0f;
}

// returns accuracy of the classifier, given features store in class Validator
double Validator::NN_classifier()
{
    float NN_dist = MAXFLOAT;
    int NN_index = 0;
    double accuracy_counter = 0;
    for (int i = 0; i < data.size(); ++i)
    {
        vector<float> temp;
        temp = data.at(i);
        for (int j = 0; j < data.size(); ++j)
        {
            if(i != j){
                float dist = euclidean_distance(data.at(i), data.at(j));
                if(dist < NN_dist){
                    NN_dist = dist;
                    NN_index = j;
                }

            }
        }
        if ((data.at(i)).at(0) == data.at(NN_index).at(0)){
            accuracy_counter++;
        }

    }

    if(accuracy_counter != 0){
        return accuracy_counter;
    }
    return 0.0;
}