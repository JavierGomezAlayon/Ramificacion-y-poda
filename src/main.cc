// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: DAA
// Curso: 3º
// Práctica 06 : Ramificación_y_poda
// Autor: javier Gómez Alayón
// Correo: alu0101562445@ull.edu.es
// Fecha: 04/25/25
// Archivo main.cc: Implementación del programa cliente
//        En este fichero se implementa la función del main
//
// Historial de revisiones
//        04/25/25 - Creación (primera versión) del código
#include"funciones_main/funciones_main.h"
#include<iostream>

int main(int argc, char *argv[]) {
  //Compruebo si se han introducido los argumentos necesarios
  vector<string> ficheros;
  try {
    Dato datos = recoger_parametro(argc, argv);
    ficheros = leer_directorio(datos.directorio);
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  } catch (std::out_of_range &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  
  for (const auto &fichero : ficheros) {
    EspacioVectorial espacio;
    try {
      espacio = leer_fichero(fichero);
    } catch (std::invalid_argument &e) {
      std::cerr << e.what() << std::endl;
      return 1;
    } catch (std::out_of_range &e) {
      std::cerr << e.what() << std::endl;
      return 1;
    }
    // Aquí puedes realizar operaciones con el espacio leído
    std::cout << "Espacio leído desde: " << fichero << std::endl;

  }


  return 0;
}