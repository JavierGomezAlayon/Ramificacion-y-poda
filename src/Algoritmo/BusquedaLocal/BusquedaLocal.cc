// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: DAA
// Curso: 3º
// Práctica 06 : Ramificación_y_poda
// Autor: javier Gómez Alayón
// Correo: alu0101562445@ull.edu.es
// Fecha: 04/25/25
// Archivo BusquedaLocal.cc: Implementación de BusquedaLocal
//        En este fichero se implementa las funciones de la clase BusquedaLocal
//
// Historial de revisiones
//        04/25/25 - Creación (primera versión) del código

#include"BusquedaLocal.h"

/** BusquedaLocal::BusquedaLocal()
  * @brief Crea el objeto de la clase BusquedaLocal.
  * @param 
  * @return objeto de la clase BusquedaLocal
  */
BusquedaLocal::BusquedaLocal() {

}

/** BusquedaLocal::solve()
  * @brief Hace la busqueda local swap cambiando los puntos de la solución por puntos del espacio
  *        Mientras que mejore se sigue repitiendo el proceso.
  * @return objeto de la clase BusquedaLocal
  */
BusquedaLocal* BusquedaLocal::solve() {
  double distancia_maxima = 0;
  Punto punto_mas_lejano;
  double coste = 0;
  int espacio_size = this->espacio_.getSize();
  int solucion_size = this->solucion_.getSize();
  EspacioVectorial solucion_aux = this->solucion_;
  do {
    coste = 0;
    for (int i = 0; i < espacio_size; i++) {
      for (int j = 0; j < solucion_size; j++) { 
        solucion_aux.addPunto(this->espacio_[i]);
        solucion_aux.removePunto(this->solucion_[j]);

      }
    }
  } while (coste > 0);
  return this;
}

BusquedaLocal* BusquedaLocal::setSolucion(EspacioVectorial& solucion) {
  this->solucion_ = solucion;
}

