MUY IMPORTANTE: No añadir este directamente a ningún proyecto. Copiar siempre los trozos de código 
        que se indican en cada ejercicio a archivos ya existentes. 
		
		

// Copiar esto dentro de la función main, tras setlocale...

// Clases declaradas en SSLib. Hay que incluir sslib/SSLib.h
Dbg dbg(true);
FileSys fs;

const char* pDir = ".";
int encontrados;
char** plistaArchivos;  // Este tipo se puede usar como dirección de una matriz de punteros a char. 
// Es similar a char* envp[], pero esa nomenclatura se puede usar en una definición de variable.

plistaArchivos = fs.ArchivosEnDirectorio(&encontrados, "."); 
dbg.CheckError(plistaArchivos == nullptr, 1, "No se han encontrado archivos en la carpeta %s\n", pDir);

printf("Se han encontrado %d archivos en la carpeta %s\n", encontrados, pDir);






static void ImprimeArchivosEnDirectorio(char* listaArchivos[]) {
	int i = 0;
	// Imprime la lista de archivos mientras no se encuentre un puntero nulo
	while (listaArchivos[i] = nullptr)
	{
		printf("#%d: %s\n", i, listaArchivos[i]);
		i++;
	}
}