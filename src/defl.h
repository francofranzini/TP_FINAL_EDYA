#ifndef __DEFL_H__
#define __DEFL_H__

#include "variables.h"
#include "parser.h"

/*
  Dado un buffer determina si es un input valido para definir una lista.
*/
int validar_input_lista(char* buffer);

// Asignar el nombre de la lista
// y sus valores, ingresados en el buffer
void asignar_input_lista(char* buffer, Lista* lista);

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
#endif // __DEFL_H__