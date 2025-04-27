// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: DAA
// Curso: 3º
// Práctica 06 : Ramificación_y_poda
// Autor: javier Gómez Alayón
// Correo: alu0101562445@ull.edu.es
// Fecha: 04/25/25
// Archivo Algoritmo.h : Declaración de la clase Algoritmo
//        En este fichero se declara la clase Algoritmo
//
// Historial de revisiones
//        04/25/25 - Creación (primera versión) del código
#ifndef C_Algoritmo_H
#define C_Algoritmo_H
#include "../EspacioVectorial/EspacioVectorial.h"
class Algoritmo {
 public:
  Algoritmo();
  virtual Algoritmo* solve() = 0;
  Algoritmo* setEspacio(EspacioVectorial espacio);
  Algoritmo* setTamSol(int tam_sol);
  EspacioVectorial getSolucion() const;

 protected:
  EspacioVectorial espacio_;
  EspacioVectorial solucion_;
  int tam_sol; // tamaño de la solución
};

#endif