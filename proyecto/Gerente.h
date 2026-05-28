#ifndef GERENTE_H
#define GERENTE_H

#include "Usuario.h"

class Gerente : public Usuario {
public:
    Gerente();
    Gerente(int id, const string& usuario, const string& contrasena);

    string getTipo() const override;
    void mostrarInformacion() const override;
};

#endif
