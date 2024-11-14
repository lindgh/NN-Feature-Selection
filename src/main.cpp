#include "../header/FeatureNode.h"
#include <ctime>
#include <iomanip>

FeatureNode ForwardExplore(FeatureNode parent);
FeatureNode ForwardSelection(int userFeatures);

int main()
{
    srand(time(0));

    cout << "Welcome to lghun001 and akath002's Feature Selection Algorithm." << "\n\nPlease enter total number of features: ";

    int userFeatures; // NUM OF FEATURES USER WANTS
    cin >> userFeatures;
    cout << endl;

    cout << "Type the number of the algorithm you want to run.\n\n";
    cout << "\t1. Forward Selection" << endl;
    cout << "\t2. Backward Elimination (UNDER CONSTRUCTION)\n"
         << endl;

    int userAlgorithm; // ALGORITHM USER WANTS
    cout << "Your choice: ";
    cin >> userAlgorithm;
    cout << endl;

    // call appropriate algorithm to get best set of features!
    FeatureNode bestFeatures;
    switch (userAlgorithm)
    {
    case 1:
        cout << "Beginning Forward Selection Search.\n"
             << endl;
        bestFeatures = ForwardSelection(userFeatures);
        break;

    case 2:
        cout << "Backward Elimination under construction!" << endl;
        break;
    }

    cout << "Finished search!! The best feature subset is " << bestFeatures << ", which has an accuracy of " << bestFeatures.accuracy << "%\n"
         << endl;

    return 0;
}

FeatureNode ForwardSelection(int userFeatures)
{

    FeatureNode initialNode(userFeatures); // make parent node. initially an empty set of features
    vector<FeatureNode> result;            // result vector to store features w increasing accuracy
    FeatureNode temp;
    bool solutionFound = false;

    while ((result.size() < initialNode.featureLimit) && (!solutionFound))
    {
        if (result.size() == 0)
        {
            temp = ForwardExplore(initialNode);
            result.push_back(temp);
        }
        else
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