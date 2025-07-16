#include "hash_table.h"


unsigned KRHash(char* key) {
    unsigned hashval;
    for(hashval = 0; *key != '\0'; key++) {
      hashval = *key + 31  * hashval;
    }
    return hashval;
}


HashTable* crear_tabla_hash(){
  HashTable* table = (HashTable*)malloc(sizeof(HashTable));
  if (!table) {
    printf("Error al crear la tabla hash.\n");
    return NULL;
  }

  table->size = 101;
  table->count = 0;
  table->load_factor = 0;
  table->hash_function = KRHash;
  table->destuir_dato = destruir_lista; 
  table->buckets = malloc(table->size * sizeof(HashEntry*));
  
  if (!table->buckets) {
    printf("Error al crear los buckets de la tabla hash.\n");
    free(table);
    return NULL;
  }
  for (int i = 0; i < table->size; i++) {
    table->buckets[i] = NULL;
  }
  return table;
}

HashTable* destruir_tabla_hash(HashTable* table) {
  if (table) {
    for (int i = 0; i < table->size; i++) {
      if (table->buckets[i]) {
        table->destruir_dato(table->buckets[i]->value);
        free(table->buckets[i]);
      }
    }
    free(table->buckets);
    free(table);
  }
  return NULL;
}

