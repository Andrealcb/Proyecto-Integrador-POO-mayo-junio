# Proyecto: Tienda ⌂

Simulador de una tienda desarrollado en **C++** utilizando **Programación Orientada a Objetos (POO)**, **herencia**, **composición**, separación en archivos `.h` y `.cpp`, y un menú interactivo por consola.

---

## ¿Para qué sirve este proyecto? (ᵔᵕᵔ)　

Este programa simula una tienda básica con las siguientes funciones:

* Crear productos con nombre, código, precio y cantidad.
* Registrar usuarios mediante herencia (Administrador, Gerente, Empleado).
* Agregar productos al carrito (composición).
* Realizar ventas y actualizar el inventario.
* Mostrar el inventario existente.
* Generar tickets de compra.
* Encapsular datos usando getters y setters.

---

## ¿Para qué NO sirve? ┬┬﹏┬┬

Este proyecto NO:

* Guarda información en archivos ni en bases de datos.
* Mantiene los datos después de cerrar el programa.
* Tiene interfaz gráfica (funciona solo por consola).
* Realiza operaciones avanzadas como reportes complejos o estadísticas.

---

## Estructura del proyecto



```
Proyecto/
│
├── main.cpp
│
├── Producto.h
├── Producto.cpp
│
├── Usuario.h
├── Usuario.cpp
│
├── Admin.h
├── Admin.cpp
│
├── Gerente.h
├── Gerente.cpp
│
├── Empleado.h
├── Empleado.cpp
│
├── Venta.h
│
├── Carrito.h
├── Carrito.cpp
│
├── Tienda.h
└── Tienda.cpp
```

---

## Descripción de las clases (según UML)

### **Producto**

* Atributos: nombre, precio, cantidad
* Métodos: mostrarInfo(), vender(), getters/setters
* Ubicación: `Producto.h / Producto.cpp`

### **Usuario**

* Atributos: nombre
* Métodos: getters, mostrarInfo
* Ubicación: `Usuario.h / Usuario.cpp`

### **Carrito (composición)**

* Contiene una lista de productos
* Métodos: agregarProducto(), mostrarCarrito(), total()
* Relación UML: **Composición**
* Ubicación: `Carrito.h / Carrito.cpp`

### **Tienda (composición + agregación)**

* Contiene: lista de productos y lista de usuarios
* Métodos: mostrarProductos(), registrarUsuario(), comprar(), menú principal
* Ubicación: `Tienda.h / Tienda.cpp`

---

## ¿Cómo se usa?


---

## ¿Cómo se usa?

### 1. Compilar

En consola:

```bash
podiar la direccion de la carpeta con los archivos y poner cd "Dirreccion"

y luego:
 
g++ main.cpp Tienda.cpp Producto.cpp Usuario.cpp Admin.cpp Gerente.cpp Empleado.cpp Carrito.cpp -o tienda


### **2. Ejecutar**

```
./proyecto
```

### **3. Interactuar con el programa**

Cuando entres al comienzo, te pedira una contraseña para Admin.

Luego volveras a ingresarla despues de haber elegido tu rango (Administrador).

Y asi ya podras interactuar con el menú y todo lo demás del programa.

El menú muestra opciones como:

* Ver productos
* Agregar productos (solo Admin)
* Agrgar gerentes o empleados (depende el rango)
* Comprar
* Ver carrito
* Salir
* Y más...

Las opciones del menú dependeran de que rango eres, entre más alto el rango mas opciones tendrás.

---


