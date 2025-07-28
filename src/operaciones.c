#include "operaciones.h"


void definir_lista(char* buffer, Listas* listas){
  if(!validar_input_lista(buffer)) return;
  
  Lista* nueva_lista = lista_crear();
  asignar_input_lista(buffer, nueva_lista);
  
  int count = listas->count;
  listas_agregar_lista(listas, nueva_lista);

  if(count == listas->count) lista_destruir(nueva_lista);
}
void definir_funcion(char* buffer, Funciones* funciones){
  if(!validar_input_funcion(buffer, funciones)) return;

  Funcion* nueva_funcion = funcion_crear();
  asignar_input_funcion(buffer, funciones, nueva_funcion);
  int count = funciones->count;
  funciones_agregar_funcion(funciones, nueva_funcion);

  if(count == funciones->count) funcion_destruir(nueva_funcion);
}
void aplicar_funcion(char* buffer, Funciones* funciones, Listas* listas) {
  int tipo = validar_input_aplicar(buffer, funciones, listas);
  if(tipo == 0) return; // Input inválido
  
  char nombre_funcion[32];
  extraer_nombre_funcion(buffer, nombre_funcion);
  int idx_funcion = funciones_buscar_funcion(funciones, nombre_funcion);

  Funcion* funcion = funciones->buckets[idx_funcion];
  Lista* lista_temp = lista_crear();

  if(tipo == 1){
    extraer_valores_lista(buffer, lista_temp);
  }
  else{
    char nombre_lista[32];
    extraer_nombre_lista(buffer, nombre_lista);
    int idx = listas_buscar_lista(listas, nombre_lista);
    lista_copiar(listas->buckets[idx], lista_temp);
  }
  int overflow = 0;
  aplicar_funcion_lista(lista_temp, funcion, &overflow);
  if(overflow) {
    printf("Error: Se alcanzó el número máximo de iteraciones (%d)\n", MAX_ITER);
  }
  else{
    printf("[ ");
    lista_recorrer(lista_temp);
    printf("]\n");
  }
  lista_destruir(lista_temp);

}
void buscar_funcion(char* buffer, Funciones* funciones, Listas* listas){
  int N = validar_input_search(buffer, listas);
  if(!N) return;

  Lista* entrada[N],  *salida[N];
  asignar_input_search(buffer, listas, entrada, salida);
  Funcion* funcion_buscada = NULL;
  BFS(funciones, entrada, salida, N, &funcion_buscada);
  if(funcion_buscada != NULL){
    printf("Funcion encontrada: \n");
    for(int i = 0; i<funcion_buscada->pasos_cantidad; i++){
      printf("%s ", funcion_buscada->pasos[i]->nombre);
    }
    printf("\n");
  }
  else{
    printf("No se encontró una función que cumpla con los criterios.\n");
  }
  funcion_destruir(funcion_buscada);

}