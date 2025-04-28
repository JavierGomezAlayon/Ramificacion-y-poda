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
  double coste = 0, mejor_coste = 0;
  Punto punto_lejano, punto_cercano;
  int solucion_size = this->solucion_.getSize();
  double zSolucion = this->solucion_.getZ();
  EspacioVectorial solucion_aux;
  // elimino del espacio los puntos que ya están en la solución
  for (int i = 0; i < solucion_size; i++) {
    this->espacio_.removePunto(this->solucion_[i]);
  }
  int espacio_size = this->espacio_.getSize();
  do {
    coste = 0;
    mejor_coste = 0;
    solucion_aux = this->solucion_;
    for (int i = 0; i < espacio_size; i++) {
      for (int j = 0; j < solucion_size; j++) { 
        solucion_aux.addPunto(this->espacio_[i]);
        solucion_aux.removePunto(this->solucion_[j]);
        coste = solucion_aux.getZ() - zSolucion;
        if (coste > mejor_coste) {
          mejor_coste = coste;
          punto_lejano = espacio_[i];
          punto_cercano = solucion_[j];
        }
        solucion_aux.addPunto(this->solucion_[j]);
        solucion_aux.removePunto(this->espacio_[i]);
      }
    }
    if (mejor_coste > 0) {
      this->solucion_.addPunto(punto_lejano);
      this->solucion_.removePunto(punto_cercano);
      this->espacio_.removePunto(punto_lejano);
      this->espacio_.addPunto(punto_cercano);
      espacio_size = this->espacio_.getSize();
      solucion_size = this->solucion_.getSize();
      zSolucion = this->solucion_.getZ();
      // cout << "intercambio: " << punto_cercano.getId() << " y " << punto_lejano.getId() << " con Z = " << zSolucion << endl;
    }
  } while (mejor_coste > 0);
  return this;
}

BusquedaLocal* BusquedaLocal::setSolucion(EspacioVectorial& solucion) {
  this->solucion_ = solucion;
  return this;
}


