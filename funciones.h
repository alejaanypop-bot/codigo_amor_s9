#ifndef FUNCIONES_H
#define FUNCIONES_H

#define CAPACIDAD_MAX 10

typedef struct {
    int id;
    char titulo[100];
    char autor[50];
    int anio;
    char estado[20];
} Libro_t;


int solicitarEntero();
void solicitarCadena(char *destino, int limite);
int existeId(Libro_t *lista, int total, int idBuscado);

void darDeAlta(Libro_t *catalogo, int *total);
void listarCatalogo(Libro_t *catalogo, int total);
void localizarLibro(Libro_t *catalogo, int total);
void conmutarEstado(Libro_t *catalogo, int total);
void darDeBaja(Libro_t *catalogo, int *total);

#endif
