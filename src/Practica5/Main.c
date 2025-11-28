#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../captura/captura.h"
#include "../Estructuras/cola/cola.h"

#define NUMERO_CAJAS 5
#define HABILITADA 1
#define DESHABILITADA 0
#define MIN_ARTICULOS 1
#define MAX_ARTICULOS 50
#define CLIENTES_MAX 20

typedef struct
{
	Cola cola;
	int estado;
}Caja;


int* generar_articulos(void);
void imprimirEntero(void*);

int main(void)
{

	//Cada nodo representa un cliente y en void dato es el total de los articulos

	Caja cajas[NUMERO_CAJAS]; 
	
	for(int i=0; i<NUMERO_CAJAS ; i++) 
	{
		cajas[i].cola = inicializarCola(); //Se inicializa una caja
		cajas[i].cola.imprimir = &imprimirEntero; //Se oone la direccion de esa funcion
		cajas[i].estado = HABILITADA;
		cajas[i].cola.capacidad = CLIENTES_MAX;
	}
	int opcion;	
	do
	{
		for(int i=0; i<NUMERO_CAJAS ; i++)
		{
			printf("\n Caja[%d]: ",i+1);
			imprimirCola(cajas[i].cola);
		}

		opcion = 0;
		printf("\n [1] Generar clientes");
		printf("\n [2] Escanear articulos");
		printf("\n [3] Habilitar caja");
		printf("\n [4] Desahabilitar caja");
		printf("\n [5] Terminar programa");
		inputEntero("\n Selecciona opcion: ",&opcion);
		switch(opcion)
		{
			case 1:
			for(int i=0; i<NUMERO_CAJAS ; i++)
			{
				if(cajas[i].estado && !llenaC(cajas[i].cola))
				{
					enqueue( &cajas[i].cola , generar_articulos() );
				}
			}
			break;

        	case 2:
            for(int i = 0; i < NUMERO_CAJAS; i++) {
      
                if (!vaciaC(cajas[i].cola)) //si la cola no esta vacia
                {
                    escanearArticulo(&cajas[i].cola);
                }

            }
            break;
			break;
			case 3:
			{
					int caja;
					do{
						printf("Que caja quieres habilitar? (1-5):");
						inputEntero("\n Selecciona opcion: ",&caja);

						if(caja > 5 || caja < 1 )
							printf("Caja invalida, por favor seleccione del 1-5");

					}while((caja > 5 || caja < 1 ));
					
					cajas[caja-1].estado = HABILITADA;
			}
			break;
			case 4:
			{
					int caja;
					do{
						printf("Que caja quieres deshabilitar? (1-5):");
						inputEntero("\n Selecciona opcion: ",&caja);

						if(caja > 5 || caja < 1 )
							printf("Caja invalida, por favor seleccione del 1-5");

					}while((caja > 5 || caja < 1 ));
					
					cajas[caja-1].estado = DESHABILITADA;
			}
			break;
			case 5:
					printf("\nAdios");
			break;
			default:
			printf("\n--- OPCION INCORRECTA---");
				
		}	
	}while(opcion!=5);
	
	printf("\n\n FIN DE PROGRAMA");

    for (int i = 0; i < NUMERO_CAJAS; i++)
    {
       
        eliminarCola(&cajas[i].cola);
    }
    
	return 0;
}


int* generar_articulos(void)
{		
	int *articulos = malloc(sizeof(int));
	*articulos = rand() % (MAX_ARTICULOS - MIN_ARTICULOS + 1) + MIN_ARTICULOS;
	return articulos; //devuelve un numero aleatorio que serian los enteros
	
}


void imprimirEntero(void *a)
{
	int *aa=a;
	printf("%d",*aa);
}