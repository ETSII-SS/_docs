MUY IMPORTANTE: No añadir este directamente a ningún proyecto. Copiar siempre los trozos de código 
        que se indican en cada ejercicio a archivos ya existentes. 
		
		
		
		
// Copiar esto dentro de la función main, tras setlocale...
// Un experimento con estructuras y uniones
struct {
	int entero;
	char car;
} vEstructura = { 256, 1 }; // Define + inicializa la estructura
union {
	int entero;
	char car;
}  vUnion= { 256}; // Define + inicializa la unión

vUnion.car= 1;
printf("Estructura: %d Tam: %d\n", vEstructura.entero, sizeof(vEstructura));
printf("Union: %d Tam: %d\n", vUnion.entero, sizeof(vUnion));


 // <- Hasta aquí ejercicio 2.1




vUnion.entero = 0x89abcdef; // byte 0: 0xef, byte 1: 0xcd, byte 2: 0xab, byte 3: 0x89
printf("vUnion.entero vale 0x%x\n", vUnion.entero);
printf("El valor del byte 2 de vUnion.entero es: 0x%x\n", 
	???);  // sustituir ??? por la xpresión que calcula el byte 2 de vUnion.entero 






CronoInicio();
Sleep(1200);
double segs = CronoLee();
printf("Han pasado %f segundos.\n", segs);





typedef struct {
	int entero;
	char car;
} tEstructura_t;
tEstructura_t var1 = { 100, 1 };
tEstructura_t var2 = { 100, 1 };
int main(int argc, char* argv[], char* envp[])
{
	tEstructura_t var3 = { 100, 1 };
	int comparacion = memcmp(&var1, &var2, sizeof(tEstructura_t));
	printf("resultado de comparar var1 y var2: %d\n", comparacion);
	comparacion= memcmp(&var1, &var3, sizeof(tEstructura_t));
	printf("resultado de comparar var1 y var3: %d\n", comparacion);
	
	
	
	
	
// Declaraciones asociadas a una clase.
// Namespace: agrupación de clases, funciones y variables globales
namespace ss {
	
	class Crono {	// Declaración de la clase Crono

	private:	//opcional. por defecto todo es privad

	public:
		Crono();  // Constructor (opcional)
		~Crono(); // Destructor (opcional)
		
	}; // fin clase
	
	
} // fin namespace ss

// Definiciones asociadas a una clase.
namespace ss {  // Namespace: agrupación de clases, funciones y variables globales

	// Definición del constructor
	Crono::Crono()
	{
	}
	// Definición del destructor
	Crono::~Crono()
	{
	}

} // fin namespace ss

void TestClase() {
	ss::Crono crono;
	crono.Inicio();
	Sleep(1200);
	double segs = crono.Lee();
	printf("Han pasado %f segundos.\n", segs);
}



/// En Java, la prueba básica de una clase similar a Crono sería
Crono crono= new Dbg();  
crono.Inicio();
Thread.sleep(1200); // Espera 1200 ms. En C-Windows usaríamos Sleep(1200)
float segs= crono.Lee();
System.out.printf("El tiempo transcurrido %f segs\n", segs);




void TestParametros(int valor, int par1, int par2[], Struct1_t par3, Union1_t par4, Clase1 par5) {
	par1 = par2[0]= par3.entero= par4.entero= par5.entero= valor;
}


// Copiar esto a la función main
TestParametros(10, var1, var2, var3, var4, var5);
printf("Valores tras la llamada printf: var1=%d, var2[0]=%d, var3.entero=%d, var4.entero=%d, var5.entero=%d\n",
	var1, var2[0], var3.entero, var4.entero, var5.entero);


