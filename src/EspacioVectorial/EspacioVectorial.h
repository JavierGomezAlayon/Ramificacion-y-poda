// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: DAA
// Curso: 3º
// Práctica 06 : Ramificación_y_poda
// Autor: javier Gómez Alayón
// Correo: alu0101562445@ull.edu.es
// Fecha: 04/25/25
// Archivo EspacioVectorial.h : Declaración de la clase EspacioVectorial
//        En este fichero se declara la clase EspacioVectorial
//
// Historial de revisiones
//        04/25/25 - Creación (primera versión) del código
#ifndef C_EspacioVectorial_H
#define C_EspacioVectorial_H
#include "../Punto/Punto.h"

class EspacioVectorial {
 public:
  EspacioVectorial();
  EspacioVectorial(const vector<vector<double>>& puntos);
  EspacioVectorial(const vector<Punto>& puntos);
  const Punto& operator[](int index) const;
  void addPunto(vector<double> punto, unsigned int id); // igualarlo a infinito (limit)
  void addPunto(const Punto& punto);
  void removePunto(int index);
  void removePunto(const Punto& punto);
  int getSize() const;
  Punto centro() const;
  double getZ() const;
  friend std::ostream& operator<<(std::ostream& os, const EspacioVectorial& espacio);
  string ids() const;
    
 private:
  std::vector<Punto> puntos_;
  int numero_dimensiones_;
  int numero_puntos_;
};

#endif