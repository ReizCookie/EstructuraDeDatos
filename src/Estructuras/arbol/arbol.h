#ifndef ARBOL_H
#define ARBOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Libro.h"

typedef struct nodo{
    Libro *libro;
    struct nodo *izq;
    struct nodo *dch;
}Nodo;

//Prototipos de las funciones para los arboles

Nodo* insertar_por_titulo(Nodo* raiz, Libro* libro);// Inserta por titulo
Nodo* insertar_por_fecha(Nodo* raiz, Libro* libro);// Inserta por fecha
Nodo* insertar_por_fecha_titulo(Nodo* raiz, Libro* libro);// Inserta por fecha y titulo
Nodo* insertar_por_autor_titulo(Nodo* raiz, Libro* libro);// Inserta por autor y titulo
void mostrar_arbol_inorden(Nodo* raiz);// Muestra en orden
void liberar_arbol(Nodo** raiz); // Libera memoria

#endif