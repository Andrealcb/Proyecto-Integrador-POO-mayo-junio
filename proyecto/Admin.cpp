#include "Admin.h"
#include <iostream>
using namespace std;

Administrador::Administrador() : Usuario() {}

Administrador::Administrador(int id, const string& usuario, const string& contrasena)
    : Usuario(id, usuario, contrasena) {}

string Administrador::getTipo() const {
    return "Administrador";
}

void Administrador::mostrarInformacion() const {
    cout << "[Administrador] " << usuario << endl;
}