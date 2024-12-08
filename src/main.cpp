/*
- Group: Advithi Kethidi – aketh002, 862331573 – Session 21, Linda Ghunaim – lghun001, 862267489 – Session 21
- DatasetID: whaaa???
- Small Dataset Results:
- Forward: Feature Subset: {5,3}, Acc: 0.92
- Backward: Feature Subset: {2,4,5,7,10} Acc: 0.82
- Large Dataset Results:
- Forward: Feature Subset: {27, 1}, Acc: 0.955
- Backward: Feature Subset: {2, 3, 4, 5, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 
    18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 
    30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40}, Acc: 0.7220
- Titanic Dataset Results:
- Forward: Feature Subset: {2}, Acc: 0.7773
- Backward: Feature Subset: {1,2,3}, Acc: 0.7913

*/

/* REFERENCES:
    - Reading in data as floating point: Stack overflow, https://stackoverflow.com/questions/48464430/how-to-read-data-from-file-to-int-float-values-in-c 
    - Z-score normalization: Geeks for geeks, https://www.statology.org/z-score-normalization/ 
    - Implementing a timer for part 2: Stack overflow, https://stackoverflow.com/questions/30702759/implementing-a-timer-in-c
*/




#include "../header/FeatureNode.h"
#include "../header/Validator.h"
#include <ctime>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <float.h>

FeatureNode ForwardExplore(FeatureNode parent, Validator &v1);
FeatureNode ForwardSelection(int userFeatures, Validator &v1);

FeatureNode BackwardExplore(FeatureNode parent, Validator &v1);
FeatureNode BackwardElimination(int userFeatures, Validator &v1);
// float euclidean_distance(vector<float> testSample, vector<float> trainSample);

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[])
{
    cout << "\nWelcome to lghun001 and aketh002's Feature Selection with Nearest Neighbor Algorithm.\n"
         << endl;

    cout << "Type the number of the algorithm you want to run.\n\n";
    cout << "\t1. Forward Selection" << endl;
    cout << "\t2. Backward Elimination\n"
         << endl;

    int userAlgorithm; // ALGORITHM USER WANTS
    cout << "Your choice: ";
    cin >> userAlgorithm;
    cout << endl;

    // READ IN FILE FROM DATA
    string filename = argv[1];
    Validator v1(filename);

    vector<float> firstSample;
    int numFeatures;

    firstSample = v1.data.at(0);
    numFeatures = firstSample.size() - 1;

    // call appropriate algorithm to get best set of features!
    FeatureNode bestFeatures;
    switch (userAlgorithm)
    {
    case 1:
        cout << "Beginning Forward Selection Search.\n"
             << endl;
        bestFeatures = ForwardSelection(numFeatures, v1);
        break;

    case 2:
        cout << "Backward Elimination Selection Search.\n"
             << endl;
        bestFeatures = BackwardElimination(numFeatures, v1);
        break;
    }

    cout << "Finished search!! The best feature subset is " << bestFeatures << ", which has an accuracy of " << bestFeatures.accuracy << "%\n"
         << endl;

    return 0;
}

FeatureNode ForwardSelection(int userFeatures, Validator &v1)
{

    FeatureNode initialNode(userFeatures); // make parent node. initially an empty set of features
    vector<FeatureNode> result;            // result vector to store features w increasing accuracy
    FeatureNode temp;
    bool solutionFound = false;

    initialNode.accuracyEvaluation(v1);
    result.push_back(initialNode);

    // cout << "Starting with feature set " << initialNode << " with accuracy " << initialNode.accuracy << "%\n"
    //      << endl;

    while ((result.back().features.size() < initialNode.featureLimit) && (!solutionFound))
    {
        temp = ForwardExplore(result.back(), v1);

        // check if child with highest accuracy is lower than parent accuracy
        if ((result.back()).accuracy > temp.accuracy)
        {
            // cout << "(WARNING, Accuracy has decreased!)" << endl;
            solutionFound = true;
        }
        else
        {
            result.push_back(temp);
        }
    }

    return result.back();
}

// given a parent node, ForwardSelection explores all possible children of parent, returns child w highest accuracy
FeatureNode ForwardExplore(FeatureNode parent, Validator &v1)
{

    FeatureNode maxChild;
    bool firstChild = false;

    for (int i = 1; i <= parent.featureLimit; ++i)
    {

        if (!parent.contains(i))
        {
            FeatureNode temp = parent;
            temp.features.push_back(i);

            v1.update_features(temp.features);
            temp.accuracyEvaluation(v1);

            cout << "\tUsing feature(s) " << temp << " accuracy is " << fixed << setprecision(2) << temp.accuracy << "%" << endl;

            if (!firstChild)
            {
                maxChild = temp;
                firstChild = true;
            }
            else
            {
                if (temp.accuracy > maxChild.accuracy)
                {
                    maxChild = temp;
                }
            }
        }
    }

    cout << "\nFeature set " << maxChild << " was best, accuracy is " << maxChild.accuracy << "%\n"
         << endl;

    return maxChild;
}

FeatureNode BackwardExplore(FeatureNode parent, Validator &v1)
{

    FeatureNode maxChild;
    bool firstChild = false;

    for (int i = 0; i < parent.features.size(); i++)
    {

        FeatureNode temp = parent;
        temp.features.erase(temp.features.begin() + i);

        v1.update_features(temp.features);
        temp.accuracyEvaluation(v1);

        cout << "\tUsing feature(s) " << temp << " accuracy is " << fixed << setprecision(2) << temp.accuracy << "%" << endl;

        if (!firstChild)
        {
            maxChild = temp;
            firstChild = true;
        }
        else
        {
            if (temp.accuracy > maxChild.accuracy)
            {
                maxChild = temp;
            }
        }
    }

    cout << "\nFeature set " << maxChild << " was best, accuracy is " << maxChild.accuracy << "%\n"
         << endl;

    return maxChild;
}

FeatureNode BackwardElimination(int userFeatures, Validator &v1)
{
    FeatureNode initialNode(userFeatures);
    vector<FeatureNode> result;
    FeatureNode temp;
    bool solutionFound = false;

    for (int i = 1; i <= userFeatures; i++)
    {
        initialNode.features.push_back(i);
    }

    v1.update_features(initialNode.features);
    initialNode.accuracyEvaluation(v1);

    result.push_back(initialNode);

    // cout << "Starting with feature set " << initialNode << " with accuracy " << initialNode.accuracy << "%\n"
    //      << endl;

    while ((result.back().features.size() > 1) && (!solutionFound))
    {
        temp = BackwardExplore(result.back(), v1);
        if (result.back().accuracy > temp.accuracy)
        {
            // cout << "(WARNING, Accuracy has decreased!)" << endl;
            solutionFound = true;
        }
        else
        {
            result.push_back(temp);
        }
    }

    return result.back();
}