// Stablo.h: interface for the Stablo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STABLO_H__5F3D5977_5DFA_4D4C_B15E_3DD09CBA589F__INCLUDED_)
#define AFX_STABLO_H__5F3D5977_5DFA_4D4C_B15E_3DD09CBA589F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <iostream>
#include <string>
using namespace std;

class Stablo {
protected:

    int m_brCvorova;
    int m_brKljuceva;

    Stablo() {
        m_brKljuceva = 0; 
        m_brCvorova = 0;
    }


public:

    virtual ~Stablo() { }

    virtual bool umetni(const string& kljuc) = 0;
	virtual bool obrisi(const string& kljuc) = 0;
    virtual void predikcija(const string&) = 0;
    virtual int trazi(const string& kljuc) = 0;

    virtual int dohvatiInfo(const string& kljuc) = 0;
	
    virtual int brojCvorova(){ return m_brCvorova; }
    virtual int brojKljuceva() { return m_brKljuceva; }

	virtual void obidji(ostream &it) = 0;
    virtual void ispisiStatistiku(ostream &it) {
        it << "Ukupno cvorova: " << brojCvorova() << endl;
        it << "Ukupno kljuceva: " << brojKljuceva() << endl;
    }
};



#endif // !defined(AFX_STABLO_H__5F3D5977_5DFA_4D4C_B15E_3DD09CBA589F__INCLUDED_)
