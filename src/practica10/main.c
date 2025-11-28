#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../Estructuras/hash/hashtable.h"
#include "../Estructuras/arbol/arbol.h"
#include "Libro.h"
#include "../Estructuras/cola/cola.h" 

HashTable ht_isbn, ht_titulo, ht_autor, ht_anio, ht_ini_tit, ht_ini_aut;

void limpiarBuffer();
void funcionQueDefinitivamenteSiLibera(void *dato);

int folding_isbn(void *dato);
int cmp_isbn(void *a, void *b);

int folding_titulo(void *dato);
int cmp_titulo(void *a, void *b);

int folding_autor(void *dato);
int cmp_autor(void *a, void *b);

int folding_anio(void *dato);
int cmp_anio(void *a, void *b);

int folding_inicial_titulo(void *dato);
int cmp_inicial_titulo(void *a, void *b);

int folding_inicial_autor(void *dato);
int cmp_inicial_autor(void *a, void *b);

int comparar_para_arbol_titulo(void *a, void *b);
int comparar_para_arbol_autor(void *a, void *b);
int comparar_para_arbol_anio(void *a, void *b);

void inicializar_sistema();
void agregar_libro_a_tablas(Libro *l);
void eliminar_libro_de_tablas(Libro *l);
void liberar_libro_memoria(Libro *l);
void mostrar_resultados_cola(Cola *c, int criterio);
void ingresar_nuevo_libro();

// Enum para los criterios de ordenamiento
enum {
    ORDENAR_POR_TITULO = 1,
    ORDENAR_POR_AUTOR = 2,
    ORDENAR_POR_ANIO = 3
};



int main(void)
{
    inicializar_sistema();

    Libro *libros = obtener_libros();
    for(int i = 0; i < CANT_LIBROS; i++) {
        agregar_libro_a_tablas(&libros[i]);
    }

    int opc, subopc;
    Libro libroAuxiliar; 
    Cola resultados;

    do {
        printf("\n\n---Biblioteca el Tilin---\n\n");
        printf("\n1. Buscar por ISBN");
        printf("\n2. Buscar por TITULO");
        printf("\n3. Buscar por AUTOR");
        printf("\n4. Buscar por FECHA");
        printf("\n5. AGREGAR Libro Nuevo");
        printf("\n6. ELIMINAR Libro");
        printf("\n7. Salir");
        printf("\nSelecciona: ");
        scanf("%d", &opc); limpiarBuffer();

        switch(opc) {
            case 1:
                printf("Ingrese ISBN a buscar: ");
                fgets(libroAuxiliar.isbn, MAX_ISBN, stdin);
                libroAuxiliar.isbn[strcspn(libroAuxiliar.isbn, "\n")] = 0; 
                
                resultados = buscarClave(&ht_isbn, &libroAuxiliar);
                mostrar_resultados_cola(&resultados, ORDENAR_POR_TITULO);
                break;

            case 2: 
                printf("\n1. Titulo Exacto\n2. Rango de Iniciales\nSelecciona: ");
                scanf("%d", &subopc); limpiarBuffer();
                if(subopc == 1) {
                    printf("Ingrese Titulo: ");
                    fgets(libroAuxiliar.titulo, MAX_TITULO, stdin);
                    libroAuxiliar.titulo[strcspn(libroAuxiliar.titulo, "\n")] = 0;
                    
                    resultados = buscarClave(&ht_titulo, &libroAuxiliar);
                    mostrar_resultados_cola(&resultados, ORDENAR_POR_TITULO);
                } else {
                    char ini, fin;
                    printf("Inicial Inicio (A-Z): "); scanf("%c", &ini); limpiarBuffer();
                    printf("Inicial Fin (A-Z): "); scanf("%c", &fin); limpiarBuffer();
                    
                    Cola acumulada = inicializarCola();
                    for(char c = toupper(ini); c <= toupper(fin); c++) {
                        libroAuxiliar.titulo[0] = c; libroAuxiliar.titulo[1] = '\0';
                        Cola parcial = buscarClave(&ht_ini_tit, &libroAuxiliar);
                        
                        while(!vaciaC(parcial)) {
                             enqueue(&acumulada, dequeue(&parcial));
                        }
                    }
                    mostrar_resultados_cola(&acumulada, ORDENAR_POR_TITULO);
                }
                break;

            case 3: 
                printf("\n1. Nombre Exacto\n2. Rango de Iniciales\nSeleccionar: ");
                scanf("%d", &subopc); limpiarBuffer();
                if(subopc == 1) {
                    printf("Ingrese Autor: ");
                    fgets(libroAuxiliar.autor, MAX_AUTOR, stdin);
                    libroAuxiliar.autor[strcspn(libroAuxiliar.autor, "\n")] = 0;
                    
                    resultados = buscarClave(&ht_autor, &libroAuxiliar);
                    mostrar_resultados_cola(&resultados, ORDENAR_POR_AUTOR);
                } else {
                    char ini, fin;
                    printf("Inicial Inicio (A-Z): "); scanf("%c", &ini); limpiarBuffer();
                    printf("Inicial Fin (A-Z): "); scanf("%c", &fin); limpiarBuffer();
                    
                    Cola acumulada = inicializarCola();
                    for(char c = toupper(ini); c <= toupper(fin); c++) {
                        libroAuxiliar.autor[0] = c; libroAuxiliar.autor[1] = '\0';
                        Cola parcial = buscarClave(&ht_ini_aut, &libroAuxiliar);
                        
                        while(!vaciaC(parcial)) {
                            enqueue(&acumulada, dequeue(&parcial));
                        }
                    }
                    mostrar_resultados_cola(&acumulada, ORDENAR_POR_AUTOR);
                }
                break;

            case 4: 
                printf("\n1. Anio Exacto\n2. Rango de Anios\nSeleccionar: ");
                scanf("%d", &subopc); limpiarBuffer();
                if(subopc == 1) {
                    printf("Ingrese Anioo: ");
                    scanf("%d", &libroAuxiliar.fecha); limpiarBuffer();
                    
                    resultados = buscarClave(&ht_anio, &libroAuxiliar);
                    mostrar_resultados_cola(&resultados, ORDENAR_POR_ANIO);
                } else {
                    int ini, fin;
                    printf("Anio Inicio: "); scanf("%d", &ini);
                    printf("Anio Fin: "); scanf("%d", &fin); limpiarBuffer();
                    
                    Cola acumulada = inicializarCola();
                    for(int y = ini; y <= fin; y++) {
                        libroAuxiliar.fecha = y;
                        Cola parcial = buscarClave(&ht_anio, &libroAuxiliar);
                        
                        while(!vaciaC(parcial)) {
                            enqueue(&acumulada, dequeue(&parcial));
                        }
                    }
                    mostrar_resultados_cola(&acumulada, ORDENAR_POR_ANIO);
                }
                break;
            
            case 5:
                ingresar_nuevo_libro();
                break;
            
            case 6: 
                printf("Ingrese ISBN del libro a eliminar: ");
                fgets(libroAuxiliar.isbn, MAX_ISBN, stdin);
                libroAuxiliar.isbn[strcspn(libroAuxiliar.isbn, "\n")] = 0;

                resultados = buscarClave(&ht_isbn, &libroAuxiliar);
                
                if(vaciaC(resultados)) {
                    printf("Error: Libro no encontrado.\n");
                } else {
                    Libro *libroReal = (Libro*)dequeue(&resultados);
                    printf("Eliminando libro: '%s' por %s\n", libroReal->titulo, libroReal->autor);
                    eliminar_libro_de_tablas(libroReal);
                    liberar_libro_memoria(libroReal);
                    printf("Libro eliminado exitosamente.\n");
                }
                break;
        }

    } while(opc != 7);
    return 0;
}

// ============ IMPLEMENTACIONES DE FUNCIONES ============

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void funcionQueDefinitivamenteSiLibera(void *dato) {
}

// Comparador para ordenar por TITULO
int comparar_para_arbol_titulo(void *a, void *b) {
    Libro *l1 = (Libro*)a;
    Libro *l2 = (Libro*)b;
    return strcmp(l1->titulo, l2->titulo); 
}

// Comparador para ordenar por AUTOR
int comparar_para_arbol_autor(void *a, void *b) {
    Libro *l1 = (Libro*)a;
    Libro *l2 = (Libro*)b;
    return strcmp(l1->autor, l2->autor); 
}

// Comparador para ordenar por AÑO
int comparar_para_arbol_anio(void *a, void *b) {
    Libro *l1 = (Libro*)a;
    Libro *l2 = (Libro*)b;
    return l1->fecha - l2->fecha; 
}

int folding_isbn(void *dato) {
    Libro *l = (Libro*)dato;
    int suma = 0;
    char *str = l->isbn;
    while(*str) {
        if(isdigit(*str)) suma += (*str - '0'); 
        str++;
    }
    return suma;
}

int cmp_isbn(void *a, void *b) {
    Libro *l1 = (Libro*)a;
    Libro *l2 = (Libro*)b;
    return strcmp(l1->isbn, l2->isbn);
}

int folding_titulo(void *dato) {
    Libro *l = (Libro*)dato;
    int suma = 0;
    char *str = l->titulo;
    for(int i=0; str[i]; i++) suma += (int)str[i];
    return suma;
}

int cmp_titulo(void *a, void *b) {
    Libro *l1 = (Libro*)a;
    Libro *l2 = (Libro*)b;
    return strcmp(l1->titulo, l2->titulo);
}

int folding_autor(void *dato) {
    Libro *l = (Libro*)dato;
    int suma = 0;
    char *str = l->autor;
    for(int i=0; str[i]; i++) suma += (int)str[i];
    return suma;
}

int cmp_autor(void *a, void *b) {
    Libro *l1 = (Libro*)a;
    Libro *l2 = (Libro*)b;
    return strcmp(l1->autor, l2->autor);
}

int folding_anio(void *dato) {
    Libro *l = (Libro*)dato;
    return l->fecha;
}

int cmp_anio(void *a, void *b) {
    Libro *l1 = (Libro*)a;
    Libro *l2 = (Libro*)b;
    return l1->fecha - l2->fecha;
}

int folding_inicial_titulo(void *dato) {
    Libro *l = (Libro*)dato;
    return (int)toupper(l->titulo[0]);
}

int cmp_inicial_titulo(void *a, void *b) {
    Libro *l1 = (Libro*)a;
    Libro *l2 = (Libro*)b;
    return toupper(l1->titulo[0]) - toupper(l2->titulo[0]);
}

int folding_inicial_autor(void *dato) {
    Libro *l = (Libro*)dato;
    return (int)toupper(l->autor[0]);
}

int cmp_inicial_autor(void *a, void *b) {
    Libro *l1 = (Libro*)a;
    Libro *l2 = (Libro*)b;
    return toupper(l1->autor[0]) - toupper(l2->autor[0]);
}

void inicializar_sistema() {
    int tam = 13; 
    ht_isbn = inicializarHashTable(tam, folding_isbn, imprimirLibro, cmp_isbn);
    ht_titulo = inicializarHashTable(tam, folding_titulo, imprimirLibro, cmp_titulo);
    ht_autor = inicializarHashTable(tam, folding_autor, imprimirLibro, cmp_autor);
    ht_anio = inicializarHashTable(tam, folding_anio, imprimirLibro, cmp_anio);
    ht_ini_tit = inicializarHashTable(tam, folding_inicial_titulo, imprimirLibro, cmp_inicial_titulo);
    ht_ini_aut = inicializarHashTable(tam, folding_inicial_autor, imprimirLibro, cmp_inicial_autor);
}

void agregar_libro_a_tablas(Libro *l) {
    insertarClave(&ht_isbn, l);
    insertarClave(&ht_titulo, l);
    insertarClave(&ht_autor, l);
    insertarClave(&ht_anio, l);
    insertarClave(&ht_ini_tit, l);
    insertarClave(&ht_ini_aut, l);
}

void eliminar_libro_de_tablas(Libro *l) {
    eliminarClave(&ht_isbn, l);
    eliminarClave(&ht_titulo, l);
    eliminarClave(&ht_autor, l);
    eliminarClave(&ht_anio, l);
    eliminarClave(&ht_ini_tit, l);
    eliminarClave(&ht_ini_aut, l);
}

void liberar_libro_memoria(Libro *l) {
    // Solo liberar si el libro NO está en el array estático original
    Libro *libros = obtener_libros();
    
    // Verificar si el libro está fuera del rango del array estático
    if (l < libros || l >= libros + CANT_LIBROS) {
        // Es un libro agregado dinámicamente, podemos liberarlo
        free(l);
    }
    // Si está dentro del array estático, no hacemos nada (no se puede liberar)
}

void mostrar_resultados_cola(Cola *c, int criterio) {
    if(vaciaC(*c)) { 
        printf(" No se encontraron resultados.\n");
        return;
    }

    Arbol arbolOrdenador;
    arbolOrdenador.raiz = NULL;
    arbolOrdenador.cantidad = 0;
    
    // Seleccionar el comparador según el criterio
    switch(criterio) {
        case ORDENAR_POR_TITULO:
            arbolOrdenador.comparar = comparar_para_arbol_titulo;
            break;
        case ORDENAR_POR_AUTOR:
            arbolOrdenador.comparar = comparar_para_arbol_autor;
            break;
        case ORDENAR_POR_ANIO:
            arbolOrdenador.comparar = comparar_para_arbol_anio;
            break;
        default:
            arbolOrdenador.comparar = comparar_para_arbol_titulo;
    }
    
    arbolOrdenador.liberar = funcionQueDefinitivamenteSiLibera; 
    arbolOrdenador.imprimir = imprimirLibro;  // Imprimir directamente

    // Insertar todos los libros en el árbol
    while(!vaciaC(*c)) {
        insertarArbol(&arbolOrdenador, dequeue(c));
    }

    // Imprimir encabezado y resultados
    printf("\n--- RESULTADOS ORDENADOS (Total: %d) ---\n", arbolOrdenador.cantidad);
    printf("%-18s  %-41s  %-25s  %s  %s\n", "ISBN", "TITULO", "AUTOR", "ANIO", "ESTADO");
    
    // Imprimir directamente desde el árbol en orden
    imprimirOrden(arbolOrdenador, ORDEN);
    
    liberarArbol(&arbolOrdenador);
}

void ingresar_nuevo_libro() {
    // Reservar memoria dinámica para el nuevo libro
    Libro *nuevoLibro = (Libro*)malloc(sizeof(Libro));
    
    if(nuevoLibro == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo libro.\n");
        return;
    }
    
    printf("\n=== AGREGAR NUEVO LIBRO ===\n");
    
    // Ingresar ISBN
    printf("Ingrese ISBN (ej: 978-X-XX-XXXXXX-X): ");
    fgets(nuevoLibro->isbn, MAX_ISBN, stdin);
    nuevoLibro->isbn[strcspn(nuevoLibro->isbn, "\n")] = 0;
    
    // Verificar si el ISBN ya existe
    Libro libroTemp;
    strcpy(libroTemp.isbn, nuevoLibro->isbn);
    Cola verificacion = buscarClave(&ht_isbn, &libroTemp);
    
    if(!vaciaC(verificacion)) {
        printf("Error: Ya existe un libro con ese ISBN.\n");
        free(nuevoLibro);
        return;
    }
    
    // Ingresar Título
    printf("Ingrese Titulo: ");
    fgets(nuevoLibro->titulo, MAX_TITULO, stdin);
    nuevoLibro->titulo[strcspn(nuevoLibro->titulo, "\n")] = 0;
    
    // Ingresar Autor
    printf("Ingrese Autor: ");
    fgets(nuevoLibro->autor, MAX_AUTOR, stdin);
    nuevoLibro->autor[strcspn(nuevoLibro->autor, "\n")] = 0;
    
    // Ingresar Año
    printf("Ingrese Anio de publicacion: ");
    scanf("%d", &nuevoLibro->fecha);
    limpiarBuffer();
    
    // Ingresar Disponibilidad
    int disponible;
    printf("Esta disponible? (1=SI, 0=NO): ");
    scanf("%d", &disponible);
    limpiarBuffer();
    nuevoLibro->disponible = disponible;
    
    // Agregar a todas las tablas hash
    agregar_libro_a_tablas(nuevoLibro);
    
    printf("\n*** Libro agregado exitosamente ***\n");
    printf("\nDatos ingresados:\n");
    printf("%-18s  %-41s  %-25s  %s  %s\n", "ISBN", "TITULO", "AUTOR", "ANIO", "ESTADO");
    imprimirLibro(nuevoLibro);
}