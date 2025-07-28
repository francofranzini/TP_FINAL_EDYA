#include "search.h"

int validar_input_search(char* buffer, Listas* listas){
  char* ptr = buffer;
  while(isspace(*ptr))ptr++;
  ptr+=6; //Saltea 'Search'
  while(isspace(*ptr))ptr++;
  if(*ptr != '{') return 0;
  ptr++;
  while(isspace(*ptr))ptr++;
  int count = 0;


  while(*ptr != '}' && *ptr != '\0'){
    count++;
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
  
  if(*ptr != ';') return 0;

  return count; //Cantidad de pares de listas
}

void asignar_input_search(char* buffer, Listas* listas, Lista* entradas[], Lista* salidas[]){
  char* ptr = buffer;
  while(isspace(*ptr)) ptr++;
  ptr += 6; //Saltea 'Search'
  while(isspace(*ptr)) ptr++;
  ptr++; //Saltea '{'
  while(isspace(*ptr)) ptr++;
  int i = 0;
  while(*ptr != '}' && *ptr != '\0'){
    //Li1, Li2;
    char nombre1[32], nombre2[32];
    int nombre_len = 0;
    
    while (isalnum(*ptr)) {
      nombre1[nombre_len] = *ptr;
      nombre_len++;
      ptr++;
    }
    nombre1[nombre_len] = '\0';
    
    while(isspace(*ptr)) ptr++;
    ptr++; //Saltea ','
    while(isspace(*ptr)) ptr++;
    //...Li2...; 
    nombre_len = 0;
    while (isalnum(*ptr)) {
      nombre2[nombre_len] = *ptr;
      nombre_len++;
      ptr++;
    }
    nombre2[nombre_len] = '\0';
    
    entradas[i] = listas->buckets[listas_buscar_lista(listas, nombre1)];
    salidas[i] = listas->buckets[listas_buscar_lista(listas, nombre2)];
    i++;



    while(isspace(*ptr)) ptr++;
    ptr++; //Saltea ';'
    while(isspace(*ptr)) ptr++;
  }
}

void BFS(Funciones* funciones, Lista* entradas[], Lista* salidas[], int N, Funcion** rta) {
 
  Funcion* definidas[funciones->count];
  ColaFuncion* cola_actual = cola_funcion_crear();
  ColaFuncion* cola_siguiente = cola_funcion_crear();

  //Creo el array de funciones existentes
  //Inicializo la cola con funciones de 1 solo paso (las funciones definidas)
  //f_aux->pasos[0] = funcion_definida
  int count = 0;
  for(int i = 0; i<funciones->size; i++){
    if(funciones->buckets[i] != NULL){
      definidas[count++] = funciones->buckets[i];
      Funcion* f_aux = funcion_crear();
      funcion_agregar_funcion(f_aux, funciones->buckets[i]);
      cola_funcion_encolar(cola_actual, f_aux);
    }
  }


  //En cada iteracion de la busqueda, probaremos entre las funciones definidas
  // si alguna consigue que L11 se transforme en L12, y luego probaremos para el
  // resto de listas. En caso de encontrar alguna solucion, asignamos esa funcion
  // a rta y liberamos la cola y las funciones definidas.

  int encontrado = 0;
  
  for(int i = 0; !encontrado && i<8; i++){
    while(!encontrado && !cola_funcion_vacia(cola_actual)){
      Funcion* f = cola_funcion_desencolar(cola_actual);
      //Creo mi lista temporal para aplicar la funcion
      Lista* lista_temp = lista_crear();
      lista_copiar(entradas[0], lista_temp);
      int overflow = 0;

      aplicar_funcion_lista(lista_temp, f, &overflow);
      //Si hubo overflow, no sigo con esta funcion y la descarto del arbol
      if(!overflow){
        if(lista_iguales(lista_temp, salidas[0]) && prueba_candidata(f, entradas, salidas, N)){
          *rta = f;
          encontrado = 1;
        }
        if(!encontrado && f->pasos_cantidad<15){ // No encontre solucion y tengo espacio para agregar pasos
          for(int j = 0; j<count; j++){
            Funcion* f_aux = funcion_crear();
            funcion_copiar(f, f_aux);
            funcion_agregar_funcion(f_aux, definidas[j]);
            cola_funcion_encolar(cola_siguiente, f_aux);
          }
        }
      }
      if(!encontrado) funcion_destruir(f);
      lista_destruir(lista_temp);
    }
    //Intercambio las colas
    if(!encontrado){
      ColaFuncion* temp = cola_actual;
      cola_actual = cola_siguiente;
      cola_siguiente = cola_funcion_crear();
      cola_funcion_destruir(temp);
    }
  }
  cola_funcion_destruir(cola_actual);
  cola_funcion_destruir(cola_siguiente);
}
int prueba_candidata(Funcion* f, Lista* E[], Lista* S[], int N){
  int verifica = 1;
  //Si la funcion consigue transformar L11 en L12
  // verifico si tambien lo hace con el resto de listas
  for(int j = 1; j < N && verifica; j++){
    int overflow_aux = 0;
    Lista* lista_temp2 = lista_crear();
    lista_copiar(E[j], lista_temp2);
    aplicar_funcion_lista(lista_temp2, f, &overflow_aux);
    if(overflow_aux || !lista_iguales(lista_temp2, S[j])){
      verifica = 0;  
    } 
    lista_destruir(lista_temp2);
  }
  return verifica;
}