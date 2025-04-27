// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: DAA
// Curso: 3º
// Práctica 06 : Ramificación_y_poda
// Autor: javier Gómez Alayón
// Correo: alu0101562445@ull.edu.es
// Fecha: 04/25/25
// Archivo Punto.h : Declaración de la clase Punto
//        En este fichero se declara la clase Punto
//
// Historial de revisiones
//        04/25/25 - Creación (primera versión) del código
#ifndef C_Punto_H
#define C_Punto_H
#include<vector>
#include<iostream>
#include<cmath>
using namespace std;
class Punto {
 public:
  Punto();
  Punto(const std::vector<double>& coordenadas);
  double Distancia(const Punto& otro) const;
  int getNumeroDimensiones() const;
  vector<double> getCoordenadas() const;

 private:
  std::vector<double> coordenadas_;
  
};

#endif