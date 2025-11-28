#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Estructuras/arbol/arbol.h"

int* crearEntero(int);
int compararEntero(void*,void*);
void imprimirEntero(void*);
void liberarEntero(void*);
void mostrarMenu();

int main(void)
{
	Arbol arbolA;
	arbolA.raiz = NULL;
	arbolA.cantidad = 0;
	arbolA.imprimir = &imprimirEntero;
	arbolA.comparar = &compararEntero;
	arbolA.liberar = &liberarEntero;
	
	Arbol arbolB;
	arbolB.raiz = NULL;
	arbolB.cantidad = 0;
	arbolB.imprimir = &imprimirEntero;
	arbolB.comparar = &compararEntero;
	arbolB.liberar = &liberarEntero;
	
	int opcion, valor;
	
	do
	{
		mostrarMenu();
		scanf("%d", &opcion);
		
		switch(opcion)
		{
			case 1:
				printf("Ingrese el valor a insertar en Arbol A: ");
				scanf("%d", &valor);
				insertarArbol(&arbolA, crearEntero(valor));
				printf("Valor %d insertado correctamente en Arbol A.\n", valor);
				break;
				
			case 2:
				printf("Ingrese el valor a insertar en Arbol B: ");
				scanf("%d", &valor);
				insertarArbol(&arbolB, crearEntero(valor));
				printf("Valor %d insertado correctamente en Arbol B.\n", valor);
				break;
				
			case 3:
				printf("\n===== COMPARACION DE ARBOLES =====\n");
				if (sonIgualesEstructura(arbolA.raiz, arbolB.raiz))
				{
					printf("Los arboles son iguales en estructura y datos.\n");
				}
				else if (tienenMismosDatos(arbolA.raiz, arbolB.raiz))
				{
					printf("Los arboles tienen los mismos datos pero diferente estructura.\n");
				}
				else
				{
					printf("Los arboles son diferentes.\n");
				}
				break;
				
			case 4:
				printf("Ingrese el valor a eliminar del Arbol A: ");
				scanf("%d", &valor);
				if (eliminarArbol(&arbolA, valor))
					printf("Valor %d eliminado correctamente del Arbol A.\n", valor);
				else
					printf("Valor %d no encontrado en el Arbol A.\n", valor);
				break;
				
			case 5:
				printf("Ingrese el valor a eliminar del Arbol B: ");
				scanf("%d", &valor);
				if (eliminarArbol(&arbolB, valor))
					printf("Valor %d eliminado correctamente del Arbol B.\n", valor);
				else
					printf("Valor %d no encontrado en el Arbol B.\n", valor);
				break;
				
			case 6:
				printf("\nProfundidades: \n");
				printf("Profundidad del Arbol A: %d\n", calcularAltura(arbolA.raiz));
				printf("Profundidad del Arbol B: %d\n", calcularAltura(arbolB.raiz));
				break;
				
			case 7:
				equilibrarArbol(&arbolA);
				equilibrarArbol(&arbolB);
				printf("\nNueva altura Arbol A: %d\n", calcularAltura(arbolA.raiz));
				printf("Nueva altura Arbol B: %d\n", calcularAltura(arbolB.raiz));
				break;
				
			case 8:
				printf("\nARBOL A\n");
				if (arbolA.raiz)
				{
					printf("Cantidad de nodos: %d\n", arbolA.cantidad);
					printf("Estructura del arbol:\n");
					imprimirArbol(arbolA);
				}
				else
					printf("El Arbol A esta vacio.\n");
				
				printf("\nARBOL B\n");
				if (arbolB.raiz)
				{
					printf("Cantidad de nodos: %d\n", arbolB.cantidad);
					printf("Estructura del arbol:\n");
					imprimirArbol(arbolB);
				}
				else
					printf("El Arbol B esta vacio.\n");
				break;
				
			case 9:
				printf("\nbai\n");
				liberarArbol(&arbolA);
				liberarArbol(&arbolB);
				printf("\nFIN DE PROGRAMA\n");
				break;
				
			default:
				printf("Opcion invalida\n");
		}
		
	} while(opcion != 9);
	
	return 0;
}

void mostrarMenu()
{
    printf("=======================================");
	printf("\n     Menusote   \n");
	printf("1. Insertar en Arbol A\n");
	printf("2. Insertar en Arbol B\n");
	printf("3. Comparar Arboles\n");
	printf("4. Eliminar dato en Arbol A\n");
	printf("5. Eliminar dato en Arbol B\n");
	printf("6. Profundidades\n");
	printf("7. Equilibrar arboles\n");
	printf("8. Mostrar arboles\n");
	printf("9. Terminar programa\n");
	printf("Seleccione una opcion: ");
}

int* crearEntero(int dato)
{
	int *nuevo = malloc(sizeof(int));
	*nuevo = dato;
	return nuevo;
}

int compararEntero(void*a, void*b)
{
	int *aa = a, *bb = b;
	if(*aa == *bb) return 0;
	else if(*aa < *bb) return -1;
	else return 1;
}

void imprimirEntero(void *a)
{
	int *aa = a;
	printf("%d", *aa);
}

void liberarEntero(void *a)
{
	free(a);
}