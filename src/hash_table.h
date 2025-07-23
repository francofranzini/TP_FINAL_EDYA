#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include "./DList/dlist.h"
typedef int (*FuncionHash)(char* nombre);
typedef void (*FuncionDestructora)(void* value);

typedef struct {
  char key[256]; // "" indica celda vacía
  DList* value;            
  int occupied;          // 0: libre, 1: ocupado, -1: borrado (opcional)
} HashEntry;

typedef struct {
  FuncionHash hash_function;
  HashEntry** buckets;              // tamaño primo
  int size;                         // número de elementos en la tabla
  int count;                        // número de entradas ocupadas
  float load_factor;                // factor de carga para rehashing
} HashTable;


HashTable* crear_tabla_hash();

HashEntry* hash_entry_crear();
void hash_entry_destruir(HashEntry* entry);


#endif /* __HASH_TABLE_H__ */