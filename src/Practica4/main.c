#include <stdio.h>
#include <stdlib.h>
#include "../Estructuras/pila/pila.h"

#define ARRIBA 1
#define ABAJO 2
#define DERECHA 4
#define IZQUIERDA 8

#define REN 27
#define COL 26

typedef struct{
    int x, y;
}Coordenada;

unsigned char **crear_laberinto(void);
void imprimirLab(unsigned char **lab);
Coordenada* crearCoordenada(int x,int y);
Coordenada* buscarInicio(unsigned char **lab);
int compararCoordenada(void *a, void *b);
void imprimirCoordenada(void *dato);
unsigned char alternativas(unsigned char **lab, Coordenada *coordenada);
void imprimirPosibles(unsigned char);
int adelante(unsigned char posible, Coordenada **nueva);


int main(void){
    Pila pila;
    inicializarPila(&pila);
    pila.imprimir = &imprimirCoordenada;

    unsigned char **lab = crear_laberinto();
    lab[20][7] = 'B';
    imprimirLab(lab);
    printf("\n\n");

    
    Coordenada* inicio = buscarInicio(lab); //Inicio salvado
    Coordenada *coord = crearCoordenada(inicio->x, inicio->y);
    push(&pila, coord); //guardar en pila

    while(lab[coord->x][coord->y] !='B'){ 
        if(adelante(alternativas(lab, coord), &coord)){ //celdas libres al rededor 
            Coordenada *nueva = crearCoordenada(coord->x, coord->y); //se mete esa nueva celda en la pila
            push(&pila, nueva); //mete a pila
            if(lab[coord->x][coord->y] != 'B'){ //si es indifenrente de B
                lab[coord->x][coord->y] = '.'; // se pone migaja
            }
        } else { // aqui si no hay celdas libres al rededor se viene al else
         
            lab[coord->x][coord->y] = 'o'; // Marca el callejón sin salida
            
            free(pop(&pila)); // Saca y libera la coordenada mala o bueno en si no es mala 

            Coordenada* anterior = pop(&pila); // Saca la coordenada buena para actualizar coord ((la cima se actualiza por la funcion))
            //actualizar valores
            coord->x = anterior->x; 
            coord->y = anterior->y;

            
            push(&pila, anterior); //se tiene que regresar a la pila para no perder el camino que tenemos 
           
        }
    }

    imprimirLab(lab);
    printf("\n\n");
    free(inicio); 
    

    return 0;
}

Coordenada* buscarInicio(unsigned char **lab) {
    Coordenada *inicio = malloc(sizeof(Coordenada));

    for (int i = 0; i < REN; i++) {
        for (int j = 0; j < COL; j++) {
            if (lab[i][j] == 'A') {
                inicio->x = i;
                inicio->y = j;
                return inicio; 
            }
        }
    }

    inicio->x = 0;
    inicio->y = 0;
    return inicio;
}

unsigned char **crear_laberinto(void){
    int i,j;
    char *tmp = 
"xxxxxxxxxxxxxxxxxxxxxxxxxx\
xAx*****x****************x\
x*xxx*x*x*xxxxxxxxx*xxxx*x\
x*****x*x******x**x****x*x\
xxxxxxx*xxxxxx*xx*xxxx*xxx\
x*****x*x****x*x****xx***x\
x*xxx*x*xxxx*x*x*xxxxx*x*x\
x***x*x****x*****xxxxxxx*x\
xxx*x*xxxx*xxxxxxx****x**x\
x*x*x***xx****xx***xx*x*xx\
x*x*x*x*xxxxx**x*xxxx*x**x\
x*x*x*x***x*xx*x****x*xx*x\
x*x*x*xxx****x*x*xx*x****x\
x*x*x*xxxxxxxx*x**x*xxxx*x\
x***x********x*xx*x*x****x\
x*xxxxxxxxxx*x**xxx*x*xxxx\
x***x******x**x*****x**x*x\
xxx*x*xxxxxxx*xxxxxxxx*x*x\
x*x*x*******x****xx****x*x\
x*x*x*xxxxx*xxxx*xx*xxxx*x\
x*x*x****xx***x**xx*x****x\
x*x*xxxxxxx*x**x*xx*x*x*xx\
x*x*********xx*x*xx*xxx*xx\
x*xxxxxxxxxxx**x*********x\
x***x***x***x*xxxxxxxxxx*x\
x*x***x***x**************x\
xxxxxxxxxxxxxxxxxxxxxxxxxx\0";

    unsigned char **lab = (unsigned char**) malloc(sizeof(unsigned char *)*REN);
    for(i = 0; i < REN; i++){
        lab[i] = (unsigned char*) malloc(sizeof(unsigned char)*COL);
    }
    for(i = 0; i < REN; i++){
        for(j = 0; j < COL; j++){
            lab[i][j] = tmp[(i*COL)+j];
        }   
    }
    return lab;
}

void imprimirLab(unsigned char **lab){
    for(int i = 0; i < REN; i++){
        printf("\n\r");
        for(int j = 0; j < COL; j++){
            if(lab[i][j] == '*') printf("  ");
            else printf("%c ", lab[i][j]);
        }
    }
}

Coordenada* crearCoordenada(int x,int y){
    Coordenada *nueva = malloc(sizeof(Coordenada));
    nueva->x = x;
    nueva->y = y;
    return nueva;
}

void imprimirCoordenada(void *dato){
    Coordenada *a = dato;
    printf("\n[%-2d,%-2d]", a->x, a->y);
}

int compararCoordenada(void *a, void *b){
    Coordenada *aa = a, *bb = b;
    return (aa->x == bb->x && aa->y == bb->y);
}

unsigned char alternativas(unsigned char **lab, Coordenada *coordenada){
    unsigned char caracter;
    unsigned char banderas = 0;

    caracter = lab[coordenada->x-1][coordenada->y];
    if(caracter!='x' && caracter!='.' && caracter!='o' && caracter!='A')
        banderas |= ARRIBA;

    caracter = lab[coordenada->x+1][coordenada->y];
    if(caracter!='x' && caracter!='.' && caracter!='o' && caracter!='A')
        banderas |= ABAJO;

    caracter = lab[coordenada->x][coordenada->y+1];
    if(caracter!='x' && caracter!='.' &&
         caracter!='o' && caracter!='A')
        banderas |= DERECHA;

    caracter = lab[coordenada->x][coordenada->y-1];
    if(caracter!='x' && caracter!='.' && caracter!='o' && caracter!='A')
        banderas |= IZQUIERDA;

    return banderas;
}



int adelante(unsigned char posible, Coordenada **nueva){
    if(posible & ARRIBA){ //PRIORIDAD
        (*nueva)->x--;
        return 1;
    }
    if(posible & ABAJO){
        (*nueva)->x++;
        return 1;
    }
    if(posible & DERECHA){
        (*nueva)->y++;
        return 1;
    }
    if(posible & IZQUIERDA){
        (*nueva)->y--;
        return 1;
    }

    return 0; 
}

void imprimirPosibles(unsigned char caminos){
    if(caminos & ARRIBA) printf("\nARRIBA");
    if(caminos & ABAJO) printf("\nABAJO");
    if(caminos & IZQUIERDA) printf("\nIZQUIERDA");
    if(caminos & DERECHA) printf("\nDERECHA");
}