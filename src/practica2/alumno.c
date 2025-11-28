#include "alumno.h"
#include <stdio.h>
#include "../Estructuras/listadoble/listadoble.h"
#include "../Estructuras/nodos/nododoble.h"


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

Alumno capturarAlumno(ListaD *lista)
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
		scanf("%u", &alumno.matricula);
		while(getchar() != '\n');
		
		NodoD *actual;
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