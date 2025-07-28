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

void definir_lista(char* buffer, Listas* listas);
void definir_funcion(char* buffer, Funciones* funciones);
void aplicar_funcion(char* buffer, Funciones* funciones, Listas* listas);
void buscar_funcion(char* buffer, Funciones* funciones, Listas* listas);


#endif // __FUNCIONES_H__




