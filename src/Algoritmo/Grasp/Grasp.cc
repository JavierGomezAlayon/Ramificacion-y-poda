// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: DAA
// Curso: 3º
// Práctica 06 : Ramificación_y_poda
// Autor: javier Gómez Alayón
// Correo: alu0101562445@ull.edu.es
// Fecha: 04/25/25
// Archivo Grasp.cc: Implementación de Grasp
//        En este fichero se implementa las funciones de la clase Grasp
//
// Historial de revisiones
//        04/25/25 - Creación (primera versión) del código

#include"Grasp.h"

/** Grasp::Grasp()
  * @brief Crea el objeto de la clase Grasp.
  * @param 
  * @return objeto de la clase Grasp
  */
Grasp::Grasp() {

}

/** Grasp::solve()
  * @brief Resuelve el problema de la clase Grasp.
  * @param 
  * @return objeto de la clase Grasp
  */
Grasp* Grasp::solve() {
  Punto centro = this->espacio_.centro();
  while (this->solucion_.getSize() < this->tam_sol) {
    Punto punto_lejano = this->puntoMasLejano(centro); 
    this->solucion_.addPunto(punto_lejano);
    this->espacio_.removePunto(punto_lejano);
    centro = this->espacio_.centro();
  }
  return this;
}

/** Grasp::puntoMasLejano(Punto centro)
  * @brief Devuelve el punto más lejano al centro.
  * @param centro objeto de la clase Punto
  * @return objeto de la clase Punto
  */
Punto Grasp::puntoMasLejano(Punto centro) {
  double distancia_maxima = 0;
  EspacioVectorial espacio_aux = this->espacio_;
  vector<Punto> puntos_mas_lejanos;
  Punto punto_mas_lejano;
  for (int j = 0; j < this->tam_lista_; j++) {
    for (int i = 0; i < espacio_aux.getSize(); i++) {
      double distancia = espacio_aux[i].Distancia(centro);
      if (distancia > distancia_maxima) {
        distancia_maxima = distancia;
        punto_mas_lejano = espacio_aux[i];
      }
    }
    espacio_aux.removePunto(punto_mas_lejano);
    distancia_maxima = 0;
    puntos_mas_lejanos.push_back(punto_mas_lejano);
  }
  return puntos_mas_lejanos[rand() % puntos_mas_lejanos.size()];
}

/** Grasp::Grasp(int tam_lista)
  * @brief Crea el objeto de la clase Grasp.
  * @param tam_lista tamaño de la lista
  * @return objeto de la clase Grasp
  */
Grasp* Grasp::setTamLista(int tam_lista) {
  if (tam_lista <= 0) {
    throw std::invalid_argument("El tamaño de la lista no puede ser negativo");
  }
  if (tam_lista > this->espacio_.getSize()) {
    throw std::invalid_argument("El tamaño de la lista no puede ser mayor que el tamaño del espacio");
  }
  this->tam_lista_ = tam_lista;
  return this;
}
