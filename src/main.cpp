#include "../header/FeatureNode.h"
#include "../header/Validator.h"
#include <ctime>
#include <iomanip>

FeatureNode ForwardExplore(FeatureNode parent);
FeatureNode ForwardSelection(int userFeatures);

FeatureNode BackwardExplore(FeatureNode parent);
FeatureNode BackwardElimination(int userFeatures);
//float euclidean_distance(vector<float> testSample, vector<float> trainSample);


int main()
{
    //Validator vd(hi); 

    //testing euclidean distance
    // vector<float> testSample;
    // testSample.push_back(1.0f);
    // testSample.push_back(5.0688373e+000);
    // testSample.push_back(3.1403378e+000);
    // testSample.push_back(1.2891084e+000);
    // // cout << testSample.size() << endl;
    // for(int i=0; i < testSample.size();i++){
    //     cout << testSample.at(i) << " ";
    // }
    // cout << endl;

    // vector<float> trainSample;
    // trainSample.push_back(2.0f);
    // trainSample.push_back(4.5426593e+000);
    // trainSample.push_back(2.5859775e+000);
    // trainSample.push_back(4.1604586e+000);

    // for(int i=0; i < trainSample.size();i++){
    //     cout << trainSample.at(i) << " ";
    // }
    // cout << endl;

    // testSample = trainSample;

    // for(int i=0; i < trainSample.size();i++){
    //     cout << trainSample.at(i) << " ";
    // }

    // float res = euclidean_distance(testSample, trainSample);
    // cout << res << endl;

    //vector<float> testSample = {2.0000000e+000, 5.0688373e+000, 3.1403378e+000, 1.2891084e+000, 5.7634216e-001, 2.7268616e+000, 1.9103920e+000, 4.6027145e+000, 3.3621920e+000, 4.0253170e+000, 2.8503988e+000}

    //vector<float> trainSample = {2.0000000e+000, 4.5426593e+000, 2.5859775e+000, 4.1604586e+000, 3.4542063e+000, 4.4436954e+000, 4.0238492e+000, 3.1987725e+000, 2.9734490e+000, 2.6177713e+000, 1.6957015e+000}
    // srand(time(0));

    // cout << "\nWelcome to lghun001 and aketh002's Feature Selection Algorithm." << "\n\nPlease enter total number of features: ";

    // int userFeatures; // NUM OF FEATURES USER WANTS
    // cin >> userFeatures;
    // cout << endl;

    // cout << "Type the number of the algorithm you want to run.\n\n";
    // cout << "\t1. Forward Selection" << endl;
    // cout << "\t2. Backward Elimination\n"
    //      << endl;

    // int userAlgorithm; // ALGORITHM USER WANTS
    // cout << "Your choice: ";
    // cin >> userAlgorithm;
    // cout << endl;

    // // call appropriate algorithm to get best set of features!
    // FeatureNode bestFeatures;
    // switch (userAlgorithm)
    // {
    // case 1:
    //     cout << "Beginning Forward Selection Search.\n"
    //          << endl;
    //     bestFeatures = ForwardSelection(userFeatures);
    //     break;

    // case 2:
    //     cout << "Backward Elimination Selection Search.\n"
    //          << endl;
    //     bestFeatures = BackwardElimination(userFeatures);
    //     break;
    // }

    // cout << "Finished search!! The best feature subset is " << bestFeatures << ", which has an accuracy of " << bestFeatures.accuracy << "%\n"
    //      << endl;

    return 0;
}

// float euclidean_distance(vector<float> testSample, vector<float> trainSample)
// {

//     float sum = 0.0f;
//     float dist = 0.0f;
//     //only testing between these two samples
//     //can be up to n features, first index is always class type 
//     //testSample ex: id #0 : [class type, feature 1 (x1), feature 2 (y1), ... feature n (z1)]
//     //trainSample ex: id #1 : [class type, feature 1 (x2), feature 2 (y2), ... feature n (z2)]

//     //testSample.at(1) till testSample.at(testSample.size()-1)
//     //i = 1 to ignore class type index
//      cout << testSample.size();
//     for(int i = 1; i < testSample.size(); i++){
//         //(x1-x2)
//         //error here
//         //cout << testSample.at(i) << "-" << trainSample.at(i);
//         dist = testSample.at(i) - trainSample.at(i);
//         //(x1-x2)^2

//         dist = pow(dist,2);
//         //(x1-x20^2 + )(y1-y2)^2 + ...
//         sum += dist; 

//     }
//     //sqrt((x1-x20^2 + )(y1-y2)^2 + ...) -> euclidean dist
//     sum = sqrt(sum);
//     if(sum != 0.0f){
//         return sum;
//     }
//     return 0.0f;
// }

FeatureNode ForwardSelection(int userFeatures)
{

    FeatureNode initialNode(userFeatures); // make parent node. initially an empty set of features
    vector<FeatureNode> result;            // result vector to store features w increasing accuracy
    FeatureNode temp;
    bool solutionFound = false;

    initialNode.accuracyEvaluation();
    result.push_back(initialNode);

    cout << "Starting with feature set " << initialNode << " with accuracy " << initialNode.accuracy << "%\n"
         << endl;

    while ((result.back().features.size() < initialNode.featureLimit) && (!solutionFound))
    {
        temp = ForwardExplore(result.back());

        // check if child with highest accuracy is lower than parent accuracy
        if ((result.back()).accuracy > temp.accuracy)
        {
            cout << "(WARNING, Accuracy has decreased!)" << endl;
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
FeatureNode ForwardExplore(FeatureNode parent)
{

    FeatureNode maxChild;
    bool firstChild = false;

    for (int i = 1; i <= parent.featureLimit; ++i)
    {

        if (!parent.contains(i))
        {
            FeatureNode temp = parent;
            temp.features.push_back(i);
            temp.accuracyEvaluation();

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

FeatureNode BackwardExplore(FeatureNode parent)
{

    FeatureNode maxChild;
    bool firstChild = false;

    for (int i = 0; i < parent.features.size(); i++)
    {

        FeatureNode temp = parent;
        temp.features.erase(temp.features.begin() + i);
        temp.accuracyEvaluation();

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

FeatureNode BackwardElimination(int userFeatures)
{
    FeatureNode initialNode(userFeatures);
    vector<FeatureNode> result;
    FeatureNode temp;
    bool solutionFound = false;

    for (int i = 1; i <= userFeatures; i++)
    {
        initialNode.features.push_back(i);
    }

    initialNode.accuracyEvaluation();
    result.push_back(initialNode);

    cout << "Starting with feature set " << initialNode << " with accuracy " << initialNode.accuracy << "%\n"
         << endl;

    while ((result.back().features.size() > 1) && (!solutionFound))
    {
        temp = BackwardExplore(result.back());
        if (result.back().accuracy > temp.accuracy)
        {
            cout << "(WARNING, Accuracy has decreased!)" << endl;
            solutionFound = true;
        }
        else
        {
            result.push_back(temp);
        }
    }

    return result.back();
}