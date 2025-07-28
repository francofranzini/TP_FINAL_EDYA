#include "search.h"

int validar_input_search(char* buffer, Listas* listas){
  char* ptr = buffer;
  while(isspace(*ptr))ptr++;
  ptr+=6; //Saltea 'Search'
  while(isspace(*ptr))ptr++;
  if(*ptr != '{') return 0;
  ptr++;
  while(isspace(*ptr))ptr++;
  while(*ptr != '}' && *ptr != '\0'){
    //Li1, Li2;
    if(!isalnum(*ptr)) return 0;
    int nombre_len = 0;
    char nombre1[32], nombre2[32];
    while (isalnum(*ptr)) {
      if (nombre_len >= MAX_NAME - 1) return 0;
      nombre1[nombre_len] = *ptr;
      nombre_len++;
      ptr++;
    }
    nombre1[nombre_len] = '\0';
    if(listas_buscar_lista(listas, nombre1) == -1) return 0;
    while(isspace(*ptr))ptr++;
    if(*ptr != ',') return 0;
    ptr++;
    while(isspace(*ptr))ptr++;
    //...Li2...; 
    nombre_len = 0;
    if(!isalnum(*ptr)) return 0;
    while (isalnum(*ptr)) {
      if (nombre_len >= MAX_NAME - 1) return 0;
      nombre2[nombre_len] = *ptr;
      nombre_len++;
      ptr++;
    }
    nombre2[nombre_len] = '\0';
    if(listas_buscar_lista(listas, nombre2) == -1) return 0;
    while(isspace(*ptr))ptr++;
    if(*ptr != ';') return 0;
    ptr++;
    while(isspace(*ptr))ptr++;
  }
  if(*ptr != '}') return 0;
  ptr++;
  while(isspace(*ptr)) ptr++;
  
  return (*ptr == ';');
}