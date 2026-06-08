#include <stdio.h>
#include "funciones.h"

int main() {
    // Implementación usando el nuevo alias del Tipo de Dato
    Libro_t inventario[CAPACIDAD_MAX];
    int itemsActivos = 0;
    int seleccion;

    do {
        printf("\n================ PANEL DE CONTROL ================\n");
        printf(" [1] Dar de alta un libro\n");
        printf(" [2] Listar catálogo actual\n");
        printf(" [3] Localizar volumen (Buscar)\n");
        printf(" [4] Conmutar disponibilidad (Estado)\n");
        printf(" [5] Dar de baja un elemento\n");
        printf(" [6] Salir de la aplicación\n");
        printf("===================================================\n");
        printf("Ingrese comando numérico: ");

        seleccion = solicitarEntero();

        switch(seleccion) {
            case 1: darDeAlta(inventario, &itemsActivos); break;
            case 2: listarCatalogo(inventario, itemsActivos); break;
            case 3: localizarLibro(inventario, itemsActivos); break;
            case 4: conmutarEstado(inventario, itemsActivos); break;
            case 5: darDeBaja(inventario, &itemsActivos); break;
            case 6: printf("\nApagando el sistema. Operaciones finalizadas.\n"); break;
            default: printf("\nComando desconocido. Intente nuevamente.\n");
        }

    } while(seleccion != 6);

    return 0;
}
