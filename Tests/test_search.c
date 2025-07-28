#include "../src/search.h"
#include "../src/operaciones.h"
void test_validar_input_search() {
  Listas* listas = listas_crear(101);
  
  definir_lista("defl L1 = [1,2,3,4];", listas);
  definir_lista("defl L2 = [1,2];", listas);
  definir_lista("defl L3 = [3,4];", listas);
  definir_lista("defl L4 = [2,3];", listas);

  assert(listas_buscar_lista(listas, "L1") != -1);
  assert(listas_buscar_lista(listas, "L2") != -1);
  assert(listas_buscar_lista(listas, "L3") != -1);
  assert(listas_buscar_lista(listas, "L4") != -1);

  //Casos validos
  assert(validar_input_search("search {L1, L2; L3, L4;};", listas) == 2);
  assert(validar_input_search("  search  {  L1 ,L2 ; L3,  L4; } ;  ", listas) == 2);

  
  //Casos invalidos
  assert(validar_input_search("search {L1 L2; L3, L4;};", listas) == 0);
  assert(validar_input_search("search {L1, L2 L3, L4;};", listas) == 0);
  assert(validar_input_search("search {L1, XX;};", listas) == 0);
  assert(validar_input_search("search {L1, L2;}", listas) == 0);
  assert(validar_input_search("search {L1, L2; L3, L4;", listas) == 0);



  listas_destruir(listas); 
}
void test_asignar_input_search() {
    Listas* listas = listas_crear(101);

    definir_lista("defl L1 = [1,2,3,4];", listas);
    definir_lista("defl L2 = [1,2];", listas);
    definir_lista("defl L3 = [3,4];", listas);
    definir_lista("defl L4 = [2,3];", listas);

    Lista* entradas[10];
    Lista* salidas[10];

    char buffer[512];
    strcpy(buffer, "search {L1, L2; L3, L4;};");

    // La función necesita tener acceso a listas, por lo tanto asumimos que listas es global o accesible
    asignar_input_search(buffer,listas, entradas, salidas);

    assert(strcmp(entradas[0]->nombre,"L1") == 0);
    assert(strcmp(entradas[1]->nombre,"L3") == 0);
    assert(strcmp(salidas[0]->nombre,"L2") == 0);
    assert(strcmp(salidas[1]->nombre,"L4") == 0);
    

    listas_destruir(listas);
}
int main() {
  test_validar_input_search();
  test_asignar_input_search();
  //gcc -o test_variables ./test_variables.c ../src/apply.c ../src/variables.c ../src/DList/dlist.c ../src/deff.c ../src/defl.c ../src/operaciones.c ../src/parser.c ../src/search.c
  printf("Todos los tests de search pasaron correctamente.\n");
  return 0;
}