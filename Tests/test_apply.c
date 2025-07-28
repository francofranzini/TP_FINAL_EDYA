
#include "../src/operaciones.h"


void test_validar_input_aplicar() {
  Funciones* funciones = funciones_crear(101);
  Listas* listas = listas_crear(101);

  Funcion* f1 = funcion_crear();
  strcpy(f1->nombre, "f1");
  funciones_agregar_funcion(funciones, f1);

  Funcion* f123 = funcion_crear();
  strcpy(f123->nombre, "f123");
  funciones_agregar_funcion(funciones, f123);

  Funcion* a123 = funcion_crear();
  strcpy(a123->nombre, "a123");
  funciones_agregar_funcion(funciones, a123);

  Lista* l1 = lista_crear();
  strcpy(l1->nombre, "L1");
  listas_agregar_lista(listas, l1);

  Lista* lista45 = lista_crear();
  strcpy(lista45->nombre, "Lista45");
  listas_agregar_lista(listas, lista45);
  Lista* b2 = lista_crear();
  strcpy(b2->nombre, "b2");
  listas_agregar_lista(listas, b2);

  // Casos válidos
  assert(validar_input_aplicar("apply f1 L1;", funciones, listas) == 2);
  assert(validar_input_aplicar("apply f123 Lista45;", funciones, listas) == 2);
  assert(validar_input_aplicar("apply f1 [1,2,3];", funciones, listas) == 1);
  assert(validar_input_aplicar(" apply   f1   [  1 , 2 , 3  ] ; ", funciones, listas) == 1);
  assert(validar_input_aplicar("apply f1 [];", funciones, listas) == 1);
  assert(validar_input_aplicar("apply a123 b2;", funciones, listas) == 2);
  assert(validar_input_aplicar("apply a123 [100];", funciones, listas) == 1);

  // Casos inválidos
  assert(validar_input_aplicar("apply;", funciones, listas) == 0); // Falta todo
  assert(validar_input_aplicar("apply f1;", funciones, listas) == 0); // Falta lista
  assert(validar_input_aplicar("apply f1 [1,];", funciones, listas) == 0); // Coma final
  assert(validar_input_aplicar("apply f1 [-1,2];", funciones, listas) == 0); // Número negativo
  assert(validar_input_aplicar("apply f1 [1 2];", funciones, listas) == 0); // Falta coma
  assert(validar_input_aplicar("apply fx [1,2];", funciones, listas) == 0); // Función no existe
  assert(validar_input_aplicar("apply f1 listax;", funciones, listas) == 0); // Lista no existe
  assert(validar_input_aplicar("apply f1 [1,,2];", funciones, listas) == 0); // Coma doble

  listas_destruir(listas);
  funciones_destruir(funciones);
}
void test_lista_desde_buffer_simple() {
    Lista* lista = lista_crear();
    char buffer[512];
    strcpy(buffer,"apply f5 [1,2,3];");
    extraer_valores_lista(buffer, lista);

    DNodo* nodo = lista->lista->primero;
    assert(nodo != NULL && nodo->dato == 1);
    nodo = nodo->sig;
    assert(nodo != NULL && nodo->dato == 2);
    nodo = nodo->sig;
    assert(nodo != NULL && nodo->dato == 3);
    nodo = nodo->sig;
    assert(nodo == NULL);
    lista_destruir(lista);

    lista = lista_crear();
    strcpy(buffer,"apply f7 [];");
    extraer_valores_lista(buffer, lista);
    assert(lista->lista->primero == NULL); // Lista vacía
    lista_destruir(lista);

    lista = lista_crear();
    strcpy(buffer,"apply f7 [111, 222, 444];");
    extraer_valores_lista(buffer, lista);
    assert(lista->lista->primero->dato == 111);
    assert(lista->lista->ultimo->dato == 444);

    lista_destruir(lista);
}
void test_extraer_nombre_funcion() {
    char buffer[512];
    strcpy(buffer, "apply f1 [1,2,3];");
    char nombre_funcion[32];
    extraer_nombre_funcion(buffer, nombre_funcion);
    assert(strcmp(nombre_funcion, "f1") == 0);

    strcpy(buffer, "apply otraFuncion [4,5];");
    extraer_nombre_funcion(buffer, nombre_funcion);
    assert(strcmp(nombre_funcion, "otraFuncion") == 0);

    strcpy(buffer, "apply f123 [6];");
    extraer_nombre_funcion(buffer, nombre_funcion);
    assert(strcmp(nombre_funcion, "f123") == 0);
}
void test_extraer_nombre_lista() {
    char buffer[512];
    strcpy(buffer, "apply f1 L1;");
    char nombre_lista[32];
    extraer_nombre_lista(buffer, nombre_lista);
    assert(strcmp(nombre_lista, "L1") == 0);

    strcpy(buffer, "apply otraLista L5;");
    extraer_nombre_lista(buffer, nombre_lista);
    assert(strcmp(nombre_lista, "L5") == 0);

    strcpy(buffer, "apply lista123 L9;");
    extraer_nombre_lista(buffer, nombre_lista);
    assert(strcmp(nombre_lista, "L9") == 0);
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
	

  int overflow = 0;
	int idx = funciones_buscar_funcion(funciones, "Od");
	aplicar_funcion_lista(lista, funciones->buckets[idx], &overflow);

	assert(lista->lista->ultimo->dato == 0);

	idx = funciones_buscar_funcion(funciones, "Oi");
	aplicar_funcion_lista(lista, funciones->buckets[idx], &overflow);

	assert(lista->lista->primero->dato == 0);

	idx = funciones_buscar_funcion(funciones, "Dd");
	aplicar_funcion_lista(lista, funciones->buckets[idx], &overflow);
	
	
	assert(lista->lista->ultimo->dato == 3);

	idx = funciones_buscar_funcion(funciones, "Di");
	aplicar_funcion_lista(lista, funciones->buckets[idx], &overflow);

	assert(lista->lista->primero->dato == 1);

	idx = funciones_buscar_funcion(funciones, "Si");
	aplicar_funcion_lista(lista, funciones->buckets[idx], &overflow);
	aplicar_funcion_lista(lista, funciones->buckets[idx], &overflow);
	aplicar_funcion_lista(lista, funciones->buckets[idx], &overflow);

	assert(lista->lista->primero->dato == 4);

	idx = funciones_buscar_funcion(funciones, "Sd");
	aplicar_funcion_lista(lista, funciones->buckets[idx], &overflow);
	aplicar_funcion_lista(lista, funciones->buckets[idx], &overflow);
	aplicar_funcion_lista(lista, funciones->buckets[idx], &overflow);

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

  int overflow = 0;

	int idx = funciones_buscar_funcion(funciones, "sumar6");
	assert(idx != -1);

	aplicar_funcion_lista(lista, funciones->buckets[idx], &overflow);

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

  int overflow = 0;

	aplicar_funcion_lista(lista, funciones->buckets[idx], &overflow);

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
	aplicar_funcion_lista(lista, funciones->buckets[idx], &overflow);
	// lista = [2,3,3,0,1]
	assert(lista->lista->primero->dato == 2);
	assert(lista->lista->ultimo->dato == 1);


	strcpy(input, "deff DDi = Od <Sd> Mi;");

	definir_funcion(input ,funciones);
	idx = funciones_buscar_funcion(funciones, "DDi");
	aplicar_funcion_lista(lista, funciones->buckets[idx], &overflow);

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
	aplicar_funcion_lista(lista, funciones->buckets[idx], &overflow);
	
	assert(lista->lista->primero->dato == 7);

	strcpy(input, "deff 2d1i = <Sd Sd Si>;");
	definir_funcion(input, funciones);
	idx = funciones_buscar_funcion(funciones, "2d1i");
	aplicar_funcion_lista(lista, funciones->buckets[idx], &overflow);

	//lista = [13,2,3,3,0,13]
	assert(lista->lista->primero->dato == lista->lista->ultimo->dato);
	assert(lista->lista->primero->dato == 13);

	idx = funciones_buscar_funcion(funciones, "Dd");
	aplicar_funcion_lista(lista, funciones->buckets[idx], &overflow);
	idx = funciones_buscar_funcion(funciones, "Di");
	aplicar_funcion_lista(lista, funciones->buckets[idx], &overflow);

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
	aplicar_funcion_lista(lista, funciones->buckets[idx], &overflow);

	assert(lista->lista->ultimo->dato == 2);
	assert(lista->lista->primero->dato == 0);


	//lista = [0,3,3,2]
	lista_agregar_valor(lista, 7);
	lista_agregar_valor(lista, 15);

	idx = funciones_buscar_funcion(funciones,"Mi");
	aplicar_funcion_lista(lista, funciones->buckets[idx], &overflow);

	assert(lista->lista->primero->dato == 15);
	assert(lista->lista->ultimo->dato == 7);

	//lista = [15, 0, 3, 3, 2, 7]

	idx = funciones_buscar_funcion(funciones,"S");
	aplicar_funcion_lista(lista, funciones->buckets[idx], &overflow);

	assert(lista->lista->ultimo->dato == 15);
	assert(lista->lista->primero->dato == 7);
  assert(overflow == 0); // No hubo overflow

	lista_destruir(lista);
	funciones_destruir(funciones);

}
void test_aplicar_funcion_overflow() {
  Funciones* funciones = funciones_crear(101);
  Lista* lista = lista_crear();
  lista_agregar_valor(lista, 1);
  lista_agregar_valor(lista, 2);


  char input[512];
  strcpy(input,"deff f1 = <Si Sd>;");
  definir_funcion(input, funciones);

  int overflow = 0;
  int idx = funciones_buscar_funcion(funciones, "f1");
  aplicar_funcion_lista(lista, funciones->buckets[idx], &overflow);

  assert(overflow == 1);

  funciones_destruir(funciones);
  lista_destruir(lista);
}

int main() {
    test_validar_input_aplicar();
    test_lista_desde_buffer_simple();
    test_extraer_nombre_funcion();
    test_extraer_nombre_lista();
    test_termina_repeticion();
    test_aplicar_funciones_base();
    test_aplicar_funcion_simple();
    test_aplicar_funcion_repeticion();
    test_aplicar_funcion_overflow();
    // gcc -o test_apply ./test_apply.c ../src/apply.c ../src/variables.c ../src/DList/dlist.c ../src/deff.c ../src/defl.c ../src/operaciones.c ../src/parser.c ../src/search.c
    printf("Todos los tests de apply pasaron correctamente.\n");
    return 0;
}