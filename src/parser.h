#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "variables.h"

#define MAX_STEPS 100
#define MAX_FUNC_NAME 32
#define MAX_LIST_NAME 32

typedef enum {
  DEFL,
  DEFF,
  APPLY,
  SEARCH,
  FINISH
} Operacion;

//Lee el input, lo guarda en el buffer y devuelve el tipo de operación
Operacion recibir_input(char buffer[]);


Operacion interpretar_operacion(const char *buffer);

int validar_largo_input(char *buffer);


void limpiar_stdin();

// Valida el input considerando que esta definiendo una lista
/*
    Formato: defl nombre = [valor1, valor2, ...];
    - Espacios en blanco permitidos
    - Nombre: alfanumérico
    - Valores: alfanuméricos separados por comas
    - Debe comenzar con '[' y terminar con ']' en los valores
    - Debe terminar con ';'
*/
int validar_input_lista(char* buffer);

// Valida el input considerando que esta definiendo una función
/*
    Formato: deff nombre = expresion;
    - Espacios en blanco permitidos
    - Nombre: alfanumérico
    - Expresión: puede contener números y letras, nombres de funciones
    - Debe terminar con ';'
*/
int validar_input_funcion(char* buffer);

  // Asignar el nombre de la lista
  // y sus valores, ingresados en el buffer
void asignar_input_lista(char* buffer, Lista* lista);



#endif // __PARSER_H__