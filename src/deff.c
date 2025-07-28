#include "deff.h"


int validar_input_funcion(char* buffer, Funciones* funciones) {
  char* ptr = buffer;
  while (isspace(*ptr)) ptr++;

  if (strncmp(buffer, "deff", 4) != 0) {
    return 0;
  }
  ptr += 4; // Saltar "deff"

  while (isspace(*ptr)) ptr++;
  
  // Verificar que hay un nombre válido (letras y números)
  if (!isalnum(*ptr)) return 0;
  
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
  
  int nula = 1, repite = 0, pasos = 0;
  while(*ptr != ';' && *ptr != '\0'){
    if(pasos++ == 30){
      printf("Puede componer hasta 30 funciones en una sola declaracion");
      return 0;
    } 
    if(nula == 1) nula = 0;

    char nombre[32];
    int i = 0;
    if(*ptr == '<')
    {
      if(repite) return 0; //caso < ... <
      ptr++;
      repite = 1;
    }
    while(isalnum(*ptr)){
      if(i == 31) return 0;  // nombre de funcion muy largo
      nombre[i++] = *ptr;
      ptr++;
    }
    nombre[i] = '\0';

    if(*ptr == '>'){
      if(repite){
        ptr++;
        repite = 0;
      } 
      else return 0; //Encuentra '>' sin '<' previamente
    }
    
    int k = funciones_buscar_funcion(funciones, nombre);
    if(k == -1) return 0;

    while(isspace(*ptr)) ptr++;

    if(!isalnum(*ptr) && *ptr != ';' && *ptr != '<') return 0; //Cualquier simbolo que no sea la siguiente definicion o haya terminado
  }
  if(*ptr != ';') return 0;
  return (nula == 0 && repite == 0); //encontro alguna funcion y cerro >
}

void asignar_input_funcion(char* buffer, Funciones* funciones,Funcion* funcion) {
  char* ptr = buffer;
  while (isspace(*ptr)) ptr++;
  ptr+=4;
  while(isspace(*ptr))ptr++;


  int i = 0;
  while (isalnum(*ptr) && i < MAX_NAME - 1) {
    funcion->nombre[i++] = *ptr;
    ptr++;
  }
  funcion->nombre[i] = '\0';

  while(isspace(*ptr)) ptr++;
  ptr++; // Saltar '='
  while(isspace(*ptr)) ptr++;

  /*
    deff s = Si  Sd <Si Si Sd> Oi;
            [0   0  1  1  1   0]
  */
  int repitiendo = 0, bucle = 0;
  while(*ptr != ';'){
    if(*ptr == '<'){ //repitiendo
      repitiendo = 1;
      bucle++;
      ptr++;
    }
    while(isspace(*ptr)) ptr++;
    char nombre[32];
    int i = 0;
    while(isalnum(*ptr)){
      nombre[i++] = *ptr;
      ptr++;
    }
    nombre[i] = '\0';
    
    int k = funciones_buscar_funcion(funciones, nombre);
    if(repitiendo) funcion->repite[funcion->pasos_cantidad] = bucle;
    funcion_agregar_funcion(funcion, funciones->buckets[k]);
    
    while(isspace(*ptr))ptr++;
    if(*ptr == '>'){
      repitiendo = 0;
      ptr++;
    }
    while(isspace(*ptr))ptr++;
  }
  
}

