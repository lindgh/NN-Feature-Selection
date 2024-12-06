#include "../header/Validator.h"
#include <cmath>
#include <chrono>
#include <float.h>
#include <algorithm>

using namespace std;
using namespace std::chrono;

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
    cout << "Reading in data..."
         << endl;

    auto start = high_resolution_clock::now();

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

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Time taken by step: " << duration.count() << " ms.\n"
         << endl;

    // print stuff from data to make sure it was stored properly
    cout << "before normalization: " << endl;
    for (int i = 0; i < data.size(); ++i)
    {
        vector<float> temp;
        temp = data.at(i);
        for (int j = 0; j < temp.size(); ++j)
        {
            cout << temp.at(j) << " ";
        }
        cout << endl;
    }
    cout << endl;

    file.close();

    cout << "Normalizing data..."
         << endl;

    start = high_resolution_clock::now();
    normalizeData();

    //min_max_normalize();

    cout << "after normalization: " << endl;
    for (int i = 0; i < data.size(); ++i)
    {
        vector<float> temp;
        temp = data.at(i);
        for (int j = 0; j < temp.size(); ++j)
        {
            cout << temp.at(j) << " ";
        }
        cout << endl;
    }
    cout << endl;

    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);

    cout << "Time taken by step: " << duration.count() << " ms.\n"
         << endl;
}

void Validator::min_max_normalize()
{
    vector<float> minValues(data[0].size(), numeric_limits<float>::max());
    vector<float> maxValues(data[0].size(), numeric_limits<float>::min());

    for (int i = 0; i < data.size(); ++i)
    {
        for (int j = 0; j < data.at(i).size(); ++j)
        {
            minValues[j] = min(minValues[j], data.at(i).at(j));
            maxValues[j] = max(maxValues[j], data.at(i).at(j));
        }
    }

    // cout << "minValues: {";
    // for (int i = 0; i < minValues.size() - 1; ++i)
    // {
    //     cout << minValues.at(i) << " ";
    // }
    // cout << minValues.at(minValues.size() - 1) << "}" << endl;

    // cout << "maxValues: {";
    // for (int i = 0; i < maxValues.size() - 1; ++i)
    // {
    //     cout << maxValues.at(i) << " ";
    // }
    // cout << maxValues.at(maxValues.size() - 1) << "}" << endl;

    for (int i = 0; i < data.size(); ++i)
    {
        for (int j = 1; j < data.at(i).size(); ++j)
        {
            data.at(i).at(j) = (data.at(i).at(j) - minValues.at(j)) / (maxValues.at(j) - minValues.at(j));
        }
    }
}

//mean and std for each column, this should be for loop
//finding mean and std for each column, updating each column then again next
//PREV
// void Validator::normalizeData()
// {
//     float mean = calcMean();
//     // cout << "mean: " << mean << endl;
//     float stdDev = calcStdDev(mean);
//     // cout << "std Dev: " << stdDev << endl;
//     float tempVal = 0.0f;

//     for (int i = 0; i < data.size(); ++i)
//     {
//         vector<float> temp;
//         temp = data.at(i);
//         for (int j = 1; j < temp.size(); ++j)
//         {
//             tempVal = temp.at(j);
//             temp.at(j) = ((tempVal - mean) / stdDev);
//         }
//         data.at(i) = temp;
//     }
    

//     // below is printing for test purposes
//     // cout << "after normalization: " << endl;
//     // for (int i = 0; i < data.size(); ++i)
//     // {
//     //     vector<float> temp;
//     //     temp = data.at(i);
//     //     for (int j = 0; j < temp.size(); ++j)
//     //     {
//     //         cout << temp.at(j) << " ";
//     //     }
//     //     cout << endl;
//     // }
//     // cout << endl;
// }
//PREV END

//NEW
void Validator::normalizeData()
{
    //per each feature
    for(int feature_index = 1; feature_index < data.at(0).size(); feature_index++){

        float mean = calcMean(feature_index);
        // cout << "mean: " << mean << endl;
        float stdDev = calcStdDev(mean, feature_index);
        // cout << "std Dev: " << stdDev << endl;
        float tempVal = 0.0f;

        // for (int i = 0; i < data.size(); ++i)
        // {

        for (int j = 0; j < data.size(); ++j)
        {
            tempVal = data.at(j).at(feature_index);
            data.at(j).at(feature_index) = ((tempVal - mean) / stdDev);

        }

        // }
    }

    // below is printing for test purposes
    // cout << "after normalization: " << endl;
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
}
//NEW END

//calc mean should be for the column not the row

// //PREV
// float Validator::calcMean()
// {
//     int totElements = 0;
//     float sum = 0.0f;

//     for (int i = 0; i < data.size(); ++i)
//     {
//         vector<float> temp;
//         temp = data.at(i);
//         for (int j = 1; j < temp.size(); ++j)
//         {
//             sum = sum + temp.at(j);
//             ++totElements;
//         }
//     }
//     return sum / totElements;
// }


// float Validator::calcStdDev(float mean)
// {
//     int totElements = 0;
//     float sumSqrdDev = 0.0f;

//     for (int i = 0; i < data.size(); ++i)
//     {
//         vector<float> temp;
//         temp = data.at(i);
//         for (int j = 1; j < temp.size(); ++j)
//         {
//             sumSqrdDev = sumSqrdDev + pow(temp.at(j) - mean, 2);
//             ++totElements;
//         }
//     }

//     return sqrt(sumSqrdDev / totElements);
// }
// PREV END

//NEW
float Validator::calcMean(int feature_index)
{
    int totElements = 0;
    float sum = 0.0f;


    for (int j = 0; j < data.size(); ++j)
    {
        sum = sum + data.at(j).at(feature_index);
        ++totElements;
    }

    return sum / totElements;
}


float Validator::calcStdDev(float mean, int feature_index)
{
    int totElements = 0;
    float sumSqrdDev = 0.0f;


    for (int j = 0; j < data.size(); ++j)
    {
        sumSqrdDev = sumSqrdDev + pow(data.at(j).at(feature_index) - mean, 2);
        ++totElements;
    }

    return sqrt(sumSqrdDev / totElements);
}
//NEW END

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
    // only testing between these two samples
    // can be up to n features, first index is always class type
    // testSample ex: id #0 : [class type, feature 1 (x1), feature 2 (y1), ... feature n (z1)]
    // trainSample ex: id #1 : [class type, feature 1 (x2), feature 2 (y2), ... feature n (z2)]

    // testSample.at(1) till testSample.at(testSample.size()-1)
    // i = 1 to ignore class type index
    int featureElement = 0;
    for (int i = 0; i < features.size(); i++)
    {
        // only test against the subset in features -> features stores the index of the datapoints, not the datapoints itself
        featureElement = features.at(i);
        //(x1-x2)
        dist = testSample.at(featureElement) - trainSample.at(featureElement);
        //(x1-x2)^2
        dist = pow(dist, 2);
        //(x1-x2)^2 + (y1-y2)^2 + ...
        sum += dist;
    }
    // sqrt((x1-x20^2 + )(y1-y2)^2 + ...) -> euclidean dist
    sum = sqrt(sum);
    if (sum != 0.0f)
    {
        return sum;
    }
    return 0.0f;
}

// returns accuracy of the classifier, given features store in class Validator
double Validator::NN_classifier()
{
    //float NN_dist = MAXFLOAT;
    //int NN_index = 0;
    int accuracy_counter = 0;
    int j = 0;
    //our test data is whatever instance is at i
    for (int i = 0; i < data.size(); ++i)
    {
        float NN_dist = MAXFLOAT;
        int NN_index = 0;
        //our train data is whatever is at j
        for (j = 0; j < data.size(); ++j)
        {
            if (i != j)
            {
                float dist = euclidean_distance(data.at(i), data.at(j));
                if (dist <= NN_dist)
                {
                    NN_dist = dist;
                    NN_index = j;
                }
            }
        }

        if ((data.at(i)).at(0) == data.at(NN_index).at(0))
        {
            accuracy_counter++;
        }

    }

    if (accuracy_counter != 0)
    {
        return (static_cast<double>(accuracy_counter) / data.size()) * 100.00;
    }
    return 0.0;
}