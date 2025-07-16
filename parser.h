#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STEPS 100
#define MAX_FUNC_NAME 32
#define MAX_LIST_NAME 32

enum Operacion {
  DEFL,
  DEFF,
  APPLY,
  SEARCH,
  FINISH
};

//Lee el input, lo guarda en el buffer y devuelve el tipo de operación
enum Operacion recibir_input(char buffer[]);
