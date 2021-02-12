#include "header_matrix_avl.hpp"

void searchKeyPosition(int** matrix, int row, int col, int key) {

	if (!matrix) {
		cout << "Matrica ne postoji.";
		return;
	}

	if (key > matrix[0][0] || key < matrix[row - 1][col - 1]) {
		cout << "Kljuc nije pronadjen.";
		return;
	}

	int i = row - 1, j = 0;
	while (i >= 0 && i < row && j >= 0 && j < col) {
		if (matrix[i][j] < key)
			i--;
		else if (matrix[i][j] > key)
			j++;
		else {
			cout << "Kljuc pronadjen na poziciji [" << i << "][" << j << "]." << endl;
			return;
		}
	}
	cout << "Kljuc nije pronadjen.";
	return;
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

void evaluateAlgorithm(int** matrix, int row, int col) {
	cout << "Uneti donju i gornju granicu kljuceva: ";
	int low, high;
	cin >> low >> high;
	double cnt = 0;
	for (int i = low; i <= high; i++) {
		cnt += numberOfSteps(matrix, row, col, i);
	}

	double value = cnt / (high - low + 1);
	cout << "Prosecan broj pristupa za pretragu kljuca je: " << value << "." << endl;
	//	<< "Koraci: " << (int)cnt;
}