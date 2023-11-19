MUY IMPORTANTE: No añadir este directamente a ningún proyecto. Copiar siempre los trozos de código 
        que se indican en cada ejercicio a archivos ya existentes. 
		

		
		
// Copiar esto dentro de la función main, ...

Dbg dbg(true);
vector<thread> hilos(NRO_HILOS);
contador = 0;
for (int i = 0; i < NRO_HILOS; i++) {
	HiloNoReentranteSimple(i);
}
dbg.Print("Contador vale: %d (cálculo secuencial)\n", contador);
contador = 0;
for (int i = 0; i < NRO_HILOS; i++) {
	hilos[i] = thread(HiloNoReentranteSimple, i);
	dbg.CheckError(hilos[i].native_handle() == NULL, "No se pudo crear el hilo");
}
for (int i = 0; i < NRO_HILOS; i++)
	hilos[i].join();
dbg.Print("Contador vale: %d (cálculo con hilos)\n", contador);


dbg.Print("\nEjecución secuencial HiloNoReentranteNoTanSimple\n");

for (int i = 0; i < NRO_HILOS; i++)
	HiloNoReentranteNoTanSimple(i);

dbg.Print("\nEjecución con hilos HiloNoReentranteNoTanSimple\n");
for (int i = 0; i < NRO_HILOS; i++) {
	hilos[i] = thread(HiloNoReentranteNoTanSimple, i);
	dbg.CheckError(hilos[i].native_handle() == NULL, "No se pudo crear el hilo");
}
for (int i = 0; i < NRO_HILOS; i++)
	hilos[i].join();

// << Hasta aquí


// puntos de entrada de los hilos
#define NRO_INCREMENTOS 10000
#define NRO_HILOS 10
static int contador = 0;


void HiloNoReentranteSimple(int nroHilo) {
	for (int i = 0; i < NRO_INCREMENTOS; i++) {
		contador += nroHilo + 1;
		contador -= nroHilo + 1;
		Sleep(0);  // No espera nada, solo fuerza más cambios de contexto
	}
}
void HiloNoReentranteNoTanSimple(int nroHilo) {
	// Código de HiloNoReentranteNoTanSimple
	printf("\n");
	for (int i = 0; i < nroHilo; i++)
		printf(" ");
	printf("hilo %i iniciado >>", nroHilo);
	for (int i = 0; i < nroHilo; i++)
		printf(" ");
	printf("<< hilo %i finalizado\n", nroHilo);
}



// Código para el ejercicio 17
HANDLE actual, siguiente;	
actual = CreateEventA(NULL, FALSE, FALSE, NULL);
dbg.CheckError(NULL == actual, 1, "Error al crear mútex");
dbg.Print("\nEjecución con hilos HiloNoReentranteNoTanSimple\n");
for (int i = 0; i < NRO_HILOS; i++) {
	siguiente = CreateEventA(NULL, FALSE, FALSE, NULL);
	hilos[i] = thread(HiloNoReentranteNoTanSimple, i, actual, siguiente);
	dbg.CheckError(hilos[i].native_handle() == NULL, "No se pudo crear el hilo");
	actual = siguiente;
}
for (int i = 0; i < NRO_HILOS; i++)
	hilos[i].join();