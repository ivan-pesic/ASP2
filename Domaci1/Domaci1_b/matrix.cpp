#include "avl.hpp"

int** generateMatrix(int& row, int& col) {
	int high;

	cout << "Uneti broj vrsta i kolona matrice: ";
	cin >> row >> col;

	int** matrix = new int* [row];
	for (int i = 0; i < row; i++) {
		matrix[i] = new int[col];
	}

	cout << endl << "Uneti najveci element matrice: ";
	cin >> high;
	int low = -high;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (i > 0 && j > 0) {
				matrix[i][j] = randNumber(low, min(matrix[i - 1][j], matrix[i][j - 1]));
			}
			else if (i > 0 && j == 0) {
				matrix[i][j] = randNumber(low, matrix[i - 1][j]);
			}
			else if (i == 0 && j > 0) {
				matrix[i][j] = randNumber(low, matrix[i][j - 1]);
			}
			else
				matrix[i][j] = high;
		}
	}
	return matrix;
}

void freeMatrix(int** matrix, int& row, int& col) {
	if (matrix) {
		for (int i = 0; i < row; i++)
			delete[] matrix[i];
		delete[] matrix;
	}
	row = col = 0;
	return;
}

int randNumber(int low, int high) {
	int max = low;
	for (int i = 0; i < 20; i++) {
		int num = (low + rand() % (high - low + 1));
		if (num > max)
			max = num;
	}
	return max;
}

int min(int a, int b) {
	return (a < b ? a : b);
}

int* linearizedMatrix(int** matrix, int row, int col) {
	int* arr = new int[row * col];
	int cnt = 0;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			arr[cnt++] = matrix[i][j];
		}
	}

	return arr;
}