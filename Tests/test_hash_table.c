#include "../src/hash_table.h"

void test_KRHash() {
  unsigned h1 = KRHash("test");
  unsigned h2 = KRHash("Test");
  unsigned h3 = KRHash("");
  assert(h1 != h2); // Case sensitive
  assert(h3 == 0);  // Empty string
}

void test_hash_table_crear() {
  HashTable* table = hash_table_crear();
  assert(table != NULL);
  assert(table->size == 101);
  assert(table->count == 0);
  assert(table->load_factor == 0);
  assert(table->buckets != NULL);
  hash_table_destruir(table);
}

void test_hash_entry_crear_y_destruir() {
  HashEntry* entry = hash_entry_crear();
  assert(entry != NULL);
  assert(entry->value != NULL);
  assert(entry->occupied == 0);
  hash_entry_destruir(entry);
}

void test_hash_table_destruir() {
  HashTable* table = hash_table_crear();
  HashEntry* entry1 = hash_entry_crear();
  table->buckets[0] = entry1;
  dlist_agregar_final(entry1->value, 42); // Agregar un valor a la lista
  dlist_agregar_final(entry1->value, 43); // Agregar otro valor
  table->count = 1;
  table->load_factor = table->count/table->size;
  HashEntry* entry2 = hash_entry_crear();
  table->buckets[1] = entry2; 
  table->count = 2;
  table->load_factor = table->count/table->size;
  HashEntry* entry3 = hash_entry_crear();
  table->buckets[2] = entry3; 
  dlist_agregar_final(entry1->value, 50); 
  table->count = 3;
  table->load_factor = table->count/table->size;
  hash_table_destruir(table);
}

int main() {
  test_KRHash();
  test_hash_table_crear();
  test_hash_entry_crear_y_destruir();
  test_hash_table_destruir();
  printf("Todos los tests pasaron correctamente.\n");
  return 0;
}
