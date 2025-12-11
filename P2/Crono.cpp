#include "Crono.h"

bool CronoInicio()
{
	bool res = false;
	int64_t _ticsAntes = 0, _ticsPorSegundoDelTimerDelPC = -1;

	// Paso 1: Obtiene la frecuencia del timer del PC en tics/segundo usando QueryPerformanceFrequency
	//   Esta frecuencia depende del hardware del PC y no cambia durante la ejecución del programa
	if (_ticsPorSegundoDelTimerDelPC < 0){
		// No se ha calculado la frecuencia aún. Se calcula ahora
		LARGE_INTEGER frecuencia;
		char* _cadDbg = (char*)"inicializacion puntero a cadena";

		if (QueryPerformanceFrequency(&frecuencia))	{
			_ticsPorSegundoDelTimerDelPC = frecuencia.QuadPart;
			snprintf(_cadDbg, sizeof(_cadDbg), "La frecuencia del contador del PC es %d Hz\n",
				_ticsPorSegundoDelTimerDelPC);
			OutputDebugStringA(_cadDbg);
		}
		else {
			OutputDebugStringA("Error al ejecutar QueryPerformanceCounter en " __FUNCTION__);
		}
	}
	if (_ticsPorSegundoDelTimerDelPC > 0){
		// Paso 2: guarda el valor actual del timer del PC en tics usando QueryPerformanceCounter 
		LARGE_INTEGER ticks;
		if (QueryPerformanceCounter(&ticks)) {
			_ticsAntes = ticks.QuadPart;
			res = true;
		}
		else {
			OutputDebugStringA("Error al ejecutar QueryPerformanceCounter en " __FUNCTION__);
		}
	}
	return res;
}

double CronoLee()
{
	int64_t _ticsAntes=0, _ticsPorSegundoDelTimerDelPC = -1;
	double segundos= -1.0;
	// Paso 3: Obtiene el valor actual del timer del PC en tics usando QueryPerformanceCounter
	// y le resta el valor guardado en el paso 2 para obtener el número de tics transcurridos.
	// Divide este número por la frecuencia del timer del PC para obtener el número de segundos transcurridos.
	int64_t ahora;
	LARGE_INTEGER ticks;
	if (QueryPerformanceCounter(&ticks)) {
		ahora = ticks.QuadPart;
		segundos = (double)(ahora - _ticsAntes) / _ticsPorSegundoDelTimerDelPC;
	}
	else {
		printf("Error al ejecutar QueryPerformanceCounter en " __FUNCTION__);
	}
	return segundos;
}

