#include "Tienda.h"
#include "Admin.h"
#include "Gerente.h"
#include "Empleado.h"

#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace std;

/* =========================
   CONSTRUCTOR Y DESTRUCTOR
========================= */

Tienda::Tienda()
    : nextProductoId(1),
      nextUsuarioId(1),
      nextVentaId(1) {}

Tienda::~Tienda() {

    for (Usuario* usuario : usuarios) {
        delete usuario;
    }
}

/* =========================
   FECHA Y HORA
========================= */

string Tienda::nowString() const {

    auto now = chrono::system_clock::now();

    time_t tiempoActual = chrono::system_clock::to_time_t(now);

    tm local_tm;

#ifdef _WIN32
    localtime_s(&local_tm, &tiempoActual);
#else
    localtime_r(&tiempoActual, &local_tm);
#endif

    char buffer[64];

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &local_tm);

    return string(buffer);
}

/* =========================
   HELPERS
========================= */

string Tienda::readLine(const string& prompt) const {

    if (!prompt.empty()) {
        cout << prompt;
    }

    string texto;
    getline(cin, texto);

    return texto;
}

double Tienda::parseDouble(const string& texto) const {

    try {
        return stod(texto);
    }
    catch (...) {
        return 0.0;
    }
}

int Tienda::parseInt(const string& texto) const {

    try {
        return stoi(texto);
    }
    catch (...) {
        return 0;
    }
}

/* =========================
   PRODUCTOS
========================= */

int Tienda::indexProductoPorCodigo(const string& codigo) const {

    for (size_t indice = 0; indice < productos.size(); indice++) {

        if (productos[indice].getCodigo() == codigo) {
            return indice;
        }
    }

    return -1;
}

bool Tienda::codigoExiste(const string& codigo) const {

    return indexProductoPorCodigo(codigo) != -1;
}

/* =========================
   USUARIOS
========================= */

bool Tienda::usuarioExisteEnColeccion(const string& nombreUsuario) const {

    for (const Usuario* usuario : usuarios) {

        if (usuario->getUsuario() == nombreUsuario) {
            return true;
        }
    }

    return false;
}

/* =========================
   CREAR TABLAS
========================= */

void Tienda::crearTablas() {

    cout << "Tablas listas." << endl;
}

/* =========================
   AGREGAR PRODUCTO
========================= */

void Tienda::agregarProducto() {

    cout << "\n--- Agregar Producto ---\n";

    string nombreProducto = readLine("Ingrese el nombre del producto: ");
    string codigoProducto = readLine("Ingrese el codigo del producto: ");

    double precioProducto = parseDouble(
        readLine("Ingrese el precio del producto: ")
    );

    int cantidadProducto = parseInt(
        readLine("Ingrese la cantidad en stock: ")
    );

    agregarProducto(nombreProducto, codigoProducto, precioProducto, cantidadProducto);
}

void Tienda::agregarProducto(string nombre, string codigo, double precio, int cantidad) {

    if (nombre.empty()) {
        cout << "El nombre no puede estar vacio.\n";
        return;
    }

    if (codigo.empty()) {
        cout << "El codigo no puede estar vacio.\n";
        return;
    }

    if (codigoExiste(codigo)) {
        cout << "Ese codigo ya existe.\n";
        return;
    }

    if (precio <= 0) {
        cout << "El precio debe ser mayor que cero.\n";
        return;
    }

    if (cantidad < 0) {
        cout << "La cantidad no puede ser negativa.\n";
        return;
    }

    Producto nuevoProducto(
        nextProductoId++,
        nombre,
        codigo,
        precio,
        cantidad
    );

    productos.push_back(nuevoProducto);

    cout << "Producto agregado correctamente.\n";
}

/* =========================
   MOSTRAR PRODUCTOS
========================= */

void Tienda::mostrarProductos() const {

    cout << "\n--- PRODUCTOS ---\n";

    if (productos.empty()) {

        cout << "No hay productos registrados.\n";
        return;
    }

    for (const Producto& producto : productos) {
        producto.mostrar();
    }
}

/* =========================
   AGREGAR GERENTE
========================= */

void Tienda::agregarGerente() {

    cout << "\n--- Agregar Gerente ---\n";

    string nombreUsuario = readLine("Ingrese el nombre de usuario: ");
    string contrasena = readLine("Ingrese contraseña: ");

    agregarGerente(nombreUsuario, contrasena);
}

void Tienda::agregarGerente(string usuario, string contrasena) {

    if (usuario.empty()) {
        cout << "El usuario no puede estar vacio.\n";
        return;
    }

    if (contrasena.empty()) {
        cout << "La contraseña no puede estar vacia.\n";
        return;
    }

    if (usuarioExisteEnColeccion(usuario)) {
        cout << "Ese usuario ya existe.\n";
        return;
    }

    usuarios.push_back(
        new Gerente(
            nextUsuarioId++,
            usuario,
            contrasena
        )
    );

    cout << "Gerente agregado correctamente.\n";
}

/* =========================
   AGREGAR EMPLEADO
========================= */

void Tienda::agregarEmpleado() {

    cout << "\n--- Agregar Empleado ---\n";

    string nombreUsuario = readLine("Ingrese el nombre de usuario: ");
    string contrasena = readLine("Ingrese contraseña: ");

    agregarEmpleado(nombreUsuario, contrasena);
}

void Tienda::agregarEmpleado(string usuario, string contrasena) {

    if (usuario.empty()) {
        cout << "El usuario no puede estar vacio.\n";
        return;
    }

    if (contrasena.empty()) {
        cout << "La contraseña no puede estar vacia.\n";
        return;
    }

    if (usuarioExisteEnColeccion(usuario)) {
        cout << "Ese usuario ya existe.\n";
        return;
    }

    usuarios.push_back(
        new Empleado(
            nextUsuarioId++,
            usuario,
            contrasena
        )
    );

    cout << "Empleado agregado correctamente.\n";
}

/* =========================
   MOSTRAR USUARIOS
========================= */

void Tienda::mostrarUsuarios() const {

    cout << "\n--- LISTA DE USUARIOS ---\n";

    if (usuarios.empty()) {

        cout << "No hay usuarios registrados.\n";
        return;
    }

    // Polimorfismo: el vector guarda Usuario*, pero se ejecuta el metodo
    // mostrarInformacion() correspondiente a cada clase hija.
    for (const Usuario* usuario : usuarios) {

        usuario->mostrarInformacion();
    }
}

void Tienda::mostrarUsuarios(string tipo) const {

    cout << "\n--- USUARIOS: " << tipo << " ---\n";

    bool encontrado = false;

    for (const Usuario* usuario : usuarios) {

        if (usuario->getTipo() == tipo) {
            usuario->mostrarInformacion();
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No hay usuarios de tipo " << tipo << ".\n";
    }
}

/* =========================
   MOSTRAR TODOS LOS USUARIOS
========================= */

void Tienda::mostrarUsuariosCombinados() const {

    cout << "\n--- TODOS LOS USUARIOS ---\n";

    if (usuarios.empty()) {

        cout << "No hay usuarios registrados.\n";
        return;
    }

    for (const Usuario* usuario : usuarios) {

        cout << usuario->getTipo()
             << " | Usuario: "
             << usuario->getUsuario()
             << endl;
    }
}

/* =========================
   LOGIN ADMINISTRADOR
========================= */

vector<string> Tienda::siAdministrador() const {

    vector<string> datosUsuario;

    string nombreUsuario;
    string contrasena;

    cout << "Usuario: ";
    getline(cin, nombreUsuario);

    cout << "Contraseña: ";
    getline(cin, contrasena);

    for (const Usuario* usuario : usuarios) {

        if (
            usuario->getTipo() == "Administrador" &&
            usuario->getUsuario() == nombreUsuario &&
            usuario->getContrasena() == contrasena
        ) {

            datosUsuario = {
                to_string(usuario->getId()),
                usuario->getUsuario(),
                usuario->getContrasena()
            };

            return datosUsuario;
        }
    }

    return datosUsuario;
}

/* =========================
   LOGIN GERENTE
========================= */

vector<string> Tienda::siGerente() const {

    vector<string> datosUsuario;

    string nombreUsuario;
    string contrasena;

    cout << "Usuario: ";
    getline(cin, nombreUsuario);

    cout << "Contraseña: ";
    getline(cin, contrasena);

    for (const Usuario* usuario : usuarios) {

        if (
            usuario->getTipo() == "Gerente" &&
            usuario->getUsuario() == nombreUsuario &&
            usuario->getContrasena() == contrasena
        ) {

            datosUsuario = {
                to_string(usuario->getId()),
                usuario->getUsuario(),
                usuario->getContrasena()
            };

            return datosUsuario;
        }
    }

    return datosUsuario;
}

/* =========================
   LOGIN EMPLEADO
========================= */

vector<string> Tienda::siEmpleado() const {

    vector<string> datosUsuario;

    string nombreUsuario;
    string contrasena;

    cout << "Usuario: ";
    getline(cin, nombreUsuario);

    cout << "Contraseña: ";
    getline(cin, contrasena);

    for (const Usuario* usuario : usuarios) {

        if (
            usuario->getTipo() == "Empleado" &&
            usuario->getUsuario() == nombreUsuario &&
            usuario->getContrasena() == contrasena
        ) {

            datosUsuario = {
                to_string(usuario->getId()),
                usuario->getUsuario(),
                usuario->getContrasena()
            };

            return datosUsuario;
        }
    }

    return datosUsuario;
}

/* =========================
   CREAR ADMINISTRADOR
========================= */

void Tienda::administradorNo() {

    cout << "\nCree un usuario y contraseña para administrador:\n";

    string nombreUsuario = readLine("Usuario: ");

    string contrasena = readLine("Contraseña: ");

    usuarios.push_back(
        new Administrador(
            nextUsuarioId++,
            nombreUsuario,
            contrasena
        )
    );

    cout << "Administrador creado correctamente.\n";
}

/* =========================
   BUSCAR PRODUCTO
========================= */

void Tienda::buscarProductoPorCodigo() const {

    cout << "\n--- Buscar Producto ---\n";

    string codigoProducto = readLine("Ingrese el codigo del producto: ");

    buscarProductoPorCodigo(codigoProducto);
}

void Tienda::buscarProductoPorCodigo(string codigo) const {

    int indiceProducto = indexProductoPorCodigo(codigo);

    if (indiceProducto == -1) {
        cout << "Producto no encontrado.\n";
        return;
    }

    const Producto& productoEncontrado = productos[indiceProducto];

    cout << "Producto encontrado:\n";
    cout << "Nombre: " << productoEncontrado.getNombre() << endl;
    cout << "Codigo: " << productoEncontrado.getCodigo() << endl;
    cout << "Precio: $" << fixed << setprecision(2)
         << productoEncontrado.getPrecio() << endl;
    cout << "Stock: " << productoEncontrado.getCantidad() << endl;
}

/* =========================
   MODIFICAR PRODUCTO
========================= */

void Tienda::modificarProducto() {

    cout << "\n--- Modificar Producto ---\n";

    string codigoProducto = readLine(
        "Ingrese el codigo del producto a modificar: "
    );

    int indiceProducto = indexProductoPorCodigo(codigoProducto);

    if (indiceProducto == -1) {

        cout << "Producto no encontrado.\n";
        return;
    }

    Producto& productoEncontrado = productos[indiceProducto];

    string nuevoNombre = readLine(
        "Nuevo nombre (enter para dejar igual): "
    );

    string nuevoPrecio = readLine(
        "Nuevo precio (enter para dejar igual): "
    );

    string nuevaCantidad = readLine(
        "Nueva cantidad (enter para dejar igual): "
    );

    if (!nuevoNombre.empty()) {
        productoEncontrado.setNombre(nuevoNombre);
    }

    if (!nuevoPrecio.empty()) {
        productoEncontrado.setPrecio(
            parseDouble(nuevoPrecio)
        );
    }

    if (!nuevaCantidad.empty()) {
        productoEncontrado.setCantidad(
            parseInt(nuevaCantidad)
        );
    }

    cout << "Producto modificado correctamente.\n";
}

/* =========================
   ELIMINAR PRODUCTO
========================= */

void Tienda::eliminarProducto() {

    cout << "\n--- Eliminar Producto ---\n";

    string codigoProducto = readLine(
        "Ingrese el codigo del producto a eliminar: "
    );

    int indiceProducto = indexProductoPorCodigo(codigoProducto);

    if (indiceProducto == -1) {

        cout << "Producto no encontrado.\n";
        return;
    }

    productos.erase(productos.begin() + indiceProducto);

    cout << "Producto eliminado correctamente.\n";
}

/* =========================
   VENDER PRODUCTO
========================= */

void Tienda::venderProducto(
    const string& nombre_usuario,
    const string& rango
) {

    cout << "\n--- Vender Producto ---\n";

    Carrito carrito;

    while (true) {

        string codigoProducto = readLine(
            "Ingrese el codigo del producto ('fin' para terminar): "
        );

        string codigoMinuscula = codigoProducto;

        for (char& letra : codigoMinuscula) {
            letra = tolower(letra);
        }

        if (codigoMinuscula == "fin") {
            break;
        }

        int indiceProducto = indexProductoPorCodigo(codigoProducto);

        if (indiceProducto == -1) {

            cout << "Producto no encontrado.\n";
            continue;
        }

        Producto& productoEncontrado = productos[indiceProducto];

        cout << "Producto encontrado:\n";

        cout << "Nombre: "
             << productoEncontrado.getNombre()
             << endl;

        cout << "Precio: $"
             << productoEncontrado.getPrecio()
             << endl;

        cout << "Stock disponible: "
             << productoEncontrado.getCantidad()
             << endl;

        int cantidadVendida = parseInt(
            readLine("Ingrese cantidad a vender: ")
        );

        if (cantidadVendida <= 0) {

            cout << "Cantidad invalida.\n";
            continue;
        }

        if (cantidadVendida > productoEncontrado.getCantidad()) {

            cout << "No hay suficiente stock.\n";
            continue;
        }

        vector<string> fila = {
            to_string(productoEncontrado.getId()),
            productoEncontrado.getNombre(),
            productoEncontrado.getCodigo(),
            to_string(productoEncontrado.getPrecio()),
            to_string(productoEncontrado.getCantidad())
        };

        carrito.agregar(fila, cantidadVendida);

        cout << "Producto agregado al carrito.\n";
    }

    if (carrito.estaVacio()) {

        cout << "No se realizo ninguna venta.\n";
        return;
    }

    double totalVenta = carrito.total();

    cout << fixed << setprecision(2);

    cout << "Total a pagar: $" << totalVenta << endl;

    double pagoCliente = 0.0;

    while (true) {

        pagoCliente = parseDouble(
            readLine("Ingrese pago del cliente: ")
        );

        if (pagoCliente >= totalVenta) {
            break;
        }

        cout << "Pago insuficiente.\n";
    }

    double cambioCliente = pagoCliente - totalVenta;

    for (const ItemCarrito& item : carrito.getItems()) {

        string codigoProducto = item.productoRow[2];

        int indiceProducto = indexProductoPorCodigo(codigoProducto);

        if (indiceProducto != -1) {

            int nuevoStock =
                productos[indiceProducto].getCantidad()
                - item.cantidad;

            productos[indiceProducto].setCantidad(nuevoStock);
        }
    }

    cout << "\n--- TICKET DE COMPRA ---\n";

    for (const ItemCarrito& item : carrito.getItems()) {

        cout << "Producto: "
             << item.productoRow[1]
             << endl;

        cout << "Cantidad: "
             << item.cantidad
             << endl;

        cout << "-----------------------\n";
    }

    cout << "Total: $" << totalVenta << endl;

    cout << "Pago: $" << pagoCliente << endl;

    cout << "Cambio: $" << cambioCliente << endl;

    vector<pair<vector<string>, int>> productosVendidos;

    for (const ItemCarrito& item : carrito.getItems()) {

        productosVendidos.push_back({
            item.productoRow,
            item.cantidad
        });
    }

    registrarVenta(
        productosVendidos,
        totalVenta,
        nombre_usuario,
        rango
    );

    carrito.limpiar();
}

/* =========================
   REGISTRAR VENTA
========================= */

void Tienda::registrarVenta(
    const vector<pair<vector<string>, int>>& productos_a_vender,
    double total_venta,
    const string& usuario,
    const string& rango
) {

    string fechaVenta = nowString();

    for (const auto& producto : productos_a_vender) {

        Venta nuevaVenta;

        nuevaVenta.id = nextVentaId++;

        nuevaVenta.producto = producto.first[1];

        nuevaVenta.cantidad = producto.second;

        nuevaVenta.precio_unitario =
            stod(producto.first[3]);

        nuevaVenta.total =
            nuevaVenta.precio_unitario
            * nuevaVenta.cantidad;

        nuevaVenta.vendedor = usuario;

        nuevaVenta.rango = rango;

        nuevaVenta.fecha_hora = fechaVenta;

        ventas_registradas.push_back(nuevaVenta);
    }
}

/* =========================
   REPORTE DE VENTAS
========================= */

void Tienda::mostrarReporteVentas() const {

    cout << "\n--- REPORTE DE VENTAS ---\n";

    if (ventas_registradas.empty()) {

        cout << "No hay ventas registradas.\n";
        return;
    }

    for (const Venta& venta : ventas_registradas) {

        cout << "Fecha: "
             << venta.fecha_hora
             << endl;

        cout << "Producto: "
             << venta.producto
             << endl;

        cout << "Cantidad: "
             << venta.cantidad
             << endl;

        cout << "Total: $"
             << venta.total
             << endl;

        cout << "Vendedor: "
             << venta.vendedor
             << endl;

        cout << "Rango: "
             << venta.rango
             << endl;

        cout << "------------------------\n";
    }
}

/* =========================
   RUN
========================= */

void Tienda::run() {

    crearTablas();

    if (usuarios.empty()) {
        administradorNo();
    }

    while (true) {

        cout << "\nSeleccione su tipo de usuario:\n";

        cout << "1. Administrador\n";
        cout << "2. Gerente\n";
        cout << "3. Empleado\n";
        cout << "4. Salir\n";

        string opcionTipoUsuario = readLine("Opcion: ");

        /* =========================
           ADMINISTRADOR
        ========================= */

        if (opcionTipoUsuario == "1") {

            vector<string> administradorLogeado =
                siAdministrador();

            if (!administradorLogeado.empty()) {

                string nombreUsuario =
                    administradorLogeado[1];

                string rangoUsuario = "Administrador";

                while (true) {

                    cout << "\n--- MENU ADMINISTRADOR ---\n";

                    cout << "1. Agregar producto\n";
                    cout << "2. Buscar producto\n";
                    cout << "3. Modificar producto\n";
                    cout << "4. Eliminar producto\n";
                    cout << "5. Vender producto\n";
                    cout << "6. Mostrar productos\n";
                    cout << "7. Mostrar usuarios\n";
                    cout << "8. Reporte de ventas\n";
                    cout << "9. Agregar gerente\n";
                    cout << "10. Agregar empleado\n";
                    cout << "11. Salir\n";

                    string opcionAdministrador =
                        readLine("Opcion: ");

                    if (opcionAdministrador == "1") {

                        agregarProducto();
                    }

                    else if (opcionAdministrador == "2") {

                        buscarProductoPorCodigo();
                    }

                    else if (opcionAdministrador == "3") {

                        modificarProducto();
                    }

                    else if (opcionAdministrador == "4") {

                        eliminarProducto();
                    }

                    else if (opcionAdministrador == "5") {

                        venderProducto(
                            nombreUsuario,
                            rangoUsuario
                        );
                    }

                    else if (opcionAdministrador == "6") {

                        mostrarProductos();
                    }

                    else if (opcionAdministrador == "7") {

                        mostrarUsuariosCombinados();
                    }

                    else if (opcionAdministrador == "8") {

                        mostrarReporteVentas();
                    }

                    else if (opcionAdministrador == "9") {

                        agregarGerente();
                    }

                    else if (opcionAdministrador == "10") {

                        agregarEmpleado();
                    }

                    else if (opcionAdministrador == "11") {

                        break;
                    }

                    else {

                        cout << "Opcion invalida.\n";
                    }
                }
            }

            else {

                cout << "Credenciales incorrectas.\n";
            }
        }

        /* =========================
           GERENTE
        ========================= */

        else if (opcionTipoUsuario == "2") {

            vector<string> gerenteLogeado =
                siGerente();

            if (!gerenteLogeado.empty()) {

                string nombreUsuario =
                    gerenteLogeado[1];

                string rangoUsuario = "Gerente";

                while (true) {

                    cout << "\n--- MENU GERENTE ---\n";

                    cout << "1. Agregar producto\n";
                    cout << "2. Buscar producto\n";
                    cout << "3. Modificar producto\n";
                    cout << "4. Eliminar producto\n";
                    cout << "5. Vender producto\n";
                    cout << "6. Mostrar productos\n";
                    cout << "7. Mostrar empleados\n";
                    cout << "8. Reporte de ventas\n";
                    cout << "9. Agregar empleado\n";
                    cout << "10. Salir\n";

                    string opcionGerente =
                        readLine("Opcion: ");

                    if (opcionGerente == "1") {

                        agregarProducto();
                    }

                    else if (opcionGerente == "2") {

                        buscarProductoPorCodigo();
                    }

                    else if (opcionGerente == "3") {

                        modificarProducto();
                    }

                    else if (opcionGerente == "4") {

                        eliminarProducto();
                    }

                    else if (opcionGerente == "5") {

                        venderProducto(
                            nombreUsuario,
                            rangoUsuario
                        );
                    }

                    else if (opcionGerente == "6") {

                        mostrarProductos();
                    }

                    else if (opcionGerente == "7") {

                        mostrarUsuarios();
                    }

                    else if (opcionGerente == "8") {

                        mostrarReporteVentas();
                    }

                    else if (opcionGerente == "9") {

                        agregarEmpleado();
                    }

                    else if (opcionGerente == "10") {

                        break;
                    }

                    else {

                        cout << "Opcion invalida.\n";
                    }
                }
            }

            else {

                cout << "Credenciales incorrectas.\n";
            }
        }

        /* =========================
           EMPLEADO
        ========================= */

        else if (opcionTipoUsuario == "3") {

            vector<string> empleadoLogeado =
                siEmpleado();

            if (!empleadoLogeado.empty()) {

                string nombreUsuario =
                    empleadoLogeado[1];

                string rangoUsuario = "Empleado";

                while (true) {

                    cout << "\n--- MENU EMPLEADO ---\n";

                    cout << "1. Buscar producto\n";
                    cout << "2. Vender producto\n";
                    cout << "3. Mostrar productos\n";
                    cout << "4. Salir\n";

                    string opcionEmpleado =
                        readLine("Opcion: ");

                    if (opcionEmpleado == "1") {

                        buscarProductoPorCodigo();
                    }

                    else if (opcionEmpleado == "2") {

                        venderProducto(
                            nombreUsuario,
                            rangoUsuario
                        );
                    }

                    else if (opcionEmpleado == "3") {

                        mostrarProductos();
                    }

                    else if (opcionEmpleado == "4") {

                        break;
                    }

                    else {

                        cout << "Opcion invalida.\n";
                    }
                }
            }

            else {

                cout << "Credenciales incorrectas.\n";
            }
        }

        /* =========================
           SALIR
        ========================= */

        else if (opcionTipoUsuario == "4") {

            break;
        }

        else {

            cout << "Opcion invalida.\n";
        }
    }

    cout << "\nPrograma finalizado.\n";
}