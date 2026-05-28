#ifndef USUARIO_H
#define USUARIO_H

#include <string>
using namespace std;

class Usuario {
protected:
    int id;
    string usuario;
    string contrasena;

public:
    Usuario();
    Usuario(int id, const string& usuario, const string& contrasena);
    virtual ~Usuario() {}

    int getId() const;
    string getUsuario() const;
    string getContrasena() const;

    void setUsuario(const string& usuario);
    void setContrasena(const string& contrasena);

    virtual string getTipo() const = 0;
    virtual void mostrarInformacion() const = 0;
};

#endif