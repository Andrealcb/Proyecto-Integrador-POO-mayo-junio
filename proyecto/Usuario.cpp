#include "Usuario.h"

Usuario::Usuario() : id(-1), usuario(""), contrasena("") {}

Usuario::Usuario(int id, const string& usuario, const string& contrasena)
    : id(id), usuario(usuario), contrasena(contrasena) {}

int Usuario::getId() const {
    return id;
}

string Usuario::getUsuario() const {
    return usuario;
}

string Usuario::getContrasena() const {
    return contrasena;
}

void Usuario::setUsuario(const string& usuario) {
    this->usuario = usuario;
}

void Usuario::setContrasena(const string& contrasena) {
    this->contrasena = contrasena;
}