#ifndef EMPLEADO_H
#define EMPLEADO_H

#include "Usuario.h"

class Empleado : public Usuario {
public:
    Empleado();
    Empleado(int id, const string& usuario, const string& contrasena);

    string getTipo() const override;
    void mostrarInformacion() const override;
};

#endif
