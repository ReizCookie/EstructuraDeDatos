#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> //pow()
#include "../captura/captura.h"
#include "../Estructuras/pila/pila.h"
#include "../Estructuras/cola/cola.h"
#include "../Estructuras/arbol/arbol.h"

typedef struct
{
    char caracter;
    float *valor;
} Dato;

void** ejercicio(Pila *pila);
void postfixCola(void** datos, Cola* cola);
void postfixArbol(Cola* cola, Arbol* arbol, Pila *pila);
int esOperador(char caracter);
void imprimirDatoArbol(void *dato);
void liberarDato(void *dato); 
void capturarValores(NodoA* raiz, char letras[], float valores[], int *n);
float evaluarArbol(NodoA* raiz);
float realizarCalculo(float a, float b, char op);
Dato* crearDato(char caracter);

int main(void){

    Pila pila;
    inicializarPila(&pila); 
    Cola cola = inicializarCola();
    Arbol arbol;

    arbol.raiz = NULL;
    arbol.cantidad = 0;
    arbol.imprimir = imprimirDatoArbol; 
    arbol.comparar = NULL; 
    arbol.liberar = liberarDato; 

    int opc = 0;
    do {
        printf("\nMenusote\n");
        printf("1. Capturar expresion\n");
        printf("2. Imprimir arbol de expresion\n");
        printf("3. Evaluar expresion\n");
        printf("4. Terminar programa\n");
        printf("Ingresa una opciion: ");
        scanf("%d", &opc);
        while(getchar() != '\n'); // Limpiar buffer de entrada

        switch(opc){
            case 1:
            {
                // Reiniciar estructuras por si se usa de nuevo
                eliminarPila(&pila);
                inicializarPila(&pila);
                eliminarCola(&cola);
                cola = inicializarCola();
                eliminarArbol(&arbol); // Libera el árbol anterior

                // Inicializar el arbol de nuevo
                arbol.raiz = NULL;
                arbol.cantidad = 0;
                arbol.imprimir = imprimirDatoArbol;
                arbol.comparar = NULL;
                arbol.liberar = liberarDato; 

                void **postfix = ejercicio(&pila);
                
                if (postfix != NULL) {
                    printf("Postfix: ");
                    for(int i=0; postfix[i] != NULL; i++) {
                        printf("%c ", ((Dato*)postfix[i])->caracter);
                    }
                    printf("\n");

                    postfixCola(postfix, &cola);
                    postfixArbol(&cola, &arbol, &pila);
                    printf("Arbol construido.\n");
                    
                    free(postfix); // El arreglo de punteros ya no se necesita
                }
                break;
            }
            case 2:
                imprimirArbol(arbol);
    
                break;
            case 3:
            {
                char letras[50];
                float valores[50];
                int n = 0;

                capturarValores(arbol.raiz, letras, valores, &n);

                    float resultado = evaluarArbol(arbol.raiz);
                printf("Resultado: %.2f\n", resultado);
            }
                break;
            case 4:
                printf("Adios\n");
                break;
            default:
                printf("Opcion incorrecta\n");
                break;
        }
    } while(opc != 4);

    // Limpieza final
    eliminarPila(&pila);
    eliminarCola(&cola);
    eliminarArbol(&arbol); // Esto usa liberarDato para limpiar todo
    
    return 0;
}


Dato* crearDato(char caracter){
    Dato *nuevo = (Dato*)calloc(1, sizeof(Dato));
    if (nuevo) {
        nuevo->caracter = caracter;
        nuevo->valor = NULL;
    }
    return nuevo;
}


void imprimirDatoArbol(void *dato) {
    Dato *info = (Dato*)dato;
    if (info) {
        printf("%c", info->caracter);
    }
}

void liberarDato(void *dato) {
    if (dato) {
        Dato *info = (Dato*)dato;
        if (info->valor) {
            free(info->valor); // Libera el float*
        }
        free(info); // Libera la struct Dato
    }
}

void** ejercicio(Pila *pila){
    void** salida = calloc(50, sizeof(void*)); 
    char mensaje[50];
    
    inputCadena("Que ecuacion quieres ingresar: ", mensaje, 50);

    int i = 0;
    int pos = 0;
    while(mensaje[i] != '\0'){
        char a = mensaje[i];

        if((a >= 'A' && a<= 'Z') || (a >= 'a' && a<= 'z')){
            salida[pos++] = crearDato(a); //Se crea el dato y se guarda en el arreglo
        } else if(a == '('){
            Dato* dato_parentesis = crearDato(a);
            Nodo *nuevo = crearNodo(dato_parentesis);  //pila usa nodo no nodoA s
            push_nodo(pila, nuevo);
        } else if(esOperador(a)){
            while(!vacia(*pila) && ((Dato*)peek_nodo(*pila))->caracter != '(' &&
                  prioridad(((Dato*)peek_nodo(*pila))->caracter) >= prioridad(a)){ //lo mismo usando dato
                Nodo *sacado = pop_nodo(pila);
                salida[pos++] = (Dato*)sacado->dato; //casteo
                free(sacado); //free del nodo
            }
            Dato* dato_operador = crearDato(a); //crea dato operador
            Nodo *nuevo = crearNodo(dato_operador); //se crea nodo para la pila
            push_nodo(pila, nuevo); 
        } else if(a == ')'){
            while(!vacia(*pila) && ((Dato*)peek_nodo(*pila))->caracter != '('){
                Nodo *sacado = pop_nodo(pila); 
                salida[pos++] = (Dato*)sacado->dato; 
                free(sacado); //free del nodo
            }
            if(vacia(*pila)){
                printf("Expresion invalida () invalidos\n");
                for(int j = 0; j < pos; j++) liberarDato(salida[j]); //libera los datos
                free(salida); //free arreglo
                eliminarPila(pila); //libera pila
                return NULL;
            }
            //Aqui si quedo el (
            Nodo *sacado = pop_nodo(pila); // Saca el '('
            liberarDato(sacado->dato); //libera el Dato del '('
            free(sacado); //Free del nodo
        }
        i++;
    }

    while (!vacia(*pila)) {
        if (((Dato*)peek_nodo(*pila))->caracter == '('){ //si quedo es invalida
            printf("Expresion invalida () desbalanceados\n");
            for (int j = 0; j < pos; j++) liberarDato(salida[j]); // Libera todos los datos
            free(salida); // es lo mismo
            eliminarPila(pila);
            return NULL; 
        }
        Nodo *extraido = pop_nodo(pila); //los datos restantes se meten al arreglo
        salida[pos++] = extraido->dato;
        free(extraido);
    }
    return salida;
}

int esOperador(char caracter){
    char *operadores = "+-*/^";
    for(int i=0; operadores[i]!='\0'; i++){
        if(caracter == operadores[i])
            return 1;
    }
    return 0;
}

void postfixCola(void** datos, Cola* cola){
    for(int i = 0; i < 50; i++){
        if(datos[i] == NULL) break; //aqui se puede usar null
        NodoA *nuevo = crearNodoA(datos[i]); //nodo de arbol
        enqueue(cola, nuevo); // La cola ahora guarda NodoA*
    }
}

/*
    if(!vacia(*pila)) {
        eliminarPila(pila);
        inicializarPila(pila);
*/

void postfixArbol(Cola* cola, Arbol* arbol, Pila *pila){

    
    while(!vaciaC(*cola)){
        NodoA* nodo  = (NodoA*)peekC(*cola);
        Dato* dato_info = (Dato*)nodo->dato;
        char a = dato_info->caracter;

        if((a >= 'a' && a <='z') || (a >= 'A' && a <='Z')){
            NodoA* nodo_operando = (NodoA*)dequeue(cola);
            push_nodo(pila, crearNodo(nodo_operando)); //se pone nodoA dentro de nodo que tiene dato
        } else if(esOperador(a)){
            NodoA *raiz = (NodoA*)dequeue(cola);
            Nodo* nodo_dch = pop_nodo(pila);
            NodoA* hijo_derecho = (NodoA*)(nodo_dch->dato); //se casteo el void no ocupamos SIGUIENTE
            free(nodo_dch); 

            //izq
            Nodo* nodo_izq = pop_nodo(pila);
            NodoA* hijo_izquierdo = (NodoA*)(nodo_izq->dato); // Saca el NodoA
            free(nodo_izq);

            raiz->dch = hijo_derecho;
            raiz->izq = hijo_izquierdo;
            push_nodo(pila, crearNodo(raiz));
        }
    }
    
    Nodo* nodo = pop_nodo(pila);
    arbol->raiz = (NodoA*)(nodo->dato);
    free(nodo);
}

float realizarCalculo(float a, float b, char op) {
    float resultado;

    switch(op) {
        case '+':
            resultado = a + b;
            break;
        case '-':
            resultado = a - b; // Izq - Dch
            break;
        case '*':
            resultado = a * b;
            break;
        case '/': 
            if (b == 0) {
                resultado = 0; // El resultado ya es 0, pero se pone por claridad
            } else {
                resultado = a / b;
            }
            break;
        case '^':
            resultado = pow(a, b);
            break;
        default:
            resultado = 0;
            break;
    }

    return resultado;
}


float evaluarArbol(NodoA* raiz) {
    if (raiz == NULL)
        return 0;
    Dato* info = (Dato*)raiz->dato; //cast void 

    if (!esOperador(info->caracter)) { // Es operando con el !
        if (info->valor != NULL) {
            return *(info->valor); //desreferencia
        } else {
            return 0;
        }
    }

    //postorden
    float val_izq = evaluarArbol(raiz->izq);
    float val_dch = evaluarArbol(raiz->dch);

    //le pasamos los valores a realizar calculo
    return realizarCalculo(val_izq, val_dch, info->caracter);
}


void capturarValores(NodoA* raiz, char letras[], float valores[], int *n) {
    if (raiz == NULL)
        return;

    // Recorre hijo izquierdo
    capturarValores(raiz->izq, letras, valores, n);

    // Nodo actual
    Dato* info = (Dato*)raiz->dato;
    if (!esOperador(info->caracter)) {
        int i;
        int existe = 0;

        // Verifica si ya se pidió esta letra
        for (i = 0; i < *n; i++) {
            if (letras[i] == info->caracter) {
                info->valor = &valores[i];
                existe = 1;
                break;
            }
        }

        // Si no existe, se pide una vez
        if (!existe) {
            letras[*n] = info->caracter;
            printf("Ingresa el valor para %c: ", info->caracter);
            inputFloat("", &valores[*n]);
            info->valor = &valores[*n];
            (*n)++;
        }
    }

    // Recorre hijo derecho
    capturarValores(raiz->dch, letras, valores, n);
}

