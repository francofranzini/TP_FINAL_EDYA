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

//Segun las primeras letras del buffer,
//devuelve a que operacion corresponde el input
Operacion interpretar_operacion(const char *buffer);

// Valida tamaño del input y que termine con ';'
int input_es_valido(char* buffer);

//En caso de que el input no sea valido, limpia el stdin
//para evitar problemas de lectura
void limpiar_stdin();

/*
  Dado un buffer que comienza en '[', valida que su contenido sea una lista bien escrita
*/
int validar_es_lista(char* ptr);




#endif // __PARSER_H__