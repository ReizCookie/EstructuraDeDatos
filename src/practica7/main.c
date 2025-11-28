#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Estructuras/pila/pila.h"
#include "../captura/captura.h"
#define MAX 100

int precedencia(char op) {
    if (op == '^')
        return 3;
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

int esOperador(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}


int esOperando(char c) {
    return ((c >= 'A' && c <= 'Z') || 
            (c >= 'a' && c <= 'z') || 
            (c >= '0' && c <= '9'));
}

// Imprime caracter para la pila
void imprimirCaracter(void *dato) {
    if (dato != NULL) {
        printf("%c", *(char*)dato);
    }
}

void infixAPostfix(char infix[], char postfix[]) {
    Pila pila;
    inicializarPila(&pila);
    pila.imprimir = imprimirCaracter;
    
    int j = 0; 
    
    //for para conversion
    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        
        if (c == ' ') //por si hay espacios en blanco los ignora
            continue;
        
        if (esOperando(c)) {
            postfix[j++] = c;
        }
        
        else if (c == '(') {
            char *nuevo = (char*)malloc(sizeof(char));
            *nuevo = c;
            push(&pila, nuevo);
        }
    
        else if (c == ')') { //Se vacia la pila si se encuentra el parentesis de cierre
            while (!vacia(pila)) {
                char *top = (char*)pila.cima->dato;
                if (*top == '(') {
                    break;
                }
                char *operador = (char*)pop(&pila);
                postfix[j++] = *operador;
                free(operador);
            }
            if (!vacia(pila)) {
                char *parentesis = (char*)pop(&pila);
                free(parentesis);
            }
        }
        
        else if (esOperador(c)) {
        
            while (!vacia(pila)) {
                char *top = (char*)pila.cima->dato;
                
                if (*top == '(')
                    break;
                
                if (precedencia(*top) < precedencia(c))
                    break;
                
                char *operador = (char*)pop(&pila);
                postfix[j++] = *operador;
                free(operador);
            }
            
            char *nuevo = (char*)malloc(sizeof(char));
            *nuevo = c;
            push(&pila, nuevo);
        }
        
    }
    
    //vacia la pila
    while (!vacia(pila)) {
        char *operador = (char*)pop(&pila);
        postfix[j++] = *operador;
        free(operador);
    }
    
    postfix[j] = '\0'; 
}

int main() {
    char infix[MAX];
    char postfix[MAX];
    int opcion;
    
    do {
        printf("CONVERSOR INFIX A POSTFIX\n");
        
        printf("Ingrese la expresion en formato INFIX: ");
        fgets(infix, MAX, stdin);
        
        // Eliminar el salto de linea
        infix[strcspn(infix, "\n")] = '\0';
        
        if (strlen(infix) == 0) {
            printf("\nLa expresion no puede estar vacia\n");
            continue;
        }
        infixAPostfix(infix, postfix);
        
        printf("\n\n==========================================");
        printf("\nExpresion POSTFIX: %s", postfix);
        printf("\n==========================================\n");
        
        printf("\nDesea convertir otra expresion? (1=Siii, 0=No): ");
        scanf("%d", &opcion);
        getchar();
        
    } while (opcion == 1);
    
    
    return 0;
}

