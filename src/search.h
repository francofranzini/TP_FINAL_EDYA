#ifndef __SEARCH_H__
#define __SEARCH_H__

#include "variables.h"
#include "apply.h"
/*
  Dado un buffer determina si es un input valido para buscar una funcion
  Un input valido es aquel que cumple con el siguiente formato:
  search {L1, L2; L3, L4;}; Donde CADA Li fue definida previamente
  por el usario.
  Devuelve un valor entero, que corresponde a la cantidad de comparaciones
  a realizar.
*/
int validar_input_search(char* buffer, Listas* listas);

/*
  Dado un input valido de search, asigna las listas de entrada y salida
  a las variables de entrada y salida.
*/
void asignar_input_search(char* buffer,Listas* listas, Lista* entradas[], Lista* salidas[]);

/*
  Realiza un BFS a lo ancho del arbol de composiciones de funciones existentes
  en el sistema, buscando una funcion que valide las igualdades esperadas, con una profundidad maxima
  de 8 niveles.
*/
void BFS(Funciones* funciones, Lista* entradas[], Lista* salidas[],int N, Funcion** rta);


//Dada una funcion, verifica si es solucion a la busqueda
int prueba_candidata(Funcion* f, Lista* E[], Lista* S[], int N);


#endif // __SEARCH_H__