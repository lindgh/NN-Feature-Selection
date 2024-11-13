#include "../header/FeatureNode.h"

int main()
{

    cout << "Welcome to lghun001 and [advithi netid]'s Feature Selection Algorithm." << "\n\nPlease enter total number of features: ";

    int userFeatures;
    cin >> userFeatures;
    cout << endl;

    FeatureNode nodeOne(userFeatures);

    // test evaluation function
    nodeOne.accuracyEvaluation();
    cout << "nodeOne's accuracy: " << nodeOne.accuracy << endl;

    return 0;
}