#include "Dbg_P5.h"
#include <stdio.h>
#include <stdarg.h>
#include <fstream>
#include <iostream>
#define TAM_BUFFER_DbgPrint 1024
// Definiciones asociadas a la clase 
namespace ss {
	Dbg::Dbg(bool salidaPorPantalla, bool salidaPorDepuracion)
	{
		setlocale(LC_ALL, "Spanish");
		SalidaDepuracion = salidaPorDepuracion;
		SalidaPantalla = salidaPorPantalla;
		MensajesErrorPorMsgBox = false;
		// Paso 1: Obtiene la frecuencia del timer del PC en tics/segundo usando QueryPerformanceFrequency
		//       Esta frecuencia depende del hardware del PC y no cambia durante la ejecución del programa
		LARGE_INTEGER frequencia;
		if (QueryPerformanceFrequency(&frequencia))
		{
			_ticsPorSegundoDelTimerDelPC = frequencia.QuadPart;
			CronoSegs = -1.0; // Un número negativo indica que no se ha iniciado el cronómetro.
		}
		else
		{
			Print("Error al ejecutar QueryPerformanceCounter en " __FUNCTION__);
		}
	}

	Dbg::~Dbg()
	{
	}

	// Esta es una función con parámetros variables, como printf. 
	// Ver N3- https://learn.microsoft.com/es-es/cpp/cpp/functions-with-variable-argument-lists-cpp?view=msvc-170
	int Dbg::Print(char const* const formatString, ...)
	{
		va_list args;
		va_start(args, formatString);
		auto aImprimir = SPrintf(formatString, args);
		va_end(args);
		if (SalidaDepuracion)
			OutputDebugStringA(aImprimir->c_str()); // Imprime en la ventana de salida de depuración
		if (SalidaPantalla)
			printf("%s", aImprimir->c_str()); // Imprime en la consola de salida

		return aImprimir->length(); // Devuelve el número de caracteres escritos (como printf)
	}
	string* Dbg::SPrintf(char const* const formatString, va_list listaArgumentos)
	{
		char buffer[TAM_BUFFER_DbgPrint];
		int ret = vsnprintf(buffer, sizeof(buffer) - 1, formatString, listaArgumentos);
		buffer[sizeof(buffer) - 1] = '\0'; // Asegura que la cadena termina en '\0'
		return new string(buffer);
	}
	void Dbg::MsgError(char const* const formatString, ...)
	{
		va_list args;
		va_start(args, formatString);
		auto aImprimir = SPrintf(formatString, args);
		va_end(args);
		if (SalidaPantalla)
			printf("%s", aImprimir->c_str()); // Imprime en la consola de salida
		if (SalidaDepuracion)
			OutputDebugStringA(aImprimir->c_str()); // Imprime en la ventana de salida de depuración
		if (MensajesErrorPorMsgBox)
		{
			MessageBoxA(NULL, aImprimir->c_str(), cabeceraError, MB_OK);
		}
	}

#pragma region Medicion de tiempo

	void Dbg::CronoInicio()
	{
		// Paso 2: guarda el valor actual del timer del PC en tics usando QueryPerformanceCounter 
		LARGE_INTEGER ticks;
		if (QueryPerformanceCounter(&ticks))
		{
			_ticsAntes = ticks.QuadPart;
		}
		else
		{
			Print("Error al ejecutar QueryPerformanceCounter en " __FUNCTION__);
		}
	}

	void Dbg::CronoFin()
	{
		// Paso 3: Obtiene el valor actual del timer del PC en tics usando QueryPerformanceCounter
		// y le resta el valor guardado en el paso 2 para obtener el número de tics transcurridos.
		// Divide este número por la frecuencia del timer del PC para obtener el número de segundos transcurridos.
		int64_t ahora;
		LARGE_INTEGER ticks;
		if (QueryPerformanceCounter(&ticks))
		{
			ahora = ticks.QuadPart;
			CronoSegs = ((double)ahora - _ticsAntes) / _ticsPorSegundoDelTimerDelPC;
		}
		else
		{
			Print("Error al ejecutar QueryPerformanceCounter en " __FUNCTION__);
		}
	}

#pragma endregion Medicion de tiempo
	// Esto se usa a partir del ejercicio 3.14

	vector<path> Dbg::ArchivosEnDirectorio(const char* nombreDir, bool imprimir)
	{
		vector<path> res;

		auto ruta = path(nombreDir);
		if (!exists(ruta))
		{
			Print("El directorio %s no existe\n", nombreDir);
		}
		else if (!is_directory(ruta))
		{
			Print("La ruta %s no es un directorio\n", nombreDir);
		}
		else {
			if (imprimir)
				printf("Archivos en el directorio %s:\n", nombreDir);
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
					auto nuevos = ArchivosEnDirectorio(x.path().string().c_str(), imprimir);
					res.insert(res.end(), nuevos.begin(), nuevos.end());
				}
				else
					res.push_back(x.path());
			}
		}
		return res;
	}
	bool Dbg::CheckError(bool condicionError, const char* mensajeUsuario)
	{
		if (condicionError)
		{
			DWORD errNum = GetLastError();
			MessageBeep(MB_ICONERROR);
			const int tamMsg = 300;
			CHAR lpvSysMsg[tamMsg];
			// Pasa código de error de Windows a mensaje
			if (errNum != 0) {
				DWORD eMsgLen = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM,
					NULL, errNum, 0, lpvSysMsg, sizeof(lpvSysMsg), NULL);
				if (eMsgLen > 0)
				{
					MsgError("%s\n  ---> %s", mensajeUsuario, lpvSysMsg);
				}
				else
				{
					MsgError("%s\n  ---> Ultimo número de error: %d", mensajeUsuario, lpvSysMsg);
				}
			}
			else
				MsgError("%s\n", mensajeUsuario);
		}
		return condicionError;
	}
	bool Dbg::CheckError(bool condicionError, int codigoSalida, const char* mensajeUsuario)
	{
		if (condicionError)
		{
			if (codigoSalida != 0) {
				cabeceraError = (char*)"ERROR: El programa terminará";
				MensajesErrorPorMsgBox = true;
			}
			CheckError(true, mensajeUsuario);
			if (codigoSalida != 0)
				ExitProcess(codigoSalida);
		}
		return condicionError;
	}


	int Dbg::BuscaDatoEnArchivo(char* block, size_t blockSize, const char* fileName,
		size_t& bytesPorAhora, int tamBuffer) {
		// Abre archivo
		ifstream file(fileName, std::ios::binary);
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
	bool Dbg::CreaArchivoTest(const char* nombre, int tamArchivo, int tamBuffer)
	{
		ss::Dbg miDgb(true); std::cout.imbue(std::locale(""));
		miDgb.CronoInicio();

		bool res = false;
		std::ofstream archivo(nombre, std::ios::binary);
		if (!archivo.is_open()) {
			printf("No se pudo abrir el archivo %s\n", nombre);
		}
		else
		{
			ss::Dbg dbg(false);
			dbg.CronoInicio();

			// Cadena ASCII para escribir en el archivo
			const char* alfanumericos = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\n";
			int idx = 0;
			int nroEscrituras = 0;
			// Crear un búfer para escribir en el archivo
			uint8_t* pbuffer = new uint8_t[tamBuffer];
			res = true;
			for (int i = 0; i < tamArchivo; i += tamBuffer)
			{
				int j;
				for (j = 0; j < tamBuffer; j++) {
					pbuffer[j] = alfanumericos[idx++];
					// Cuando idx sea igual que el tamaño de la cadena, se pone a 0
					if (alfanumericos[idx] == '\0')
						idx = 0;
				}
				// Escribir el búfer en el archivo
				size_t tamAEscribir = min(tamBuffer, tamArchivo - i);
				archivo.write((const char*)pbuffer, (std::streamsize)tamAEscribir);
				nroEscrituras += tamAEscribir;
			}
			archivo.close();
			dbg.CronoFin();
			dbg.Print("Escrito con byffer de %d bytes, en (%f) s. Tam: %d. Archivo: %s\n",
				tamBuffer, dbg.CronoSegs, tamArchivo, nombre);
			delete[] pbuffer;
		}

		miDgb.CronoFin();
		cout << "\nCreando archivo de test: " << nombre << "\n   ";
		cout << "      (" << tamArchivo << ") bytes, tamBuffer: " << tamBuffer << ",  en "
			<< miDgb.CronoSegs << " segs por " << __FUNCTION__ << "hilos. \n\n";

		return res;
	}
} // Fin namespace