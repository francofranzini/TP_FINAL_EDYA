#ifndef __DLIST_H__
#define __DLIST_H__

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef void (*FuncionVisitante) (int dato);
typedef int (*FuncionComparacion) (int dato1, int dato2);

typedef struct _DNodo {
  int dato;
  struct _DNodo *sig, *ant;
} DNodo;

typedef struct DList {
  DNodo *primero;
  DNodo *ultimo;
} DList;


/**
 * Devuelve una lista vacía.
 */
DList* dlist_crear();

/**
 * Destruccion de la lista.
 */
void dlist_destruir(DList* lista);

/**
 * Determina si la lista es vacía.
  1: es vacia
  0: no es vacia
 */
int dlist_vacia(DList* lista);

/**
 * Agrega un elemento al final de la lista.
 */
void dlist_agregar_ultimo(DList* lista, int dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
void dlist_agregar_primero(DList* lista, int dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void dlist_recorrer(DList* lista, FuncionVisitante visit);

void dlist_eliminar_ultimo(DList* lista);

void dlist_eliminar_primero(DList* lista);

void dlist_sumar_ultimo(DList* lista);

void dlist_sumar_primero(DList* lista);

#endif /* __DLIST_H__ */
