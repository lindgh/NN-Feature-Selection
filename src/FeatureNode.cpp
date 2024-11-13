#include "../header/FeatureNode.h"
#include <ctime>

FeatureNode::FeatureNode()
{
    accuracy = 0.0;
    featureLimit = 0;
}

FeatureNode::FeatureNode(int numFeatures)
{
    // set featureLimit to features
    accuracy = 0.0;
    featureLimit = numFeatures;
}

void FeatureNode::accuracyEvaluation()
{
    // PART ONE: STUB FUNCTION BELOW

    // set the node's accuracy to a random number between 0 and 1, multiply by 100
    srand(time(0));
    double random = (double)rand() / RAND_MAX;
    accuracy = random * 100.00;
}

// contains

// copy constructor