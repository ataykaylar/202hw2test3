#include "NgramTree.h"
#include <iostream>
#include <fstream>

using namespace std;

NgramTree::NgramTree()
{
	root = NULL;
}
ostream &operator<<(ostream &out, NgramTree &tree)
{
	return tree.print(out);
}

ostream &NgramTree::print(ostream &out)
{
	return printHelper(out, root);
}

ostream &NgramTree::printHelper(ostream &out, TreeNode *rootPtr)
{
	if (rootPtr != NULL)
	{
		printHelper(out, rootPtr->leftChildPtr);
		out << "\"" << rootPtr->item << "\" "
			<< "appears " << rootPtr->count << " time(s)" << endl;
		printHelper(out, rootPtr->rightChildPtr);
	}
	return out;
}

void NgramTree::generateTree(string fileName, int n)
{
	ifstream file;
	file.open(fileName.c_str());

	string word;
	while (file >> word)
	{
		if (word.length() >= n)
		{
			for (int i = 0; i <= word.length() - n; i++)
			{
				addNgram(word.substr(i, n));
		
			}
		}
	}
}

void NgramTree::addNgram(string ngram)
{

	TreeNode *temp = new TreeNode(ngram, NULL, NULL);
	TreeNode *cur = root;
	if (cur == NULL)
	{
		root = temp;
		root->count++;
		temp = NULL;
		cur = NULL;
		return;
	}
	else
	{
		while (cur != NULL)
		{
			if (ngram == cur->item)
			{
				cur->count++;
				delete temp;
				temp = NULL;
				cur = NULL;
				return;
			}
			else if (ngram.compare(cur->item) < 0)
			{
				if (cur->leftChildPtr == NULL)
				{
					cur->leftChildPtr = temp;
					cur->leftChildPtr->count++;
					temp = NULL;
					cur = NULL;
					return;
				}
				else
				{
					cur = cur->leftChildPtr;
				}
			}
			else if (ngram.compare(cur->item) > 0)
			{
				if (cur->rightChildPtr == NULL)
				{
					cur->rightChildPtr = temp;
					cur->rightChildPtr->count++;
					temp = NULL;
					cur = NULL;
					return;
				}
				else
				{
					cur = cur->rightChildPtr;
				}
			}
		}
	}
}

int NgramTree::getTotalNgramCount()
{
	int counter = 0;
	getTotalNgramCount(root, counter);
	return counter;
}

void NgramTree::getTotalNgramCount(TreeNode *subTreePtr, int &counter)
{
	if (subTreePtr != NULL)
	{
		counter++;
		getTotalNgramCount(subTreePtr->leftChildPtr, counter);
		getTotalNgramCount(subTreePtr->rightChildPtr, counter);
	}
}

int NgramTree::totalNodes(TreeNode *rootPtr)
{
	if (rootPtr == NULL)
		return 0;

	return 1 + totalNodes(rootPtr->leftChildPtr) + totalNodes(rootPtr->rightChildPtr);
}

bool NgramTree::isFull()
{
	return isFullHelper(root);
}

bool NgramTree::isFullHelper(TreeNode *subTreePtr)
{

	if (subTreePtr == NULL)
		return true;

	if (subTreePtr->leftChildPtr == NULL && subTreePtr->rightChildPtr == NULL)
		return true;

	if ((subTreePtr->leftChildPtr) && (subTreePtr->rightChildPtr))
		return (isFullHelper(subTreePtr->leftChildPtr) && isFullHelper(subTreePtr->rightChildPtr));

	return false;
}

bool NgramTree::isComplete()
{

	return isCompleteHelper(root, 0, totalNodes(root));
}

bool NgramTree::isCompleteHelper(TreeNode *rootPtr, int indx, int totalNodes)
{

	// empty tree
	if (rootPtr == NULL)
		return true;

	// present index >= number of nodes in tree
	if (indx >= totalNodes)
		return false;

	// recurse
	return isCompleteHelper(rootPtr->leftChildPtr, 2 * indx + 1, totalNodes) && isCompleteHelper(rootPtr->rightChildPtr, 2 * indx + 2, totalNodes);
}

NgramTree::~NgramTree()
{
	destroyTree(root);
}

void NgramTree::destroyTree(TreeNode *&treePtr)
{

	if (treePtr != NULL)
	{
		destroyTree(treePtr->leftChildPtr);
		destroyTree(treePtr->rightChildPtr);
		delete treePtr;
		treePtr = NULL;
	}
}

TreeNode *NgramTree::getRoot()
{

	return root;
}
