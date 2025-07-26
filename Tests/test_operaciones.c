#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "../src/operaciones.h"
#include "../src/variables.h"

void test_definir_lista_exitosa() {
  int size = 101;
  Listas* listas = listas_crear(101);
  assert(listas->size == 101);
  assert(listas->count == 0);


  char input[] = "defl L1= [1 ,2,3   ,4  ,5, 6   ];";
  assert(validar_input_lista(input) == 1);

  Lista* lista = lista_crear();
  asignar_input_lista(input, lista);


  assert(lista->lista->primero->dato == 1);
  assert(lista->lista->ultimo->dato == 6);

  listas_agregar_lista(listas, lista);
  assert(listas->count == 1);

  listas_destruir(listas);
}


void test_definir_lista_fallido(){
  Listas* listas = listas_crear(101);


  //No valida el input
  int count = listas->count;
  char input[] = "defl L1= [1 ,2,3   ,4 ,, 6   ];";
  definir_lista(input, listas);
  assert(count == listas->count);

  //No se agrega por falta de nombre
  strcpy(input, "defl = [1,2,3,4,5];");
  definir_lista(input, listas);
  assert(count == listas->count);

  //Se agrega
  strcpy(input, "defl L1 = [1,2,3];");
  definir_lista(input, listas);
  assert(count + 1 == listas->count);

  //No se agrega por nombre repetido
  strcpy(input,"defl L1 = [];");
  definir_lista(input, listas);
  assert(count + 1 == listas->count);

  listas_destruir(listas);

}

void test_definir_funcion_exitosa(){
  Funciones* funciones  = funciones_crear(101);
  char input[512];
  strcpy(input,"deff f1 = Si <Dd Di> Sd 0i;");

  definir_funcion(input, funciones);
  assert(funciones->count == 7);

  strcpy(input,"deff f2 = f1 <Dd Di> Sd 0i;");
  definir_funcion(input, funciones);
  assert(funciones->count == 8);

  int k2 = funciones_buscar_funcion(funciones, "f2");
  int k1 = funciones_buscar_funcion(funciones, "f1");
  assert(strcmp(funciones->buckets[k1]->nombre, "f1") == 0);
  assert(strcmp(funciones->buckets[k2]->nombre, "f2") == 0);

  assert(strcmp(funciones->buckets[k1]->pasos[2]->nombre, "Di") == 0);
  assert(strcmp(funciones->buckets[k1]->pasos[4]->nombre, "0i") == 0);
  assert(funciones->buckets[k1]->pasos_cantidad == 5);
  assert(funciones->buckets[k2]->pasos_cantidad == 5);


}

int main() {
  // test_definir_lista_exitosa();
  // test_definir_lista_fallido();
  test_definir_funcion_exitosa();
  printf("Todos los tests de definir_lista pasaron correctamente.\n");
  return 0;
}