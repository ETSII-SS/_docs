MUY IMPORTANTE: No añadir este directamente a ningún proyecto. Copiar siempre los trozos de código 
        que se indican en cada ejercicio a archivos ya existentes. 
		

		
		
// Copiar esto dentro de la función main, ...
ss::Dbg dbg(true);

if (argc < 2)
{
	dbg.MsgError("Falta el nombre del directorio");
	return 1;
}
auto rutaDir= argv[1];
cout << "Calculando tamaño del directorio: " << rutaDir << "...\n\n";

int resMsgBox= MessageBoxA((HWND)INVALID_HANDLE_VALUE, "Programa terminado", "Fin", MB_OK);
if (resMsgBox == 0)  // <<-- Debe ejecutar correctamente hasta aquí. 
{
	const char * mensaje = "Al ejecutar MessageBoxA";

	DWORD errNum = GetLastError();
	const int tamMsg = 300;
	CHAR lpvSysMsg[tamMsg];
	// Pasa código de error de Windows a mensaje
	DWORD eMsgLen = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errNum, 0, lpvSysMsg, sizeof(lpvSysMsg), NULL);
	if (eMsgLen > 0)
	{
		dbg.MsgError("%s\n  ---> %s", mensaje, lpvSysMsg);
	}
	else
	{
		dbg.MsgError("%s\n  ---> Ultimo número de error: %d", mensaje, lpvSysMsg);
	}
}
(void)getchar();
return 0;
	// Borrar el resto de main
	
// <- Hasta aquí ejercicio 4.1



dbg.CheckError(0 == MessageBoxA((HWND)INVALID_HANDLE_VALUE, "Programa terminado", "Fin", MB_OK)
		, "Al ejecutar MessageBoxA");





// El código de CalculaBytesEnArchivos
Dbg miDgb(true); // usamos un objeto Dbg para cada función por 
	// si queremos variar las opciones de salida de depuración  
std::cout.imbue(std::locale(""));

miDgb.CronoInicio();

size_t bytes = 0;
for (int i = 0; i < listaArchivos.size(); i++) {
	bytes += file_size(listaArchivos[i]);
}

miDgb.CronoFin();

cout << listaArchivos.size() << " Archivos en el directorio " << ruta << "\n   ";
cout << bytes << " bytes.\n";
cout << "    Calculado en: " << miDgb.CronoSegs << " segs por " << __FUNCTION__ << "\n";






vector<path> Dbg::ArchivosEnDirectorioTratamientoErroresConExcepciones(const char* nombreDir, bool imprimir)
{
	vector<path> res;
	try
	{
		auto ruta = path(nombreDir);
		ThrowOnError(!exists(ruta), 1, Print("El directorio %s no existe\n", nombreDir));
		ThrowOnError(!is_directory(ruta), 2, Print("La ruta %s no es un directorio\n", nombreDir));
		if (imprimir)
			printf("Archivos en el directorio %s:\n", nombreDir);
		try
		{
			for (auto x : directory_iterator(ruta)) {
				if (imprimir)
				{
					if (x.is_directory())
						cout << x.path().filename() << "  (Directorio)\n";
					else
						cout << x.path().filename() << '\n';
				}
				if (x.is_directory())
				{
					auto nuevo = ArchivosEnDirectorio(x.path().string().c_str(), imprimir);
					res.insert(res.end(), nuevo.begin(), nuevo.end());
				}
				else
				{
					res.push_back(x.path());
				}
			}
		}
		catch (...)
		{
			Dbg objDbg(false); // Por si queremos que solo aparezcan los mensajes de eror
							   // por la ventana de depuración
			objDbg.Print("(%s) Error al procesar directorio %s \n", __FUNCTION__, nombreDir);
		}
	}
	catch (int codigo)
	{
		Dbg objDbg(true, true); // Fuerzo salida por pantalla y MessageBox
		objDbg.MensajesErrorPorMsgBox = true;
		objDbg.Print("(%s) Error %d al procesar ejecutar función\n", __FUNCTION__, codigo);
	}
	return res;
}









//////     SESION 2. 


// lanza hilos usando std::thread
static size_t tamAcumulado;
// Punto de entrada del hilo. 
static void CalculaTamGrupoArchivos(vector<path> listaArchivos)
{
	size_t tamGrupo = 0;
	for (int i = 0; i < listaArchivos.size(); i++) {
		tamGrupo += file_size(listaArchivos[i]);
	}
	tamAcumulado+= tamGrupo;
}
static size_t CalculaBytesEnArchivosConVariosHilos(vector<path> listaArchivos, char* ruta, int nroHilos)
{
	Dbg miDgb(true); std::cout.imbue(std::locale(""));
	miDgb.CronoInicio();

	thread * hilos= new thread[nroHilos];
	tamAcumulado = 0;
	for (int i = 0; i < nroHilos; i++)
	{
		hilos[i] = thread(CalculaTamGrupoArchivos, listaArchivos);
		miDgb.CheckError(hilos[i].native_handle() == NULL, "No se pudo crear hilo");
	}

	miDgb.CronoFin();
	cout << listaArchivos.size() << " Archivos en el directorio " << ruta << "\n   ";
	cout << tamAcumulado << " bytes.\n";
	cout << "    Calculado en: " << miDgb.CronoSegs << " segs por " << __FUNCTION__ << " (" << nroHilos<< ") hilos. \n\n";
	return tamAcumulado;
}






// Código parcial de la función BuscaTextoEnArchivos
miDgb.CronoInicio();
cout << std::fixed << setprecision(2);// Formato floats con 2 decimales. 
char marcasAvance[] = "-\\|/"; // Para animación simple
unsigned int idxMarca = 0;
size_t bytesAcumulados = 0;
miDgb.Print("\nBuscando texto \"%s\" en directorio %s \n",
	textoABuscar, dirBusqueda.lexically_normal().string().c_str());
	
for (auto x : listaArchivos) {
	int ocurrencias = miDgb.BuscaDatoEnArchivo(textoABuscar, strlen(textoABuscar),
		x.string().c_str(), bytesAcumulados);
	if (ocurrencias > 0) {
		nroVeces.push_back(ocurrencias);
		encontrados.push_back(x);
	}
	// Muestra el avance del proceso
	if (bytesTotal > 0) {
		miDgb.Print("\r%.02f %%     %c         ", (double)bytesAcumulados * 100 / bytesTotal,
			marcasAvance[idxMarca++ % (sizeof(marcasAvance) - 1)]);
	}
}

if (encontrados.size() > 0) {
	miDgb.Print("\nEncontrado en:\n");
	for (int i = 0; i < encontrados.size(); i++) {
		miDgb.Print("(%d)  %s\n ", nroVeces[i], encontrados[i].lexically_normal().string().c_str());
	}
}
else {
	miDgb.Print("\n     No se encontro en ningun archivo\n");
}

miDgb.CronoFin();
cout << listaArchivos.size() << " Archivos en el directorio " << dirBusqueda.lexically_normal() << "\n   ";
cout << bytesTotal << " bytes.\n";
cout << "    Calculado en: " << miDgb.CronoSegs << " segs por " << __FUNCTION__ << "\n";






// Método BuscaDatoEnArchivo, de la clase Dbg:
// devuelve el número de veces que se encuentra el bloque a buscar
// dentro de un archivo. También modifica incrementa bytesPorAhora con 
// el tamaño del archivo. 
int Dbg::BuscaDatoEnArchivo(char* block, size_t blockSize, const char* fileName,
	size_t bytesPorAhora, int tamBuffer) {
// Abre archivo
ifstream   file(fileName, std::ios::binary);
int res = 0;
if (!file.is_open()) {
	// No se pudo abrir el archivo.
	return -1;
}
char* buffer = new char[tamBuffer];
int idxBusqueda = 0;
while (file.read(buffer, tamBuffer)) {
	size_t bytesRead = file.gcount();
	bytesPorAhora += bytesRead;
	for (size_t i = 0; i < bytesRead; i++) {
		if (buffer[i] == block[idxBusqueda]) {
			idxBusqueda++;
			if (idxBusqueda == blockSize) {
				res++;
				idxBusqueda = 0;
			}
		}
		else {
			idxBusqueda = 0;
		}
	}
}
delete[] buffer;  // delete aplicado a matriz.
file.close();
return res;
}

