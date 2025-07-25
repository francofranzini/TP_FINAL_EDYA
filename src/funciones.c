#include "funciones.h"


void definir_lista(char* buffer, Listas* listas){
  if(!validar_input_lista(buffer)) return;
  
  Lista* nueva_lista = lista_crear();
  asignar_input_lista(buffer, nueva_lista);
  
  int count = listas->count;
  listas_agregar_lista(listas, nueva_lista);

  if(count == listas->count) lista_destruir(nueva_lista);
}
void definir_funcion(char* buffer, Funciones* funciones){
  if(!validar_input_funcion(buffer)) return;

  Funcion* nueva_funcion = funcion_crear();
  asignar_input_funcion(buffer, nueva_funcion);
  // int count = funciones->count;
  // funciones_agregar_funcion(funciones, nueva_funcion);

  // if(count == funciones->count) funcion_destruir(nueva_funcion);
}