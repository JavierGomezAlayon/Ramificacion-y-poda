// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: DAA
// Curso: 3º
// Práctica 06 : Ramificación_y_poda
// Autor: javier Gómez Alayón
// Correo: alu0101562445@ull.edu.es
// Fecha: 05/03/25
// Archivo RamificacionPoda.h : Declaración de la clase RamificacionPoda
//        En este fichero se declara la clase RamificacionPoda
//
// Historial de revisiones
//        05/03/25 - Creación (primera versión) del código
#ifndef C_RamificacionPoda_H
#define C_RamificacionPoda_H
#include "../Algoritmo.h"
#include "../Grasp/Grasp.h"
#include <stack>
#include <set>
#include <algorithm>
#include <limits>
#include <vector>
#include <utility>

class RamificacionPoda : public Algoritmo {
 public:
  RamificacionPoda();
  RamificacionPoda* solve() override;
  RamificacionPoda* setGraspSolution(const EspacioVectorial& grasp_solution);
  RamificacionPoda* setTamLista(int tam_lista);
  RamificacionPoda* setIteraciones(int iteraciones);

 private:
  // Estructura para almacenar la matriz de distancias
  std::vector<std::vector<double>> distance_matrix_;
  // Vector para almacenar la distancia total de cada punto a todos los demás
  std::vector<double> total_distance_to_others_;
  // Vector de vectores para almacenar los índices ordenados por distancia para cada punto
  std::vector<std::vector<int>> sorted_indices_by_distance_;
  // Mejor valor conocido (límite inferior)
  double best_known_solution_value_;
  // Mejor solución encontrada
  std::set<int> best_solution_;
  // Solución GRASP
  EspacioVectorial grasp_solution_;
  // Parámetros para GRASP
  int tam_lista_;
  int iteraciones_;

  // Métodos auxiliares
  void precomputeDistances();
  double calculateObjectiveValue(const std::set<int>& selected_elements);
  void updateBestSolution(const std::set<int>& solution, double value);
};

#endif
