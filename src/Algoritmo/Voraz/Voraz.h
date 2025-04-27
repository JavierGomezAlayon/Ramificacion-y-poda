// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: DAA
// Curso: 3º
// Práctica 06 : Ramificación_y_poda
// Autor: javier Gómez Alayón
// Correo: alu0101562445@ull.edu.es
// Fecha: 04/25/25
// Archivo Voraz.h : Declaración de la clase Voraz
//        En este fichero se declara la clase Voraz
//
// Historial de revisiones
//        04/25/25 - Creación (primera versión) del código
#ifndef C_Voraz_H
#define C_Voraz_H
#include "../Algoritmo.h"

class Voraz : public Algoritmo {
 public:
  Voraz();
  Voraz* solve() override;

 private:
  Punto puntoMasLejano(const Punto& centro);
};

#endif