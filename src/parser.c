#include "parser.h"
#define MAX_INPUT 512

int input_es_valido(char* buffer) {
  // Asegurar longitud máxima
  if (strlen(buffer) >= MAX_INPUT - 1) return 0;

  
  char* pto_coma = strchr(buffer, ';');
  if (!pto_coma) return 0;

  //Buscar el punto y coma al final
  if(*(buffer + strlen(buffer) - 2) != ';') return 0;

  return 1;
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
Operacion recibir_input(char buffer[]) {
  while (1) {
    fgets(buffer, MAX_INPUT, stdin);
    if (!input_es_valido(buffer)) {
      printf("Input inválido. Debe tener hasta 512 caracteres y terminar en ';'\n");
      limpiar_stdin();
    } else {
      return interpretar_operacion(buffer);
    }
  }
}
int validar_es_lista(char* ptr){
  if (*ptr != '[') {
    return 0;
  }
  ptr++;
  while (isspace(*ptr)) ptr++;
  
  while(*ptr != ']' && *ptr != '\0') {
    // Saltar espacios
    while (isspace(*ptr)) ptr++;
    
    // Verificar que hay un valor válido
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

  return 1;
}