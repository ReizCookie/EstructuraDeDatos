//INCLUDES
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Estructuras/listadoble/listadoble.h"
#include "alumno.h"
//FUNCION MAIN

int main(void)
{
	ListaD lista;
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
				insertarOrdenadoD(&lista, crearAlumno(nuevo));
				printf("\nAlumno ingresado correctamente");
			
			break;
			}
			case 2:
			{
				int opcMostrar;
					printf("\n---Mostrar Alumnos---\n");
					printf("\n[1] Ascendente");
					printf("\n[2] Descendente");
					printf("\nSelecciona una opcion: ");
					scanf("%d", &opcMostrar);
					while(getchar() != '\n');
					
					switch(opcMostrar)
					{
						case 1:
							printf("\n--- Lista de Alumnos ---");
							mostrarListaD(lista);
							break;
						case 2:
							printf("\n--- Lista de Alumnos ---");
							mostrarListaDDescendente(lista);
							break;
						default:
							printf("\nOpcion invalida");
							break;
					}
				}
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
						
						reordenarD(&lista, &compararMatricula);
						
					break;
					case 2:
					
						reordenarD(&lista, &compararAlumnos);
					
					break;
					case 3:
					
						reordenarD(&lista, &compararSemestre);
					
					break;
					case 4:
					
						reordenarD(&lista, &compararPromedio);
					
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
						
						Alumno* encontrado = (Alumno*) buscarDatoD (lista, &temp);
						
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
					
						
						Alumno* encontrado = (Alumno*) buscarDatoD (lista, &temp);
						
						
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
						
						Alumno* encontrado = (Alumno*) buscarDatoD (lista, &temp);
						
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
						
						Alumno* encontrado = (Alumno*) buscarDatoD (lista, &temp);
						
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
						
						Alumno* encontrado = (Alumno*) buscarDatoD (lista, &temp);
						
						//restauracion
						lista.comparar = compararOriginal;
						
						if (encontrado != NULL){
							printf("Alumno borrado");
							borrarDatoD(&lista,encontrado);
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