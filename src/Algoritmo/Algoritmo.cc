// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: DAA
// Curso: 3º
// Práctica 06 : Ramificación_y_poda
// Autor: javier Gómez Alayón
// Correo: alu0101562445@ull.edu.es
// Fecha: 04/25/25
// Archivo Algoritmo.cc: Implementación de Algoritmo
//        En este fichero se implementa las funciones de la clase Algoritmo
//
// Historial de revisiones
//        04/25/25 - Creación (primera versión) del código

#include"Algoritmo.h"

/** Algoritmo::Algoritmo()
  * @brief Crea el objeto de la clase Algoritmo.
  * @param 
  * @return objeto de la clase Algoritmo
  */
Algoritmo::Algoritmo() {

}

/** Algoritmo::setEspacio(EspacioVectorial espacio)
  * @brief Establece el espacio vectorial del algoritmo.
  * @param espacio objeto de la clase EspacioVectorial
  * @return 
  */
Algoritmo* Algoritmo::setEspacio(EspacioVectorial espacio) {
  this->espacio_ = espacio;
  return this;
}

