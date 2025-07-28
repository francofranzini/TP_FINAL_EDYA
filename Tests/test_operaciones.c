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
  strcpy(input,"deff f1 = Si <Dd Di> Sd Oi;");

  definir_funcion(input, funciones);
  assert(funciones->count == 7);

  strcpy(input,"deff f2 = f1 <Dd Di> Sd Oi;");
  definir_funcion(input, funciones);
  assert(funciones->count == 8);

  int k2 = funciones_buscar_funcion(funciones, "f2");
  int k1 = funciones_buscar_funcion(funciones, "f1");
  assert(strcmp(funciones->buckets[k1]->nombre, "f1") == 0);
  assert(strcmp(funciones->buckets[k2]->nombre, "f2") == 0);

  assert(strcmp(funciones->buckets[k1]->pasos[2]->nombre, "Di") == 0);
  assert(strcmp(funciones->buckets[k1]->pasos[4]->nombre, "Oi") == 0);
  assert(funciones->buckets[k1]->pasos_cantidad == 5);
  assert(funciones->buckets[k2]->pasos_cantidad == 5);

  funciones_destruir(funciones);

}

void test_aplicar_funcion() {
  Funciones* funciones = funciones_crear(101);
  Listas* listas = listas_crear(101);
  char buffer[512];

  strcpy(buffer, "deff f1 = Si Si;");
  definir_funcion(buffer, funciones);
  
  strcpy(buffer, "apply f1 [1, 3, 6];");

  aplicar_funcion(buffer, funciones, listas);

  // Test 2: aplicar f1 sobre lista nombrada
  
  strcpy(buffer, "defl miLista = [1, 2, 3, 4, 5];");
  definir_lista(buffer, listas);

  strcpy(buffer, "apply f1 miLista;");
  aplicar_funcion(buffer, funciones, listas);

  strcpy(buffer, "deff Mi = Oi <Si> Dd;");
	definir_funcion(buffer ,funciones);

  strcpy(buffer, "deff Md = Od <Sd> Di;");
	definir_funcion(buffer, funciones);
  
  strcpy(buffer,"deff S1 = Md Oi Mi Oi;");
	definir_funcion(buffer, funciones);

	strcpy(buffer,"deff S2 = <Si Md Md Si Mi Mi>;");
	definir_funcion(buffer, funciones);

	strcpy(buffer,"deff S3 = Dd Di Md;");
	definir_funcion(buffer, funciones);

	strcpy(buffer,"deff S = S1 S2 S3;");
	definir_funcion(buffer, funciones);

  strcpy(buffer, "apply S miLista;");
  aplicar_funcion(buffer, funciones, listas);

  funciones_destruir(funciones);
  listas_destruir(listas);
}
void test_aplicar_funcion_overflow() {
  Funciones* funciones = funciones_crear(101);
  Listas* listas = listas_crear(101);
  char buffer[512];

  int overflow = 0;

  strcpy(buffer, "deff f1 = Si Si;");
  definir_funcion(buffer, funciones);

  strcpy(buffer, "deff ferror = <Si Sd>;");
  definir_funcion(buffer, funciones);

  strcpy(buffer, "apply ferror [1, 3, 6];");
  aplicar_funcion(buffer, funciones, listas);

  funciones_destruir(funciones);
  listas_destruir(listas);
}

int main() {
  test_definir_funcion_exitosa();
  test_definir_lista_exitosa();
  test_definir_lista_fallido();
  test_aplicar_funcion();
  test_aplicar_funcion_overflow();
  //gcc -o test_operaciones ./test_operaciones.c ../src/apply.c ../src/variables.c ../src/DList/dlist.c ../src/deff.c ../src/defl.c ../src/operaciones.c ../src/parser.c ../src/search.c
  printf("Todos los tests de definir_lista pasaron correctamente.\n");
  return 0;
}