#include "../src/parser.h"

void test_validar_largo_input() {
  char corto[] = "defl lista = [1,2,3];\n";
  char largo[600];
  memset(largo, 'a', 599);
  largo[599] = '\0';

  assert(validar_largo_input(corto) == 1);   // contiene '\n'
  assert(validar_largo_input(largo) == 0);   // no contiene '\n'
}

void test_recibir_input() {
  char s[512];
  strncpy(s, "defl L1 = ...\0", 512);
  assert(interpretar_operacion(s) == DEFL);
  strncpy(s, "deff suma = ...\0", 512);
  assert(interpretar_operacion(s) == DEFF);
  strncpy(s, "apply suma lista \0", 512);
  assert(interpretar_operacion(s) == APPLY);
  strncpy(s, "search lista valor\0", 512);
  assert(interpretar_operacion(s) == SEARCH);
  strncpy(s, "otra cosa \0", 512);
  assert(interpretar_operacion(s) == FINISH);
}

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

void test_validar_input_funcion() {
  Funciones* funciones = funciones_crear(101);
  
  // Casos válidos
  assert(validar_input_funcion("deff suma = Si Sd;", funciones) == 1);
  assert(validar_input_funcion("deff f1 = Si <Sd>;", funciones) == 1);
  assert(validar_input_funcion("deff f1 = Si <Sd Sd Sd Sd>;", funciones) == 1);
  assert(validar_input_funcion("deff f1 = Si <Sd>;", funciones) == 1);
  assert(validar_input_funcion("deff Suma23 = Si <0i> <Dd>;", funciones) == 1);
  assert(validar_input_funcion("deff   nombreFunc   =   Si   Sd ;", funciones) == 1);
  assert(validar_input_funcion("deff x1 = Si ;", funciones) == 1);
  assert(validar_input_funcion("deff 123suma = Si;", funciones) == 1);                
  
  // Casos inválidos
  assert(validar_input_funcion("deff f1 = Si <S1 S2 S3 S4>;", funciones) == 0);
  assert(validar_input_funcion("deff f1 = Si <S1 S2 S3 S4>;", funciones) == 0);
  assert(validar_input_funcion("deff Suma23 = Si <0i  Dd;", funciones) == 0);
  assert(validar_input_funcion("def suma = Si Sd;", funciones) == 0);                 // "def"
  assert(validar_input_funcion("deff = Si Sd;", funciones) == 0);                     // falta nombre
  assert(validar_input_funcion("deff suma Si Sd;", funciones) == 0);                  // falta '='
  assert(validar_input_funcion("deff suma = ;", funciones) == 0);                     // sin funciones
  assert(validar_input_funcion("deff suma = Si Sd", funciones) == 0);                 // sin ';' final
  assert(validar_input_funcion("deff suma =  Si> Sd;", funciones) == 0);              // cierra > sin <
  assert(validar_input_funcion("deff suma = ; Si Sd;", funciones) == 0);              // función después de ';'
  assert(validar_input_funcion("deff suma = Si 0i Sd &;", funciones) == 0);           // símbolo inválido al final
  assert(validar_input_funcion("deff esteesunnombremuylargoparaprobarquenoguarda = Si Sd;", funciones) == 0);
  funciones_destruir(funciones);
}
void test_asignar_input_funcion(){
  Funciones* funciones = funciones_crear(101);

  char input[512];
  strcpy(input,"deff f1 = Si 0i;");
  Funcion* f1 = funcion_crear();

  asignar_input_funcion(input, funciones, f1);

  funciones_agregar_funcion(funciones, f1);

  assert(strcmp(f1->pasos[0]->nombre,"Si") == 0);
  assert(strcmp(f1->pasos[1]->nombre,"0i") == 0);
  assert(f1->repite[0] == 0);
  assert(f1->repite[1] == 0);

  strcpy(input, "deff f2 = Si <0i 0i f1> f1;");
  Funcion* f2 = funcion_crear();

  asignar_input_funcion(input, funciones, f2);

  assert(strcmp(f2->pasos[0]->nombre, "Si") == 0);
  assert(strcmp(f2->pasos[1]->nombre, "0i") == 0);
  assert(strcmp(f2->pasos[2]->nombre, "0i") == 0);
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

int main() {
    test_validar_largo_input();
    test_recibir_input();
    test_validar_input_lista();
    test_asignar_input_lista();
    test_validar_input_funcion();
    test_asignar_input_funcion();
//  gcc -o test_parser test_parser.c ../src/parser.c ../src/variables.c ../src/DList/dlist.c
    printf("Todos los tests de parser pasaron correctamente.\n");
    return 0;
}