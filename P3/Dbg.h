#pragma once
#include <stdint.h>

namespace ss {

	class Dbg
	{
	private:	// Opcional, por defecto todo es privado
		int64_t _ticsPorSegundoDelTimerDelPC;
		int64_t _ticsAntes = 0;
		bool _cronoIniciado = false;
	public:
		Dbg(bool salidaPorPantalla = false, bool salidaPorDepuracion= true);
		~Dbg();

		// Medición tiempos
		void CronoInicio();
		void CronoFin();
		double CronoSegs;

		// Funciona exactamente igual que printf, pero envía la salida a la ventana de salida de depuración
		int Print(char const* const formatString, ...);
		bool SalidaDepuracion; // Si es true, se envía la salida a la ventana de depuración
		bool SalidaPantalla; // Si es true, se envía la salida a la consola de salida
		
		//vector<path> ArchivosEnDirectorio(const char* rutaDir, bool imprimir= false);
	};

} // Fin namespace


