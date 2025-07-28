#include "../src/defl.h"

void test_validar_input_lista() {
  // Casos válidos
  assert(validar_input_lista("defl lista = [1];") == 1);
  assert(validar_input_lista("defl L123 = [1, 2, 3];") == 1);
  assert(validar_input_lista("defl x = [42];") == 1);
  assert(validar_input_lista("defl abc = [1 ,2 ,3];") == 1);
  assert(validar_input_lista("defl L1 = [];") == 1);

  // Casos inválidos
  assert(validar_input_lista("def lista = [1];") == 0);               // comando mal
  assert(validar_input_lista("defl = [1,2,3];") == 0);                // falta nombre
  assert(validar_input_lista("defl lista = [1,2,];") == 0);           // coma colgante
  assert(validar_input_lista("defl lista [1,2,3];") == 0);            // falta '='
  assert(validar_input_lista("defl lista = 1,2,3;") == 0);            // sin corchetes
  assert(validar_input_lista("defl lista = [1 2 3];") == 0);          // sin comas
  assert(validar_input_lista("defl lista = [1,2,3]") == 0);           // sin ;
  assert(validar_input_lista("defl 1lista = [1,2,3];") == 0);         // nombre inválido
  assert(validar_input_lista("defl lista = [abc];") == 0);           // elementos no numéricos
}

void test_asignar_input_lista() {
  Lista* nueva_lista = lista_crear();
  char input[] = "defl lista = [1, 2, 3];";
  asignar_input_lista(input, nueva_lista);

  
  assert(strcmp(nueva_lista->nombre, "lista") == 0);
  assert(nueva_lista->lista != NULL);
  assert(!dlist_vacia(nueva_lista->lista));
  
  // Verificar los valores en la lista
  DNodo* nodo = nueva_lista->lista->primero;
  assert(nodo != NULL);
  assert(nodo->dato == 1);
  
  nodo = nodo->sig;
  assert(nodo != NULL);
  assert(nodo->dato == 2);
  
  nodo = nodo->sig;
  assert(nodo != NULL);
  assert(nodo->dato == 3);
  
  nodo = nodo->sig;
  assert(nodo == NULL); // Fin de la lista
  
  
  lista_destruir(nueva_lista);



  nueva_lista = lista_crear();
  strcpy(input, "defl L1 = [];");
  asignar_input_lista(input, nueva_lista);
  assert(strcmp(nueva_lista->nombre, "L1") == 0);
  assert(nueva_lista->lista != NULL);
  lista_destruir(nueva_lista);
    
}

int main() {
  test_validar_input_lista();
  test_asignar_input_lista();
  // gcc -o test_defl ./test_defl.c ../src/apply.c ../src/variables.c ../src/DList/dlist.c ../src/deff.c ../src/defl.c ../src/operaciones.c ../src/parser.c ../src/search.c
  printf("Todos los tests de defl pasaron correctamente.\n");
  return 0;
}