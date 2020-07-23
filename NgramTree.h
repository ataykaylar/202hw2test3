

#include <iostream>
using namespace std;

class TreeNode
{ // node in the tree
private:
    TreeNode()
    {
        item = "";
        leftChildPtr = NULL;
        rightChildPtr = NULL;
        count = 0;
    }
    TreeNode(string &nodeItem, TreeNode *left = NULL, TreeNode *right = NULL)
    {
        item = nodeItem;
        leftChildPtr = left;
        rightChildPtr = right;
        count = 0;
    }
    string item; // data portion
    int count;
    TreeNode *leftChildPtr;  // pointer to left child
    TreeNode *rightChildPtr; // pointer to right child
    friend class NgramTree;
};

class NgramTree
{
public:
    NgramTree();
    ~NgramTree();
    void destroyTree(TreeNode *&treePtr);
    void addNgram(string ngram);
    int getTotalNgramCount();
    void getTotalNgramCount(TreeNode *subTreePtr, int &counter);
    bool isComplete();
    bool isFull();
    void generateTree(string fileName, int n);
    TreeNode *getRoot();

private:
    TreeNode *root;
    ostream &print(ostream &out);
    ostream &printHelper(ostream &out, TreeNode *rootPtr);
    friend ostream &operator<<(ostream &out, NgramTree &tree);
    bool isCompleteHelper(TreeNode* rootPtr, int indx, int totalNodes);
    bool isFullHelper( TreeNode* subTreePtr);
    int totalNodes(TreeNode* rootPtr);
};
