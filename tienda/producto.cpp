#include "producto.h"
#include <iostream>
using namespace std;

// Constructor
Producto::Producto(string _nombre, double _precio, int _cantidad) {
    nombre = _nombre;
    precio = _precio;
    cantidad = _cantidad;
}

// Getters
string Producto::getNombre() { return nombre; }
double Producto::getPrecio() { return precio; }
int Producto::getCantidad() { return cantidad; }

// Setters
void Producto::setNombre(string n) { nombre = n; }
void Producto::setPrecio(double p) { if (p > 0) precio = p; }
void Producto::setCantidad(int c) { if (c >= 0) cantidad = c; }

// Metodo mostrar
void Producto::mostrar() {
    cout << "Producto: " << nombre << endl;
    cout << "Precio: $" << precio << endl;
    cout << "Cantidad: " << cantidad << endl;
}

// Metodo vender
void Producto::vender(int unidades) {
    if (unidades <= cantidad) {
        cantidad -= unidades;
        cout << "Venta realizada: " << unidades << " unidades." << endl;
    } else {
        cout << "No hay suficiente inventario." << endl;
    }
}
