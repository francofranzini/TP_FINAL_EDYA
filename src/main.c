#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "operaciones.h"

void liberar_variables( Listas* listas, Funciones* funciones){
  listas_destruir(listas);
  funciones_destruir(funciones);
}

void iniciar_programa(Listas* listas, Funciones* funciones) {
    printf("Bienvenido al programa de funciones de lista.\n");
    //Inicializar variables o estructuras necesarias
    Operacion operacion = DEFL;
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
          definir_lista(buffer, listas);
          printf("Cantidad de listas definidas: %i\nFactor de carga: %f\n", listas->count, listas->load_factor);
          break;
        case DEFF:
          definir_funcion(buffer, funciones);
          printf("Cantidad de funciones definidas: %i\nFactor de carga: %f\n", funciones->count, funciones->load_factor);
          break;
        case APPLY:
          aplicar_funcion(buffer, funciones, listas);
          break;
        case SEARCH:
          buscar_funcion(buffer, funciones, listas);
          break;
        case FINISH:
          printf("Saliendo del programa.\n");
          break;
      }
      operacion = recibir_input(buffer);
    }
}



int main(){
  Listas* listas = listas_crear(101);
  Funciones* funciones = funciones_crear(101);

  iniciar_programa(listas, funciones);
  liberar_variables(listas, funciones);

  return 0;
}