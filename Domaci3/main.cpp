#include <iostream>
#include <istream>
#include <fstream>
#include <filesystem>
#include <string>
#include <cctype>
using namespace std;


#include <chrono>


#include "DigitalnoStablo.h"

bool slova(string& rec) {
    for (int i = 0; i < rec.length(); i++) {
        if ((rec[i] < 'a' || rec[i] > 'z') && (rec[i] < 'A' || rec[i] > 'Z'))
            return false;
    }
    return true;
}

void citajIzFajla(Stablo& s, const string& imeDat) {
    ifstream dat;
    dat.open(imeDat);
    if (!dat.is_open()) {
        cout << endl << "Greska! Nepostojeca datoteka!" << endl << endl;
        return;
    }
    string rec;
    while (!dat.eof()) {
        dat >> rec;
        if (slova(rec))
            s.umetni(rec);
    }
    dat.close();
}

void citajIzDir(Stablo& s, string& path) {
    ifstream dat;
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        dat.open(entry);
        string rec;
        while (!dat.eof()) {
            dat >> rec;
            if (slova(rec))
                s.umetni(rec);
        }
        dat.close();
    }
}

int main() {
    Stablo* stablo = nullptr;
    while (true) {
        int res;
        cout << "############################# MENI #############################" << endl
             << "# 1. Stvaranje praznog recnika                                 #" << endl
             << "# 2. Unistavanje recnika                                       #" << endl
             << "# 3. Stvaranje recnika na osnovu datoteke                      #" << endl
             << "# 4. Stvaranje recnika na osnovu datoteka iz direktorijuma     #" << endl
             << "# 5. Pretrazivanje reci                                        #" << endl
             << "# 6. Umetanje i azuriranje frekvencija                         #" << endl
             << "# 7. Predvidjanje reci na osnovu zadatog stringa               #" << endl
             << "# 8. Kraj programa                                             #" << endl
             << "################################################################" << endl << endl;
        cin >> res;
        switch (res) {
        case 1:
            stablo = new DigitalnoStablo;
            cout << endl << "Recnik je stvoren." << endl << endl;
            break;
        case 2:
            if (!stablo) {
                cout << endl << "Recnik ne postoji! Prvo napraviti recnik!" << endl << endl;
                break;
            }
            delete stablo;
            stablo = nullptr;
            cout << endl << "Recnik je izbrisan." << endl << endl;
            break;
        case 3: {
            if (!stablo) {
                cout << endl << "Recnik ne postoji! Prvo napraviti recnik!" << endl << endl;
                break;
            }
            cout << endl << "Uneti ime datoteke: ";
            string imeDat;
            cin >> imeDat;
            citajIzFajla(*stablo, imeDat);
            cout << endl << "Recnik je stvoren." << endl << endl;
        }
              break;
        case 4: {
            if (!stablo) {
                cout << endl << "Recnik ne postoji! Prvo napraviti recnik!" << endl << endl;
                break;
            }
            cout << endl << "Uneti putanju do direktorijuma u kome se nalaze datoteke: ";
            cin.ignore();
            string path;
            getline(cin, path);

            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

            citajIzDir(*stablo, path);
            
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[s]" << std::endl;
            stablo->ispisiStatistiku(cout);
            cout << endl << "Recnik je ucitan." << endl << endl;
        }
              break;
        case 5: {
            if (!stablo) {
                cout << endl << "Recnik ne postoji! Prvo napraviti recnik!" << endl << endl;
                break;
            }
            cout << endl << "Uneti rec koju zelite pretraziti: ";
            string rec;
            cin >> rec;
            int res = stablo->trazi(rec);//trazi(*stablo, rec);
            cout << "Trazim kljuc: " << rec << endl;
            if (res) {
                cout << "<" << rec << ">" << " : " << res << endl << endl;
            }
            else {
                cout << "Ne postoji kljuc: " << rec << endl << endl;
            }
        }
              break;
        case 6: {
            if (!stablo) {
                cout << endl << "Recnik ne postoji! Prvo napraviti recnik!" << endl << endl;
                break;
            }
            cout << endl << "Uneti rec koju zelite umetnuti u stablo: ";
            string rec;
            cin >> rec;
            stablo->umetni(rec);
            cout << endl << "Rec " << rec << " je uneta." << endl << endl;
        }
              break;
        case 7: {
            if (!stablo) {
                cout << endl << "Recnik ne postoji! Prvo napraviti recnik!" << endl << endl;
                break;
            }
            cout << endl << "Simuliranje tastature. Uneti rec: ";
            string rec;
            cin >> rec;
            stablo->predikcija(rec);
        }
              break;
        case 8: {
            delete stablo;
            cout << endl << "Kraj." << endl;
            return 0;
        }
              break;
        default:
            cout << endl << "Nekorektan unos. Uneti ponovo!" << endl << endl;
            break;
        }
    }
}