#include "listadoble.h"
#include <stdio.h>


ListaD inicializarListaD(void)
{
	return (ListaD) {NULL,NULL,0,NULL,NULL,NULL};
}
void mostrarListaD(ListaD lista)
{
	NodoD *p;	
	printf("\n Lista[%d]: ",lista.cant);
	for( p = lista.inicio ;  p!=NULL ; p = p->sig  )
	{
		printf(" ");
		lista.imprimir(p->dato);
		printf("->");
	}
	printf("NULL");
}

void borrarListaD(ListaD *lista)
{
	NodoD *actual,*anterior = NULL;
	for( actual = lista->inicio ; actual!=NULL ;  )
	{
		anterior = actual;
		actual = actual->sig;
		//free(anterior->dato);
		free(anterior);		
	}
	lista->inicio = NULL;
	lista->cant = 0;		
}

void borrarDatoD(ListaD *lista,void* dato,int  (*nuevocomparar)(void*,void*))
{
	NodoD *actual,*anterior = NULL;
	int  (*old)(void*,void*) = lista->comparar;
	lista->comparar = nuevocomparar;
	for( actual = lista->inicio ; actual!=NULL ;  actual = actual->sig)
	{
		if(lista->comparar(dato,actual->dato) == 0)
		{
			if(anterior!=NULL)
				anterior->sig = actual->sig;
			else
				lista->inicio = actual->sig;
			//free(actual->dato);
			free(actual);
			lista->cant--;
			break;			
		}		
		anterior = actual;
	}		
	lista->comparar = old;
}

void reordenarD(ListaD *listaOrigen,int  (*comparar)(void*,void*) )
{
	
	ListaD aux = inicializarListaD();
	aux.comparar = comparar;
	aux.imprimir = listaOrigen->imprimir;
	NodoD *actual;
	for( actual = listaOrigen->inicio ; actual!=NULL ;  )
	{
		insertarOrdenadoD( &aux, actual->dato);
		actual = actual->sig;
		eliminarEnPosicionD(listaOrigen,0);
	}
	*listaOrigen = aux;	
}


void* buscarDatoD(ListaD lista,void *dato,int  (*comparar)(void*,void*))
{
	NodoD *actual;
	for( actual = lista.inicio ; actual!=NULL ;  actual = actual->sig)
	{
		if( comparar(dato,actual->dato) == 0)
		{
			return actual->dato;
		}
	}	
	return NULL;
	
}

void insertarOrdenadoD(ListaD *lista,void* dato)
{
	NodoD *nuevo = crearNodoD(dato);
	NodoD *actual,*anterior=NULL;
	for( actual = lista->inicio ; actual!=NULL ;  actual = actual->sig)
	{
		if( lista->comparar(dato,actual->dato) == -1)
		//if( dato < actual->dato) //CONDICION DE PARO: AQUI VOY A INSERTAR
		{
			if(anterior!=NULL)
			{
				//INSERTO EN MEDIO
				anterior->sig = nuevo;
				nuevo->sig = actual;
			}
			else
			{
				//INSERTAR EN EL INICIO
				nuevo->sig = actual;
				lista->inicio = nuevo;
			}
			break;
		}
		anterior = actual;
	}		
	if(lista->inicio == NULL) //LISTA VACIA : INSERTAR UNICO DATO
		lista->inicio = nuevo;
	else if ( anterior !=NULL) // RECORRI TODA LA LISTA: INSERTAR AL FINAL
		anterior->sig = nuevo;	
	lista->cant++;	
}


void insertarFinalD(ListaD *lista,void* dato)
{
	//CREAR NODO
	NodoD *nuevo = crearNodoD(dato);
	if(lista->inicio == NULL && lista->cant == 0)
	{
		//LISTA VACIA
		//ASOCIAMOS AL INICIO
		lista->inicio = nuevo;
	}
	else
	{
		//RECORRER Y ENCONTRAR EL ULTIMO NODO
		//INSERTAR
		NodoD *p;
		for( p = lista->inicio ;  p!=NULL ; p = p->sig  )
		{
			if(p->sig == NULL)
			{
				p->sig = nuevo;
				break;
			}
		}
	}
	lista->cant++;
}



void insertarInicioD(ListaD *lista,void* dato)
{
	NodoD *nuevo = crearNodoD(dato);
	nuevo->sig = lista->inicio;
	lista->inicio = nuevo;	
	lista->cant++;
}

void insertarEnPosicionD(ListaD *lista,void* dato,int pos)
{	
	//VALIDAR
	if( pos==0 ||(pos > 0  && pos <= lista->cant ))
	{			
		NodoD *anterior ,*actual;
		anterior = NULL;
		actual = lista->inicio;
		for (int i=0; i<=lista->cant  ; i++)
		{
			if( i==pos)
			{
				if(anterior == NULL)
				{
					insertarInicioD(lista,dato);
					return;
				}
				else
				{
					NodoD *nuevo = crearNodoD(dato);
					nuevo->sig = actual;
					anterior->sig = nuevo;
					lista->cant++;
					return;
				
				}
			}
			anterior = actual;
			actual = actual->sig;
		}				
	}	
}


void eliminarEnPosicionD(ListaD *lista,int pos)
{		
	//VALIDAR
	if( pos==0 ||(pos > 0  && pos < lista->cant ))
	{			
		NodoD *anterior ,*actual;
		anterior = NULL;
		actual = lista->inicio;
		for (int i=0; i<lista->cant  ; i++)
		{
			if( i==pos)
			{
				if(anterior == NULL)
					lista->inicio = actual->sig;
				else
					anterior->sig = actual->sig;
	
				free(actual);
				lista->cant--;
				break;
			}
			anterior = actual;
			actual = actual->sig;
		}			
	}	
}

