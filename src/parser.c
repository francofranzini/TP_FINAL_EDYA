#include "parser.h"


int validar_largo_input(char *buffer) {
  int incompleto = strchr(buffer, '\n') != NULL;
  return incompleto; // Input válido
}

void limpiar_stdin() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

Operacion interpretar_operacion(const char *buffer) {
  //Quita espacios al inicio
  while (isspace(*buffer)) buffer++;

  if (strncmp(buffer, "defl", 4) == 0) return DEFL;
  if (strncmp(buffer, "deff", 4) == 0) return DEFF;
  if (strncmp(buffer, "apply", 5) == 0) return APPLY;
  if (strncmp(buffer, "search", 6) == 0) return SEARCH;

  return FINISH;
}


Operacion recibir_input(char buffer[]){
  fgets(buffer, 512, stdin);
  if(!validar_largo_input(buffer)) {
    printf("El input es muy largo. Por favor ingrese menos de 512 caracteres.\n");
    limpiar_stdin();
    recibir_input(buffer);
  }

  return interpretar_operacion(buffer);
}

int validar_input_lista(char* buffer) {

  char* ptr = buffer;
  while (isspace(*ptr)) ptr++;

  if (strncmp(buffer, "defl", 4) != 0) {
    return 0;
  }
  ptr += 4; // Saltar "defl"

  while (isspace(*ptr)) ptr++;
  // Verificar que hay un nombre válido (letras y números)
  if (!isalpha(*ptr)) {
    return 0;
  }
  //Saltea el nombre de la lista
  while (isalnum(*ptr)) ptr++;
  // Saltea espacios
  while (isspace(*ptr)) ptr++;
  
  // Verificar el '='
  if (*ptr++ != '=') {
      return 0;
  }
  // Saltar espacios después del '='
  while (isspace(*ptr)) ptr++;

  // Verificar que comienza con '['
  //Empieza el parsing de la lista
  
  if (*ptr != '[') {
    return 0;
  }
  ptr++;
  while (isspace(*ptr)) ptr++;
  
  while(*ptr != ']' && *ptr != '\0') {
    // Saltar espacios
    while (isspace(*ptr)) ptr++;
    
    // Verificar que hay un valor válido (número o palabra)
    if (!isdigit(*ptr)) return 0;
    
    // Saltar el valor
    while (isdigit(*ptr)) ptr++;
    
    // Saltar espacios
    while (isspace(*ptr)) ptr++;
    
    // Verificar si hay una coma o el cierre de la lista
    if (*ptr == ',') {
      ptr++;
      while (isspace(*ptr)) ptr++;
      if(*ptr == ']') return 0;
    }
    else if (*ptr != ']') return 0; 
  }
  
  // Verificar cierre ']'
  if (*ptr != ']') return 0;
  ptr++;
  // Saltar espacios
  while (isspace(*ptr)) ptr++;

  // Verificar terminación con ';'
  if (*ptr != ';') {
    return 0;
  }
  return 1;
}

void asignar_input_lista(char* buffer, HashEntry* bucket){
  char* ptr = buffer;
  while (isspace(*ptr)) ptr++;

  // Saltar "defl"
  ptr += 4;
  while (isspace(*ptr)) ptr++;
  // Copiar el nombre de la lista al bucket
  int i = 0;
  while (isalnum(*ptr) && i < MAX_LIST_NAME - 1) {
    bucket->key[i++] = *ptr++;
  }
  bucket->key[i] = '\0'; // Terminar la cadena
  // Saltar espacios y '='
  while (isspace(*ptr)) ptr++;
  ptr++;
  // Saltar espacios y '['
  while (isspace(*ptr)) ptr++;
  ptr++; 
  while (isspace(*ptr)) ptr++;
  //ptr -> primer valor | ']'


  // Asignar valores a la lista
  bucket->value = dlist_crear();
  assert(bucket->value != NULL);


  while (*ptr != ']' && *ptr != '\0') {
    while (isspace(*ptr)) ptr++;
    char value[32];
    int j = 0;
    while (isdigit(*ptr) && j < 31) {
      value[j++] = *ptr++;
    }
    value[j] = '\0'; //Terminar la cadena

    dlist_agregar_final(bucket->value, atoi(value)); //Agregar valor a la lista

    while (isspace(*ptr)) ptr++;
    if (*ptr == ',') {
      ptr++; // Saltar la coma
    }
  }
}

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
    HashEntry* bucket = hash_entry_crear();
    char input[] = "defl lista = [1, 2, 3];";
    asignar_input_lista(input, bucket);

    assert(strcmp(bucket->key, "lista") == 0);
    assert(bucket->value != NULL);
    assert(!dlist_vacia(bucket->value));
    
    // Verificar los valores en la lista
    DNodo* nodo = bucket->value->primero;
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

    hash_entry_destruir(bucket);
    free(bucket);
}

int main() {
    test_validar_largo_input();
    test_recibir_input();
    test_validar_input_lista();
    test_asignar_input_lista();


    printf("Todos los tests de parser pasaron correctamente.\n");
    return 0;
}