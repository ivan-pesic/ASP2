#include "avl.hpp"

void printMatrix(int** matrix, int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << setw(5) << matrix[i][j];
		}
		cout << endl;
	}
}

void printArray(int* arr, int n) {
	for (int i = 0; i < n; i++) {
		cout << setw(3) << arr[i];
	}
	cout << endl;
}

void inorder(treeNode* root) {
	treeNode* next = root;
	stack <treeNode*> s;
	while (true) {
		while (next != nullptr) {
			s.push(next);
			next = next->left;
		}
		if (!s.empty()) {
			next = s.top();
			s.pop();
			cout << next->key << ",";
			next = next->right;
		}
		else {
			cout << endl;
			return;
		}
	}
}

int main() {

	srand(time(nullptr));
	//std::mt19937 mt(/*seed*/);
	//std::lognormal_distribution<float> dist(1.0, 2.0);

	//float randomValue = dist(mt);

	int row, col;
	int** matrix = generateMatrix(row, col);
	//printMatrix(matrix, row, col);
	int* arr = linearizedMatrix(matrix, row, col);
	//printArray(arr, row * col);
	

	treeNode* tree = formTree(arr, row * col);
	treeNode* copy = copyTree(tree);

	//inorder(tree);
	printTree(tree);
	printTree(copy);
	
	
	return 0;
}