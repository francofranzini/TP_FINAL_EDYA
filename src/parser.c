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

int validar_input_funcion(char* buffer) {
  char* ptr = buffer;
  while (isspace(*ptr)) ptr++;

  if (strncmp(buffer, "deff", 4) != 0) {
    return 0;
  }
  ptr += 4; // Saltar "deff"

  while (isspace(*ptr)) ptr++;
  
  // Verificar que hay un nombre válido (letras y números)
  if (!isalnum(*ptr)) return 0;
  
  // Saltea el nombre de la función
  while (isalnum(*ptr)) ptr++;
  
  // Saltea espacios
  while (isspace(*ptr)) ptr++;
  
  // Verificar el '='
  if (*ptr++ != '=') {
      return 0;
  }
  
  // Saltar espacios después del '='
  while (isspace(*ptr)) ptr++;
  
  int nula = 1;
  while(*ptr != ';' && *ptr != '\0'){
    if(nula == 1) nula = 0;
    while(isalnum(*ptr)) ptr++;
    while(isspace(*ptr)) ptr++;

    if(!isalnum(*ptr) && *ptr != ';') return 0; //Cualquier simbolo que no sea la siguiente definicion o haya terminado
  }
  if(*ptr != ';') return 0;
  return (nula == 0); //encontro alguna funcion
}


void asignar_input_lista(char* buffer, Lista* lista){
  char* ptr = buffer;
  while (isspace(*ptr)) ptr++;

  // Saltar "defl"
  ptr += 4;
  while (isspace(*ptr)) ptr++;
  // Copiar el nombre de la lista al bucket
  int i = 0;
  while (isalnum(*ptr) && i < MAX_LIST_NAME - 1) {
    lista->nombre[i++] = *ptr++;
  }
  lista->nombre[i] = '\0'; // Terminar la cadena
  // Saltar espacios y '='
  while (isspace(*ptr)) ptr++;
  ptr++;
  // Saltar espacios y '['
  while (isspace(*ptr)) ptr++;
  ptr++; 
  while (isspace(*ptr)) ptr++;
  //ptr -> primer valor o ']'


  while (*ptr != ']' && *ptr != '\0') {
    while (isspace(*ptr)) ptr++;
    char value[32];
    int j = 0;
    while (isdigit(*ptr) && j < 31) {
      value[j++] = *ptr++;
    }
    value[j] = '\0'; //Terminar la cadena

    lista_agregar_valor(lista, atoi(value)); //Agregar valor a la lista

    while (isspace(*ptr)) ptr++;
    if (*ptr == ',') {
      ptr++; // Saltar la coma
    }
  }
}

