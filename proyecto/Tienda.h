#ifndef TIENDA_H
#define TIENDA_H

#include "Admin.h"
#include "Gerente.h"
#include "Empleado.h"
#include "Producto.h"
#include "Usuario.h"
#include "Venta.h"
#include "Carrito.h"

#include <vector>
#include <string>

using namespace std;

class Tienda {
private:

    vector<Usuario*> usuarios;
    vector<Producto> productos;
    vector<Venta> ventas_registradas;

    int nextProductoId;
    int nextUsuarioId;
    int nextVentaId;

    string nowString() const;
    string readLine(const string& prompt = "") const;

    double parseDouble(const string& texto) const;
    int parseInt(const string& texto) const;

    int indexProductoPorCodigo(const string& codigo) const;

    bool codigoExiste(const string& codigo) const;
    bool usuarioExisteEnColeccion(const string& nombreUsuario) const;

public:

    Tienda();
    ~Tienda();

    void crearTablas();

    
    void agregarProducto();
    void agregarProducto(string nombre, string codigo, double precio, int cantidad);

    void buscarProductoPorCodigo() const;
    void buscarProductoPorCodigo(string codigo) const;

    void modificarProducto();
    void eliminarProducto();
    void mostrarProductos() const;

    void agregarGerente();
    void agregarGerente(string usuario, string contrasena);

    void agregarEmpleado();
    void agregarEmpleado(string usuario, string contrasena);

    void mostrarUsuarios() const;
    void mostrarUsuarios(string tipo) const;
    void mostrarUsuariosCombinados() const;

    void venderProducto(const string& nombre_usuario = "Desconocido",
                        const string& rango = "Desconocido");

    void registrarVenta(
        const vector<pair<vector<string>, int>>& productos_a_vender,
        double total_venta,
        const string& usuario,
        const string& rango
    );

    void mostrarReporteVentas() const;

    vector<string> siAdministrador() const;
    vector<string> siGerente() const;
    vector<string> siEmpleado() const;

    void administradorNo();

    void run();
};

#endif
