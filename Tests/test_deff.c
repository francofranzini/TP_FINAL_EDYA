#include "../src/deff.h"


void test_validar_input_funcion() {
  Funciones* funciones = funciones_crear(101);
  
  // Casos válidos
  
  assert(validar_input_funcion("deff f1 = Si <Dd Di> Sd Oi;", funciones) == 1);
  assert(validar_input_funcion("deff suma = Si Sd;", funciones) == 1);
  assert(validar_input_funcion("deff f1 = Si <Sd>;", funciones) == 1);
  assert(validar_input_funcion("deff f1 = Si <Sd Sd Sd Sd>;", funciones) == 1);
  assert(validar_input_funcion("deff f1 = Si <Sd>;", funciones) == 1);
  assert(validar_input_funcion("deff Suma23 = Si <Oi> <Dd>;", funciones) == 1);
  assert(validar_input_funcion("deff   nombreFunc   =   Si   Sd ;", funciones) == 1);
  assert(validar_input_funcion("deff x1 = Si ;", funciones) == 1);
  assert(validar_input_funcion("deff 123suma = Si;", funciones) == 1);                
  
  // Casos inválidos
  assert(validar_input_funcion("deff f1 = Si <S1 S2 S3 S4>;", funciones) == 0);
  assert(validar_input_funcion("deff f1 = Si <S1 S2 S3 S4>;", funciones) == 0);
  assert(validar_input_funcion("deff Suma23 = Si <Oi  Dd;", funciones) == 0);
  assert(validar_input_funcion("def suma = Si Sd;", funciones) == 0);                 // "def"
  assert(validar_input_funcion("deff = Si Sd;", funciones) == 0);                     // falta nombre
  assert(validar_input_funcion("deff suma Si Sd;", funciones) == 0);                  // falta '='
  assert(validar_input_funcion("deff suma = ;", funciones) == 0);                     // sin funciones
  assert(validar_input_funcion("deff suma = Si Sd", funciones) == 0);                 // sin ';' final
  assert(validar_input_funcion("deff suma =  Si> Sd;", funciones) == 0);              // cierra > sin <
  assert(validar_input_funcion("deff suma = ; Si Sd;", funciones) == 0);              // función después de ';'
  assert(validar_input_funcion("deff suma = Si Oi Sd &;", funciones) == 0);           // símbolo inválido al final
  assert(validar_input_funcion("deff esteesunnombremuylargoparaprobarquenoguarda = Si Sd;", funciones) == 0);
  funciones_destruir(funciones);
}
void test_asignar_input_funcion(){
  Funciones* funciones = funciones_crear(101);

  char input[512];
  strcpy(input,"deff f1 = Si Oi;");
  Funcion* f1 = funcion_crear();

  asignar_input_funcion(input, funciones, f1);

  funciones_agregar_funcion(funciones, f1);

  assert(strcmp(f1->pasos[0]->nombre,"Si") == 0);
  assert(strcmp(f1->pasos[1]->nombre,"Oi") == 0);
  assert(f1->repite[0] == 0);
  assert(f1->repite[1] == 0);

  strcpy(input, "deff f2 = Si <Oi Oi f1> f1;");
  Funcion* f2 = funcion_crear();

  asignar_input_funcion(input, funciones, f2);

  assert(strcmp(f2->pasos[0]->nombre, "Si") == 0);
  assert(strcmp(f2->pasos[1]->nombre, "Oi") == 0);
  assert(strcmp(f2->pasos[2]->nombre, "Oi") == 0);
  assert(strcmp(f2->pasos[3]->nombre, "f1") == 0);
  assert(strcmp(f2->pasos[4]->nombre, "f1") == 0);

  assert(f2->repite[0] == 0);
  assert(f2->repite[1] == 1);
  assert(f2->repite[2] == 1);
  assert(f2->repite[3] == 1);
  assert(f2->repite[4] == 0);
  
  funciones_agregar_funcion(funciones, f2);

  Funcion* f3 = funcion_crear();
  strcpy(input, "deff f3 = f2 <f1> <f1 Si>;");

  asignar_input_funcion(input, funciones, f3);

  assert(strcmp(f3->pasos[0]->nombre, "f2") == 0);
  assert(strcmp(f3->pasos[1]->nombre, "f1") == 0);
  assert(strcmp(f3->pasos[2]->nombre, "f1") == 0);
  assert(strcmp(f3->pasos[3]->nombre, "Si") == 0);

  assert(f3->repite[0] == 0);
  assert(f3->repite[1] == 1);
  assert(f3->repite[2] == 2);
  assert(f3->repite[3] == 2);

  funciones_agregar_funcion(funciones, f3);

  funciones_destruir(funciones);
}

int main(){
  test_validar_input_funcion();
  test_asignar_input_funcion();
  //gcc -o test_deff ./test_deff.c ../src/defl.c ../src/operaciones.c ../src/parser.c ../src/variables.c ../src/DList/dlist.c ../src/apply.c ../src/deff.c ../src/search.c
  printf("Todos los tests de deff pasaron correctamente.\n");
  return 0;
}