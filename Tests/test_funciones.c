#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "../src/funciones.h"
#include "../src/variables.h"

void test_definir_lista_exitosa() {
    int size = 101;
    Listas* listas = listas_crear(101);
    assert(listas->size == 101);
    assert(listas->count == 0);


    char input[] = "defl L1= [1 ,2,3   ,4  ,5, 6   ];";
    assert(validar_input_lista(input) == 1);

    Lista* lista = lista_crear();
    asignar_input_lista(input, lista);


    assert(lista->lista->primero->dato == 1);
    assert(lista->lista->ultimo->dato == 6);

    listas_agregar_lista(listas, lista);
    assert(listas->count == 1);

    listas_destruir(listas);
}


void test_definir_lista_fallido(){
    Listas* listas = listas_crear(101);
    

    //No valida el input
    int count = listas->count;
    char input[] = "defl L1= [1 ,2,3   ,4 ,, 6   ];";
    definir_lista(input, listas);
    assert(count == listas->count);

    //No se agrega por falta de nombre
    strcpy(input, "defl = [1,2,3,4,5];");
    definir_lista(input, listas);
    assert(count == listas->count);

    //Se agrega
    strcpy(input, "defl L1 = [1,2,3];");
    definir_lista(input, listas);
    assert(count + 1 == listas->count);

    //No se agrega por nombre repetido
    strcpy(input,"defl L1 = [];");
    definir_lista(input, listas);
    assert(count + 1 == listas->count);

    listas_destruir(listas);

}

int main() {
    test_definir_lista_exitosa();
    test_definir_lista_fallido();
    printf("Todos los tests de definir_lista pasaron correctamente.\n");
    return 0;
}