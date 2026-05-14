#include <iostream>
#include "producto.h"
using namespace std;

int main() {

    // Crear un producto
    Producto gansito("Gansito", 15.0, 20);

    // Mostrar sus datos
    gansito.mostrar();

    // Vender 5 unidades
    gansito.vender(5);

    // Mostrar de nuevo para ver cambios
    gansito.mostrar();

    return 0;
}
