#include "funciones.h"


void definir_lista(char* buffer, Listas* listas){
  if(!validar_input_lista(buffer)) return;
  
  Lista* nueva_lista = lista_crear();
  asignar_input_lista(buffer, nueva_lista);
  
  int count = listas->count;
  listas_agregar_lista(listas, nueva_lista);

  if(count == listas->count) lista_destruir(nueva_lista);
}
