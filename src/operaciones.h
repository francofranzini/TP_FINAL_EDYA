#ifndef __FUNCIONES_H__
#define __FUNCIONES_H__
#include "variables.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void definir_lista(char* buffer, Listas* listas);
void definir_funcion(char* buffer, Funciones* funciones);
void aplicar_funcion(char* buffer, Funciones* funciones, Listas* listas);
void buscar_funciones(char* buffer, Listas* listas, Funciones* funciones);


#endif // __FUNCIONES_H__




