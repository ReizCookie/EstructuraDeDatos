#ifndef ALUMNO_H
#define ALUMNO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Estructuras/listadoble/listadoble.h"

// Definición de la estructura Alumno
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
Alumno capturarAlumno(ListaD *lista);
int compararMatricula(void *a, void *b);
int compararSemestre(void *a, void *b);
int compararPromedio(void *a, void *b);

#endif
