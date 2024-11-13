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

// PART ONE: STUB FUNCTION BELOW
void FeatureNode::accuracyEvaluation()
{
    // set the node's accuracy to a random number between 0 and 1, multiply by 100
    srand(time(0));
    double random = (double)rand() / RAND_MAX;
    accuracy = random * 100.00;
}

bool FeatureNode::contains(int num){
    if (features.size() == 0){
        return false;
    }
    else{
        for(int i = 0; i < features.size(); i++){
            if(num == features.at(i)){
                return true;
            }
        }
    }
    return false;
}


// contains

// copy constructor
FeatureNode &FeatureNode::operator=(const FeatureNode &rhs)
{

    // copy vector of rhs
    for (int i = 0; i < rhs.features.size(); ++i)
    {
        this->features.push_back(rhs.features.at(i));
    }

    this->accuracy = rhs.accuracy;
    this->featureLimit = rhs.featureLimit;

    return *this;
}

// overload output operator for a FeatureNode
ostream &operator<<(ostream &out, const FeatureNode &node)
{
    out << "Using feature(s) {";

    if (!(node.features.size() == 0))
    {
        out << node.features.at(0);

        if (!(node.features.size() == 1))
        {
            for (int i = 1; i < node.features.size(); ++i)
            {
                out << ", " << node.features.at(i);
            }
        }
    }

    out << "} accuracy is " << node.accuracy << "%" << endl;
    return out;
}