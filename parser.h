#ifndef __PARSER_H__
#define __PARSER_H__

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


int validar_largo_input(char *buffer);
void limpiar_stdin();

// Valida el input considerando que esta definiendo una lista
/*
    Formato: defl nombre = [valor1, valor2, ...];
    - Espacios en blanco permitidos
    - Nombre: alfanumérico
    - Valores: alfanuméricos separados por comas
    - Debe comenzar con '[' y terminar con ']'
    - Debe terminar con ';'
*/
int validar_input_lista(char* buffer);


#endif // __PARSER_H__