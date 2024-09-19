

...

// Sustituir el contenido del archivo .cpp por esto:
#include <stdio.h>
#include <locale.h>
 
int main(int argc, char* argv[], char* envp[])
{
	// Necesario para imprimir caracteres específicos del español
	setlocale(LC_ALL, "Spanish"); // Necesita #include <locale.h>
 
	HolaMundo_ComoC();
 
	printf("\nPor favor, pulse la tecla ENTRAR para terminar ...\n");
	(void)getchar();  // printf y getchar=> necesitan #include <stdio.h>
	return 0;
}
static void HolaMundo_ComoC() {
	printf("\nHola mundo, desde C/C++\n");
}


...



// Copiar esto en un nuevo archivo: ImprimeGhz.cpp y hacerlo compilar
#define ESPERA_MS (500)
void ImprimeGhz() {
	int antes, ahora;
	double VelocidadCPUGhz;

	antes = __rdtsc(); // Leo el valor del contador RDTSC y lo guardo
	Sleep(ESPERA_MS); // Espero un segundo
	ahora = __rdtsc();// Leo el valor del contador ahora

	VelocidadCPUGhz = (ahora - antes) / (ESPERA_MS * _1MHzEnHerzios);
	printf("\nLa frecuencia en GHz es: %d", VelocidadCPUGhz);
}







