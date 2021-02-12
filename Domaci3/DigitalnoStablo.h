// DigitalnoStablo.h: interface for the DigitalnoStablo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIGITALNOSTABLO_H__3A24581B_2902_4E94_9213_DD2E7CFBE607__INCLUDED_)
#define AFX_DIGITALNOSTABLO_H__3A24581B_2902_4E94_9213_DD2E7CFBE607__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Stablo.h" 
#include <queue>
#include <stack>

#define EOK 0

class DigitalnoStablo : public Stablo {
public:

    class DSCvor {
    //public:
        // static string map(char c);
    protected:

        DSCvor* m_roditelj;

    public:
        DSCvor(DSCvor *roditelj) : m_roditelj(roditelj) { }
        virtual ~DSCvor() { }

        DSCvor *roditelj() { return m_roditelj; }

        virtual int dohvatiInfo() { return 0; }
        virtual void postaviInfo(int info) { }
        virtual void poseti(ostream &it) = 0;
        virtual DSCvor *pronadjiPodstablo(char deoKljuca) { return 0; }
        virtual void dodajPodstablo(char deoKljuca, DSCvor *cvor) { }
        virtual void ukloniPodstablo(char deoKljuca) { }
        virtual int brojPodstabala() const { return 0; }
    };

    class DSUnutrasnjiCvor : public DSCvor {
    public:
        struct ListElem {
            char deoKljuca;
            DSCvor* podstablo;
            ListElem* sledeci;

            ListElem(char _deoKljuca, DSCvor* p) {
                deoKljuca = _deoKljuca;
                podstablo = p;
                sledeci = 0;
            }
            DSUnutrasnjiCvor* dohvPodstablo() { return static_cast<DSUnutrasnjiCvor*>(podstablo); }
        };
    protected:

        ListElem* m_prvi;
        int m_brojPodstabala;

    public:

        DSUnutrasnjiCvor(DSCvor *roditelj) : DSCvor(roditelj), m_prvi(0), m_brojPodstabala(0) {}

        ~DSUnutrasnjiCvor();

        ListElem* dohvListu() { return m_prvi; }
        

        virtual DSCvor *pronadjiPodstablo(char deoKljuca);
        virtual void dodajPodstablo(char deoKljuca, DSCvor *cvor);
        virtual void ukloniPodstablo(char deoKljuca);

        virtual int brojPodstabala() const { return m_brojPodstabala; }
        virtual void poseti(ostream &it);
    };

    class DSList : public DSCvor {
    protected:
        int m_info;

    public:
        DSList(DSCvor *roditelj) : DSCvor(roditelj), m_info(1) { 
            //postaviInfo(info); 
        }
            
        ~DSList();

        virtual int dohvatiInfo() { return m_info; }
        virtual void postaviInfo(int info);
        virtual void poseti(ostream &it);
    };
            
    DSUnutrasnjiCvor* m_koren;

    DSList* pronadjiCvor(const string& kljuc);   // pronalazi list koji sadrzi dati kljuc
public:
    DigitalnoStablo();
	virtual ~DigitalnoStablo();

    int trazi(const string& kljuc);
    void predikcija(const string& prefiks);
    void insertujReci(priority_queue<pair<int, string>, vector<pair<int, string>>>& pq, const string& rec);

	virtual bool umetni(const string& kljuc);
	virtual bool obrisi(const string& kljuc);

    virtual int dohvatiInfo(const string& kljuc);
	
	virtual void obidji(ostream &it);
};

#endif // !defined(AFX_DIGITALNOSTABLO_H__3A24581B_2902_4E94_9213_DD2E7CFBE607__INCLUDED_)
