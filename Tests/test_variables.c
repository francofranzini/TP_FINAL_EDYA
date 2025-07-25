#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../src/variables.h" 



void test_lista_crear_y_agregar() {
	Lista* l = lista_crear();
	assert(l != NULL);
	assert(dlist_vacia(l->lista));

	lista_agregar_valor(l, 10);
	lista_agregar_valor(l, 20);
	lista_agregar_valor(l, 30);

	assert(l->lista->primero->sig->sig->dato == 30);

	lista_destruir(l);
}

void test_listas_agregar_y_buscar() {
	Listas* listas = listas_crear(17);  // número primo
	assert(listas->size == 17);

	Lista* l1 = lista_crear();
	strcpy(l1->nombre, "numeros");
	lista_agregar_valor(l1, 5);

	assert(l1->lista->primero->dato == 5);

	listas_agregar_lista(listas, l1);

	assert(listas->count == 1);


	// Aseguramos que se insertó
	unsigned k1 = listas->hash_function1(l1->nombre) % listas->size;
	unsigned k2 = 1 + (listas->hash_function2(l1->nombre) % (listas->size - 1));
	int i = 0;
	unsigned idx = (k1 + i*k2) % listas->size;
	while (i < listas->size) {
			idx = (k1 + i * k2) % listas->size;
			if (listas->buckets[idx] && strcmp(listas->buckets[idx]->nombre, "numeros") == 0) {
					break;
			}
			i++;
	}
	assert(i < listas->size); 

	// Intentar redefinir la misma lista
	Lista* l2 = lista_crear();
	strcpy(l2->nombre, "numeros");
	listas_agregar_lista(listas, l2); // debería imprimir error y no insertar
	
	assert(listas->buckets[idx] == l1);

	lista_destruir(l2);
	listas_destruir(listas);
}

void test_funciones_crear(){
	Funciones* funciones = funciones_crear(101);
	assert(funciones->hash_function1 != NULL);
	assert(funciones->hash_function2 != NULL);
	assert(funciones->count == 0);
	assert(funciones->load_factor == 0.0);
	
	funciones_destruir(funciones);
}
void test_funcion_crear(){
	Funcion* funcion = funcion_crear();
	strcpy(funcion->nombre, "Si");
	for(int i = 0; i<20; i++) assert(funcion->pasos[i] == NULL);
	assert(funcion->pasos_cantidad == 0);
	assert(strcmp(funcion->nombre, "Si") == 0);
	funcion_destruir(funcion);

	funcion
}

int main() {
	test_lista_crear_y_agregar();
	test_listas_agregar_y_buscar();
	test_funciones_crear();
	test_funcion_crear();

	printf("Todos los tests pasaron correctamente\n");
	return 0;
}
