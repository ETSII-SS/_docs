MUY IMPORTANTE: No añadir este directamente a ningún proyecto. Copiar siempre los trozos de código 
        que se indican en cada ejercicio a archivos ya existentes. 
		
		

// Copiar esto dentro de la función main, tras setlocale...

// Clases declaradas en SSLib. Hay que incluir sslib/SSLib.h
Dbg dbg(true);
FileSys fs;
// Para depurar este programa, poner . en Propiedades del proyecto->Depurar->Directorio de trabajo
const char* pDir = argv[1];		//Nombre del directorio a procesar
// comprueba si el directorio existe
dbg.CheckError(argc < 2, 1, "Debe indicar el nombre del directorio a procesar");
DWORD atributos = GetFileAttributesA(argv[1]);
dbg.CheckError(atributos == INVALID_FILE_ATTRIBUTES, 2, "No se ha dado un nombre de directorio correcto: %s", argv[1]);
dbg.CheckError((atributos & FILE_ATTRIBUTE_DIRECTORY) == 0, 3, "No es un directorio: %s", argv[1]);

// Obtiene la lista de archivos en el directorio
int encontrados;
char** plistaArchivos;  // Este tipo se puede usar como dirección de una matriz de punteros a char. 
// Es similar a char* envp[], pero esa nomenclatura NO se puede usar en una definición de variable.

plistaArchivos = fs.ArchivosEnDirectorio(&encontrados, pDir);
dbg.CheckError(plistaArchivos == nullptr, 4, "No se han encontrado archivos en la carpeta %s\n", pDir);

printf("Se han encontrado %d archivos en la carpeta %s\n", encontrados, pDir);












static void ImprimeArchivosEnDirectorio(char* listaArchivos[]) {
	int i = 0;
	// Imprime la lista de archivos mientras no se encuentre un puntero nulo
	while (listaArchivos[i] = nullptr)
	{
		printf("#%d: %s\n", i, listaArchivos[i]);
		i++;
	}
}


// Sesión 2
//Ejercicio inicial: 

using namespace std;
static size_t tamAcumulado = 0;
static size_t CalculaBytesEnArchivos(char* listaArchivos[], int nroArchivos) {
	size_t total = 0;
	int i = 0;
	WIN32_FILE_ATTRIBUTE_DATA info;
	for (i = 0; i < nroArchivos; i++) {
		if (dbg.CheckError(FALSE ==
			GetFileAttributesExA(listaArchivos[i], GetFileExInfoStandard, &info),
			"Error en GetFileAttributesExA para el archivo %s\n", listaArchivos[i]))
			continue;  // Salta a la siguiente iteración del bucle si hay error
		int64_t tam = ((int64_t)info.nFileSizeHigh << 32) + info.nFileSizeLow;
		total += tam;
	}
	return total;
}
static size_t CalculaBytesEnArchivosConVariosHilos(
	char* ruta, unsigned int hilosAdicionales, bool usaUltimaBusqueda) {
	static FileSys fs;
	static char** plistaArchivos = nullptr;
	static int encontrados = 0;
	if (!usaUltimaBusqueda || plistaArchivos == nullptr) {
		plistaArchivos = fs.ArchivosEnDirectorio(&encontrados, ruta, false);
		printf("\t\tLa búsqueda de archivos ha tardado %f segs\n", fs.TiempoUltimoMetodo());
	}
	if (!MuestraNroArchivosEncontradosEnDirectorio(encontrados, ruta))
		return 0;
	dbg.CronoInicio();
	size_t tamTotal = 0;
	tamTotal = CalculaBytesEnArchivos(plistaArchivos, encontrados);
	auto segs = dbg.CronoLee();
	printf("\tCalculados %lld bytes\n", tamTotal);
	printf("\t\tCalculado en: %f segs por %s (%d hilos adicionales).\n\n", segs, __FUNCTION__, hilosAdicionales);
	return tamTotal;
}
















	if (hilosAdicionales == 0) 
		tamTotal = CalculaBytesEnArchivos(plistaArchivos, encontrados); // Ejecución síncrona
	else { // Aquí irá la ejecución asíncrona.
		tamTotal = BytesEnArchivosHilo(plistaArchivos, encontrados); 
	}





















if (hilosAdicionales == 0) 
		tamTotal = CalculaBytesEnArchivos(plistaArchivos, encontrados); // Ejecución síncrona
	else { // Ejecución asíncrona.
		thread* hilos = new thread[hilosAdicionales]; // reserva memoria para la matriz de hilos
		for (int i = 0; i < hilosAdicionales; i++) {
			hilos[i] = thread(BytesEnArchivosHilo, plistaArchivos, encontrados);
			_dbg.CheckError(hilos[i].native_handle() == NULL, "no se pudo crear hilo");
		}
		delete[] hilos;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	static int BuscaTextoEnArchivos(const char* dirBusqueda, const char* textoABuscar) {
	Dbg dbg;
	FileSys fs;
	int ocurrencias, encontrados = 0, nroArchivos, idxMarca = 0;
	char** listaArchivos = fs.ArchivosEnDirectorio(&nroArchivos, dirBusqueda, false);
	if (dbg.CheckError(listaArchivos == nullptr, "No se han encontrado archivos en la carpeta %s\n", dirBusqueda)) {
		return -1;
	}
	char marcasAvance[] = "-\\|/"; // Para animación simple
	size_t bytesTotal, bytesAcumulados = 0;
	bytesTotal = CalculaBytesEnArchivos(listaArchivos, nroArchivos);
	if (dbg.CheckError(bytesTotal == 0, "No se han encontrado archivos en la carpeta %s\n", dirBusqueda)) {
		return -1;
	}
	MuestraNroArchivosEncontradosEnDirectorio(nroArchivos, (char*)dirBusqueda);
	printf("\nBuscando texto \"%s\" en %lld bytes\n", textoABuscar, bytesTotal);

	dbg.CronoInicio();
	for (int i = 0; i < nroArchivos; i++) {
		// Busca el texto en el archivo usando un método de FileSys
		ocurrencias = fs.BuscaDatoEnArchivo(textoABuscar, strlen(textoABuscar),
			listaArchivos[i], &bytesAcumulados, 10000);
		if (ocurrencias > 0) {
			encontrados++;
			dbg.DbgPrint("#%d: %d ocurrencias en %s\n", encontrados, ocurrencias, listaArchivos[i]);
		}
		else if (ocurrencias < 0) {
			dbg.DbgPrint("Error %s\n", listaArchivos[i]);
		}
		// Muestra el avance del proceso
		if (i == nroArchivos - 1)
			bytesAcumulados = bytesTotal; // Para que muestre 100% al final, aunque no sea exacto
		printf("\r%c  %.02f %%   %d/%d   ", marcasAvance[idxMarca++ % (sizeof(marcasAvance) - 1)],
			(double)bytesAcumulados * 100 / bytesTotal, i + 1, nroArchivos);
	}
	double segs = dbg.CronoLee();
	printf("\nSe han encontrado %d archivos con el texto\n", encontrados, textoABuscar, dirBusqueda);
	printf("\t\tCalculado en: %f segs por %s\n", segs, __FUNCTION__);
	return encontrados;
}
