#ifndef ADMIN_H
#define ADMIN_H

#include "Usuario.h"

class Administrador : public Usuario {
public:
    Administrador();
    Administrador(int id, const string& usuario, const string& contrasena);

    string getTipo() const override;
    void mostrarInformacion() const override;
};

#endif