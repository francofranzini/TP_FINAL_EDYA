#include "../src/DList/dlist.h"

void test_dlist_destruir() {
  DList* lista = dlist_crear();
  dlist_agregar_final(lista, 1);
  dlist_agregar_final(lista, 2);
  dlist_agregar_final(lista, 3);
  
  assert(!dlist_vacia(lista));
  
  dlist_destruir(lista);
  
}

void test_dlist_crear_y_agregar() {
  DList* lista = dlist_crear();
  assert(dlist_vacia(lista));
  dlist_agregar_final(lista, 42);
  assert(!dlist_vacia(lista));
  assert(lista->primero->dato == 42);
  assert(lista->ultimo->dato == 42);
  dlist_agregar_final(lista, 84);
  assert(lista->ultimo->dato == 84);
  assert(lista->primero->sig->dato == 84);
  dlist_destruir(lista);
  assert(lista == NULL);
}
int main(){
  test_dlist_destruir();


  return 0;
}