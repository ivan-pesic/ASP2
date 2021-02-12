// DigitalnoStablo.cpp: implementation of the DigitalnoStablo class.
//
//////////////////////////////////////////////////////////////////////

#include "DigitalnoStablo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

string mapa(char c) {
    switch (c) {
    case 'a': return "qwsz";
        break;
    case 'b':return "vghn";
        break;
    case 'c':return "xdfv";
        break;
    case 'd':return "xserfc";
        break;
    case 'e':return "wsdr";
        break;
    case 'f':return "drtgvc";
        break;
    case 'g':return "ftyhbv";
        break;
    case 'h':return "gyujnb";
        break;
    case 'i':return "ujko";
        break;
    case 'j':return "huikmn";
        break;
    case 'k':return "jiolm";
        break;
    case 'l':return "kop";
        break;
    case 'm':return "njk";
        break;
    case 'n':return "bhjm";
        break;
    case 'o':return "iklp";
        break;
    case 'p':return "ol";
        break;
    case 'q':return "aw";
        break;
    case 'r':return "edft";
        break;
    case 's':return "awedxz";
        break;
    case 't':return "rfgy";
        break;
    case 'u':return "yhji";
        break;
    case 'v':return "cfgb";
        break;
    case 'w':return "qase";
        break;
    case 'x':return "zsdc";
        break;
    case 'y':return "tghu";
        break;
    case 'z':return "asx";
        break;

        //velika slova

    case 'A': return "QWSZ";
        break;
    case 'B':return "VGHN";
        break;
    case 'C':return "XDFV";
        break;
    case 'D':return "XSERFC";
        break;
    case 'E':return "WSDR";
        break;
    case 'F':return "DRTGVC";
        break;
    case 'G':return "FTYHBV";
        break;
    case 'H':return "GYUJNB";
        break;
    case 'I':return "UJKO";
        break;
    case 'J':return "HUIKMN";
        break;
    case 'K':return "JIOLM";
        break;
    case 'L':return "KOP";
        break;
    case 'M':return "NJK";
        break;
    case 'N':return "BHJM";
        break;
    case 'O':return "IKLP";
        break;
    case 'P':return "OL";
        break;
    case 'Q':return "AW";
        break;
    case 'R':return "EDFT";
        break;
    case 'S':return "AWEDXZ";
        break;
    case 'T':return "RFGY";
        break;
    case 'U':return "YHJI";
        break;
    case 'V':return "CFGB";
        break;
    case 'W':return "QASE";
        break;
    case 'X':return "ZSDC";
        break;
    case 'Y':return "TGHU";
        break;
    case 'Z':return "ASX";
        break;

    }
}

DigitalnoStablo::DSUnutrasnjiCvor::~DSUnutrasnjiCvor() {
    while(m_prvi) {
        ListElem *cvor = m_prvi;

        m_prvi=m_prvi->sledeci;
        delete cvor->podstablo;
        delete cvor;
    }
}

DigitalnoStablo::DSCvor * DigitalnoStablo::DSUnutrasnjiCvor::pronadjiPodstablo(char deoKljuca) {
    if(!m_prvi)
        return 0;

    ListElem *cvor = m_prvi;
    while(cvor) {
        if(cvor->deoKljuca == deoKljuca)
            return cvor->podstablo;

        cvor = cvor->sledeci;
    }

    return 0;
}


void DigitalnoStablo::DSUnutrasnjiCvor::dodajPodstablo(char deoKljuca, DigitalnoStablo::DSCvor *cvor) {
    ListElem *novi = new ListElem(deoKljuca, cvor);

    if (!m_prvi) {
        m_prvi = novi;
    }
          
    else {
        ListElem *tek = m_prvi, *preth = 0;

        while(tek && tek->deoKljuca < deoKljuca) {
            preth = tek;
            tek = tek->sledeci;
        }

        if(preth)
            preth->sledeci = novi;
        else
            m_prvi = novi;
            
        novi->sledeci = tek;
    }

    m_brojPodstabala++;
}

void DigitalnoStablo::DSUnutrasnjiCvor::ukloniPodstablo(char deoKljuca) {
    if(!m_prvi)
        return;

    ListElem *tek = m_prvi, *preth = 0;

    while( tek && tek->deoKljuca != deoKljuca ) {
        preth = tek;
        tek = tek->sledeci;
    }

    if (!tek)
        return;

    if (preth)
        preth->sledeci = tek->sledeci;
    else
        m_prvi = m_prvi->sledeci;

    delete tek;
    m_brojPodstabala--;
}

void DigitalnoStablo::DSUnutrasnjiCvor::poseti(ostream &it) {
    for(ListElem *tek = m_prvi; tek; tek = tek->sledeci)
        tek->podstablo->poseti(it);
}

//----------------------------------------------

DigitalnoStablo::DSList::~DSList() {}

void DigitalnoStablo::DSList::postaviInfo(int info) {
    m_info = info;
}

void DigitalnoStablo::DSList::poseti(ostream &it) {
    if (m_info)
        it << m_info << endl;
}

//-----------------------------------------------

DigitalnoStablo::DigitalnoStablo(): m_koren(0) {}

DigitalnoStablo::~DigitalnoStablo() {
    if (m_koren)
        delete m_koren;
}

int DigitalnoStablo::trazi(const string& kljuc) {
    int rez = dohvatiInfo(kljuc);
    if (rez)
        return rez;
    return 0;
}

void DigitalnoStablo::predikcija(const string& prefiks) {

    int rez;
    if (rez = dohvatiInfo(prefiks)) {
        cout << endl << prefiks << ":" << rez << endl << endl;
    }

    priority_queue<pair<int, string>, vector<pair<int, string>>> pq;
    insertujReci(pq, prefiks);
    //pretraga i umetanje
    for (int i = 0; i < prefiks.length(); i++) {
        string uRed = prefiks;
        char c1 = uRed[i];
        string g1 = mapa(prefiks[i]);
        for (int j = 0; j < g1.length(); j++) {
            uRed[i] = g1[j];
            insertujReci(pq, uRed);
            for (int k = i + 1; k < prefiks.length(); k++) {
                char c2 = uRed[k];
                string g2 = mapa(prefiks[k]);
                for (int l = 0; l < g2.length(); l++) {
                    uRed[k] = g2[l];
                    insertujReci(pq, uRed);
                    for (int m = k + 1; m < prefiks.length(); m++) {
                        char c3 = uRed[m];
                        string g3 = mapa(prefiks[m]);
                        for (int n = 0; n < g3.length(); n++) {
                            uRed[m] = g3[n];
                            insertujReci(pq, uRed);
                        }
                        uRed[m] = c3;
                    }
                }
                uRed[k] = c2;
            }
        }
        uRed[i] = c1;
    }

    //ispis 3 najfrekventnije reci
    int cnt = 3;
    while (!pq.empty() && cnt > 0) {
        cout << endl << pq.top().second << " : " << pq.top().first << endl;
        pq.pop();
        cnt--;
    }
    cout << endl;
     
}

void DigitalnoStablo::insertujReci(priority_queue<pair<int, string>, vector<pair<int, string>>>& pq, const string& prefiks) {
    string str = prefiks;

    DSCvor* tek = m_koren;
    int len = prefiks.length();
    for (int i = 0; i < len && tek; i++)
        tek = tek->pronadjiPodstablo(prefiks[i]);

    if (!tek) {
        //cout << endl << "Ne postoji prefiks " << prefiks << endl << endl;
        return; //ovde ce biti continue najverovatnije u petlji
    }


    DSUnutrasnjiCvor* cvor = static_cast<DSUnutrasnjiCvor*>(tek);
    DSUnutrasnjiCvor::ListElem* next = cvor->dohvListu();
    stack<DSUnutrasnjiCvor::ListElem*>st;
    bool flag;
    while (true) {
        while (next && next->deoKljuca != EOK) {
            st.push(next);
            str.push_back(next->deoKljuca);
            next = next->dohvPodstablo()->dohvListu();
        }

        if (next) {
            flag = true;
            st.push(next);
        }

        if (!st.empty()) {
            next = st.top();

            if (flag) {
                DSList* freq = static_cast<DSList*>(next->podstablo);
                pq.push({ freq->dohvatiInfo(),str });
                flag = false;
            }
            if (next->deoKljuca != EOK) {
                str.pop_back();
            }
            st.pop();
            next = next->sledeci;
        }
        else {
            break;
        }
    }
}

DigitalnoStablo::DSList *DigitalnoStablo::pronadjiCvor(const string& kljuc) {   // pronalazi list koji sadrzi dati kljuc

    if (!m_koren)
        return 0;

    DSCvor* tek = m_koren;
    int len = kljuc.length();
    for(int i = 0; i < len && tek; i++)
        tek = tek->pronadjiPodstablo(kljuc[i]);

    if(tek)
        tek = tek->pronadjiPodstablo(EOK);

    if(tek)
        return (DSList *)tek;

    return 0;
}

bool DigitalnoStablo::umetni(const string& kljuc) {
    if(!m_koren) {
        m_koren = new DSUnutrasnjiCvor(0);
        m_brCvorova++;
    }

    DSCvor *tek = m_koren;
    DSCvor *sledeci = 0;
    int len = kljuc.length();
    for( int i = 0; i < len; i++ ) {
      
        sledeci = tek->pronadjiPodstablo( kljuc[i] );

        if(!sledeci) {
            sledeci = new DSUnutrasnjiCvor(tek);
            tek->dodajPodstablo( kljuc[i], sledeci );
            m_brCvorova++;
        }

        tek = sledeci;
    }

    if (sledeci = tek->pronadjiPodstablo(EOK)) {
        sledeci->postaviInfo(sledeci->dohvatiInfo() + 1);
    }
    else {
        sledeci = new DSList(tek);
        tek->dodajPodstablo( EOK, sledeci );
        m_brKljuceva++;
    }

    return true;
}


bool DigitalnoStablo::obrisi(const string& kljuc) {
    if (!m_koren)
        return false;

    DSCvor *tek = pronadjiCvor(kljuc);
    if (!tek)
        return false;

    tek->postaviInfo(0);
    int i = kljuc.length();
      
    while( i >= 0 && tek && tek->brojPodstabala() == 0) {
        DSCvor *roditelj = tek->roditelj();

        delete tek;
        m_brCvorova--;

        if(roditelj)
            roditelj->ukloniPodstablo( kljuc[i--] );
        else
            m_koren = 0;
        tek = roditelj;
    }

    m_brKljuceva--;

    return true;
}

int DigitalnoStablo::dohvatiInfo(const string& kljuc) {
    DSList *list = pronadjiCvor(kljuc);

    if(list)
        return list->dohvatiInfo();

    return 0;
}

void DigitalnoStablo::obidji(ostream &it) {
    if(m_koren)
        m_koren->poseti(it);
}