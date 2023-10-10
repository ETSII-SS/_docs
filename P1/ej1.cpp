...

// Copiar esto dentro de la función main, tras setlocale...
int tout(10);
int tecla(0);
for (int i = 0; i < tout; i++)
{
	printf("Pulsa una tecla antes de %d segundos\n", tout -i);
	int tecla= esperaPulseTecla(1000);
	if (tecla != 0)
		break;
}
if (tecla)
	printf("Se ha pulsado la tecla \'%c\'\n", tecla);
else
	printf("\nNo se ha pulsado ninguna tecla en %d segundos\n", tout);

...

// y esto a su archivo nusuario-P1_a.cpp
int esperaPulseTecla(int toutMs)
{
	int res = 0;
	int antes = GetTickCount();
	int ahora;
	do {
		if (_kbhit())
		{
			res = _getch();
			break;
		}
		if (toutMs>0)
			Sleep(1);
		ahora = GetTickCount();
	} while (ahora - antes < toutMs);
	return res;
}

// Experimento: ¿añadir includes de más modifica el tamaño del código?
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>
#include <limits.h>
#include <float.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <locale.h>
#include <iso646.h>
#include <wchar.h>
#include <wctype.h>
#include <complex.h>
#include <fenv.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <tgmath.h>
#include <uchar.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>






printf("Pulsa una tecla para salir \n");
int contador = 0;
int tecla = 0;
printf("Tam. contador: %d bytes\n", sizeof(contador));
while (tecla = 0)
{
	printf("\r%d        ", ++contador);
	tecla = esperaPulseTecla(0);
}





void LeeFabricanteCPU(char fabricante[], int tamfabricante)
{

	int info[4];
	__cpuid(info, 0); // Ver la ayuda de VS para ver qué hace la funcion __cpuid
	// Ver https://en.wikipedia.org/wiki/CPUID  para la instruccion CPUID.

	// Lo que hace función anterior es cargar EAX con 0 y ejecutar la instrucción CPUID
	// Tras ello, EBX, EDX, ECX contienen 12 bytes ASCII con la "cadena del fabricante"

	for (size_t k = 0; k < sizeof(info[0]); k++)
	{
		fabricante[0 * 4 + k] = info[1] >> k * 8; // Qué hace esta línea?
	}
	for (size_t k = 0; k < sizeof(info[0]); k++)
	{
		fabricante[1 * 4 + k] = info[3] >> k * 8;
	}
	for (size_t k = 0; k < sizeof(info[0]); k++)
	{
		fabricante[2 * 4 + k] = info[2] >> k * 8;
	}
}


void  LeeModeloCPU(char modelo[], int tamModelo)
{
	int info[4];
	__cpuid(info, 0x80000000);	// Comprueba que el procesador soporta las caracteristicas extendidas de EAX
	if (info[0] < 0x80000000)
	{
		strncpy(modelo,
			"La CPU no soporta caracteristicas extendidas de CPUID\n",
			tamModelo - 1);
	}
	else
	{
		// Ejecuta __cpuid con los códigos 0x80000002, 0x80000003 y 0x80000004
		for (int i = 0; i < 3; i++)
		{
			__cpuid(info, 0x80000002 + i);
			for (int j = 0; j < 4; j++)	// Copia el bloque de 4x4 caracteres
			{
				for (size_t k = 0; k < sizeof(info[0]); ++k)
				{
					modelo[i * 12 + j * 4 + k] = info[j] >> k * 8;
				}
			}
		}
	}
}





// Declaración de la clase ss::Dbg
namespace ss {

	class Dbg
	{
	private:	// Opcional, por defecto todo es privado
	public:
		Dbg();
		~Dbg();
		// Funciona exactamente igual que printf, pero envía la salida a la ventana de salida de depuración
		static int Print(char const* const formatString, ...);
	};

} // Fin namespace
...




// Definiciones asociadas a la clase Dbg
namespace ss {
	Dbg::Dbg() 
	{
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
			OutputDebugStringA(buffer); // Imprime en la ventana de salida de depuración
		}
		va_end(args);
		return ret;
	}

} // Fin namespace



/// En Java, la prueba básica de una clase como Dbg sería
System.out.printf("Iniciando prueba Ej ...\n");
int nroTests=1;
Dbg dbgObj= null; //en C++ se usa nullptr en lugar de null
while ((nroTests--)>0){   // Solo para poder repetir el trozo de dentro 
    dbgObj = new Dbg();  
    dbgObj.CronoInicio();
    Thread.sleep(1000); // Espera 500 ms. En C-Windows usaríamos Sleep(1000)
    dbgObj.CronoFin();
    System.out.printf("El tiempo transcurrido %f segs\n", 
                  dbgObj.CronoSegs);
}





// Medición de tiempos en Dbg. 

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




// Paso 3: Obtiene el valor actual del timer del PC en tics usando QueryPerformanceCounter
// y le resta el valor guardado en el paso 2 para obtener el número de tics transcurridos.
// Divide este número por la frecuencia del timer del PC para obtener el número de segundos transcurridos.
int64_t ahora;
LARGE_INTEGER ticks;
if (QueryPerformanceCounter(&ticks))
{
	ahora = ticks.QuadPart;
	CronoSegs = ((ahora)-_ticsAntes) / _ticsPorSegundoDelTimerDelPC;
}
else
{
	Print("Error al ejecutar QueryPerformanceCounter en " __FUNCTION__);
}
