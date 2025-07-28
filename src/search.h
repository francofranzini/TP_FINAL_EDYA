#ifndef __SEARCH_H__
#define __SEARCH_H__

#include "variables.h"

/*
  Dado un buffer determina si es un input valido para buscar una funcion
*/
int validar_input_search(char* buffer, Listas* listas);


void asignar_input_search(char* buffer,Listas* listas, Lista* entradas[], Lista* salidas[]);

#endif // __SEARCH_H__