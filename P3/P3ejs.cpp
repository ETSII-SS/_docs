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

ss::Dbg dbg(true);
dbg.CronoInicio();
Sleep(1200); // Espera 1.2 segundos
dbg.CronoFin();
dbg.Print("Tiempo transcurrido: %f segundos\n", dbg.CronoSegs);

path ruta(argv[0]);  // NO comentar esta línea
 // <- Hasta aquí ejercicio 3.1




vUnion.entero = 0x89abcdef; // byte 0: 0xef, byte 1: 0xcd, byte 2: 0xab, byte 3: 0x89
printf("vUnion.entero vale 0x%x\n", vUnion.entero);
printf("El valor del byte 2 de vUnion.entero es: 0x%x\n", 
	???);  // sustituir ??? por la xpresión que calcula el byte 2 de vUnion.entero 








// Ej 3.14
ss::Dbg dbg(true);

// Imprime los archivos del directorio que se pasa como argumento
dbg.ArchivosEnDirectorio(argv[1]);






// Los parámetros de llamada a CompruebaSolucion son:
// * su UVUS
// * nro de práctica, 
// * nombre programa visual studio: poner $(DevEnvDir)$(VSAPPIDNAME) como 
//              argumento de programa en las propiedades del depurador
auto res = dbg.CompruebaSolucion(argv[1], argv[2], argv[3]);





uintmax_t Dbg::CalculaTam(const char* nombreArchivoODir)
{
	auto ruta = path(nombreArchivoODir);
	intmax_t res = -1;
	if (!exists(ruta))
	{
		Print("La ruta %s es de un archivo o directorio que no existe\n", ruta);
	}
	else if (is_regular_file(ruta))
	{
		res= file_size(ruta);
	}
	return res;
}

	uintmax_t CalculaTam(const char* ruta);



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
