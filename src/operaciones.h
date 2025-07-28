#ifndef __FUNCIONES_H__
#define __FUNCIONES_H__
#include "variables.h"
#include "parser.h"
#include "deff.h"
#include "defl.h"
#include "apply.h"
#include "search.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*
  Dado un buffer que contiene 'defl' al comienzo,
  define una lista en caso de que el resto del input sea válido.
*/
void definir_lista(char* buffer, Listas* listas);
/*
  Dado un buffer que contiene 'deff' al comienzo,
  define una función en caso de que el resto del input sea válido.
*/
void definir_funcion(char* buffer, Funciones* funciones);
/*
  Dado un buffer que contiene 'apply' al comienzo,
  aplica una función a una lista en caso de que el resto del input sea válido.
*/
void aplicar_funcion(char* buffer, Funciones* funciones, Listas* listas);
/*
  Dado un buffer que contiene 'search' al comienzo,
  busca una función en las listas y funciones definidas.
  Imprime el resultado de la búsqueda.
*/
void buscar_funcion(char* buffer, Funciones* funciones, Listas* listas);


#endif // __FUNCIONES_H__




