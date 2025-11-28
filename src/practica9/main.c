#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../captura/captura.h"
#include "../Estructuras/heap/heap.h"

typedef struct {
    char *nombre;
    int paginas;
} Archivo;

// Prototipos
int compararArchivo(void*, void*);
void imprimirArchivo(void*);
void liberarArchivo(void*);
void mostrarMenu();
void mostrarTop5(Heap heap);
void mostrarEstadoHeap(Heap heap, const char *momento);
void cambiarPrioridad(Heap *heap);
void agregarArchivo(Heap *heap);
void procesarArchivo(Heap *heap);
void eliminarArchivoEspecifico(Heap *heap);
void eliminarTodosArchivos(Heap *heap);

int main(void) {
    Heap heap = inicializarHeap(&imprimirArchivo, &compararArchivo);
    heap.tipo = MIN; // e e ee e e e 
    int opcion;
    
    do {
        printf("\n");
        printf("=================================================\n");
        printf("         Cafe Internet e Impresiones el tilin\n");
        printf("=================================================\n");
        mostrarTop5(heap);
        printf("\n");
        mostrarMenu();
        
        if(inputEntero("\nSeleccione una opcion: ", &opcion) != 1) {
            printf("\nEntrada invalida. Intente de nuevo.\n");
            continue;
        }
        
        switch(opcion) {
            case 0:
                cambiarPrioridad(&heap);
                break;
            case 1:
                mostrarEstadoHeap(heap, "");
                break;
            case 2:
                agregarArchivo(&heap);
                break;
            case 3:
                procesarArchivo(&heap);
                break;
            case 4:
                eliminarArchivoEspecifico(&heap);
                break;
            case 5:
                eliminarTodosArchivos(&heap);
                break;
            case 6:
                printf("\nTerminando programa...\n");
                eliminarTodosArchivos(&heap);
                break;
            default:
                printf("\nOpcion invalida. Intente de nuevo.\n");
        }
        
    } while(opcion != 6);
    
    return 0;
}

void mostrarMenu() {
    printf("\n-------------------------------------------------\n");
    printf(" [0] Cambiar prioridad\n");
    printf(" [1] Mostrar cola de impresion\n");
    printf(" [2] Agregar archivo\n");
    printf(" [3] Imprimir archivo\n");
    printf(" [4] Eliminar archivo\n");
    printf(" [5] Eliminar todos los archivos\n");
    printf(" [6] Terminar el programa\n");
    printf("-------------------------------------------------\n");
}

//Funcion para mostrar los 5 primeros archivos en el heap
void mostrarTop5(Heap heap) {
    printf("Prioridad: %s\n", heap.tipo == MIN ? "MINIMO" : "MAXIMO");
    
    if(heap.cantidad == 0) {
        printf("  (x.x)\n");
        return;
    }
    
    int limite = heap.cantidad < 5 ? heap.cantidad : 5;
    for(int i = 0; i < limite; i++) {
        Archivo *arch = (Archivo*)heap.arr[i]->dato;
        printf("  %d. %s (%d pags)\n", i+1, arch->nombre, arch->paginas);
    }
}

void mostrarEstadoHeap(Heap heap, const char *momento) {
    if(strlen(momento) > 0) {
        printf("\n=== %s ===\n", momento);
    }
    
    printf("\n--- Heap como arreglo ---\n");
    if(heap.cantidad == 0) {
        printf("(vacio)\n");
    } else {
        printf("[ ");
        imprimirHeap(heap);
        printf(" ]\n");
    }
    
    printf("\n--- Heap como arbol ---\n");
    if(heap.cantidad == 0) {
        printf("(vacio)\n");
    } else {
        imprimirArbol(heap.arbol);
        printf("\n");
    }
}

void cambiarPrioridad(Heap *heap) {
    mostrarEstadoHeap(*heap, "ANTES");
    
    if(heap->tipo == MIN) {
        heap->tipo = MAX;
    } else {
        heap->tipo = MIN;
    }
    
    heapify(heap);
    mostrarEstadoHeap(*heap, "DESPUES");
}

void agregarArchivo(Heap *heap) {
    mostrarEstadoHeap(*heap, "ANTES");
    
    Archivo *nuevo = (Archivo*)malloc(sizeof(Archivo));
    if(!nuevo) {
        printf("\nError al asignar memoria yiyi.\n");
        return;
    }
    
    char nombre[100];
    if(inputCadena("Nombre del archivo: ", nombre, 100) != 1) {
        free(nuevo);
        printf("\nError al capturar nombre.\n");
        return;
    }
    
    int paginas;
    if(inputEntero("Numero de paginas: ", &paginas) != 1 || paginas <= 0) {
        free(nuevo);
        printf("\nNumero de paginas invalido baboso.\n");
        return;
    }
    
    nuevo->nombre = cadenaDinamica(nombre);
    nuevo->paginas = paginas;
    
    insertarHeap(heap, nuevo);
    mostrarEstadoHeap(*heap, "DESPUES");
}

void procesarArchivo(Heap *heap) {
    mostrarEstadoHeap(*heap, "ANTES");
    
    if(heap->cantidad == 0) {
        printf("\nNo hay archivos.\n");
        return;
    }
    
    Archivo *arch = (Archivo*)quitarHeap(heap);
    if(arch) {
        printf("\n>>> Archivo enviado a la impresora >>>");
        liberarArchivo(arch);
    }
    
    mostrarEstadoHeap(*heap, "DESPUES");
}

void eliminarArchivoEspecifico(Heap *heap) {
    
    if(heap->cantidad == 0) {
        printf("\nNo hay archivos\n");
        return;
    }
    
    printf("\nArchivos en cola:\n");
    for(int i = 0; i < heap->cantidad; i++) {
        Archivo *arch = (Archivo*)heap->arr[i]->dato;
        printf("  [%d] %s (%d pags)\n", i, arch->nombre, arch->paginas);
    }
    
    int indice;
    if(inputEntero("\nIndice del archivo a eliminar: ", &indice) != 1) {
        printf("\nEntrada invalida.\n");
        return;
    }
    
    if(indice < 0 || indice >= heap->cantidad) {
        printf("\nIndice fuera de rango.\n");
        return;
    }
    
    mostrarEstadoHeap(*heap, "ANTES");
    
    Archivo *arch = (Archivo*)heap->arr[indice]->dato;

    liberarArchivo(arch);
    free(heap->arr[indice]);
    
    // Mover el ultimo a posicion elimianda
    heap->arr[indice] = heap->arr[heap->cantidad - 1];
    heap->cantidad--;
    
    // Reajustar memoria y rehacer heap
    if(heap->cantidad > 0) {
        heap->arr = realloc(heap->arr, sizeof(NodoA*) * heap->cantidad);
        heapify(heap);
    } else {
        free(heap->arr);
        heap->arr = NULL;
    }
    
    mostrarEstadoHeap(*heap, "DESPUES");
}

void eliminarTodosArchivos(Heap *heap) {
    mostrarEstadoHeap(*heap, "ANTES");
    
    if(heap->cantidad == 0) {
        printf("\nLa cola ya esta vacia.\n");
        return;
    }
    
    // Liberar todos los archivos
    for(int i = 0; i < heap->cantidad; i++) {
        Archivo *arch = (Archivo*)heap->arr[i]->dato;
        liberarArchivo(arch);
        free(heap->arr[i]);
    }
    
    free(heap->arr);
    heap->arr = NULL;
    heap->cantidad = 0;
    heap->arbol.raiz = NULL;
    heap->arbol.cantidad = 0;

    mostrarEstadoHeap(*heap, "DESPUES");
}

int compararArchivo(void *a, void *b) {
    Archivo *aa = (Archivo*)a;
    Archivo *bb = (Archivo*)b;
    
    if(aa->paginas == bb->paginas) return 0;
    else if(aa->paginas < bb->paginas) return -1;
    else return 1;
}

void imprimirArchivo(void *a) {
    Archivo *arch = (Archivo*)a;
    printf("%s(%d)", arch->nombre, arch->paginas);
}

void liberarArchivo(void *a) {
    Archivo *arch = (Archivo*)a;
    if(arch) {
        if(arch->nombre) free(arch->nombre);
        free(arch);
    }
}