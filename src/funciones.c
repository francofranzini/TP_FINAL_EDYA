#include "funciones.h"


void definir_lista(char* buffer, Listas* listas, Funciones* funciones){
  if(!validar_input_lista(buffer)) return;
  
  Lista* nueva_lista = lista_crear();
  asignar_input_lista(buffer, nueva_lista);
  
  agregar_lista(listas, nueva_lista);
  
}
