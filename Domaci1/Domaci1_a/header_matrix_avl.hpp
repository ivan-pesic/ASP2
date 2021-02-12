#pragma once

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <cstdlib>
#include <ctime> //used for generating random numbers
#include <random>

#define _CRTDBG_MAP_ALLOC //used for memory leak checking
#include <crtdbg.h>

#include <fstream> //used for file reading

#include <iomanip> //used for manipulating input and output

#include <stack> //stack and queue
#include <queue>

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

int** formMatrix(int& row, int& col);
int** readMatrix(int& row, int& col, istream& input);

int** generateMatrix(int& row, int& col);

int* linearizedMatrix(int** matrix, int row, int col);

void printMatrix(int** matrix, int row, int col);
void freeMatrix(int** matrix, int& row, int& col);

int randNumber(int low, int high);
int min(int a, int b);

void searchKeyPosition(int** matrix, int row, int col, int key);

void evaluateAlgorithm(int** matrix, int row, int col);

treeNode* formTree(int* arr, int n);
void insertAVL(treeNode*& root, int k);
void searchKey(treeNode* root, int key);
treeNode* formNode(int key);
treeNode* copyTree(treeNode* root);
void printTree(treeNode* tree);
int treeDepth(treeNode* root);

void performanceOfAlgorithm(treeNode* root, int** matrix, int row, int col);
int* insertArray(int& n);
int* readArray(int& n, istream& input);
int numberOfSteps(int** matrix, int row, int col, int key);
int numberOfSteps(treeNode* root, int key);

void deleteTree(treeNode* root);

int menu();

#endif