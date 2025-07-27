#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "variables.h"


#define MAX_NAME 32

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
  Si cualquiera de las condiciones falla, devuelve 0.
  Si es válido, devuelve 1.
*/
int validar_input_lista(char* buffer);

// Valida el input considerando que esta definiendo una función
/*
    Formato: deff nombre = expresion;
    - Espacios en blanco permitidos
    - Nombre: alfanumérico
    - Expresión: puede contener números y letras, nombres de funciones
    - Debe terminar con ';'
  Si cualquiera de las condiciones falla, devuelve 0.
  Si es válido, devuelve 1.
*/
int validar_input_funcion(char* buffer, Funciones* funciones);
/*
  Valida el input considerando que esta aplicando una función a una lista definida o a una lista nueva
  Formato: apply nombre_funcion lista;
    - Espacios en blanco permitidos
    - Nombre de función: alfanumérico, debe existir
    - Lista: puede ser un nombre de lista existente o una lista nueva entre corchetes
    - Debe terminar con ';'
    - Si es una lista nueva, debe estar entre corchetes y contener numeros separados por comas
  Si cualquiera de las condiciones falla, devuelve 0.
  Si es válido, devuelve 1 si es una lista nueva o 2 si es una lista existente.
*/
int validar_input_aplicar(char* buffer, Funciones* funciones, Listas* listas);

/*
  Buffer parseado para definir una lista solo con valores.
  Asigna el input a una lista nueva o existente.
*/
void extraer_valores_lista(char* buffer, Lista* lista);
/*
  Buffer parseado y valido para aplicar una funcion a lista.
*/
void extraer_nombre_lista(char* buffer, char* nombre_lista);
/*
  Buffer parseado aplicar funcion a una lista.
  Extrae el nombre de la función del buffer.
*/
void extraer_nombre_funcion(char* buffer, char* nombre_funcion);


  // Asignar el nombre de la lista
  // y sus valores, ingresados en el buffer
void asignar_input_lista(char* buffer, Lista* lista);

void asignar_input_funcion(char* buffer, Funciones* funciones,Funcion* funcion);

#endif // __PARSER_H__