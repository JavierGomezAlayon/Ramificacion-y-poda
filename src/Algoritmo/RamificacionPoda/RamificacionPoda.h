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
#include <queue>
#include <set>
#include <algorithm>
#include <limits>
#include <vector>
#include <utility>

struct Node {
  std::set<int> selected;   // Elementos seleccionados
  std::set<int> unselected; // Elementos no seleccionados
  int level;                // Nivel del nodo en el árbol de búsqueda
};

struct NodeWithBound : public Node {
  double upper_bound;   // Cota superior (UB) del nodo
  
  // Operador de comparación para la cola de prioridad (orden descendente por UB)
  bool operator<(const NodeWithBound& other) const {
    return upper_bound < other.upper_bound;  // Ordenar en orden descendente por UB
  }
};

class RamificacionPoda : public Algoritmo {
 public:
  RamificacionPoda();
  RamificacionPoda* solve() override;
  RamificacionPoda* setGraspSolution(const EspacioVectorial& grasp_solution);
  RamificacionPoda* setVorazSolution(const EspacioVectorial& voraz_solution);
  RamificacionPoda* setTamLista(int tam_lista);
  RamificacionPoda* setIteraciones(int iteraciones);
  int getNodesGenerated() const;

 private:
  std::vector<std::vector<double>> distance_matrix_;
  std::vector<double> total_distance_to_others_;
  std::vector<std::vector<int>> sorted_indices_by_distance_;
  double best_known_solution_value_;
  std::set<int> best_solution_;
  EspacioVectorial grasp_solution_;
  // Parámetros para GRASP
  int tam_lista_;
  int iteraciones_;
  int nodes_generated_;
  // Solución Voraz
  EspacioVectorial voraz_solution_;

  // Métodos auxiliares
  void precomputeDistances();
  double calculateObjectiveValue(const std::set<int>& selected_elements);
  double calculateUpperBound(const std::set<int>& selected_elements, const std::set<int>& unselected_elements, int elements_to_select);
  void updateBestSolution(const std::set<int>& solution, double value);
};

#endif
