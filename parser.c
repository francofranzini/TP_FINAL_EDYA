#include "parser.h"


int validar_largo_input(char *buffer) {
  int incompleto = strchr(buffer, '\n') != NULL;
  return incompleto; // Input válido
}

void limpiar_stdin() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}


enum Operacion recibir_input(char buffer[]){
  fgets(buffer, 512, stdin);
  if(!validar_largo_input(buffer)) {
    printf("El input es muy largo. Por favor ingrese menos de 512 caracteres.\n");
    limpiar_stdin();
    recibir_input(buffer);
  }

  //Quita espacios al inicio
  while (isspace(*buffer)) buffer++;

  if (strncmp(buffer, "defl", 4) == 0) return DEFL;
  if (strncmp(buffer, "deff", 4) == 0) return DEFF;
  if (strncmp(buffer, "apply", 5) == 0) return APPLY;
  if (strncmp(buffer, "search", 6) == 0) return SEARCH;

  return FINISH; // Si no coincide con ninguna operación, se considera FINISH
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