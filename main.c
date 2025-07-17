#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "funciones.h"



void iniciar_programa(HashTable* variables) {
    printf("Bienvenido al programa de funciones de lista.\n");
    //Inicializar variables o estructuras necesarias
    enum Operacion operacion = DEFL;
    /* ejecutando:
        DEFF. Definiendo funciones de lista
        DEFL. Definiendo listas
        APPLY. Expresiones de aplicacion
        SEARCH. Expresiones de busqueda
        FINISH. Salir del programa
    */
    char buffer[512];
    operacion = recibir_input(buffer);
    while(operacion != FINISH){
      switch(operacion) {
        case DEFL:
          printf("Definiendo lista...\n");
          definir_lista(buffer, variables);
          break;
        case DEFF:
          //definir_funciones_lista(buffer, variables);
          break;
        case APPLY:
          //aplicar_funciones_lista(buffer, variables);
          break;
        case SEARCH:
          //buscar_funciones_lista(buffer, variables);
          break;
      }
      operacion = recibir_input(buffer);
    }
}



int main(){
  HashTable* variables;

  //inicializar_variables(variables);
  iniciar_programa(variables);
  //liberar_variables(variables);

  return 0;
}