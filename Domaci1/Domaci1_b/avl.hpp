#ifndef AVL_HPP_INCLUDED
#define AVL_HPP_INCLUDED

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <random>
#include <stack>
#include <queue>
#include <iomanip>

using namespace std;

struct treeNode
{
	int key;
	char b;
	struct treeNode* left; 
	struct treeNode* right;
};

struct qNode {
	treeNode* node;
	int level;
};

//matrix functions
int** generateMatrix(int& row, int& col);
int randNumber(int low, int high);
int min(int a, int b);
int* linearizedMatrix(int** matrix, int row, int col);

//tree functions
treeNode* formNode(int key);
void printTree(treeNode* root);
void insertAVL(treeNode*& root, int key);
void rightRotation(treeNode*& x);
void leftRotation(treeNode*& x);
int treeDepth(treeNode* root);
/*
	AVL tree functions
*/
treeNode* formTree(int* arr, int n);
void searchKey(treeNode* root, int key);
treeNode* copyTree(treeNode* root);

//evaluation of algorithms
void performanceOfAlgorithm(treeNode* root, int** matrix, int row, int col);
int* insertArray(int& n);
int* readArray(int& n, istream& input);
int numberOfSteps(int** matrix, int row, int col, int key);
int numberOfSteps(treeNode* root, int key);

//clearing memory
void deleteTree(treeNode* root);
void freeMatrix(int** matrix, int& row, int& col);

#endif