#include "../header/FeatureNode.h"
#include "../header/Validator.h"
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
// find random number between 0 and 1, multiply by 100
// returns 0 if features set is empty
void FeatureNode::accuracyEvaluation(Validator &v1)
{
    if (this->features.size() == 0)
    {
        this->accuracy = 0.00;
    }
    else
    {
        this->accuracy = v1.NN_classifier();
    }
}

bool FeatureNode::contains(int num)
{
    if (features.size() == 0)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < features.size(); i++)
        {
            if (num == features.at(i))
            {
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
    while (!this->features.empty())
    {
        this->features.pop_back();
    }

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
    out << "{";

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

    out << "}";
    return out;
}