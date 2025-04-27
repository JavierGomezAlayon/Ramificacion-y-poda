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
#include<iostream>

int main(int argc, char *argv[]) {
  //Compruebo si se han introducido los argumentos necesarios
  srand(time(0));
  vector<string> ficheros;
  try {
    Dato datos = recoger_parametro(argc, argv);
    ficheros = leer_directorio(datos.directorio);
  } catch (invalid_argument &e) {
    cerr << e.what() << endl;
    return 1;
  } catch (out_of_range &e) {
    cerr << e.what() << endl;
    return 1;
  }
  
  for (const auto &fichero : ficheros) {
    EspacioVectorial espacio;
    try {
      espacio = leer_fichero(fichero);
    } catch (invalid_argument &e) {
      cerr << e.what() << endl;
      return 1;
    } catch (out_of_range &e) {
      cerr << e.what() << endl;
      return 1;
    }
    // Aquí puedes realizar operaciones con el espacio leído
    cout << "---------------------------------------------------------" << endl;
    cout << "Espacio leído desde: " << fichero << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "Voraz" << endl;
    Algoritmo *algoritmo = new Voraz();
    for (int i = 2; i <= 5; i++) {
      EspacioVectorial solucion = algoritmo->setEspacio(espacio)->setTamSol(i)->solve()->getSolucion();
      cout << "Solución: \n" << solucion << endl;
      algoritmo->reset();
    }
    delete algoritmo;
    cout << "---------------------------------------------------------" << endl;
    cout << "GRASP"<< endl;
    algoritmo = new Grasp();
    for (int i = 2; i <= 5; i++) {
      for (int j = 2; j <= 3; j++) {
        dynamic_cast<Grasp*>(algoritmo->setEspacio(espacio))->setTamLista(j)->setTamSol(i);
        EspacioVectorial solucion = algoritmo->solve()->getSolucion();
        cout << "Solución: \n" << solucion << endl;
        algoritmo->reset();
      }
    }
    delete algoritmo; 
  }


  return 0;
}