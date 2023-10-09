...

// Copiar esto dentro de la función main, tras setlocale...
printf("Nombre del programa: %s\n", argv[0]);
printf("\nVersion estilo C (char *):\n");
// LLamo a una funcion que devuelve una matriz con las partes de argv[0]
partesRutaC_t *componentes = DescomponeRutaCMal(argv[0]);
for (size_t i = 0; (*componentes)[i][0] != 0; i++)
{
	cout << (*componentes)[i] << "    ";
	//ComePila();
}
cout << endl;



typedef char partesRutaC_t[50][100];
// Función para descomponer una ruta de archivo en sus componentes
partesRutaC_t* DescomponeRutaCMal(const char* ruta) {
	partesRutaC_t componentesC;
	char* inicio = (char*)ruta;
	char* fin;
	int i = 0;

	while ((fin = strchr(inicio, '\\')) != NULL) {
		strncpy(componentesC[i++], inicio, fin - inicio);
		inicio = fin + 1;
	}
	strncpy(componentesC[i], inicio, strlen(inicio)); // Añade el último componente
	componentesC[i + 1][0] = 0; // Termina la matriz con NULL

	return &componentesC;
}


void ComePila() { // Ignorar, por ahora
	char variableLocalGrande[10000];
	memset(&variableLocalGrande, 'W', sizeof(variableLocalGrande));
}





printf("\nVersion estilo C++ (vectores de string):\n");
vector<string> componentes2 = DescomponeRutaCpp(argv[0]);
for (size_t i = 0; i < componentes2.size(); i++)
{
	cout << componentes2[i] << "    ";
	//ComePila();
}




vector<string> DescomponeRutaCpp(const char* pruta) {
	string ruta(pruta);
	vector<string> vComponentes;
	string::size_type fin, inicio = 0;

	while ((fin = ruta.find("\\", inicio)) != std::string::npos) {
		vComponentes.push_back(ruta.substr(inicio, fin - inicio));
		inicio = fin + 1;
	}
	vComponentes.push_back(ruta.substr(inicio)); // Añade el último componente
	return vComponentes;
}





// Iterators (C++98)
printf("\nVersion estilo C++ (acceso con iteradores):\n");
for (vector<string>::iterator pIt = componentes2.begin(); pIt != componentes2.end(); pIt++)
{
	cout << *pIt << "    "; 
}
cout << endl;

// Iterators + foreach (C++11) + auto (C++11)
printf("\nVersion estilo C++ (acceso con iteradores-foreach):\n");
for (auto item : componentes2)
{
	cout << item << "    ";
}
cout << endl;





printf("\nVersion estilo C++ usando la biblioteca boost/filesystem:\n");
path ruta(argv[0]);
cout << "Ruta completa: " << ruta << endl;
for (auto item : ruta) {
	cout << item.string() << "    ";
}
cout << endl;
