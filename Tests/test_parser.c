#include "../src/parser.h"
#include "../src/operaciones.h"

void test_recibir_input() {
  char s[512];
  strncpy(s, "defl L1 = ...\0", 512);
  assert(interpretar_operacion(s) == DEFL);
  strncpy(s, "deff suma = ...\0", 512);
  assert(interpretar_operacion(s) == DEFF);
  strncpy(s, "apply suma lista \0", 512);
  assert(interpretar_operacion(s) == APPLY);
  strncpy(s, "search lista valor\0", 512);
  assert(interpretar_operacion(s) == SEARCH);
  strncpy(s, "otra cosa \0", 512);
  assert(interpretar_operacion(s) == FINISH);
}

int main() {
    test_recibir_input();

    printf("Todos los tests de parser pasaron correctamente.\n");
    return 0;
}