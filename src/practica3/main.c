#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../captura/captura.h"
#include "../Estructuras/pila/pila.h"

#define LONGITUD 64

void imprimirCadena(void *a);
void liberarCadena(void *a);

int main(void)
{
    Pila pila;
    inicializarPila(&pila);
	pila.imprimir = imprimirCadena;

    int opc = 0;

    do {
        printf(" MENU\n");
        printf("[1] Palindromo\n");
        printf("[2] Verificacion de parentesis\n");
        printf("[3] Salir\n");
        inputEntero("Elige una opcion ", &opc);

        switch(opc)
        {
            case 1:
            {
                printf("\nVerificacion de palindromo\n");
				ejercicioUno(&pila);
            }
            break;

            case 2:
            {
                printf("\nVerificacion de parentesis\n");
                ejercicioDos(&pila);
            }
            break;

            case 3:
                printf("\nbai pusi\n");
                break;

            default:
                printf("\nOpcion invalida\n");
                break;
        }
    } while(opc != 3);

    return 0;
}


void imprimirCadena(void *a)
{
	char *aa = a;
	printf("%s",aa);
	
}

void liberarCadena(void *a)
{
	char *aa = a;
	free(aa);
}