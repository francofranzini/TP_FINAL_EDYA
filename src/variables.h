#ifndef __VARIABLES_H__
#define __VARIABLES_H__

#define MAX_NAME 32
#define MAX_ITER 1000

#include "./DList/dlist.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>

typedef int (*FuncionHash)(char* nombre);
typedef void (*FuncionDestructora)(void* value);

typedef struct {
  char nombre[MAX_NAME];          // Nombre de la variable
  DList* lista;                  // Lista de valores asociados a la variable
} Lista;

typedef struct _Funcion{
  char nombre[MAX_NAME];          
  struct _Funcion* pasos[30];
  int pasos_cantidad;
  int repite[30];
} Funcion;

typedef struct {
  FuncionHash hash_function1, hash_function2;
  Lista** buckets;              // tamaño primo
  int size;                         // número de elementos en la tabla
  int count;                        // número de entradas ocupadas
  float load_factor;                // factor de carga para rehashing
} Listas;

typedef struct {
  FuncionHash hash_function1, hash_function2;
  Funcion** buckets;              // tamaño primo
  int size;                         // número de elementos en la tabla
  int count;                        // número de entradas ocupadas
  float load_factor;                // factor de carga para rehashing
} Funciones;

typedef struct NodoFuncion {
    Funcion* funcion;
    struct NodoFuncion* sig;
} NodoFuncion;

typedef struct {
    NodoFuncion* frente;
    NodoFuncion* fondo;
} ColaFuncion;

ColaFuncion* cola_funcion_crear();
void cola_funcion_encolar(ColaFuncion* cola, Funcion* f);
Funcion* cola_funcion_desencolar(ColaFuncion* cola);
int cola_funcion_vacia(ColaFuncion* cola);
void cola_funcion_destruir(ColaFuncion* cola);


unsigned KRHash(char* key);
unsigned Hash2(char* key);

Listas* listas_crear();
void listas_destruir(Listas* listas);
int listas_buscar_lista(Listas* listas, char* nombre);
void listas_agregar_lista(Listas* listas, Lista* lista);


void funciones_agregar_funcion(Funciones* funciones, Funcion* funcion);
Funciones* funciones_crear();
void funciones_destruir(Funciones* funciones);
int funciones_buscar_funcion(Funciones* funciones, char* nombre);

Lista* lista_crear();
void lista_destruir(Lista* entry);

Funcion* funcion_crear();
void funcion_destruir(Funcion* funcion);
void funcion_agregar_funcion(Funcion* funcion, Funcion* f_agregar);
void funcion_copiar(Funcion* origen, Funcion* destino);

void lista_destruir(Lista* lista);
void lista_agregar_valor(Lista* lista, int value);
void lista_copiar(Lista* origen, Lista* destino);
void lista_recorrer(Lista* lista);
int lista_iguales(Lista* A, Lista* B);








#endif /* __VARIABLES_H__ */