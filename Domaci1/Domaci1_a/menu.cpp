#include "header_matrix_avl.hpp"

int menu() {
	int ans;
	cout<<"******************      MENI      *****************"<< endl << endl;
	cout << "1.\tUnos matrice" << endl
		<< "2.\tGenerisanje matrice" << endl
		<< "3.\tPretraga matrice" << endl
		<< "4.\tEvaluacija performansi za matricu" << endl
		<< "5.\tFormiranje stabla na osnovu postojece matrice" << endl
		<< "6.\tPretraga stabla na zadati kljuc" << endl
		<< "7.\tUmetanje kljuca u stablo" << endl
		<< "8.\tIspis stabla" << endl
		<< "9.\tBrisanje stabla" << endl
		<< "10.\tEvaluacija performansi za obe strukture" << endl
		<< "11.\tKraj" << endl;
	
	do {
		printf("\nUneti zeljeni podmeni: ");
		cin >> ans;

		if (ans < 1 || ans > 11) {
			cout << endl << "Nekorektan unos. Unesite odgovarajuci podmeni ponovo." << endl;
		}
	} while (ans < 1 || ans > 11);
	return ans;
}