#include <stdio.h>
#include <stdlib.h>
#include "parser.h"


void procesar_operacion(enum Operacion operacion, char buffer[]){
  switch(operacion) {
    case DEFL:
      // Aquí iría la lógica para definir una lista
      break;
    case DEFF:
      // Aquí iría la lógica para definir una función
      break;
    case APPLY:
      // Aquí iría la lógica para aplicar una expresión
      break;
    case SEARCH:
      // Aquí iría la lógica para buscar una expresión
      break;
  }
}


void iniciar_programa() {
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
          
          break;
        case DEFF:
          
          break;
        case APPLY:
          
          break;
        case SEARCH:
          
          break;
      }
      operacion = recibir_input(buffer);
    }
}



int main(){

  iniciar_programa();

  return 0;
}