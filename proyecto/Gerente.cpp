#include "Gerente.h"
#include <iostream>
using namespace std;

Gerente::Gerente() : Usuario() {}

Gerente::Gerente(int id, const string& usuario, const string& contrasena)
    : Usuario(id, usuario, contrasena) {}

string Gerente::getTipo() const {
    return "Gerente";
}

void Gerente::mostrarInformacion() const {
    cout << "[Gerente] " << usuario << endl;
}