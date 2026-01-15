#ifndef STANICA_H
#define STANICA_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Stanica{
private:
    static int _counter;

    int _id;
    string _ime;
    vector<int> _redPutnika;
    int _ulica;
public:
    Stanica(string, int);
    ~Stanica();

    virtual void stampa() const = 0;

    virtual void dodajPutnika(int) = 0;
    void ukloniPutnika(int);

    vector<int> getRedPutnika() const;
    void setRedPutnika(vector<int>);

    int brojPutnika() const;

    int getUlica() const;

    int getID() const;
    string getIme() const;
};

#endif