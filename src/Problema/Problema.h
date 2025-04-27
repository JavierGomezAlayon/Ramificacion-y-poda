// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: DAA
// Curso: 3º
// Práctica 06 : Ramificación_y_poda
// Autor: javier Gómez Alayón
// Correo: alu0101562445@ull.edu.es
// Fecha: 04/27/25
// Archivo Problema.h : Declaración de la clase Problema
//        En este fichero se declara la clase Problema
//
// Historial de revisiones
//        04/27/25 - Creación (primera versión) del código
#ifndef C_Problema_H
#define C_Problema_H
#include"../EspacioVectorial/EspacioVectorial.h"
#include"../Algoritmo/Voraz/Voraz.h"
#include"../Algoritmo/Grasp/Grasp.h"


class Problema {
 public:
  Problema();
  Problema& setEspacio(const EspacioVectorial& espacio);
  Problema& getSolucion(int index);
 private:
  EspacioVectorial espacio_;
  vector<Algoritmo*> algoritmos_;
};

#endif