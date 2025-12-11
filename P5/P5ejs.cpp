MUY IMPORTANTE: No añadir este directamente a ningún proyecto. Copiar siempre los trozos de código 
        que se indican en cada ejercicio a archivos ya existentes. 
		
		

// Copiar esto en su código y llamar a TestHiloNoReentranteSimple 
//    con nroIncrementos igual a 100* 1000 y número de hilos de 1 a 100
static Dbg dbg(true);
void HiloNoReentrante_Simple(int nroVeces, int* pContador) {
	for (int i = 0; i < nroVeces; i++) {
		*pContador += nroVeces + 1;
		*pContador -= nroVeces + 1;
	}
}
static bool TestHiloNoReentranteSimple(int nroIncrementos, int nroHilos) {
	int contador = 0;
	thread * hilos = new thread[nroHilos];
	for (int i = 0; i < nroHilos; i++) {
		hilos[i] = thread(HiloNoReentrante_Simple, nroIncrementos, &contador);
		dbg.CheckError(hilos[i].native_handle() == NULL, "No se pudo crear el hilo");
	}
	for (int i = 0; i < nroHilos; i++)
		hilos[i].join();
	printf("Contador vale: %d (calculado con %d hilos)\n", contador, nroHilos);
	return contador == 0;
}


















static void TurnosHilo(int nroHilo) {
	for (int i = 0; i < nroHilo; i++)
		printf(" ");
	printf("hilo %i iniciado >>", nroHilo);
	for (int i = 0; i < nroHilo; i++)
		printf(" ");
	printf("<< hilo %i finalizado\n", nroHilo);
}
static void TestTurnos(int nroHilos) {
	bool res = true;
	Dbg dbg(true);
	thread* hilos = new thread[nroHilos];
	for (int i = 0; i < nroHilos; i++) {
		hilos[i] = thread(TurnosHilo, i);
		dbg.CheckError(hilos[i].native_handle() == NULL, "No se pudo crear el hilo");
	}
	for (int i = 0; i < nroHilos; i++)
		hilos[i].join();
	return;
}











static void TestTurnos_Ev(int nroHilos) {
	bool res = true;
	HANDLE actual, siguiente;
	actual = CreateEventA(NULL, FALSE, FALSE, NULL);
	dbg.CheckError(actual == NULL, 1, "No se pudo crear el evento inicial\n");
	thread* hilos = new thread[nroHilos];
	for (int i = 0; i < nroHilos; i++) {
		siguiente = CreateEventA(NULL, FALSE, FALSE, NULL);
		dbg.CheckError(siguiente == NULL, 2, "No se pudo crear el evento inicial\n");
		hilos[i] = thread(TurnosHilo_Ev, i, actual, siguiente);
		actual = siguiente;
		dbg.CheckError(hilos[i].native_handle() == NULL, "No se pudo crear el hilo");
	}
	for (int i = 0; i < nroHilos; i++)
		hilos[i].join();
	return;
}




static void TestTurnos_Ev2(int nroHilos) {
	bool res = true;
	Dbg dbg(true);
	thread* hilos = new thread[nroHilos];
	HANDLE* turnos = new HANDLE[nroHilos];
	for (int i = 0; i < nroHilos; i++) {
		turnos[i] = CreateEventA(NULL, FALSE, FALSE, NULL);
		_dbg.CheckError(turnos[i] == NULL, 2, "No se pudo crear el evento inicial\n");
		hilos[i] = thread(TurnosHiloBeep, i, turnos, nroHilos);
		dbg.CheckError(hilos[i].native_handle() == NULL, "No se pudo crear el hilo");
	}
	for (int i = 0; i < nroHilos; i++)
		hilos[i].join();
	return;
}





