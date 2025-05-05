// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: DAA
// Curso: 3º
// Práctica 06 : Ramificación_y_poda
// Autor: javier Gómez Alayón
// Correo: alu0101562445@ull.edu.es
// Fecha: 04/25/25
// Archivo funciones_main.cc: Implementación de las funciones del main
//        En este directorio se implementa las funciones utilizadas en el main
//
// Historial de revisiones
//        04/25/25 - Creación (primera versión) del código

#include"funciones_main.h"
#include<fstream>

/**
 * @brief Recoge los parámetros que se han enviado por linea del comando. Comprobando si los parámetros son correctos.
 * @param numero_argumentos 
 * @param argv 
 * @return retorna un booleano que indica si se ha recogido correctamente los parámetros (true si es correcto, false si no)
 */
Dato recoger_parametro(int numero_argumentos, char *argv[]) {
  Dato datos;
  const std::string kHelp = "--help";
  const std::string kH = "-h";
  switch (numero_argumentos) {
    case 2:
      if (argv[1] == kHelp || argv[1] == kH) {
        mostrar_ayuda();
        exit(0);
      } else {
        datos.directorio = argv[1];
      }
      return datos;
    default:
      mostrar_ayuda_resumida();
      throw std::invalid_argument("Error: los argumentos se han introducido mal");
  }
}
/**
 * @brief Muestra una ayuda detallada del programa
 */
void mostrar_ayuda() {
  std::cout << "\nEste programa se encarga de realizar distintos algoritmos para la resolución del Maximum diversity problem" << std::endl;
  std::cout << "El programa recibe como argumentos el nombre del directorio que contiene todos los ficheros con los datos de entrada al problema " << std::endl;
  std::cout << "Usage: ./busqueda_no_informada directorio" << std::endl;
}

/**
 * @brief Muestra una ayuda resumida del programa
 */
void mostrar_ayuda_resumida() {
  std::cout << "\nUsage: ./busqueda_no_informada directorio" << std::endl;
  std::cout << "Usa el parámetro -h para más información" << std::endl;
}

void mostrar_ayuda_menu() {
  std::cout << "Introduce una de las siguientes opciones: " << std::endl;
  std::cout << "0. Salir" << std::endl;
  std::cout << "1. Mostrar ayuda" << std::endl;
  std::cout << "2. indicar nodo inicial y nodo final" << std::endl;
}

/**
 * @brief implementación del menú del programa
 */
void menu() { 
  mostrar_ayuda_menu();
  int opcion;
  while (true) {
    std::cout << std::endl;
    std::cout << "Introduzca una opción: ";
    std::cin >> opcion;
    switch (opcion) {
      case 1:
        mostrar_ayuda_menu();
        break;
      case 0:
        return;
        break;
      default:
        std::cerr << "Error: Opción no válida" << std::endl;
        break;
    }
  }
}

/**
 * @brief Lee un directorio y lo guarda en un objeto de tipo EspacioVectorial
 * @param directorio 
 * @return retorna un objeto de tipo EspacioVectorial
 */
vector<string> leer_directorio(const string &directorio) {
  vector<string> directorios;
  for (const auto &entry : fs::directory_iterator(directorio)) {
    if (entry.is_regular_file()) {
      directorios.push_back(entry.path().string());
    }
  }
  return directorios;
}


/**
 * @brief Lee un fichero y lo guarda en un objeto de tipo EspacioVectorial
 * @param nombre_fichero 
 * @return retorna un objeto de tipo EspacioVectorial
 * @throw std::invalid_argument si no se ha podido abrir el fichero
 * @throw std::out_of_range si el fichero no tiene el formato correcto
 */
EspacioVectorial leer_fichero(const string &nombre_fichero) {
  int numero_puntos;
  int numero_dimensiones;
  std::fstream fichero(nombre_fichero);
  if (!fichero.is_open()) {
    throw std::invalid_argument("No se ha podido abrir el fichero");
  }
  string linea;
  fichero >> numero_puntos;
  fichero >> numero_dimensiones;
  vector<vector<double>> puntos(numero_puntos, vector<double>(numero_dimensiones));
  for (int i = 0; i < numero_puntos; ++i) {
    std::vector<double> punto;
    for (int j = 0; j < numero_dimensiones; ++j) {
      double valor;
      fichero >> valor;
      punto.push_back(valor);
    }
    puntos[i] = punto;
  }
  EspacioVectorial espacio(puntos);
  return espacio;
}