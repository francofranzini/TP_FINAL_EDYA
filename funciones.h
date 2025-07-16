#include "parser.h"
#include "hash_table.h"



typedef struct {
    char nombre[MAX_FUNC_NAME];
    char pasos[MAX_STEPS][8];  // strings como "Od", "Si", "<Si>", etc.
    int cantidad_pasos;
} Function;

typedef struct {
    char nombre[MAX_LIST_NAME];
    int elementos[MAX_STEPS];  // Asumiendo que los elementos son enteros
    int cantidad_elementos;
} List;



