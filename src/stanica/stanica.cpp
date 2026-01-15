#include "stanica.h"
#include <algorithm>
using namespace std;

int Stanica::_counter = 1;

Stanica::Stanica(string naziv, int ulica) :  
    _ime(naziv), _ulica(ulica) {
       _id = _counter++; 
    }

Stanica::~Stanica(){}

void Stanica::ukloniPutnika(int putnik){
    _redPutnika.erase(remove(_redPutnika.begin(), _redPutnika.end(),putnik), _redPutnika.end());
}

int Stanica::getID() const{
    return _id;
}

string Stanica::getIme() const{
    return _ime;
}

int Stanica::getUlica() const{
    return _ulica;
}

vector<int> Stanica::getRedPutnika() const{
    return _redPutnika;
}

void Stanica::setRedPutnika(vector<int> redPutnika){
    _redPutnika = redPutnika;
}

int Stanica::brojPutnika() const{
    return _redPutnika.size();
}