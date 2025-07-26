#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../src/variables.h"
#include "../src/operaciones.h"



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
	assert(funciones->count == 6);
	// assert(funciones->load_factor == 6.0/101.0);
	// Verificar que las funciones base se hayan agregado
	char* nombres_base[] = {"Si", "Di", "Dd", "Sd", "0i", "0d"};
	for (int i = 0; i < 6; i++) {
		unsigned k1 = funciones->hash_function1(nombres_base[i]) % funciones->size;
		unsigned k2 = 1 + (funciones->hash_function2(nombres_base[i]) % (funciones->size - 1));
		int j = 0;
		while (j < funciones->size) {
			unsigned idx = (k1 + j * k2) % funciones->size;
			if (funciones->buckets[idx] && strcmp(funciones->buckets[idx]->nombre, nombres_base[i]) == 0) {
				break;
			}
			j++;
		}
		assert(j < funciones->size); // Debe encontrar la función base
	}
	
	funciones_destruir(funciones);
}
void test_funcion_crear(){
	Funcion* funcion = funcion_crear();
	strcpy(funcion->nombre, "Si");
	for(int i = 0; i<20; i++) assert(funcion->pasos[i] == NULL);
	assert(funcion->pasos_cantidad == 0);
	assert(strcmp(funcion->nombre, "Si") == 0);
	funcion_destruir(funcion);
}
void test_funciones_buscar(){
	Funciones* funciones = funciones_crear(101);

	assert(funciones_buscar_funcion(funciones, "Si") != -1);
	assert(funciones_buscar_funcion(funciones, "Di") != -1);
	assert(funciones_buscar_funcion(funciones, "0i") != -1);
	assert(funciones_buscar_funcion(funciones, "0d") != -1);
	assert(funciones_buscar_funcion(funciones, "Dd") != -1);

	assert(funciones_buscar_funcion(funciones, "f1") == -1);
	assert(funciones_buscar_funcion(funciones, "f2") == -1);
	assert(funciones_buscar_funcion(funciones, "f3") == -1);
	assert(funciones_buscar_funcion(funciones, "f6") == -1);


	funciones_destruir(funciones);
}
void test_funciones_agregar_y_buscar(){
	Funciones* funciones = funciones_crear(17);  // número primo
	assert(funciones->size == 17);

	Funcion* f1 = funcion_crear();
	strcpy(f1->nombre, "suma");
	funciones_agregar_funcion(funciones, f1);
	assert(funciones->count == 7);

	// Aseguramos que se insertó
	unsigned k1 = funciones->hash_function1(f1->nombre) % funciones->size;
	unsigned k2 = 1 + (funciones->hash_function2(f1->nombre) % (funciones->size - 1));
	int i = 0;
	unsigned idx = (k1 + i*k2) % funciones->size;
	while (i < funciones->size) {
			idx = (k1 + i * k2) % funciones->size;
			if (funciones->buckets[idx] && strcmp(funciones->buckets[idx]->nombre, "suma") == 0) {
					break;
			}
			i++;
	}
	assert(i < funciones->size); 

	// Intentar redefinir la misma función
	Funcion* f2 = funcion_crear();
	strcpy(f2->nombre, "suma");
	funciones_agregar_funcion(funciones, f2); //No inserta
	assert(funciones->buckets[idx] == f1);

	funcion_destruir(f2);
	funciones_destruir(funciones);
}
void test_funcion_agregar(){
	Funcion* funcion = funcion_crear();

	Funcion* funcion_base = funcion_crear();
	
	strcpy(funcion_base->nombre, "Si");

	funcion_agregar_funcion(funcion, funcion_base);
	assert(funcion->pasos_cantidad == 1);
	assert(strcmp(funcion->pasos[0]->nombre, "Si") == 0);
	funcion_destruir(funcion_base);
	funcion_destruir(funcion);

}
void test_termina_repeticion() {
	Lista* lista = lista_crear();
	lista_agregar_valor(lista, 3);
	lista_agregar_valor(lista, 3);
	assert(termina_repeticion(lista));
	dlist_sumar_primero(lista->lista); // ahora son 4 y 3
	assert(!termina_repeticion(lista));
	lista_destruir(lista);
}

void test_aplicar_funcion_simple() {
	Funciones* funciones = funciones_crear(101);
	Lista* lista = lista_crear();
	lista_agregar_valor(lista, 1);

	char input[512];
	strcpy(input,"deff sumar3 = Si Si Si;");

	definir_funcion(input, funciones);

	strcpy(input,"deff sumar6 = sumar3 sumar3;");

	definir_funcion(input, funciones);



	int idx = funciones_buscar_funcion(funciones, "sumar6");
	assert(idx != -1);

	aplicar_funcion_lista(lista, funciones->buckets[idx]);

	assert(lista->lista->primero->dato == 7); // 
	// assert(lista->lista->ultimo->dato == 2);  // 1 + 1 (Sd)
	lista_destruir(lista);
	funciones_destruir(funciones);
}
void test_aplicar_funcion_repeticion() {
  Funciones* funciones = funciones_crear(101);
  Lista* lista = lista_crear();
  lista_agregar_valor(lista, 0);
  lista_agregar_valor(lista, 3);

  // repetirá Si hasta que primero == ultimo (es decir, 0 -> 3 con 3 Si)
  char input[] = "deff f2 = <Si>;";
  definir_funcion(input, funciones);
  int idx = funciones_buscar_funcion(funciones, "f2");
  aplicar_funcion_lista(lista, funciones->buckets[idx]);

  assert(lista->lista->primero->dato == lista->lista->ultimo->dato);
  lista_destruir(lista);
  funciones_destruir(funciones);
}

int main() {
	test_lista_crear_y_agregar();
	test_listas_agregar_y_buscar();
	test_funciones_crear();
	test_funcion_crear();
	test_funciones_agregar_y_buscar();
	test_funciones_crear();
	test_funciones_buscar();
	test_funcion_agregar();
	test_termina_repeticion();
	test_aplicar_funcion_simple();

	//gcc -o test_variables ./test_variables.c ../src/DList/dlist.c ../src/variables.c ../src/operaciones.c ../src/parser.c
	printf("Todos los tests pasaron correctamente\n");
	return 0;
}
