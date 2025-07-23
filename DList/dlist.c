#include "dlist.h"

DList* dlist_crear() {
  DList* lista = malloc(sizeof(DList));
  assert(lista != NULL);
  lista->primero = NULL;
  lista->ultimo = NULL;
  return lista;
}
void dlist_destruir(DList* lista) {
  DNodo *nodoAEliminar;
  while (lista->primero != NULL) {
    nodoAEliminar = lista->primero;
    lista->primero = lista->primero->sig;
    free(nodoAEliminar);
  }
  free(lista);
}
int dlist_vacia(DList* lista) {
  return lista->primero == NULL;
}
void dlist_agregar_final(DList* lista, int dato) {
  DNodo *nuevoNodo = malloc(sizeof(DNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;
  nuevoNodo->ant = lista->ultimo;
  if(lista->ultimo != NULL){
    lista->ultimo->sig = nuevoNodo;
    lista->ultimo = nuevoNodo;
  }else{
    lista->primero = nuevoNodo;
    lista->ultimo = nuevoNodo;
  }
}
void dlist_agregar_inicio(DList* lista, int dato) {
  DNodo *nuevoNodo = malloc(sizeof(DNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista->primero;
  nuevoNodo->ant = NULL;
  if (lista->primero != NULL) {
    lista->primero->ant = nuevoNodo;
  }
  lista->primero = nuevoNodo;
  if (lista->ultimo == NULL) {
    lista->ultimo = nuevoNodo;
  }
}
void dlist_recorrer(DList* lista, FuncionVisitante visit) {
  for (DNodo *nodo = lista->primero; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}
void dlist_eliminar_ultimo(DList* lista) {
  DNodo* nodoAEliminar = lista->ultimo;
  lista->ultimo = nodoAEliminar->ant;
  if(lista->ultimo != NULL) {
    lista->ultimo->sig = NULL;
  } else {
    lista->primero = NULL;
  }
  free(nodoAEliminar);
}
void dlist_eliminar_primero(DList* lista){
  DNodo* nodoAEliminar = lista->primero;
  lista->primero = nodoAEliminar->sig;
  if(lista->primero != NULL) {// hay mas elementos
    lista->primero->ant = NULL;
  } else { //unico elemento
    lista->ultimo = NULL;
  }
  free(nodoAEliminar);
}


