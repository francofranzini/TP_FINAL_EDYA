#ifndef __VARIABLES_H__
#define __VARIABLES_H__

#include "./DList/dlist.h"
#include <string.h>
typedef int (*FuncionHash)(char* nombre);
typedef void (*FuncionDestructora)(void* value);


typedef struct {
  char nombre[256];          // Nombre de la variable
  DList* lista;                  // Lista de valores asociados a la variable
} Lista;

typedef struct _Funcion{
  char nombre[256];          
  struct _Funcion* funciones[20];             
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


unsigned KRHash(char* key);


Listas* listas_crear();
void listas_destruir(Listas* listas);

Funciones* funciones_crear();


Lista* lista_crear();
void lista_destruir(Lista* lista);
void lista_agregar_valor(Lista* lista, int value);
void listas_agregar_lista(Listas* listas, Lista* lista);
void funciones_agregar_funcion(Funciones* funciones, Funcion* funcion);



#endif /* __VARIABLES_H__ */