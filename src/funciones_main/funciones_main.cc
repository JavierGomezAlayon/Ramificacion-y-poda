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
//        En este fichero se implementa las funciones utilizadas en el main
//
// Historial de revisiones
//        04/25/25 - Creación (primera versión) del código

#include"funciones_main.h"

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
    case 1:
      std::cerr << "Error: No se han introducido los argumentos necesarios" << std::endl;
      mostrar_ayuda_resumida();
      datos.correcto = false;
      return datos;
    case 2:
      if (argv[1] == kHelp || argv[1] == kH) {
        mostrar_ayuda();
        datos.correcto = true;
      } else {
        datos.fichero = argv[1];
        datos.correcto = true;
      }
      return datos;
    default:
      datos.correcto = false;
      return datos;
  }
}
/**
 * @brief Muestra una ayuda detallada del programa
 */
void mostrar_ayuda() {
  std::cout << "\nEste programa se encarga de realizar " << std::endl;
  std::cout << "El programa recibe como argumentos el nombre del fichero que contiene " << std::endl;
  std::cout << "Usage: ./busqueda_no_informada fichero.txt " << std::endl;
}

/**
 * @brief Muestra una ayuda resumida del programa
 */
void mostrar_ayuda_resumida() {
  std::cout << "\nUsage: ./busqueda_no_informada fichero.txt" << std::endl;
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


