#include "avl.hpp"

void performanceOfAlgorithm(treeNode* root, int** matrix, int row, int col) {
	int n;
	int* array = insertArray(n);

	double cntAVL = 0;
	double cntMX = 0;

	for (int i = 0; i < n; i++) {
		cntAVL += numberOfSteps(root, array[i]);
		cntMX += numberOfSteps(matrix, row, col, array[i]);
	}

	cntAVL /= n;
	cntMX /= n;

	cout << "AVL: " << cntAVL << endl
		<< "Matrix: " << cntMX << endl;
}

int* readArray(int& n, istream& input) {
	input >> n;

	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		input >> arr[i];
	}

	return arr;
}

int* insertArray(int& n) {
	cout << "Izabrati ulaz:" << endl
		<< "\t1. Standardni ulaz" << endl
		<< "\t2. Datoteka" << endl;

	int answer;
	while (true) {
		cin >> answer;

		switch (answer) {
		case 1:
			cout << endl << "1. Unos sa standardnog ulaza." << endl
				<< "Uneti velicinu niza: ";
			return readArray(n, cin);

		case 2: {
			string fileName;
			cout << endl << "2. Unos iz datoteke." << endl
				<< "Uneti ime datoteke: ";
			cin >> fileName;
			ifstream inputFile(fileName);
			if (inputFile) {
				int* array = readArray(n, inputFile);
				inputFile.close();
				return array;
			}
			else {
				cout << "Nepostojeca datoteka!" << endl;
				return nullptr;
			}
		}
		default:
			cout << "Nekorektan unos! Uneti ponovo." << endl;
		}
	}
}

int numberOfSteps(treeNode* root, int key) {
	int cnt = 0;
	treeNode* p = root;

	while (p != nullptr && key != p->key) {
		cnt++;
		if (key < p->key)
			p = p->left;
		else
			p = p->right;
	}
	return cnt;
}

int numberOfSteps(int** matrix, int row, int col, int key) {
	int cnt = 0;
	if (!matrix) {
		return 0;
	}

	if (key > matrix[0][0] || key < matrix[row - 1][col - 1]) {
		return 1;
	}

	int i = row - 1, j = 0;
	while (i >= 0 && i < row && j >= 0 && j < col) {
		cnt++;
		if (matrix[i][j] < key) {
			i--;
		}
		else if (matrix[i][j] > key) {
			j++;
		}
		else {
			return cnt;
		}
	}
	return cnt;
}