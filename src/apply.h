#ifndef __APPLY_H__
#define __APPLY_H__
#include "variables.h"
#include "parser.h"
#include "defl.h"
int es_funcion_base(Funcion* funcion);
int termina_repeticion(Lista* lista);
void aplicar_funcion_lista_base(Lista* lista,Funcion* funcion);
void aplicar_funcion_lista(Lista* lista, Funcion* funcion, int* overflow);

/*
  Valida el input considerando que esta aplicando una función a una lista definida o a una lista nueva
  Formato: apply nombre_funcion lista;
    - Espacios en blanco permitidos
    - Nombre de función: alfanumérico, debe existir
    - Lista: puede ser un nombre de lista existente o una lista nueva entre corchetes
    - Debe terminar con ';'
    - Si es una lista nueva, debe estar entre corchetes y contener numeros separados por comas
  Si cualquiera de las condiciones falla, devuelve 0.
  Si es válido, devuelve 1 si es una lista nueva o 2 si es una lista existente.
*/
int validar_input_aplicar(char* buffer, Funciones* funciones, Listas* listas);

/*
  Recibe un buffer parseado para definir una lista solo con valores.
  Asigna el input a una lista.
*/
void extraer_valores_lista(char* buffer, Lista* lista);
/*
  Recibe un buffer parseado y valido para aplicar una funcion a lista.
  y extrae el nombre de la lista en 'nombre_lista'.
*/
void extraer_nombre_lista(char* buffer, char* nombre_lista);
/*
  Recibe un buffer parseado aplicar funcion a una lista.
  Extrae el nombre de la función del buffer.
*/
void extraer_nombre_funcion(char* buffer, char* nombre_funcion);

/*
  Dado un buffer, determina si es un input valido para aplicar una función a una lista.
*/
int validar_input_aplicar(char* buffer, Funciones* funciones, Listas* listas);



#endif // 




