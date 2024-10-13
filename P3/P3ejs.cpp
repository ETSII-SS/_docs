MUY IMPORTANTE: No añadir este directamente a ningún proyecto. Copiar siempre los trozos de código 
        que se indican en cada ejercicio a archivos ya existentes. 
		
		
	
		
// Copiar esto dentro de la función main, tras setlocale...
	if (argc < 2) {
		printf("Error: Debe indicar el nombre del directorio a procesar\n");
		return 1;
	}
	printf("Mostrando los archivos del directorio:\n%s\n\n", argv[1]);

	// comprueba si el directorio existe
	DWORD atributos = GetFileAttributesA(argv[1]);
	if (atributos == INVALID_FILE_ATTRIBUTES) {
		printf("Error: No se ha dado un nombre de directorio correcto:\n(%s)\n", argv[1]);
		return 2;
	}
	if ((atributos & FILE_ATTRIBUTE_DIRECTORY)!=0) {
		printf("Error: No es un directorio:\n(%s)\n", argv[1]);
		return 3;
	}

	// A partir de aquí, muestra los archivos del directorio: