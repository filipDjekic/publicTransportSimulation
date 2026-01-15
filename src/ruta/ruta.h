#ifndef RUTA_H
#define RUTA_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Ruta{
private:
    static int _counter;

    int _id;
    string _naziv;
    int _prevoz;
    double _cenaKarte; // stanica -> stanica
    vector<int> _ruta; // id - id stanice
public:
    Ruta(string, double);
    ~Ruta();

    void setPrevoz(int);
    void setRuta(vector<int>, int);
    vector<int> getRuta();

    bool nalaziSeNaRuti(int, int);

    double cena(int, int);

    int getID() const;

    void stampa() const;
};

#endif
