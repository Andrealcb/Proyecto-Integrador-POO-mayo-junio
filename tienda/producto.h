#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>
using namespace std;

class Producto {
private:
    string nombre;
    double precio;
    int cantidad;

public:
    // Constructor
    Producto(string _nombre, double _precio, int _cantidad);

    // Getters
    string getNombre();
    double getPrecio();
    int getCantidad();

    // Setters
    void setNombre(string n);
    void setPrecio(double p);
    void setCantidad(int c);

    // Metodos
    void mostrar();
    void vender(int unidades);
};

#endif
