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
#include"Algoritmo/Voraz/Voraz.h"
#include"Algoritmo/Grasp/Grasp.h"
#include"Algoritmo/BusquedaLocal/BusquedaLocal.h"
#include"Algoritmo/RamificacionPoda/RamificacionPoda.h"
#include"Problema/Problema.h"
#include<iostream>

int main(int argc, char *argv[]) {
  //Compruebo si se han introducido los argumentos necesarios
  //srand(time(0));
  srand(0);
  vector<string> ficheros;
  Dato datos;
  try {
    datos = recoger_parametro(argc, argv);
  } catch (invalid_argument &e) {
    cerr << e.what() << endl;
    return 1;
  } catch (out_of_range &e) {
    cerr << e.what() << endl;
    return 1;
  }
  try {
    ficheros = leer_directorio(datos.directorio);
  } catch (invalid_argument &e) {
    cerr << e.what() << endl;
    return 1;
  } catch (out_of_range &e) {
    cerr << e.what() << endl;
    return 1;
  }
  EspacioVectorial espacio; 
  Problema problema;
  for (const auto &fichero : ficheros) { // por cada fichero
    try {
      espacio = leer_fichero(fichero);
      cout << fichero << endl;
    } catch (invalid_argument &e) {
      cerr << e.what() << endl;
      return 1;
    } catch (out_of_range &e) {
      cerr << e.what() << endl;
      return 1;
    }
    problema.set_espacio(espacio)->set_fichero(fichero.substr(5));
    for (int i = 2; i <= 5; i++) { // posibles tamaño de soluciones
      problema.voraz(i);
      problema.voraz_con_mejora(i);
      for (int j = 2; j <= 3; j++) { // posibles tamaño de listas de candidatos (Grasp)
        for (int iteraciones = 10; iteraciones <= 20; iteraciones += 10) {
          problema.grasp(i, j, iteraciones);
        }
      }
      problema.ramificacion_poda(i, 3, 10, true);
    }
  }
  problema.mostrar_resultados();
  return 0;
}
