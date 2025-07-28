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
  assert(validar_input_search("search {};", listas) == 0);
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

void test_prueba_candidata(){
  Funciones* funciones = funciones_crear(17);
  Listas* listas = listas_crear(17);
  definir_lista("defl L1 = [1,2,3, 4];", listas);
  definir_lista("defl L2 = [1,2, 3, 7];", listas);
  definir_lista("defl L3 = [3,4, 5, 6];", listas);
  definir_lista("defl L4 = [3, 4, 5, 9];", listas);
  definir_funcion("deff f1 = Sd Sd Sd;", funciones);

  
  Lista* E[2], *S[2];
  E[0] = listas->buckets[listas_buscar_lista(listas, "L1")];
  E[1] = listas->buckets[listas_buscar_lista(listas, "L3")];
  S[0] = listas->buckets[listas_buscar_lista(listas, "L2")];
  S[1] = listas->buckets[listas_buscar_lista(listas, "L4")];

  int idx = funciones_buscar_funcion(funciones, "f1");
  Funcion* f1 = funciones->buckets[idx];

  assert(prueba_candidata(f1, E, S, 2) == 1); //Si hay funcion definida, devuelve 1

  // assert(prueba_candidata(funciones->buckets[funciones_buscar_funcion(funciones, "f1")], E, S, 2) == 0); //Si no hay funcion definida, devuelve 0
  funciones_destruir(funciones);
  listas_destruir(listas);
}

void test_search_base(){
  Funciones* funciones = funciones_crear(17);  
  Listas* listas = listas_crear(17); 
  Funcion* rta;
  definir_funcion("deff f1 = Si Si Si;", funciones);
  
  definir_lista("defl L1 = [2,2,3,0];", listas);
  definir_lista("defl L2 = [4,2,3,3];", listas);
  definir_lista("defl L3 = [3,6,7,10];", listas);
  definir_lista("defl L4 = [5,6,7,13];", listas);
  
  int N = validar_input_search("search {L1, L2; L3, L4;};", listas);
  Lista* entradas[N], *salidas[N];
  asignar_input_search("search {L1, L2; L3, L4;};", listas, entradas, salidas);
  assert(strcmp(entradas[0]->nombre, "L1") == 0);
  assert(strcmp(salidas[0]->nombre, "L2") == 0);
  assert(strcmp(entradas[1]->nombre, "L3") == 0);
  assert(strcmp(salidas[1]->nombre, "L4") == 0);


  BFS(funciones, entradas, salidas, N, &rta);
  assert(rta->pasos_cantidad > 0); //Debe encontrar al menos una funcion
  for(int i = 0; i<rta->pasos_cantidad; i++){
    printf("Paso %d: %s\n", i, rta->pasos[i]->nombre);
  }
  
  funciones_destruir(funciones);
  listas_destruir(listas);
  funcion_destruir(rta);
}

void test_search_enunciado(){
  Funciones* funciones = funciones_crear(17);
  Listas* listas = listas_crear(17);
  Funcion* rta;
  definir_funcion("deff Md = Od <Sd> Dd;", funciones);

  definir_lista("defl L1 = [0,1,2];", listas);
  definir_lista("defl L2 = [1,2,3];", listas);
  definir_lista("defl L3 = [0,0,0];", listas);
  definir_lista("defl L4 = [1,1,1];", listas);
  
  int N = validar_input_search("search {L1, L2; L3, L4;};", listas);
  Lista* entradas[N], *salidas[N];
  asignar_input_search("search {L1, L2; L3, L4;};", listas, entradas, salidas);

  BFS(funciones, entradas, salidas, N, &rta);
  assert(rta->pasos_cantidad > 0); 
  for(int i = 0; i<rta->pasos_cantidad; i++){
    printf("Paso %d: %s\n", i, rta->pasos[i]->nombre);
  }
  funciones_destruir(funciones);
  listas_destruir(listas);
  funcion_destruir(rta);

}
int main() {
  test_validar_input_search();
  test_asignar_input_search();
  test_search_base();
  test_prueba_candidata();
  test_search_enunciado();
  //gcc -o test_search ./test_search.c ../src/apply.c ../src/variables.c ../src/DList/dlist.c ../src/deff.c ../src/defl.c ../src/operaciones.c ../src/parser.c ../src/search.c
  printf("Todos los tests de search pasaron correctamente.\n");
  return 0;
}