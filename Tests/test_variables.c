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

	int idx = listas_buscar_lista(listas, "numeros");
	assert(idx != -1);

	// Intentar redefinir la misma lista
	Lista* l2 = lista_crear();
	strcpy(l2->nombre, "numeros");
	listas_agregar_lista(listas, l2); // debería imprimir error y no insertar
	
	assert(listas->buckets[idx] == l1);



	Lista* l3 = lista_crear();
	strcpy(l3->nombre, "test");
	lista_agregar_valor(l3, 8);

	assert(l3->lista->primero->dato == 8);

	listas_agregar_lista(listas, l3);
	assert(listas->count == 2);

	int idx2 = listas_buscar_lista(listas, "test");
	assert(idx2 != -1);
	assert(strcmp(listas->buckets[idx2]->nombre, "test") == 0);

	

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
	char* nombres_base[] = {"Si", "Di", "Dd", "Sd", "Oi", "Od"};
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
	assert(funciones_buscar_funcion(funciones, "Oi") != -1);
	assert(funciones_buscar_funcion(funciones, "Od") != -1);
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
void test_aplicar_funciones_base(){
	Funciones* funciones = funciones_crear(101);
	Lista* lista = lista_crear();
	lista_agregar_valor(lista, 1);
	lista_agregar_valor(lista, 2);
	lista_agregar_valor(lista, 3);
	


	int idx = funciones_buscar_funcion(funciones, "Od");
	aplicar_funcion_lista(lista, funciones->buckets[idx]);

	assert(lista->lista->ultimo->dato == 0);

	idx = funciones_buscar_funcion(funciones, "Oi");
	aplicar_funcion_lista(lista, funciones->buckets[idx]);

	assert(lista->lista->primero->dato == 0);

	idx = funciones_buscar_funcion(funciones, "Dd");
	aplicar_funcion_lista(lista, funciones->buckets[idx]);
	
	
	assert(lista->lista->ultimo->dato == 3);

	idx = funciones_buscar_funcion(funciones, "Di");
	aplicar_funcion_lista(lista, funciones->buckets[idx]);

	assert(lista->lista->primero->dato == 1);

	idx = funciones_buscar_funcion(funciones, "Si");
	aplicar_funcion_lista(lista, funciones->buckets[idx]);
	aplicar_funcion_lista(lista, funciones->buckets[idx]);
	aplicar_funcion_lista(lista, funciones->buckets[idx]);

	assert(lista->lista->primero->dato == 4);

	idx = funciones_buscar_funcion(funciones, "Sd");
	aplicar_funcion_lista(lista, funciones->buckets[idx]);
	aplicar_funcion_lista(lista, funciones->buckets[idx]);
	aplicar_funcion_lista(lista, funciones->buckets[idx]);

	assert(lista->lista->ultimo->dato == 6);

	funciones_destruir(funciones);
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
	// assert(lista->lista->ultimo->dato == 2);  
	lista_destruir(lista);
	funciones_destruir(funciones);
}
void test_aplicar_funcion_repeticion() {
	Funciones* funciones = funciones_crear(101);
	Lista* lista = lista_crear();
	lista_agregar_valor(lista, 0);
	lista_agregar_valor(lista, 3);

	// repetirá Si hasta que primero == ultimo (es decir, 0 -> 3 con 3 Si)

	char input[512];
	strcpy(input, "deff f2 = <Si>;");
	definir_funcion(input, funciones);
	int idx = funciones_buscar_funcion(funciones, "f2");
	aplicar_funcion_lista(lista, funciones->buckets[idx]);

	assert(lista->lista->primero->dato == lista->lista->ultimo->dato);
	
	// lista = [3,3];

	lista_agregar_valor(lista, 0);
	lista_agregar_valor(lista, 1);
	lista_agregar_valor(lista, 2);
	//lista = [3,3,0,1,2]
	strcpy(input, "deff Mi = Oi <Si> Dd;");

	definir_funcion(input ,funciones);
	idx = funciones_buscar_funcion(funciones, "Mi");
	assert(idx != -1);
	aplicar_funcion_lista(lista, funciones->buckets[idx]);
	// lista = [2,3,3,0,1]
	assert(lista->lista->primero->dato == 2);
	assert(lista->lista->ultimo->dato == 1);


	strcpy(input, "deff DDi = Od <Sd> Mi;");

	definir_funcion(input ,funciones);
	idx = funciones_buscar_funcion(funciones, "DDi");
	aplicar_funcion_lista(lista, funciones->buckets[idx]);

	//lista = [2,2,3,3,0,1]
	assert(lista->lista->primero->dato == 2);
	assert(lista->lista->primero->sig->dato == 2);
	assert(lista->lista->primero->sig->sig->dato == 3);
	assert(lista->lista->ultimo->ant->dato == 0);
	assert(lista->lista->ultimo->dato == 1);


	strcpy(input, "deff Md = Od <Sd> Di;");
	definir_funcion(input, funciones);

	strcpy(input, "deff S5i = Si Si Si Si Si;");
	definir_funcion(input, funciones);	

	idx = funciones_buscar_funcion(funciones, "S5i");
	aplicar_funcion_lista(lista, funciones->buckets[idx]);
	
	assert(lista->lista->primero->dato == 7);

	strcpy(input, "deff 2d1i = <Sd Sd Si>;");
	definir_funcion(input, funciones);
	idx = funciones_buscar_funcion(funciones, "2d1i");
	aplicar_funcion_lista(lista, funciones->buckets[idx]);

	//lista = [13,2,3,3,0,13]
	assert(lista->lista->primero->dato == lista->lista->ultimo->dato);
	assert(lista->lista->primero->dato == 13);

	idx = funciones_buscar_funcion(funciones, "Dd");
	aplicar_funcion_lista(lista, funciones->buckets[idx]);
	idx = funciones_buscar_funcion(funciones, "Di");
	aplicar_funcion_lista(lista, funciones->buckets[idx]);

	//lista = [2,3,3,0]
	assert(lista->lista->ultimo->dato == 0);
	assert(lista->lista->primero->dato == 2);

	strcpy(input,"deff S1 = Md Oi Mi Oi;");
	definir_funcion(input, funciones);

	strcpy(input,"deff S2 = <Si Md Md Si Mi Mi>;");
	definir_funcion(input, funciones);

	strcpy(input,"deff S3 = Dd Di Md;");
	definir_funcion(input, funciones);

	strcpy(input,"deff S = S1 S2 S3;");
	definir_funcion(input, funciones);

	idx = funciones_buscar_funcion(funciones,"S");
	aplicar_funcion_lista(lista, funciones->buckets[idx]);

	assert(lista->lista->ultimo->dato == 2);
	assert(lista->lista->primero->dato == 0);


	//lista = [0,3,3,2]
	lista_agregar_valor(lista, 7);
	lista_agregar_valor(lista, 15);

	idx = funciones_buscar_funcion(funciones,"Mi");
	aplicar_funcion_lista(lista, funciones->buckets[idx]);

	assert(lista->lista->primero->dato == 15);
	assert(lista->lista->ultimo->dato == 7);

	//lista = [15, 0, 3, 3, 2, 7]

	idx = funciones_buscar_funcion(funciones,"S");
	aplicar_funcion_lista(lista, funciones->buckets[idx]);

	assert(lista->lista->ultimo->dato == 15);
	assert(lista->lista->primero->dato == 7);

	lista_destruir(lista);
	funciones_destruir(funciones);

}
void test_lista_copiar() {
	Lista* origen = lista_crear();
	Lista* destino = lista_crear();

	lista_agregar_valor(origen, 10);
	lista_agregar_valor(origen, 20);
	lista_agregar_valor(origen, 30);

	lista_copiar(origen, destino);

	// Verifica que los elementos están en el mismo orden (si usaste agregar_ultimo)
	DNodo* n1 = destino->lista->primero;
	assert(n1 != NULL && n1->dato == 10);

	DNodo* n2 = n1->sig;
	assert(n2 != NULL && n2->dato == 20);

	DNodo* n3 = n2->sig;
	assert(n3 != NULL && n3->dato == 30);

	assert(n3->sig == NULL);

	n1 = origen->lista->primero;
	assert(n1 != NULL && n1->dato == 10);
	assert(n1->sig->dato == 20);
	assert(n1->sig->sig->dato == 30);

	lista_destruir(origen);
	lista_destruir(destino);
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
	test_aplicar_funcion_repeticion();
	test_aplicar_funciones_base();
	// test_lista_copiar();

	//gcc -o test_variables ./test_variables.c ../src/DList/dlist.c ../src/variables.c ../src/operaciones.c ../src/parser.c
	printf("Todos los tests pasaron correctamente\n");
	return 0;
}
