#pragma once
#include <stdint.h>
#include <vector>
#include <Windows.h>
#include <boost/filesystem.hpp>

// Archivo Dbg_P5.h
using namespace std;
using namespace boost::filesystem;

namespace ss {
	class Dbg
	{
	private:	// Opcional, por defecto todo es privado
		int64_t _ticsPorSegundoDelTimerDelPC;
		int64_t _ticsAntes = 0;
		bool _cronoIniciado = false;
		string* SPrintf(char const* const formatString, va_list listaArgumentos);
		char * cabeceraError = (char *)"ERROR";
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

		bool MensajesErrorPorMsgBox;
		void MsgError(char const* const formatString, ...);
		vector<path> ArchivosEnDirectorio(const char* rutaDir, bool imprimir= false);
        static size_t CalculaBytesEnArchivos(vector<path> &listaArchivos);

		bool CheckError(bool condicionError, const char* mensajeUsuario);
		bool CheckError(bool condicionError, int codigoSalida, const char* mensajeUsuario);
		int BuscaDatoEnArchivo(char* aBuscar, size_t tamABuscar, const char * nombreArchivo,
			size_t &bytesAcumulados, int tamBuffer=1);
		bool CreaArchivoTest(const char* nombre, int tamArchivo, int tamBuffer=1);
	};

} // Fin namespace
