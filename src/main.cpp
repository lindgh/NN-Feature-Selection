#include "../header/FeatureNode.h"

// FeatureNode explore(FeatureNode parent);

int main()
{

    cout << "Welcome to lghun001 and [advithi netid]'s Feature Selection Algorithm." << "\n\nPlease enter total number of features: ";

    int userFeatures;
    cin >> userFeatures;
    cout << endl;

    FeatureNode initialNode(userFeatures); // THIS IS THE PARENT

    // 1. FIRST IMPLEMENT CONTAINS & COPY CONSTRUCTOR, THEN TEST ---

    /* COPY CONSTRUCTOR & OVERLOADING OPERATOR TESTS
    initialNode.features.push_back(1);
    initialNode.features.push_back(4);

    FeatureNode temp = initialNode;
    temp.accuracyEvaluation();
    cout << "initialNode: " << initialNode << "\ncopy node: " << temp << endl;
    */

    /* CONTAINS FUNCTION TEST
    for(int i = 0; i < userFeatures; i++){
        int test_num_2;
        cout << "Enter num to add to features: ";
        cin >> test_num_2;
        initialNode.features.push_back(test_num_2);
        cout << endl;
    }

    int test_num;
    cout << "Enter number to test contains in features: ";
    cin >> test_num;
    cout << endl;
    if(initialNode.contains(test_num)){
        cout << "features contains " << test_num << endl;
    }
    else{
        cout << "features does not contain " << test_num << endl;
    }
    */

    // 2. IMPLEMENT EXPLORE, THEN TEST (ONLY FORWARD RN) ---

    // 3. FINISH IMPLEMENTING MAIN FUNC ---

    // assuming parent is {} from beginning

    // BELOW IN MAIN FOR NOW

    // vector<FeatureNode> result;
    // FeatureNode temp;

    // while (result.size() < initialNode.featureLimit)
    // {
    //     if (result.size() == 0)
    //     {S
    //         temp = explore(initialNode);
    //     }
    //     else
    //     {
    //         temp = explore(result.at(result.size() - 1));
    //     }
    //     result.push_back(temp);
    // }

    return 0;
}

// FeatureNode explore(FeatureNode parent)
// {

//     // FeatureNode maxChild;
//     // bool firstChild = false;

//     // explore function, resturns featurenode, pass in a feature node "parent"
//     // //ex parent = {}
//     // for (int i = 1; i <= featureLimit; ++i) {

//     //    if (!parent.contains(i)) {
//     //     FeatureNode temp = parent;
//     //     temp.feature.push_back(i);
//     //     temp.accuracyEvaluation();

//     //     if (!firstChild) {
//     //     maxChild = temp;
//     //     firstChild = true;
//     //     }
//     //     else {
//     //         if (temp.accuracy > maxChild.accuracy)
//     //         maxChild = temp;
//     //     }
//     //     }
//     // }

//     // return maxChild
// }