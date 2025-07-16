#include "parser.h"


int validar_input(char *buffer) {
  int incompleto = strchr(buffer, '\n') != NULL;
  return incompleto; // Input válido
}

void limpiar_stdin() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}


enum Operacion recibir_input(char buffer[]){
  fgets(buffer, 512, stdin);
  if(!validar_input(buffer)) {
    printf("El input es muy largo. Por favor ingrese menos de 512 caracteres.\n");
    limpiar_stdin(); // Limpiar el buffer de entrada
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