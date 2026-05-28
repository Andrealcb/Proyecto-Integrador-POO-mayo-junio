#include "Empleado.h"
#include <iostream>
using namespace std;

Empleado::Empleado() : Usuario() {}

Empleado::Empleado(int id, const string& usuario, const string& contrasena)
    : Usuario(id, usuario, contrasena) {}

string Empleado::getTipo() const {
    return "Empleado";
}

void Empleado::mostrarInformacion() const {
    cout << "[Empleado] " << usuario << endl;
}
