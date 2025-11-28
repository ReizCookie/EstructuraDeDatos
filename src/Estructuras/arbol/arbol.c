#include "Arbol.h"

// Pone un libro en orden ascendente por titulo
Nodo* insertar_por_titulo(Nodo* raiz, Libro* libro){
    if (libro==NULL){
        return raiz;  // No hace nada si el libro es null
    }
    if (raiz==NULL){
        Nodo* nuevo=(Nodo*)malloc(sizeof(Nodo));
        if (nuevo==NULL){
            fprintf(stderr, "No se pudo asignar memoria :(\n");
            exit(EXIT_FAILURE);
        }
        nuevo->libro = libro;
        nuevo->izq = NULL;
        nuevo->dch = NULL;
        return nuevo;
    }
    
    int comparacion=strcmp(libro->titulo, raiz->libro->titulo);
    if (comparacion<0){
        raiz->izq=insertar_por_titulo(raiz->izq, libro);
    }else if (comparacion>0){
        raiz->dch = insertar_por_titulo(raiz->dch, libro);
    }else{
        // Si los titulos son iguales se ordenan por fechas
        if (libro->fecha<raiz->libro->fecha){
            raiz->izq=insertar_por_titulo(raiz->izq, libro);
        }else{
            raiz->dch=insertar_por_titulo(raiz->dch, libro);
        }
    }
    return raiz;
}

// Pone un libro en el arbol por orden acendente por fecha
Nodo* insertar_por_fecha(Nodo* raiz, Libro* libro){
    if (libro==NULL){
        return NULL;  // No hace nada si el libro es null
    }
    
    if (raiz==NULL){
        Nodo* nuevo=(Nodo*)malloc(sizeof(Nodo));
        if (nuevo==NULL){
            fprintf(stderr, "No se pudo asignar memoria :( \n");
            exit(EXIT_FAILURE);
        }
        nuevo->libro = libro;
        nuevo->izq = NULL;
        nuevo->dch = NULL;
        return nuevo;
    }
    
    if (libro->fecha < raiz->libro->fecha){
        raiz->izq = insertar_por_fecha(raiz->izq, libro);
    }else if (libro->fecha > raiz->libro->fecha){
        raiz->dch = insertar_por_fecha(raiz->dch, libro);
    }
    
    return raiz;
}

// Inserta un libro en el arbol ordenado primero por fecha y luego por titulo
Nodo* insertar_por_fecha_titulo(Nodo* raiz, Libro* libro){
    if (libro == NULL){
        return raiz;  // No hace nada si el libro es null
    }
    if (raiz == NULL){
        Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
        if (nuevo == NULL){
            fprintf(stderr, "No se pudo asignar memoria :(\n");
            exit(EXIT_FAILURE);
        }
        nuevo->libro = libro;
        nuevo->izq = NULL;
        nuevo->dch = NULL;
        return nuevo;
    }
    
    // Primero ordenamos por fecha
    if (libro->fecha < raiz->libro->fecha){
        raiz->izq = insertar_por_fecha_titulo(raiz->izq, libro);
    } else if (libro->fecha > raiz->libro->fecha){
        raiz->dch = insertar_por_fecha_titulo(raiz->dch, libro);
    } else {
        // Si las fechas son iguales, ordenamos por título
        int comparacion = strcmp(libro->titulo, raiz->libro->titulo);
        if (comparacion < 0){
            raiz->izq = insertar_por_fecha_titulo(raiz->izq, libro);
        } else {
            raiz->dch = insertar_por_fecha_titulo(raiz->dch, libro);
        }
    }
    
    return raiz;
}

// Muestra todos los libros del arbol en orden
void mostrar_arbol_inorden(Nodo* raiz){
    if (raiz!=NULL){
        mostrar_arbol_inorden(raiz->izq);
        
        // Verifica que el libro no sea NULL antes de imprimirlo
        if (raiz->libro!=NULL){
            printf("\n ");
            imprimir(*(raiz->libro));
        }
        mostrar_arbol_inorden(raiz->dch);
    }
}

// Inserta un libro en el arbol ordenado por autor y luego por título
Nodo* insertar_por_autor_titulo(Nodo* raiz, Libro* libro){
    if (libro == NULL){
        return raiz;  // No hace nada si el libro es null
    }
    if (raiz == NULL){
        Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
        if (nuevo == NULL){
            fprintf(stderr, "No se pudo asignar memoria :(\n");
            exit(EXIT_FAILURE);
        }
        nuevo->libro = libro;
        nuevo->izq = NULL;
        nuevo->dch = NULL;
        return nuevo;
    }
    
    // Primero ordenamos por autor
    int comparacion=strcmp(libro->autor, raiz->libro->autor);
    if (comparacion<0){
        raiz->izq=insertar_por_autor_titulo(raiz->izq, libro);
    }else if(comparacion > 0){
        raiz->dch=insertar_por_autor_titulo(raiz->dch, libro);
    }else{
        // Si los autores son iguales, ordenamos por título
        int comp_titulo=strcmp(libro->titulo, raiz->libro->titulo);
        if (comp_titulo<0){
            raiz->izq=insertar_por_autor_titulo(raiz->izq, libro);
        }else{
            raiz->dch=insertar_por_autor_titulo(raiz->dch, libro);
        }
    }
    
    return raiz;
}

// Libera memoria de todos los nodos y pone null a la raiz
void liberar_arbol(Nodo** raiz){
    if (raiz==NULL || *raiz==NULL){
        return; // no hace nada si la raiz es null
    }
    
    liberar_arbol(&((*raiz)->izq));
    liberar_arbol(&((*raiz)->dch));

    free(*raiz);
    *raiz = NULL;
}