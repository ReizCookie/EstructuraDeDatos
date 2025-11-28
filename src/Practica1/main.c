//INCLUDES
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Lista.h"
//FUNCION MAIN

typedef struct
{
	unsigned int matricula;
	char nombre[64];
	int semestres;
	float promedio;
}Alumno;


void* crearEntero(int dato);
int compararEnteros(void *a, void *b);
void imprimirEntero(void *a);
void* crearFlotante(float dato);
int compararFlotante(void *a, void *b);
void imprimirFlotante(void *a);

void* crearAlumno( Alumno a);
int compararAlumnos(void *a,void *b);
void imprimirAlumno(void *a);
Alumno capturarAlumno(Lista *lista);
int compararMatricula(void *a, void *b);
int compararSemestre(void *a, void *b);
int compararPromedio(void *a, void *b);

int main(void)
{
	Lista lista;
	lista.inicio = NULL;
	lista.cant = 0;
	lista.comparar = &compararAlumnos;
	lista.imprimir = &imprimirAlumno;
	int opc;
	
	do{
		
		printf("\nMENU\n");
		printf("\n[1] Registrar alumno");
		printf("\n[2] Desplegar alumnos");
		printf("\n[3] Reordenar");
		printf("\n[4] Buscar alumno");
		printf("\n[5] Borrar alumno");
		printf("\n[6] Salir");
		printf("\nSelecciona una opcion: ");
		scanf("%d", &opc);
		while(getchar() != '\n');
		
		switch(opc)
		{
		
			case 1:
			{
				Alumno nuevo = capturarAlumno(&lista);
				insertarOrdenado(&lista, crearAlumno(nuevo));
				printf("\nAlumno ingresado correctamente");
			
			break;
			}
			case 2:
			
				mostrarLista(lista);
			
			break;
			case 3:
			{
				int opcReordenar;
				printf("\n---Reordenar---\n");
				printf("\n[1] Matricula");
				printf("\n[2] Nombre");
				printf("\n[3] Semestres");
				printf("\n[4] Promedio");
				printf("\nSelecciona una opcion: ");
				scanf("%d", &opcReordenar);
				while(getchar() != '\n');
				
				switch(opcReordenar)
				{
					case 1:
						
						reordenar(&lista, &compararMatricula);
						
					break;
					case 2:
					
						reordenar(&lista, &compararAlumnos);
					
					break;
					case 3:
					
						reordenar(&lista, &compararSemestre);
					
					break;
					case 4:
					
						reordenar(&lista, &compararPromedio);
					
					break;
					default:
						
						printf("\nOpcion invalida");
						return 1;
						
					break;
				}
				printf("\nLista reordenada");
			
			break;
			}
			case 4:
			{
				 int opcBuscar;
				printf("\n---Buscar---\n");
				printf("\n[1] Matricula");
				printf("\n[2] Nombre");
				printf("\n[3] Semestres");
				printf("\n[4] Promedio");
				printf("\nSelecciona una opcion: ");
				scanf("%d", &opcBuscar);
				while(getchar() != '\n');
				
				switch(opcBuscar)
				{
					case 1:
					{
						//Se crea la variable de la matricula a buscar
						unsigned int matriculaB;
						printf("Ingresa la matricula a buscar: ");
						scanf("%u", &matriculaB);
						while(getchar() != '\n');
						
						//Creo un alumno temporal al que le ingresaremos solo el dato de matricula
						Alumno temp;
						temp.matricula = matriculaB;
						
						//Cambio temporalmente la funcion de comparar en la lista, se guarda para luego restaurarlo.
						int (*compararOriginal) (void*, void*) = lista.comparar;
						lista.comparar = &compararMatricula;
						
						Alumno* encontrado = (Alumno*) buscarDato (lista, &temp);
						
						//restauracion
						lista.comparar = compararOriginal;
						
						if (encontrado != NULL){
							printf("Alumno encontrado");
							imprimirAlumno (encontrado);
						}
						else
							printf("Alumno no encontrado");
					
						break;
					}
						
					case 2:
					{
					
						Alumno temp;
						printf("Ingresa el nombre a buscar: ");
						fgets (temp.nombre, 64, stdin);
						while(getchar() != '\n');
					
						
						Alumno* encontrado = (Alumno*) buscarDato (lista, &temp);
						
						
						if (encontrado != NULL){
							printf("Alumno encontrado");
							imprimirAlumno (encontrado);
						}
						else
							printf("Alumno no encontrado");	
					
						
					
					break;
					}
					case 3:
					{
						//Se crea la variable de la matricula a buscar
						int semestreB;
						printf("Ingresa el semestre a buscar: ");
						scanf("%d", &semestreB);
						while(getchar() != '\n');
						
						//Creo un alumno temporal al que le ingresaremos solo el dato del smestre
						Alumno temp;
						temp.semestres = semestreB;
						
						//Cambio temporalmente la funcion de comparar en la lista, se guarda para luego restaurarlo.
						int (*compararOriginal) (void*, void*) = lista.comparar;
						lista.comparar = &compararSemestre;
						
						Alumno* encontrado = (Alumno*) buscarDato (lista, &temp);
						
						//restauracion
						lista.comparar = compararOriginal;
						
						if (encontrado != NULL){
							printf("Alumno encontrado");
							imprimirAlumno (encontrado);
						}
						else
							printf("Alumno no encontrado");
					
						break;
					}
				
					case 4:
					{
						//Se crea la variable de el promedio a buscar
						int promedioB;
						printf("Ingresa el promedio a buscar: ");
						scanf("%d", &promedioB);
						while(getchar() != '\n');
						
						//Creo un alumno temporal al que le ingresaremos solo el dato del smestre
						Alumno temp;
						temp.promedio = promedioB;
						
						//Cambio temporalmente la funcion de comparar en la lista, se guarda para luego restaurarlo.
						int (*compararOriginal) (void*, void*) = lista.comparar;
						lista.comparar = &compararPromedio;
						
						Alumno* encontrado = (Alumno*) buscarDato (lista, &temp);
						
						//restauracion
						lista.comparar = compararOriginal;
						
						if (encontrado != NULL){
							printf("Alumno encontrado");
							imprimirAlumno (encontrado);
						}
						else
							printf("Alumno no encontrado");
					
						break;
					}
					default:
						
						printf("\nOpcion invalida");
						return 1;
						
		
				}
			
			break;
			
			case 5:
			{
						//Se crea la variable de la matricula a buscar
						unsigned int matriculaB;
						printf("Ingresa la matricula a buscar: ");
						scanf("%u", &matriculaB);
						while(getchar() != '\n');
						
						//Creo un alumno temporal al que le ingresaremos solo el dato de matricula
						Alumno temp;
						temp.matricula = matriculaB;
						
						//Cambio temporalmente la funcion de comparar en la lista, se guarda para luego restaurarlo.
						int (*compararOriginal) (void*, void*) = lista.comparar;
						lista.comparar = &compararMatricula;
						
						Alumno* encontrado = (Alumno*) buscarDato (lista, &temp);
						
						//restauracion
						lista.comparar = compararOriginal;
						
						if (encontrado != NULL){
							printf("Alumno borrado");
							borrarDato(&lista,encontrado);
						}
						else
							printf("Alumno no encontrado");
					
						break;
					}
			break;
			case 6:
			printf("\nADIOS");
			break;
			default:
			printf("\nOpcion invalida");
			break;
		
		}
		}
		
	}while(opc != 6);
	
	
	return 0;
}


void* crearEntero(int dato)
{
	int *nuevo = malloc(sizeof(int));
	*nuevo = dato;
	return nuevo;
}

int compararEnteros(void *a, void *b)
{
	int *aa, *ab;
	aa = a;
	ab = b;
	if( *aa < *ab )
		return -1;
	else if ( *aa > *ab)
		return 1;
	else
		return 0;	
}

void imprimirEntero(void *a)
{
	int *ea;
	ea = a;
	printf("%d",*ea);
}

void* crearFlotante(float dato)
{
	float *nuevo = malloc(sizeof(float));
	*nuevo = dato;
	return nuevo;
}



int compararFlotante(void *a, void *b)
{
	float *ea,*eb;
	ea = a;
	eb = b;
	if( *ea < *eb )
		return -1;
	else if ( *ea > *eb)
		return 1;
	else
		return 0;	
}


void imprimirFlotante(void *a)
{
	float *ea;
	ea = a;
	printf("%.2f",*ea);
}




void* crearAlumno( Alumno a)
{
	Alumno *nuevo = malloc(sizeof(Alumno));
	*nuevo = a;
	return nuevo;	
}

int compararAlumnos(void *a,void *b)
{
	Alumno *aa,*ab;
	aa = a;
	ab = b;
	return strcmp( aa->nombre,ab->nombre);
}
void imprimirAlumno(void *a)
{
	Alumno *aa;
	aa = a;
	printf("\nNombre: %s | Matricula:  %d | Semestre: %d | Promedio = %f",aa->nombre,aa->matricula,aa->semestres,aa->promedio);
	
}

Alumno capturarAlumno(Lista *lista)
{
	Alumno alumno;
	int matricula;
	
	printf("\nIngresa el nombre del alumno: ");
	fgets(alumno.nombre, sizeof(alumno.nombre), stdin);
	
	printf("\nIngresa el semestre: ");
	scanf("%d", &alumno.semestres);
	
	printf("\nIngresa el promedio: ");
	scanf("%f", &alumno.promedio);
	while(getchar() != '\n');
	
	do{
		matricula = 0;
		printf("\nIngresa la matricula: ");
		scanf("%d", &alumno.matricula);
		while(getchar() != '\n');
		
		Nodo *actual;
		for(actual = lista->inicio; actual != NULL; actual = actual->sig)
		{
			Alumno *a = (Alumno*)actual->dato;
			if(a->matricula == alumno.matricula)
			{
				printf("La matricula ya existe, ingresa otra");
				matricula = 1;
				break;
			}
		}
	}while(matricula);
	
	return alumno;
}

int compararMatricula(void *a, void *b)
{
	Alumno *aa = (Alumno *)a;
	Alumno *ab = (Alumno *)b;
	
	if(aa->matricula < ab->matricula)
		return -1;
	else if(aa ->matricula > ab->matricula)
		return 1;
	else
		return 0;
}

int compararSemestre(void *a, void *b)
{
	Alumno *aa = (Alumno *)a;
	Alumno *ab = (Alumno *)b;
	
	if(aa->semestres < ab->semestres)
		return -1;
	else if(aa ->semestres > ab->semestres)
		return 1;
	else
		return 0;
}

int compararPromedio(void *a, void *b)
{
	Alumno *aa, *ab;
	aa = a;
	ab = b;
	if(aa->promedio < ab->promedio )
		return -1;
	else if (aa->promedio > ab->promedio)
		return 1;
	else
		return 0;	
}