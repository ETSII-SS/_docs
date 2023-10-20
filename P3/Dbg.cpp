#include "Dbg.h"
#include <stdio.h>
#include <stdarg.h>
#include <Windows.h>

#define TAM_BUFFER_DbgPrint 1024
// Definiciones asociadas a la clase 
namespace ss {
	Dbg::Dbg(bool salidaPorPantalla, bool salidaPorDepuracion)
	{
		SalidaDepuracion = salidaPorDepuracion;
		SalidaPantalla = salidaPorPantalla;
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
		char buffer[TAM_BUFFER_DbgPrint];
		va_list args;
		va_start(args, formatString);
		int ret = vsnprintf(buffer, sizeof(buffer), formatString, args);
		if (ret >= 0 && ret < sizeof(buffer))
		{
			if (SalidaDepuracion)
				OutputDebugStringA(buffer); // Imprime en la ventana de salida de depuración
			if (SalidaPantalla)
				printf("%s", buffer); // Imprime en la consola de salida
		}
		va_end(args);
		return ret;
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
			CronoSegs = (ahora-_ticsAntes) / _ticsPorSegundoDelTimerDelPC;
		}
		else
		{
			Print("Error al ejecutar QueryPerformanceCounter en " __FUNCTION__);
		}
	}

#pragma endregion Medicion de tiempo
	// Esto se usa a partir del ejercicio 3.14
	
	//vector<path> Dbg::ArchivosEnDirectorio(const char * nombreDir, bool imprimir)
	//{
	//	vector<path> res;

	//	auto ruta = path(nombreDir);
	//	if (!exists(ruta))
	//	{
	//		Print("El directorio %s no existe\n", nombreDir);
	//	}
	//	else if (!is_directory(ruta))
	//	{
	//		Print("La ruta %s no es un directorio\n", nombreDir);
	//	}
	//	else {
	//		if (imprimir)
	//			printf("Archivos en el directorio %s:\n", nombreDir);
	//		for (auto x : directory_iterator(ruta)) {
	//			if (imprimir)
	//			{
	//				if (x.is_directory())
	//					cout << x.path().filename() << "  (Directorio)\n";
	//				else
	//					cout << x.path().filename() << '\n';
	//			}
	//			res.push_back(x.path());
	//		}
	//	}
	//	return res;
	//}
} // Fin namespace