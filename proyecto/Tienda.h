#ifndef TIENDA_H
#define TIENDA_H

#include "Admin.h"
#include "Gerente.h"
#include "Empleado.h"
#include <vector>
#include <string>
#include "Producto.h"
#include "Usuario.h"
#include "Venta.h"
#include "Carrito.h"

/*
 * Clase Tienda: contiene las "tablas" en memoria, métodos CRUD, ventas y reportes.
 */
class Tienda {
private:
    // "Tablas" simuladas
    std::vector<Venta> ventas_registradas;
    std::vector<std::vector<std::string>> reporte_ventas;
    std::vector<Administrador> administradores;
    std::vector<Gerente> gerentes;
    std::vector<Empleado> empleados;
    std::vector<Producto> productos;



    // IDs automáticos
    int nextProductoId;
    int nextUsuarioId;
    int nextVentaId;

    // Helpers
    std::string nowString() const;
    std::string readLine(const std::string& prompt = "") const;
    double parseDouble(const std::string& s) const;
    int parseInt(const std::string& s) const;

    int indexProductoPorCodigo(const std::string& codigo) const;
    bool codigoExiste(const std::string& codigo) const;
    bool usuarioExisteEnColeccion(const std::string& nombre) const;

public:
    Tienda();

    // Inicialización
    void crearTablas();

    // Productos
    void agregarProducto();
    void buscarProductoPorCodigo() const;
    void modificarProducto();
    void eliminarProducto();
    void mostrarProductos() const;

    // Usuarios
    void agregarGerente();
    void agregarEmpleado();
    void modificarGerente();
    void modificarEmpleado();
    void eliminarGerente();
    void eliminarEmpleado();
    void mostrarUsuarios() const;
    void mostrarUsuariosCombinados() const;

    // Ventas / Carrito
    void venderProducto(const std::string& nombre_usuario = "Desconocido",
                        const std::string& rango = "Desconocido");
    void registrarVenta(const std::vector<std::pair<std::vector<std::string>,int>>& productos_a_vender,
                        double total_venta,
                        const std::string& usuario,
                        const std::string& rango);

    // Reportes
    void mostrarReporteVentas() const;

    // Login
    std::vector<std::string> siAdministrador() const;
    std::vector<std::string> siGerente() const;
    std::vector<std::string> siEmpleado() const;
    void administradorNo();

    // Run / Menú
    void run();
};

#endif
