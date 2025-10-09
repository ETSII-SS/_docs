MUY IMPORTANTE: No añadir este directamente a ningún proyecto. Copiar siempre los trozos de código 
        que se indican en cada ejercicio a archivos ya existentes. 
		
// Ejemplo union real: https://github.com/cnoviello/mastering-stm32/blob/master/nucleo-f446RE/system/include/cmsis/core_cm7.h?utm_source=chatgpt.com#L323



// ============================================================================
// Ejemplos de distintas formas de definir estructuras (struct) en C y C++
// Software de Sistemas – Práctica 2
// ============================================================================

// ---------------------------------------------------------------------------
// 1. Definición clásica con nombre explícito
// ---------------------------------------------------------------------------
struct Persona {
    int edad;
    char nombre[20];
};

void ejemplo1() {
    struct Persona p1, *pp;        // En C: hay que escribir 'struct Persona'
    p1.edad = 25;
    strcpy(p1.nombre, "Ana");
	pp= &p1;
    printf("Edad: %d, Nombre: %s\n", p1.edad, p1.nombre);
	printf("Edad: %d, Nombre: %s   (usando puntero)\n", pp->edad, pp->nombre);
}

// ---------------------------------------------------------------------------
// 2. Definición + declaración de variables en una sola instrucción
// ---------------------------------------------------------------------------
struct Punto {
    int x;
    int y;
} p1, p2;    // Se define el tipo y dos variables de ese tipo

void ejemplo2() {
    p1.x = 10;  p1.y = 20;
    printf("(%d, %d)\n", p1.x, p1.y);
	struct Punto *ppunto= &p1;
    printf("(%d, %d)\n", ppunto->x, ppunto->y);	
}

// ---------------------------------------------------------------------------
// 3. Estructura anónima (sin nombre de tipo)
// ---------------------------------------------------------------------------
struct {
    int codigo;
    float precio;
} producto1, producto2;    // No se puede reutilizar este tipo

void ejemplo3() {
    producto1.codigo = 101;
    producto1.precio = 9.99f;
    printf("Producto: %d, Precio: %.2f\n", producto1.codigo, producto1.precio);
}

// ---------------------------------------------------------------------------
// 4. Definición con typedef (forma más usada en C)
// ---------------------------------------------------------------------------
typedef struct {
    int dia;
    int mes;
    int año;
} Fecha_t;     // El alias Fecha_t puede usarse directamente sin 'struct'

void ejemplo4() {
    Fecha_t hoy = {6, 10, 2025};
    printf("Fecha: %02d/%02d/%04d\n", hoy.dia, hoy.mes, hoy.año);
}

// ---------------------------------------------------------------------------
// 5. Definición con typedef y nombre estructural
// ---------------------------------------------------------------------------
typedef struct Fecha {
    int dia;
    int mes;
    int año;
} Fecha2_t;

void ejemplo5() {
    struct Fecha f1 = {1, 1, 2024};  // Se puede usar antes del typedef
    Fecha2_t f2 = {6, 10, 2025};     // O usar el alias directamente
    printf("f1: %d/%d/%d  f2: %d/%d/%d\n",
        f1.dia, f1.mes, f1.año, f2.dia, f2.mes, f2.año);
}

// ---------------------------------------------------------------------------
// 6. Definición con typedef y puntero al tipo
// ---------------------------------------------------------------------------
typedef struct {
    int x;
    int y;
} Punto_t, *pPunto_t;    // Define tipo y puntero al tipo

void ejemplo6() {
    Punto_t a = {5, 7};
    pPunto_t ptr = &a;
    printf("Punto: (%d,%d)\n", ptr->x, ptr->y);
}

// ---------------------------------------------------------------------------
// 7. Estructura anidada (struct dentro de struct)
// ---------------------------------------------------------------------------
typedef struct {
    char nombre[20];
    struct {
        int dia, mes, año;
    } nacimiento;   // Estructura interna sin nombre
} Persona_t;

void ejemplo7() {
    Persona_t p = {"Luis", {6, 10, 2025}};
    printf("%s nació el %d/%d/%d\n",
           p.nombre, p.nacimiento.dia, p.nacimiento.mes, p.nacimiento.año);
}

// ---------------------------------------------------------------------------
// 8. En C++: struct con métodos (equivalente a class con miembros públicos)
// ---------------------------------------------------------------------------
// NOTA: Este bloque solo compila como C++ (no en C puro)
#ifdef __cplusplus
struct PuntoConMetodo {
    int x, y;
    void Muestra() {
        printf("(%d, %d)\n", x, y);
    }
};
void ejemplo8() {
    PuntoConMetodo p = {3, 4};
    p.Muestra();
}
#endif

// ---------------------------------------------------------------------------
// 9. Estructura autoreferenciada (lista enlazada)
// ---------------------------------------------------------------------------
typedef struct Nodo {
    int dato;
    struct Nodo *siguiente;   // Puntero a otra estructura del mismo tipo
} Nodo_t;

void ejemplo9() {
    Nodo_t n1 = {1, NULL};
    Nodo_t n2 = {2, NULL};
    n1.siguiente = &n2;
    printf("n1=%d, siguiente=%d\n", n1.dato, n1.siguiente->dato);
}

// ---------------------------------------------------------------------------
// 10. Con alineamiento o empaquetado explícito (avanzado)
// ---------------------------------------------------------------------------
#pragma pack(push, 1)  // Empaquetar sin relleno (alineación 1 byte)
typedef struct {
    char c;
    int i;
} Empaquetado_t;
#pragma pack(pop)

void ejemplo10() {
    Empaquetado_t e = {'A', 12345};
    printf("Tamaño de Empaquetado_t = %zu bytes\n", sizeof(Empaquetado_t));
}

// ---------------------------------------------------------------------------
// FIN DE EJEMPLOS
// ---------------------------------------------------------------------------
int main() {
    ejemplo1();
    ejemplo2();
    ejemplo3();
    ejemplo4();
    ejemplo5();
    ejemplo6();
    ejemplo7();
#ifdef __cplusplus
    ejemplo8();
#endif
    ejemplo9();
    ejemplo10();
    return 0;
}
