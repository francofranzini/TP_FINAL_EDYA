#include "apply.h"

void aplicar_funcion_lista(Lista* lista, Funcion* funcion, int* overflow) {
  if(*overflow == 1) return;
  if(es_funcion_base(funcion)) return aplicar_funcion_lista_base(lista, funcion);

  for(int i = 0; i<funcion->pasos_cantidad;){
    int repite_id = funcion->repite[i];
    if (repite_id != 0) {
      // Buscar fin del bloque de repetición
      int fin = i;
      while (fin < funcion->pasos_cantidad && funcion->repite[fin] == repite_id) {
        fin++;
      }
      int count = 0;
      while (!termina_repeticion(lista) && count < MAX_ITER) {
        for (int j = i; j < fin; j++) 
          aplicar_funcion_lista(lista, funcion->pasos[j], overflow);
        count++;
      }
      if(count == MAX_ITER){
        *overflow = 1;
        return;
      } 
        
      i = fin; // Saltar todo el bloque
    }
    else{
      aplicar_funcion_lista(lista, funcion->pasos[i], overflow);
      i++;
    }
  }
}
void aplicar_funcion_lista_base(Lista* lista,Funcion* funcion){
  if(!dlist_vacia(lista->lista)){
    if(strcmp(funcion->nombre, "Si") == 0) dlist_sumar_primero(lista->lista);
    if(strcmp(funcion->nombre, "Sd") == 0) dlist_sumar_ultimo(lista->lista); 
    if(strcmp(funcion->nombre, "Di") == 0) dlist_eliminar_primero(lista->lista);
    if(strcmp(funcion->nombre, "Dd") == 0) dlist_eliminar_ultimo(lista->lista);
  }
  if(strcmp(funcion->nombre, "Oi") == 0) dlist_agregar_primero(lista->lista, 0);
  if(strcmp(funcion->nombre, "Od") == 0) dlist_agregar_ultimo(lista->lista, 0);
}
int termina_repeticion(Lista* lista){
  if(!dlist_vacia(lista->lista)) return lista->lista->primero->dato == lista->lista->ultimo->dato;
  else return 0;
}
int es_funcion_base(Funcion* funcion){
  return (strcmp(funcion->nombre, "Si") == 0 ||
          strcmp(funcion->nombre, "Sd") == 0 ||
          strcmp(funcion->nombre, "Oi") == 0 ||
          strcmp(funcion->nombre, "Od") == 0 ||
          strcmp(funcion->nombre, "Di") == 0 ||
          strcmp(funcion->nombre, "Dd") == 0);
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
