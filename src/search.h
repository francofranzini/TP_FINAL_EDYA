#ifndef __SEARCH_H__
#define __SEARCH_H__

#include "variables.h"
#include "apply.h"
/*
  Dado un buffer determina si es un input valido para buscar una funcion
*/
int validar_input_search(char* buffer, Listas* listas);


void asignar_input_search(char* buffer,Listas* listas, Lista* entradas[], Lista* salidas[]);


void BFS(Funciones* funciones, Lista* entradas[], Lista* salidas[],int N, Funcion** rta);


//Dada una funcion, verifica si es solucion a la busqueda
int prueba_candidata(Funcion* f, Lista* E[], Lista* S[], int N);


#endif // __SEARCH_H__