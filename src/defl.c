#include "defl.h"


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
  // Saltea el nombre de la lista
  // y verifica que no sea demasiado largo
  int nombre_len = 0;
  while (isalnum(*ptr)) {
    nombre_len++;
    if (nombre_len >= MAX_NAME-1) return 0;  // nombre demasiado largo
    ptr++;
  }
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
  
  if(!validar_es_lista(ptr)) return 0;
  while(*ptr != ']') ptr++;
  ptr++;
  
  // Saltar espacios
  while (isspace(*ptr)) ptr++;

  // Verificar terminación con ';'
  return(*ptr == ';');
}
void asignar_input_lista(char* buffer, Lista* lista){
  char* ptr = buffer;
  while (isspace(*ptr)) ptr++;

  // Saltar "defl"
  ptr += 4;
  while (isspace(*ptr)) ptr++;
  // Copiar el nombre de la lista al bucket
  int i = 0;
  while (isalnum(*ptr) && i < MAX_NAME - 1) {
    lista->nombre[i++] = *ptr++;
  }
  lista->nombre[i] = '\0'; 
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
    value[j] = '\0';

    lista_agregar_valor(lista, atoi(value)); //Agregar valor a la lista

    while (isspace(*ptr)) ptr++;
    if (*ptr == ',') {
      ptr++; // Saltar la coma
    }
  }
}


