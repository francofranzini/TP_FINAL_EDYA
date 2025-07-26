#include "../src/DList/dlist.h"

void test_dlist_destruir() {
  DList* lista = dlist_crear();
  dlist_agregar_ultimo(lista, 1);
  dlist_agregar_ultimo(lista, 2);
  dlist_agregar_ultimo(lista, 3);
  
  assert(!dlist_vacia(lista));
  
  dlist_destruir(lista);
  
}

void test_dlist_crear_y_agregar() {
  DList* lista = dlist_crear();
  assert(dlist_vacia(lista));
  dlist_agregar_ultimo(lista, 42);
  assert(!dlist_vacia(lista));
  assert(lista->primero->dato == 42);
  assert(lista->ultimo->dato == 42);
  dlist_agregar_ultimo(lista, 84);
  assert(lista->ultimo->dato == 84);
  assert(lista->primero->sig->dato == 84);
  dlist_destruir(lista);

}

void test_agregar_primero() {
  DList* lista = dlist_crear();
  dlist_agregar_primero(lista, 10);
  assert(lista->primero->dato == 10);
  assert(lista->ultimo->dato == 10);

  dlist_agregar_primero(lista, 20);
  assert(lista->primero->dato == 20);
  assert(lista->primero->sig->dato == 10);
  assert(lista->ultimo->dato == 10);
  dlist_destruir(lista);
}

void test_agregar_ultimo() {
  DList* lista = dlist_crear();
  dlist_agregar_ultimo(lista, 5);
  assert(lista->primero->dato == 5);
  assert(lista->ultimo->dato == 5);

  dlist_agregar_ultimo(lista, 15);
  assert(lista->ultimo->dato == 15);
  assert(lista->primero->sig->dato == 15);
  dlist_destruir(lista);
}
void test_eliminar_primero() {
  DList* lista = dlist_crear();
  dlist_agregar_primero(lista, 1);
  dlist_agregar_primero(lista, 2); // Lista: 2 -> 1

  dlist_eliminar_primero(lista); // Queda: 1
  assert(lista->primero->dato == 1);
  assert(lista->primero == lista->ultimo);

  dlist_eliminar_primero(lista); // Vacía
  assert(lista->primero == NULL);
  assert(lista->ultimo == NULL);
  dlist_destruir(lista);
}
void test_eliminar_ultimo() {
  DList* lista = dlist_crear();
  dlist_agregar_ultimo(lista, 3);
  dlist_agregar_ultimo(lista, 4); // Lista: 3 -> 4

  dlist_eliminar_ultimo(lista); // Queda: 3
  assert(lista->ultimo->dato == 3);
  assert(lista->primero == lista->ultimo);

  dlist_eliminar_ultimo(lista); // Vacía
  assert(lista->primero == NULL);
  assert(lista->ultimo == NULL);
  dlist_destruir(lista);
}

void test_sumar_primero_y_ultimo() {
  DList* lista = dlist_crear();
  dlist_agregar_primero(lista, 7);
  dlist_agregar_ultimo(lista, 8); // Lista: 7 -> 8

  dlist_sumar_primero(lista);
  dlist_sumar_ultimo(lista);

  assert(lista->primero->dato == 8);
  assert(lista->ultimo->dato == 9);
  dlist_destruir(lista);
}

int main(){
  test_dlist_destruir();
  test_dlist_crear_y_agregar();
  test_agregar_primero();
  test_agregar_ultimo();
  test_eliminar_primero();
  test_eliminar_ultimo();
  test_sumar_primero_y_ultimo();
  //gcc -o test_dlist ./test_dlist.c ../src/DList/dlist.c
  printf("Todos los test de dlist fueron completados con exito\n");
  return 0;
}