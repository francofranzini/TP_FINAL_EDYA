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
Operacion recibir_input(char buffer[]){
  fgets(buffer, 512, stdin);
  if(!validar_largo_input(buffer)) {
    printf("El input es muy largo. Por favor ingrese menos de 512 caracteres.\n");
    limpiar_stdin();
    recibir_input(buffer);
  }
  if(buffer[strlen(buffer) - 2] != ';') {
    printf("El input debe terminar con ';'\n");
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

int validar_input_aplicar(char* buffer, Funciones* funciones, Listas* listas) {
  char* ptr = buffer;

  while (isspace(*ptr)) ptr++;

  // Debe empezar con "apply"
  if (strncmp(ptr, "apply", 5) != 0) return 0;
  ptr += 5;

  while (isspace(*ptr)) ptr++;

  // Nombre de función válido
  if (!isalnum(*ptr)) return 0;
  int nombre_len = 0;
  char nombre[32];
  while (isalnum(*ptr)) {
    if (nombre_len >= MAX_NAME - 1) return 0;
    nombre[nombre_len] = *ptr;
    nombre_len++;
    ptr++;
  }
  nombre[nombre_len] = '\0';
  if(funciones_buscar_funcion(funciones, nombre) == -1) return 0; //No existe la funcion

  while (isspace(*ptr)) ptr++;

  
  int tipo = 0; // 1: lista nueva, 2: lista existente
  if(*ptr == '['){
    if(!validar_es_lista(ptr)) return 0;
    while(*ptr != ']') ptr++;
    ptr++;
    tipo = 1; 
  }
  else{
    if(!isalnum(*ptr)) return 0;
    int nombre_len = 0;
    char nombre[32];
    while (isalnum(*ptr)) {
      if (nombre_len >= MAX_NAME - 1) return 0;
      nombre[nombre_len] = *ptr;
      nombre_len++;
      ptr++;
    }
    nombre[nombre_len] = '\0';
    if(listas_buscar_lista(listas, nombre) == -1) return 0; // no existe la lista
    tipo = 2;
  }
  while(isspace(*ptr))ptr++;
  if(*ptr != ';') return 0; // debe terminar con ';'
  return tipo;
}
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
    if(pasos++ == 20){
      printf("Puede componer hasta 20 funciones en una sola declaracion");
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
void extraer_nombre_lista(char* buffer,char* nombre_lista){
  char* ptr = buffer;
  while (isspace(*ptr)) ptr++;
  ptr += 5; // Saltar "apply"
  while (isspace(*ptr)) ptr++;
  while(isalnum(*ptr)) ptr++;
  while (isspace(*ptr)) ptr++;

  int i = 0;
  while (isalnum(*ptr)) {
    nombre_lista[i++] = *ptr++;
  }
  nombre_lista[i] = '\0';
}
void extraer_valores_lista(char* buffer, Lista* lista) {
  char* ptr = buffer;
  while(*ptr != '[') ptr++;
  ptr++;
  // Extraer valores hasta ']'
  while (*ptr != ']' && *ptr != '\0') {
    while (isspace(*ptr)) ptr++;
    char value[32];
    int j = 0;
    while (isdigit(*ptr)) {
      value[j++] = *ptr++;
    }
    value[j] = '\0'; //Terminar la cadena

    lista_agregar_valor(lista, atoi(value));

    while (isspace(*ptr)) ptr++;
    if (*ptr == ',') {
      ptr++;
    }
  }
}
void extraer_nombre_funcion(char* buffer, char* nombre_funcion) {
  char* ptr = buffer;
  while (isspace(*ptr)) ptr++;
  ptr += 5; // Saltar "apply"
  while (isspace(*ptr)) ptr++;

  int i = 0;
  while (isalnum(*ptr) && i < MAX_NAME - 1) {
    nombre_funcion[i++] = *ptr++;
  }
  nombre_funcion[i] = '\0'; // Terminar la cadena
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

