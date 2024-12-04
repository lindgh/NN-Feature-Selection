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