#ifndef LISTA_DOBLE_H
#define LISTA_DOBLE_H

#include "../nodos/nododoble.h"

typedef struct 
{
	NodoD *inicio;
	NodoD *fin;
	int cant;
	int (*comparar)(void *datoA,void *dataB);
	void (*imprimir)(void *datoA);
	void (*liberar)(void *datoA);
}ListaD;

ListaD inicializarListaD(void);
void mostrarListaD(ListaD lista);


void insertarFinalD(ListaD*,void*);
void borrarListaD(ListaD *);
void borrarDatoD(ListaD *lista,void* dato,int  (*)(void*,void*));
void* buscarDatoD(ListaD lista,void *dato,int  (*)(void*,void*));

void reordenarD(ListaD *,int  (*)(void*,void*) );
void insertarOrdenadoD(ListaD *lista,void* dato);
void insertarInicioD(ListaD *lista,void* dato);
void insertarEnPosicionD(ListaD *lista,void* dato,int pos);
void eliminarEnPosicionD(ListaD *lista,int pos);



#endif