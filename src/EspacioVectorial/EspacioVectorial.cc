// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: DAA
// Curso: 3º
// Práctica 06 : Ramificación_y_poda
// Autor: javier Gómez Alayón
// Correo: alu0101562445@ull.edu.es
// Fecha: 04/25/25
// Archivo EspacioVectorial.cc: Implementación de EspacioVectorial
//        En este fichero se implementa las funciones de la clase EspacioVectorial
//
// Historial de revisiones
//        04/25/25 - Creación (primera versión) del código

#include"EspacioVectorial.h"

/** EspacioVectorial::EspacioVectorial()
  * @brief Crea el objeto de la clase EspacioVectorial.
  * @param 
  * @return objeto de la clase EspacioVectorial
  */
EspacioVectorial::EspacioVectorial() {

}

/** EspacioVectorial::EspacioVectorial(const vector<vector<double>>& puntos)
  * @brief Crea el objeto de la clase EspacioVectorial.
  * @param puntos vector de puntos
  * @return objeto de la clase EspacioVectorial
  * @throw std::out_of_range si el número de dimensiones no es el mismo para todos los puntos
  * @throw std::invalid_argument si el vector de puntos está vacío
  */
EspacioVectorial::EspacioVectorial(const vector<vector<double>>& puntos) {
  if (puntos.empty()) {
    throw std::invalid_argument("Error: El vector de puntos está vacío");
  }
  this->numero_puntos_ = puntos.size();
  this->numero_dimensiones_ = puntos[0].size();
  for (int i = 0; i < this->numero_puntos_; i++) {
    if (puntos[i].size() != this->numero_dimensiones_) {
      throw std::out_of_range("Error: El número de dimensiones no es el mismo para todos los puntos");
    }
    Punto punto(puntos[i]);
    this->puntos_.push_back(punto);
  }
}

/** EspacioVectorial::EspacioVectorial(const vector<Punto>& puntos)
  * @brief Crea el objeto de la clase EspacioVectorial.
  * @param puntos vector de puntos
  * @return objeto de la clase EspacioVectorial
  * @throw std::invalid_argument si el vector de puntos está vacío
  */
EspacioVectorial::EspacioVectorial(const vector<Punto>& puntos) {
  if (puntos.empty()) {
    throw std::invalid_argument("Error: El vector de puntos está vacío");
  }
  this->numero_puntos_ = puntos.size();
  this->numero_dimensiones_ = puntos[0].getNumeroDimensiones();
  for (int i = 0; i < this->numero_puntos_; i++) {
    if (puntos[i].getNumeroDimensiones() != this->numero_dimensiones_) {
      throw std::out_of_range("Error: El número de dimensiones no es el mismo para todos los puntos");
    }
    this->puntos_.push_back(puntos[i]);
  }
}

/** EspacioVectorial::addPunto(vector<double> punto)
  * @brief Añade un punto al espacio vectorial.
  * @param punto vector de coordenadas del punto
  * @return 
  * @throw std::out_of_range si el número de dimensiones no es el mismo para todos los puntos
  */
void EspacioVectorial::addPunto(vector<double> punto) {
  if (punto.size() != this->numero_dimensiones_) {
    throw std::out_of_range("Error: El número de dimensiones no es el mismo para todos los puntos");
  }
  Punto nuevo_punto(punto);
  this->puntos_.push_back(nuevo_punto);
  this->numero_puntos_++;
}

/** EspacioVectorial::addPunto(Punto punto)
  * @brief Añade un punto al espacio vectorial.
  * @param punto objeto de la clase Punto
  * @return 
  * @throw std::out_of_range si el número de dimensiones no es el mismo para todos los puntos
  */
void EspacioVectorial::addPunto(const Punto& punto) {
  if (punto.getNumeroDimensiones() != this->numero_dimensiones_) {
    throw std::out_of_range("Error: El número de dimensiones no es el mismo para todos los puntos");
  }
  this->puntos_.push_back(punto);
  this->numero_puntos_++;
}

/** EspacioVectorial::removePunto(int index)
  * @brief Elimina un punto del espacio vectorial.
  * @param index índice del punto a eliminar
  * @return 
  * @throw std::out_of_range si el índice está fuera de rango
  */
void EspacioVectorial::removePunto(int index) {
  if (index < 0 || index >= this->numero_puntos_) {
    throw std::out_of_range("Error: El índice está fuera de rango");
  }
  this->puntos_.erase(this->puntos_.begin() + index);
  this->numero_puntos_--;
}

/** EspacioVectorial::removePunto(Punto punto)
  * @brief Elimina un punto del espacio vectorial.
  * @param punto objeto de la clase Punto
  * @return 
  * @throw std::out_of_range si el número de dimensiones no es el mismo para todos los puntos
  */
void EspacioVectorial::removePunto(const Punto& punto) {
  if (punto.getNumeroDimensiones() != this->numero_dimensiones_) {
    throw std::out_of_range("Error: El número de dimensiones no es el mismo para todos los puntos");
  }
  for (int i = 0; i < this->numero_puntos_; i++) {
    if (this->puntos_[i].getCoordenadas() == punto.getCoordenadas()) {
      this->puntos_.erase(this->puntos_.begin() + i);
      this->numero_puntos_--;
      break;
    }
  }
}

/** EspacioVectorial::getSize()
  * @brief Devuelve el número de puntos del espacio vectorial.
  * @param 
  * @return número de puntos del espacio vectorial
  */
int EspacioVectorial::getSize() const {
  return this->numero_puntos_;
}

/** EspacioVectorial::centro()
  * @brief Devuelve el centro del espacio vectorial.
  * @param 
  * @return centro del espacio vectorial
  */
Punto EspacioVectorial::centro() const {
  std::vector<double> coordenadas(this->numero_dimensiones_, 0);
  for (int i = 0; i < this->numero_puntos_; i++) {
    for (int j = 0; j < this->numero_dimensiones_; j++) {
      coordenadas[j] += this->puntos_[i].getCoordenadas()[j];
    }
  }
  for (int j = 0; j < this->numero_dimensiones_; j++) {
    coordenadas[j] /= this->numero_puntos_;
  }
  Punto centro(coordenadas);
  return centro;
}
