#include "variables.h"



unsigned KRHash(char* key) {
    unsigned hashval;
    for(hashval = 0; *key != '\0'; key++) {
      hashval = *key + 31  * hashval;
    }
    return hashval;
}
unsigned Hash2(char* key) {
    unsigned hashval;
    for(hashval = 0; *key != '\0'; key++) {
      hashval = *key + 31  * hashval;
    }
    return hashval;
}

Listas* listas_crear(int size) {
    Listas* listas = malloc(sizeof(Listas));
    assert(listas != NULL);
    listas->size = size;
    listas->count = 0;
    listas->load_factor = 0.0f;
    listas->hash_function1 = (FuncionHash)KRHash;
    listas->hash_function2 = (FuncionHash)Hash2;
    listas->buckets = malloc(listas->size * sizeof(Lista*));
    for(int i = 0; i<listas->size; i++) listas->buckets[i] = NULL;
    return listas;
}
void listas_destruir(Listas* listas) {
  for (int i = 0; i < listas->size; i++) {
    if (listas->buckets[i]) {
      lista_destruir(listas->buckets[i]);
    }
  }
  free(listas->buckets);
  free(listas);
}
void listas_agregar_lista(Listas* listas, Lista* lista){
  unsigned k1 = listas->hash_function1(lista->nombre) % listas->size;
  unsigned k2 = 1 + (listas->hash_function2(lista->nombre) % (listas->size - 1));

  int i = 0;
  while (i < listas->size){
    int indice = (k1 + i*k2) % listas->size;
    if(listas->buckets[indice] == NULL){
      listas->buckets[indice] = lista;
      listas->count++;
      listas->load_factor = (float)listas->count / (float)listas->size;
      return;
    }
    else if(strcmp(listas->buckets[indice]->nombre, lista->nombre) == 0){
      printf("El nombre de la lista ya esta en uso\n");
      return;
    }
    i++;
  }
  
}

int listas_buscar_lista(Listas* listas, char* nombre){
  unsigned k1 = listas->hash_function1(nombre) % listas->size;
  unsigned k2 = 1 + (listas->hash_function2(nombre) % (listas->size - 1));
  int j = 0;
  while(j < listas->size){
    unsigned idx = (k1 + j*k2) % listas->size;

    if(listas->buckets[idx] == NULL) return -1;

    if(strcmp(listas->buckets[idx]->nombre, nombre) == 0) return idx;
    
    j++;
  }
  return -1;
}

Lista* lista_crear(){
  Lista* nueva_lista = malloc(sizeof(Lista));
  assert(nueva_lista != NULL);
  nueva_lista->lista = dlist_crear();
  assert(nueva_lista->lista != NULL);
  return nueva_lista;
}

void lista_destruir(Lista* entry) {
  if (entry) {
    dlist_destruir(entry->lista);
    free(entry);
  }
}
void lista_agregar_valor(Lista* lista, int value){
  assert(lista != NULL);
  dlist_agregar_ultimo(lista->lista, value);
}
void lista_copiar(Lista* origen, Lista* destino) {
  DNodo* nodo = origen->lista->primero;
  while(nodo != NULL) {
    dlist_agregar_ultimo(destino->lista, nodo->dato); 
    nodo = nodo->sig;
  }
}
void lista_recorrer(Lista* lista) {
  if (lista == NULL || lista->lista == NULL) return;
  DNodo* nodo = lista->lista->primero;
  while (nodo != NULL) {
    printf("%d ", nodo->dato);
    nodo = nodo->sig;
  }
}
int lista_iguales(Lista* A, Lista* B) {
  DNodo *a = A->lista->primero, *b = B->lista->primero;
  while (a && b) {
    if (a->dato != b->dato) return 0;
    a = a->sig; b = b->sig;
  }
  return (a == NULL && b == NULL);
}

void agregar_funciones_base(Funciones* funciones) {
  Funcion* si = funcion_crear();
  strcpy(si->nombre, "Si");
  funciones_agregar_funcion(funciones, si);

  Funcion* sd = funcion_crear();
  strcpy(sd->nombre, "Sd");
  funciones_agregar_funcion(funciones, sd);

  Funcion* cero_d = funcion_crear();
  strcpy(cero_d->nombre, "Od");
  funciones_agregar_funcion(funciones, cero_d);

  Funcion* cero_i = funcion_crear();
  strcpy(cero_i->nombre, "Oi");
  funciones_agregar_funcion(funciones, cero_i);

  Funcion* ed = funcion_crear();
  strcpy(ed->nombre, "Dd");
  funciones_agregar_funcion(funciones, ed);

  Funcion* ei = funcion_crear();
  strcpy(ei->nombre, "Di");
  funciones_agregar_funcion(funciones, ei);
}

Funciones* funciones_crear(int size){
  Funciones* funciones = malloc(sizeof(Funciones));

  funciones->hash_function1 = (FuncionHash)KRHash;
  funciones->hash_function2 = (FuncionHash)Hash2;
  funciones->size = size;
  funciones->buckets = malloc(sizeof(Funcion*) * size);
  for(int i = 0; i<size; i++) funciones->buckets[i] = NULL;
  funciones->count = 0;
  funciones->load_factor = 0.0;

  agregar_funciones_base(funciones);

  return funciones;
}

int funciones_buscar_funcion(Funciones* funciones, char* nombre){
  unsigned k1 = funciones->hash_function1(nombre) % funciones->size;
  unsigned k2 = 1+ (funciones->hash_function2(nombre) % (funciones->size -1));

  int j = 0;
  while(j < funciones->size){
    unsigned idx = (k1 + j*k2) % funciones->size;

    if(funciones->buckets[idx] == NULL) return -1;

    if(strcmp(funciones->buckets[idx]->nombre, nombre) == 0) return idx;
    j++;
  }
  return -1;
}

void funciones_destruir(Funciones* funciones){
  for(int i = 0; i<funciones->size; i++) 
  if(funciones->buckets[i] != NULL ){
    funcion_destruir(funciones->buckets[i]);
  
  }
  free(funciones->buckets);
  free(funciones);
}

void funciones_agregar_funcion(Funciones* funciones, Funcion* funcion){
  unsigned k1 = funciones->hash_function1(funcion->nombre) % funciones->size;
  unsigned k2 = 1 + (funciones->hash_function2(funcion->nombre) % (funciones->size - 1));

  int i = 0;
  while (i < funciones->size){
    unsigned indice = (k1 + i*k2) % funciones->size;
    if(funciones->buckets[indice] == NULL){
      funciones->buckets[indice] = funcion;
      funciones->count++;
      funciones->load_factor = (float)funciones->count / (float)funciones->size;
      return;
    }
    else if(strcmp(funciones->buckets[indice]->nombre, funcion->nombre) == 0){
      printf("El nombre de la funcion ya esta en uso\n");
      return;
    }
    i++;
  }
}

Funcion* funcion_crear(){
  Funcion* nueva_funcion = malloc(sizeof(Funcion));
  assert(nueva_funcion != NULL);
  for(int i = 0; i<30; i++){
    nueva_funcion->pasos[i] = NULL;
    nueva_funcion->repite[i] = 0;
  }
  nueva_funcion->pasos_cantidad = 0;
  return nueva_funcion;
}

void funcion_agregar_funcion(Funcion* funcion, Funcion* f_agregar){
  funcion->pasos[funcion->pasos_cantidad++] = f_agregar;
}

void funcion_destruir(Funcion* funcion){
  free(funcion);
}
void funcion_copiar(Funcion* origen, Funcion* destino){
  for(int k = 0; k < origen->pasos_cantidad; k++){
    funcion_agregar_funcion(destino, origen->pasos[k]);
  }
}

ColaFuncion* cola_funcion_crear(){
  ColaFuncion* cola = malloc(sizeof(ColaFuncion));
  cola->frente = NULL;
  cola->fondo = NULL;
  return cola;
}
void cola_funcion_encolar(ColaFuncion* cola, Funcion* funcion){
  NodoFuncion* nuevo_nodo = malloc(sizeof(NodoFuncion));
  nuevo_nodo->funcion = funcion;
  nuevo_nodo->sig = NULL;

  if(cola->fondo == NULL) {
    cola->frente = nuevo_nodo;
    cola->fondo = nuevo_nodo;
  } else {
    cola->fondo->sig = nuevo_nodo;
    cola->fondo = nuevo_nodo;
  }
}
Funcion* cola_funcion_desencolar(ColaFuncion* cola) {
  if (cola->frente == NULL) return NULL; // Cola vacía

  NodoFuncion* nodo = cola->frente;
  Funcion* funcion = nodo->funcion;

  cola->frente = nodo->sig;
  if (cola->frente == NULL) {
    cola->fondo = NULL;
  }
  free(nodo);
  return funcion;
}
int cola_funcion_vacia(ColaFuncion* cola) {
  return (cola->frente == NULL);
}
void cola_funcion_destruir(ColaFuncion* cola){
  while(!cola_funcion_vacia(cola)){
    Funcion* f = cola_funcion_desencolar(cola);
    funcion_destruir(f);
  }
  free(cola);
}

void chequear_variables(Listas* listas, Funciones* funciones) {
  float factor_listas = (float)listas->count / listas->size;
  if (factor_listas > 0.75) {
    rehash_listas(listas);
  }

  float factor_funciones = (float)funciones->count / funciones->size;
  if (factor_funciones > 0.75) {
    rehash_funciones(funciones);
  }
}
void rehash_listas(Listas* listas) {
  int old_size = listas->size;
  Lista** old_buckets = listas->buckets;

  listas->size = siguiente_primo(listas->size * 2);
  listas->buckets = malloc(listas->size * sizeof(Lista*));
  for(int i = 0; i < listas->size; i++) listas->buckets[i] = NULL;
  listas->count = 0;

  for(int i = 0; i < old_size; i++) {
    if(old_buckets[i] != NULL)  listas_agregar_lista(listas, old_buckets[i]);
  }
  
  free(old_buckets);
}
void rehash_funciones(Funciones* funciones) {
  int old_size = funciones->size;
  Funcion** old_buckets = funciones->buckets;

  funciones->size = siguiente_primo(funciones->size * 2);
  funciones->buckets = malloc(funciones->size * sizeof(Funcion*));
  for(int i = 0; i < funciones->size; i++) funciones->buckets[i] = NULL;
  funciones->count = 0;

  for(int i = 0; i < old_size; i++) {
    if(old_buckets[i] != NULL) {
      funciones_agregar_funcion(funciones, old_buckets[i]);
    }
  }
  
  free(old_buckets);
}
int siguiente_primo(int n) {
  while(!es_primo(n)) n++;
  return n;
}
int es_primo(int n) {
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) return 0;
  }
  return 1;
}
