#include "header_matrix_avl.hpp"

int main() {
	srand(time(nullptr));
	int row = 0, col = 0;
	int** matrix = nullptr;
	treeNode* tree = nullptr;
	treeNode* copy = nullptr;
	int ans = menu();

	while (true) {
		switch (ans)
		{
		case 1: {
			freeMatrix(matrix, row, col);
			matrix = formMatrix(row, col);
			printMatrix(matrix, row, col);
		}
			  break;
		case 2: {
			freeMatrix(matrix, row, col);
			matrix = generateMatrix(row, col);
			//printMatrix(matrix, row, col);
		}
			  break;
		case 3: {
			int key;
			cout << "\nUneti kljuc za pretragu: ";
			cin >> key;
			searchKeyPosition(matrix, row, col, key);
		}
			  break;
		case 4: {
			evaluateAlgorithm(matrix, row, col);
		}
			  break;
		case 5: {
			int* arr = linearizedMatrix(matrix, row, col);

			tree = formTree(arr, row * col);
			copy = copyTree(tree);
			delete[] arr;
		}
			  break;
		case 6: {
			int key;
			cout << "\nUneti kljuc za pretragu: ";
			cin >> key;
			searchKey(tree, key);
		}
			  break;
		case 7: {
			int key;
			cout << "\nUneti kljuc koji zelite da umetnete u stablo: ";
			cin >> key;
			if (!tree)
				tree = formNode(key);
			else
				insertAVL(tree, key);
		}
			  break;
		case 8: {
			printTree(tree);
		}
			  break;
		case 9: {
			deleteTree(tree);
			deleteTree(copy);
			tree = copy = nullptr;
		}
			  break;
		case 10: {
			performanceOfAlgorithm(copy, matrix, row, col);
		}
			   break;
		case 11:
			deleteTree(tree);
			deleteTree(copy);
			freeMatrix(matrix, row, col);
			_CrtDumpMemoryLeaks();
			return 0;
		}
		//cout << "Uneti zeljeni podmeni: ";
		ans = menu();
	}	

	
}