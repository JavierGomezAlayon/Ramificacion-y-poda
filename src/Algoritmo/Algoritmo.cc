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

/** Algoritmo::solve()
  * @brief Resuelve el problema.
  * @param 
  * @return 
  */
Algoritmo* Algoritmo::solve() {
  return this;
}

/**Algoritmo::setTamSol(int tam_sol)
  * @brief Establece el tamaño de la solución.
  * @param tam_sol tamaño de la solución
  * @return 
  */
Algoritmo* Algoritmo::setTamSol(int tam_sol) {
  this->tam_sol = tam_sol;
  return this;
}

/** Algoritmo::getSolucion()
  * @brief Devuelve la solución del algoritmo.
  * @param 
  * @return objeto de la clase EspacioVectorial
  */
EspacioVectorial Algoritmo::getSolucion() const {
  return this->solucion_;
}


