#include "funciones.h"


void definir_lista(char* buffer, HashTable* variables){
  if(!validar_input_lista(buffer)) return;
  
  HashEntry* bucket = hash_entry_crear();
  asignar_input_lista(buffer, bucket);
  char* nombre = bucket->key;
  int k = variables->hash_function(nombre);
  
}
