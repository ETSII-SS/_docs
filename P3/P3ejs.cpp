MUY IMPORTANTE: No añadir este directamente a ningún proyecto. Copiar siempre los trozos de código 
        que se indican en cada ejercicio a archivos ya existentes. 
		
		
		
		
// Copiar esto dentro de la función main, tras setlocale...
setlocale(LC_ALL, "Spanish");
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
 // <- Hasta aquí ejercicio 3.1




// Ej 3.6
ss::Dbg dbg(true);

// Imprime los archivos del directorio que se pasa como argumento
dbg.ArchivosEnDirectorio(argv[1]);






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