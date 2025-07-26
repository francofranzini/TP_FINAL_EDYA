#ifndef __VARIABLES_H__
#define __VARIABLES_H__

#define MAX_NAME 32
#define MAX_ITER 10000

#include "./DList/dlist.h"
#include <string.h>

typedef int (*FuncionHash)(char* nombre);
typedef void (*FuncionDestructora)(void* value);

typedef struct {
  char nombre[MAX_NAME];          // Nombre de la variable
  DList* lista;                  // Lista de valores asociados a la variable
} Lista;

typedef struct _Funcion{
  char nombre[MAX_NAME];          
  struct _Funcion* pasos[20];
  int pasos_cantidad;
  int repite[20];
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
void funciones_destruir(Funciones* funciones);
int funciones_buscar_funcion(Funciones* funciones, char* nombre);

Lista* lista_crear();
void lista_destruir(Lista* entry);

Funcion* funcion_crear();
void funcion_destruir(Funcion* funcion);

void lista_destruir(Lista* lista);
void lista_agregar_valor(Lista* lista, int value);


void listas_agregar_lista(Listas* listas, Lista* lista);
void funciones_agregar_funcion(Funciones* funciones, Funcion* funcion);
void funcion_agregar_funcion(Funcion* funcion, Funcion* f_agregar);

void dlist_sumar_uno_inicio(DList* lista);

int es_funcion_base(Funcion* funcion);
int termina_repeticion(Lista* lista);
int aplicar_funcion_lista_base(Lista* lista,Funcion* funcion);
int aplicar_funcion_lista(Lista* lista, Funcion* funcion);


#endif /* __VARIABLES_H__ */