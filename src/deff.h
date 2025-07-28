#ifndef __DEFF_H__
#define __DEFF_H__

#include "variables.h"
#include "parser.h"
/*
  Recibe un buffer parseado y valido para definir una función.
  Asigna nombre de la funcion y cada uno de sus pasos, junto con las repeticiones
  a la estructura de la función.
*/
void asignar_input_funcion(char* buffer, Funciones* funciones,Funcion* funcion);

// Valida el input considerando que esta definiendo una función
/*
    Formato: deff nombre = [i1, i2, ..., in] donde i es un natural
    - Espacios en blanco permitidos
    - Nombre: alfanumérico
    - Expresión: puede contener números y letras, nombres de funciones
    - Debe terminar con ';'
  Si cualquiera de las condiciones falla, devuelve 0.
  Si es válido, devuelve 1.
*/
int validar_input_funcion(char* buffer, Funciones* funciones);

#endif // __DEFF_H__