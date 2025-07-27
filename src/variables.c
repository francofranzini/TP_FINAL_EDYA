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
  for(int i = 0; i<20; i++){
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

void aplicar_funcion_lista(Lista* lista, Funcion* funcion){
  if(es_funcion_base(funcion)) aplicar_funcion_lista_base(lista, funcion);

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
          aplicar_funcion_lista(lista, funcion->pasos[j]);
        count++;
      }

      i = fin; // Saltar todo el bloque
    }
    else{
      aplicar_funcion_lista(lista, funcion->pasos[i]);
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
