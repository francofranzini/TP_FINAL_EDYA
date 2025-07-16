typedef int (*FuncionHash)(char* nombre);
typedef void (*FuncionDestructora)(void* value);

typedef struct {
  char key[MAX_LIST_NAME]; // "" indica celda vacía
  void* value;
  int occupied;          // 0: libre, 1: ocupado, -1: borrado (opcional)
} HashEntry;

typedef struct {
  FuncionHash hash_function;
  FuncionDestructora destuir_dato;
  HashEntry** buckets; // tamaño primo
  int size;               // número de elementos en la tabla
  int count;              // número de entradas ocupadas
  float load_factor; // factor de carga para rehashing
} HashTable;


HashTable* crear_tabla_hash();