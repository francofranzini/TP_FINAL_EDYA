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

/*
  Revisa ambos factores de carga y si es necesario, rehashing.
*/
void chequear_variables(Listas* listas, Funciones* funciones);
void rehash_listas(Listas* listas);
void rehash_funciones(Funciones* funciones);

/*
  Funciones de hash para las tablas de hash
*/
unsigned KRHash(char* key);
unsigned Hash2(char* key);

/*
  Funciones de creación y destrucción de estructuras
*/
Listas* listas_crear();
void listas_destruir(Listas* listas);
/*
  Dada una lista, busca si existe en la tabla de listas.
  Devuelve el índice de la lista si existe, -1 si no.
*/
int listas_buscar_lista(Listas* listas, char* nombre);
/*
  Agrega una lista a la tabla de listas, si no existe.
*/
void listas_agregar_lista(Listas* listas, Lista* lista);


/*
Funciones de creacion y destrucción de estructuras
*/
Funciones* funciones_crear();
void funciones_destruir(Funciones* funciones);


/*
  Dada una función, busca si existe en la tabla de funciones.
  Devuelve el índice de la función si existe, -1 si no.
*/
void funciones_agregar_funcion(Funciones* funciones, Funcion* funcion);
/*
  Dada una función, busca si existe en la tabla de funciones.
  Devuelve el índice de la función si existe, -1 si no.
*/
int funciones_buscar_funcion(Funciones* funciones, char* nombre);

/*
  Funciones de creacion y destruccion de listas y funciones
*/
Lista* lista_crear();
void lista_destruir(Lista* entry);

Funcion* funcion_crear();
void funcion_destruir(Funcion* funcion);


/*
  Dada una funcion, agrega una función a la lista de pasos.
*/
void funcion_agregar_funcion(Funcion* funcion, Funcion* f_agregar);
/*
  Dada una funcion, copia los valores de otra funcion en la funcion destino.
*/
void funcion_copiar(Funcion* origen, Funcion* destino);

/*
  Dada una lista, agrega un valor al final de la lista.
*/
void lista_agregar_valor(Lista* lista, int value);
/*
  Dadas dos listas, copia los valores de la lista origen a la lista destino.
*/
void lista_copiar(Lista* origen, Lista* destino);
/*
  Dada una lista, imprime sus valores.
*/
void lista_recorrer(Lista* lista);
/*
  Dadas dos listas, compara si son iguales.
  Devuelve 1 si son iguales, 0 si no.
*/
int lista_iguales(Lista* A, Lista* B);

/*
  Funciones auxiliares para el rehashing de estructuras
*/
int siguiente_primo(int n);
int es_primo(int n);





#endif /* __VARIABLES_H__ */