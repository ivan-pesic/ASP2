#include "Tree.h"

int menu() {

	cout << "************************** MENI **************************" << endl
		<< "1. Formiranje stabla iz datoteke." << endl
		<< "2. Pretrazivanje stabla po prioritetu akcije." << endl
		<< "3. Umetanje nove akcije u stablo" << endl
		<< "4. Brisanje proizvoljne akcije po prioritetu." << endl
		<< "5. Brisanje akcije najviseg prioriteta." << endl
		<< "6. Ispisivanje 2-3-4 stabla." << endl
		<< "7. Ispisivanje red-black stabla" << endl
		<< "8. Izmena prioriteta akcije." << endl
		<< "9. Pronalazenje ukupnog broja akcija sa zadatim prioritetom." << endl
		<< "10. Kraj programa." << endl;

	int ans;
	do {
		cin >> ans;
		if (ans < 1 || ans > 10) {
			cout << "Neispravan unos. Uneti ponovo.";
		}
	} while (ans < 1 || ans > 10);
	return ans;
}