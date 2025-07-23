#include "hash_table.h"

unsigned KRHash(char* key) {
    unsigned hashval;
    for(hashval = 0; *key != '\0'; key++) {
      hashval = *key + 31  * hashval;
    }
    return hashval;
}


HashTable* hash_table_crear(){
  HashTable* table = (HashTable*)malloc(sizeof(HashTable));
  assert(table != NULL);
  table->size = 101;
  table->count = 0;
  table->load_factor = 0;
  table->hash_function = (FuncionHash)KRHash;
  table->buckets = malloc(table->size * sizeof(HashEntry));
  assert(table->buckets != NULL);
  for (int i = 0; i < table->size; i++) {
    table->buckets[i] = NULL;
  }
  return table;
}

void hash_table_destruir(HashTable* table) {
  if (table) {
    for (int i = 0; i < table->size; i++) {
      if (table->buckets[i]) hash_entry_destruir(table->buckets[i]);
    }
    free(table->buckets);
    free(table);
  }
}

HashEntry* hash_entry_crear(){
  HashEntry* entry = malloc(sizeof(HashEntry));
  assert(entry != NULL);
  entry->value = dlist_crear();
  assert(entry->value != NULL);
  entry->occupied = 0; // Inicialmente no ocupado
  return entry;
}

void hash_entry_destruir(HashEntry* entry) {
  if (entry) {
    dlist_destruir(entry->value);
    free(entry);
  }
}