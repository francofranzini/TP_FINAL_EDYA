#include "../src/parser.h"

void test_validar_largo_input() {
    char corto[] = "defl lista = [1,2,3];\n";
    char largo[600];
    memset(largo, 'a', 599);
    largo[599] = '\0';

    assert(validar_largo_input(corto) == 1);   // contiene '\n'
    assert(validar_largo_input(largo) == 0);   // no contiene '\n'
}

void test_recibir_input() {
    char s[512];
    strncpy(s, "defl L1 = ...\0", 512);
    assert(interpretar_operacion(s) == DEFL);
    strncpy(s, "deff suma = ...\0", 512);
    assert(interpretar_operacion(s) == DEFF);
    strncpy(s, "apply suma lista \0", 512);
    assert(interpretar_operacion(s) == APPLY);
    strncpy(s, "search lista valor\0", 512);
    assert(interpretar_operacion(s) == SEARCH);
    strncpy(s, "otra cosa \0", 512);
    assert(interpretar_operacion(s) == FINISH);
}

void test_validar_input_lista() {
    // Casos válidos
    assert(validar_input_lista("defl lista = [1];") == 1);
    assert(validar_input_lista("defl L123 = [1, 2, 3];") == 1);
    assert(validar_input_lista("defl x = [42];") == 1);
    assert(validar_input_lista("defl abc = [1 ,2 ,3];") == 1);
    assert(validar_input_lista("defl L1 = [];") == 1);

    // Casos inválidos
    assert(validar_input_lista("def lista = [1];") == 0);               // comando mal
    assert(validar_input_lista("defl = [1,2,3];") == 0);                // falta nombre
    assert(validar_input_lista("defl lista = [1,2,];") == 0);           // coma colgante
    assert(validar_input_lista("defl lista [1,2,3];") == 0);            // falta '='
    assert(validar_input_lista("defl lista = 1,2,3;") == 0);            // sin corchetes
    assert(validar_input_lista("defl lista = [1 2 3];") == 0);          // sin comas
    assert(validar_input_lista("defl lista = [1,2,3]") == 0);           // sin ;
    assert(validar_input_lista("defl 1lista = [1,2,3];") == 0);         // nombre inválido
    assert(validar_input_lista("defl lista = [abc];") == 0);           // elementos no numéricos
}

void test_asignar_input_lista() {
    HashEntry* bucket = hash_entry_crear();
    char input[] = "defl lista = [1, 2, 3];";
    asignar_input_lista(input, bucket);

    assert(strcmp(bucket->key, "lista") == 0);
    assert(bucket->value != NULL);
    assert(!dlist_vacia(bucket->value));
    
    // Verificar los valores en la lista
    DNodo* nodo = bucket->value->primero;
    assert(nodo != NULL);
    assert(nodo->dato == 1);
    
    nodo = nodo->sig;
    assert(nodo != NULL);
    assert(nodo->dato == 2);
    
    nodo = nodo->sig;
    assert(nodo != NULL);
    assert(nodo->dato == 3);
    
    nodo = nodo->sig;
    assert(nodo == NULL); // Fin de la lista
    
    
    hash_entry_destruir(bucket);
    
}

int main() {
    test_validar_largo_input();
    test_recibir_input();
    test_validar_input_lista();
    test_asignar_input_lista();


    printf("Todos los tests de parser pasaron correctamente.\n");
    return 0;
}