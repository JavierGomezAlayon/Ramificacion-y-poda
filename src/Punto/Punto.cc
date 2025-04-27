// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: DAA
// Curso: 3º
// Práctica 06 : Ramificación_y_poda
// Autor: javier Gómez Alayón
// Correo: alu0101562445@ull.edu.es
// Fecha: 04/25/25
// Archivo Punto.cc: Implementación de Punto
//        En este fichero se implementa las funciones de la clase Punto
//
// Historial de revisiones
//        04/25/25 - Creación (primera versión) del código

#include"Punto.h"

/** Punto::Punto()
  * @brief Crea el objeto de la clase Punto.
  * @param 
  * @return objeto de la clase Punto
  */
Punto::Punto() {

}

/** Punto::Punto(const vector<double>& coordenadas)
  * @brief Crea el objeto de la clase Punto.
  * @param coordenadas vector de coordenadas
  * @return objeto de la clase Punto
  * @throw std::out_of_range si el número de dimensiones no es el mismo para todos los puntos
  * @throw std::invalid_argument si el vector de coordenadas está vacío
  */
Punto::Punto(const std::vector<double>& coordenadas) {
  if (coordenadas.empty()) {
    throw std::invalid_argument("Error: El vector de coordenadas está vacío");
  }
  this->coordenadas_ = coordenadas;
}

/** Punto::Distancia(const Punto& otro)
  * @brief Calcula la distancia euclidea entre dos puntos.
  * @param otro punto con el que se quiere calcular la distancia
  * @return distancia entre los dos puntos
  */
double Punto::Distancia(const Punto& otro) const {
  if (this->coordenadas_.size() != otro.coordenadas_.size()) {
    throw std::out_of_range("Error: El número de dimensiones no es el mismo para todos los puntos");
  }
  double distancia = 0;
  for (int i = 0; i < this->coordenadas_.size(); i++) {
    distancia += pow(this->coordenadas_[i] - otro.coordenadas_[i], 2);
  }
  return sqrt(distancia);
}

/** Punto::getNumeroDimensiones()
  * @brief Devuelve el número de dimensiones del punto.
  * @param 
  * @return número de dimensiones del punto
  */
int Punto::getNumeroDimensiones() const {
  return this->coordenadas_.size();
}

/** Punto::getCoordenadas()
  * @brief Devuelve las coordenadas del punto.
  * @param 
  * @return coordenadas del punto
  */
std::vector<double> Punto::getCoordenadas() const {
  return this->coordenadas_;
}
