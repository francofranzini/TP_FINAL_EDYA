#ifndef __FUNCIONES_H__
#define __FUNCIONES_H__
#include "hash_table.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void definir_lista(char* buffer, HashTable* variables);
void definir_funciones_lista(char* buffer, HashTable* variables);
void aplicar_funciones_lista(char* buffer, HashTable* variables);
void buscar_funciones_lista(char* buffer, HashTable* variables);


#endif // __FUNCIONES_H__




