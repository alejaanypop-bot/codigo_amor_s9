#include <stdio.h>
#include <string.h>
#include "funciones.h"

int solicitarEntero() {
    int valor;
    while (scanf("%d", &valor) != 1) {
        printf("[!] Entrada no válida. Reintente: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n'); 
    return valor;
}


void solicitarCadena(char *destino, int limite) {
    fgets(destino, limite, stdin);
    destino[strcspn(destino, "\n")] = '\0';
}


int existeId(Libro_t *lista, int total, int idBuscado) {
    for (int i = 0; i < total; i++) {
        if ((lista + i)->id == idBuscado) return i; 
    }
    return -1;
}


void darDeAlta(Libro_t *catalogo, int *total) {
    if (*total >= CAPACIDAD_MAX) {
        printf("\nAlerta: Se ha alcanzado el límite máximo de %d registros.\n", CAPACIDAD_MAX);
        return;
    }

    Libro_t nuevo_libro;
    int temporal_id;

    while (1) {
        printf("\nAsigne un ID numérico al libro: ");
        temporal_id = solicitarEntero();

        if (temporal_id <= 0) {
            printf("El ID debe ser mayor a cero.\n");
        } else if (existeId(catalogo, *total, temporal_id) != -1) {
            printf("El ID %d ya pertenece a otro producto. Ingrese uno diferente.\n", temporal_id);
        } else {
            nuevo_libro.id = temporal_id;
            break; // ID verificado y único, salimos del bucle
        }
    }

    printf("Nombre de la obra: ");
    solicitarCadena(nuevo_libro.titulo, 100);

    printf("Autor / Escritor: ");
    solicitarCadena(nuevo_libro.autor, 50);

    printf("Año de edición: ");
    nuevo_libro.anio = solicitarEntero();

    strcpy(nuevo_libro.estado, "Disponible");

    
    catalogo[*total] = nuevo_libro;
    (*total)++;

    printf("-> Registro completado de forma exitosa.\n");
}


void listarCatalogo(Libro_t *catalogo, int total) {
    if (total == 0) {
        printf("\nEl catálogo se encuentra vacío actualmente.\n");
        return;
    }

    printf("\n%s\n", "==================== REPOSITORIO DE TEXTOS ====================");
    printf("%-8s %-25s %-20s %-8s %-12s\n", "CÓDIGO", "TÍTULO DE LA OBRA", "AUTOR", "AÑO", "SITUACIÓN");
    printf("%s\n", "---------------------------------------------------------------");

    for (int i = 0; i < total; i++) {
        // Acceso a datos alternativo (catalogo[i] en lugar de punteros directos para balancear legibilidad)
        printf("%-8d %-25s %-20s %-8d %-12s\n",
               catalogo[i].id, catalogo[i].titulo, catalogo[i].autor, catalogo[i].anio, catalogo[i].estado);
    }
    printf("%s\n", "===============================================================");
}


void localizarLibro(Libro_t *catalogo, int total) {
    if (total == 0) {
        printf("\nNo hay datos cargados en el sistema.\n");
        return;
    }

    int criterio;
    printf("\nModalidad de búsqueda:\n[1] Por Código ID\n[2] Por Título\nSelección: ");
    criterio = solicitarEntero();

    if (criterio == 1) {
        printf("Introduzca ID: ");
        int id = solicitarEntero();
        int indice = existeId(catalogo, total, id);

        if (indice != -1) {
            printf("\nFicha del Libro:\n> ID: %d\n> Título: %s\n> Autor: %s\n> Edición: %d\n> Estado: %s\n",
                   catalogo[indice].id, catalogo[indice].titulo, catalogo[indice].autor, catalogo[indice].anio, catalogo[indice].estado);
        } else {
            printf("No se registraron coincidencias para el ID %d.\n", id);
        }
    } else if (criterio == 2) {
        char busqueda[100];
        printf("Introduzca Título: ");
        solicitarCadena(busqueda, 100);

        for (int i = 0; i < total; i++) {
            if (strcasecmp(catalogo[i].titulo, busqueda) == 0) {
                printf("\nFicha del Libro:\n> ID: %d\n> Título: %s\n> Autor: %s\n> Edición: %d\n> Estado: %s\n",
                       catalogo[i].id, catalogo[i].titulo, catalogo[i].autor, catalogo[i].anio, catalogo[i].estado);
                return;
            }
        }
        printf("No se encontraron obras con el título '%s'.\n", busqueda);
    } else {
        printf("Opción fuera de rango.\n");
    }
}


void conmutarEstado(Libro_t *catalogo, int total) {
    if (total == 0) {
        printf("\nOperación abortada: Sistema vacío.\n");
        return;
    }

    printf("Identificador del libro a modificar: ");
    int id = solicitarEntero();
    int pos = existeId(catalogo, total, id);

    if (pos != -1) {
        if (strcmp(catalogo[pos].estado, "Disponible") == 0) {
            strcpy(catalogo[pos].estado, "Prestado");
        } else {
            strcpy(catalogo[pos].estado, "Disponible");
        }
        printf("Modificación guardada. Estado actual de '%s': %s\n", catalogo[pos].titulo, catalogo[pos].estado);
    } else {
        printf("El ID ingresado no coincide con ningún libro activo.\n");
    }
}

void darDeBaja(Libro_t *catalogo, int *total) {
    if (*total == 0) {
        printf("\nNada que eliminar. El catálogo está vacío.\n");
        return;
    }

    printf("ID del libro a dar de baja definitiva: ");
    int id = solicitarEntero();
    int pos = existeId(catalogo, *total, id);

    if (pos != -1) {
        // En lugar de recorrer todos los elementos, reemplazamos el borrado por el último de la lista
        catalogo[pos] = catalogo[*total - 1];
        (*total)--;
        printf("El registro fue removido del almacenamiento de manera exitosa.\n");
    } else {
        printf("No se encontró ningún registro vinculado al ID %d.\n", id);
    }
}
