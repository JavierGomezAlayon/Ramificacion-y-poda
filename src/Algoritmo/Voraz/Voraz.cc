// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: DAA
// Curso: 3º
// Práctica 06 : Ramificación_y_poda
// Autor: javier Gómez Alayón
// Correo: alu0101562445@ull.edu.es
// Fecha: 04/25/25
// Archivo Voraz.cc: Implementación de Voraz
//        En este fichero se implementa las funciones de la clase Voraz
//
// Historial de revisiones
//        04/25/25 - Creación (primera versión) del código

#include"Voraz.h"

/** Voraz::Voraz()
  * @brief Crea el objeto de la clase Voraz.
  * @param 
  * @return objeto de la clase Voraz
  */
Voraz::Voraz() {

}

/** Voraz::solve()
  * @brief Resuelve el problema de la mochila utilizando el algoritmo voraz.
  * @param 
  * @return objeto de la clase Voraz
  */
Voraz* Voraz::solve() {
  Punto centro = this->espacio_.centro();
  while (this->solucion_.getSize() < this->tam_sol) {
    Punto punto_lejano = this->puntoMasLejano(centro); 
    // Step 6: S = S ∪ {s∗}
    this->solucion_.addPunto(punto_lejano);
    // Step 7: Elem = Elem − {s∗}
    this->espacio_.removePunto(punto_lejano);
    // Step 8: Obtener sc = centro(S)
    centro = this->espacio_.centro();
  }
  return this;
}