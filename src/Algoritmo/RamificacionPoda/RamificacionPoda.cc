// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: DAA
// Curso: 3º
// Práctica 06 : Ramificación_y_poda
// Autor: javier Gómez Alayón
// Correo: alu0101562445@ull.edu.es
// Fecha: 05/03/25
// Archivo RamificacionPoda.cc: Implementación de RamificacionPoda
//        En este fichero se implementa las funciones de la clase RamificacionPoda
//
// Historial de revisiones
//        05/03/25 - Creación (primera versión) del código

#include "RamificacionPoda.h"

/** RamificacionPoda::RamificacionPoda()
  * @brief Crea el objeto de la clase RamificacionPoda.
  * @return objeto de la clase RamificacionPoda
  */
RamificacionPoda::RamificacionPoda() {
  this->tam_lista_ = 3;  // Valor por defecto
  this->iteraciones_ = 10;  // Valor por defecto
  this->best_known_solution_value_ = 0.0;
}

/** RamificacionPoda::setGraspSolution()
  * @brief Establece la solución GRASP inicial.
  * @param grasp_solution Solución GRASP
  * @return this
  */
RamificacionPoda* RamificacionPoda::setGraspSolution(const EspacioVectorial& grasp_solution) {
  this->grasp_solution_ = grasp_solution;
  return this;
}

/** RamificacionPoda::setTamLista()
  * @brief Establece el tamaño de la lista de candidatos para GRASP.
  * @param tam_lista Tamaño de la lista
  * @return this
  */
RamificacionPoda* RamificacionPoda::setTamLista(int tam_lista) {
  this->tam_lista_ = tam_lista;
  return this;
}

/** RamificacionPoda::setIteraciones()
  * @brief Establece el número de iteraciones para GRASP.
  * @param iteraciones Número de iteraciones
  * @return this
  */
RamificacionPoda* RamificacionPoda::setIteraciones(int iteraciones) {
  this->iteraciones_ = iteraciones;
  return this;
}

/** RamificacionPoda::precomputeDistances()
  * @brief Precomputa las distancias entre todos los puntos y crea listas ordenadas.
  */
void RamificacionPoda::precomputeDistances() {
  int number_of_elements = this->espacio_.getSize();
  
  // Inicializar la matriz de distancias
  this->distance_matrix_.resize(number_of_elements, std::vector<double>(number_of_elements, 0.0));
  
  // Calcular todas las distancias entre puntos
  for (int i = 0; i < number_of_elements; i++) {
    for (int j = 0; j < number_of_elements; j++) {
      if (i != j) {
        this->distance_matrix_[i][j] = this->espacio_[i].Distancia(this->espacio_[j]);
      }
    }
  }
  
  // Inicializar vectores para distancias totales e índices ordenados
  this->total_distance_to_others_.resize(number_of_elements, 0.0);
  this->sorted_indices_by_distance_.resize(number_of_elements);
  
  // Calcular distancias totales y listas ordenadas para cada punto
  for (int vertex = 0; vertex < number_of_elements; vertex++) {
    // Calcular la distancia total a otros puntos
    for (int other_vertex = 0; other_vertex < number_of_elements; other_vertex++) {
      if (other_vertex != vertex) {
        this->total_distance_to_others_[vertex] += this->distance_matrix_[vertex][other_vertex];
      }
    }
    
    // Crear lista de pares (distancia, índice) para ordenar
    std::vector<std::pair<double, int>> distances;
    for (int other_vertex = 0; other_vertex < number_of_elements; other_vertex++) {
      if (other_vertex != vertex) {
        distances.push_back({this->distance_matrix_[vertex][other_vertex], other_vertex});
      }
    }
    
    // Ordenar por distancia descendente
    std::sort(distances.begin(), distances.end(), std::greater<std::pair<double, int>>());
    
    // Almacenar los índices ordenados
    this->sorted_indices_by_distance_[vertex].clear();
    for (auto& p : distances) {
      this->sorted_indices_by_distance_[vertex].push_back(p.second);
    }
  }
}

/** RamificacionPoda::calculateObjectiveValue()
  * @brief Calcula el valor objetivo para un conjunto de elementos seleccionados.
  * @param selected_elements Conjunto de elementos seleccionados
  * @return Valor objetivo (suma de distancias entre todos los pares)
  */
double RamificacionPoda::calculateObjectiveValue(const std::set<int>& selected_elements) {
  double objective_value = 0.0;
  
  for (auto it1 = selected_elements.begin(); it1 != selected_elements.end(); ++it1) {
    for (auto it2 = std::next(it1); it2 != selected_elements.end(); ++it2) {
      objective_value += this->distance_matrix_[*it1][*it2];
    }
  }
  
  return objective_value;
}

/** RamificacionPoda::updateBestSolution()
  * @brief Actualiza la mejor solución si se encuentra una mejor.
  * @param solution Solución candidata
  * @param value Valor objetivo de la solución
  */
void RamificacionPoda::updateBestSolution(const std::set<int>& solution, double value) {
  if (value > this->best_known_solution_value_) {
    this->best_known_solution_value_ = value;
    this->best_solution_ = solution;
  }
}

/** RamificacionPoda::solve()
  * @brief Resuelve el problema utilizando el algoritmo de Ramificación y Poda.
  * @return this
  */
RamificacionPoda* RamificacionPoda::solve() {
  // Si no tenemos una solución GRASP, la calculamos
  if (this->grasp_solution_.getSize() == 0) {
    Grasp grasp;
    dynamic_cast<Grasp*>(grasp.setEspacio(this->espacio_)
         ->setTamSol(this->tam_sol))
         ->setTamLista(this->tam_lista_)
         ->solve();
    this->grasp_solution_ = grasp.getSolucion();
  }
  
  // Precomputar distancias y listas ordenadas
  this->precomputeDistances();
  
  int number_of_elements = this->espacio_.getSize();
  int elements_to_select = this->tam_sol;
  
  // Inicializar el límite inferior usando la solución GRASP
  this->best_known_solution_value_ = this->grasp_solution_.getZ();
  
  // Crear conjunto con los índices de la solución GRASP
  std::set<int> grasp_indices;
  for (int i = 0; i < this->grasp_solution_.getSize(); i++) {
    // Buscar el índice del punto en el espacio original
    for (int j = 0; j < number_of_elements; j++) {
      if (this->grasp_solution_[i].getId() == this->espacio_[j].getId()) {
        grasp_indices.insert(j);
        break;
      }
    }
  }
  this->best_solution_ = grasp_indices;
  
  // Pila para nodos, empezar con nodo raíz (ninguna selección, k=0)
  std::stack<std::pair<std::set<int>, int>> exploration_stack;
  exploration_stack.push({std::set<int>(), 0}); // Comenzar con conjunto vacío y k=0
  
  while (!exploration_stack.empty()) {
    auto current_node = exploration_stack.top(); exploration_stack.pop();
    std::set<int> current_selected_elements = current_node.first;
    int number_of_selected = current_node.second;
    
    if (number_of_selected == elements_to_select) { // Solución completa
      double objective_value = this->calculateObjectiveValue(current_selected_elements);
      this->updateBestSolution(current_selected_elements, objective_value);
    } else {
      // Regla de dominancia: podar si hay un elemento no seleccionado con mayor distancia total que algún seleccionado
      double min_total_distance_selected = std::numeric_limits<double>::infinity();
      if (!current_selected_elements.empty()) {
        for (int s : current_selected_elements) {
          if (this->total_distance_to_others_[s] < min_total_distance_selected) {
            min_total_distance_selected = this->total_distance_to_others_[s];
          }
        }
      }
      
      double max_total_distance_unselected = -std::numeric_limits<double>::infinity();
      for (int v = 0; v < number_of_elements; v++) {
        if (current_selected_elements.find(v) == current_selected_elements.end()) {
          if (this->total_distance_to_others_[v] > max_total_distance_unselected) {
            max_total_distance_unselected = this->total_distance_to_others_[v];
          }
        }
      }
      
      if (min_total_distance_selected < max_total_distance_unselected && !current_selected_elements.empty()) {
        continue; // Poda por dominancia
      }
      
      // Calcular cota superior (z1 + UB23)
      double sum_distances_within_selected = this->calculateObjectiveValue(current_selected_elements);
      
      std::vector<std::pair<double, int>> estimated_contributions;
      for (int v = 0; v < number_of_elements; v++) {
        if (current_selected_elements.find(v) == current_selected_elements.end()) {
          double contribution_to_selected = 0;
          for (int s : current_selected_elements) {
            contribution_to_selected += this->distance_matrix_[s][v];
          }
          
          double sum_unselected_distances = 0;
          int count = 0;
          for (int u : this->sorted_indices_by_distance_[v]) {
            if (current_selected_elements.find(u) == current_selected_elements.end() && 
                count < elements_to_select - number_of_selected - 1) {
              sum_unselected_distances += this->distance_matrix_[v][u];
              count++;
            }
          }
          
          double contribution_unselected = 0.5 * sum_unselected_distances;
          double total_estimated_contribution = contribution_to_selected + contribution_unselected;
          estimated_contributions.push_back({total_estimated_contribution, v});
        }
      }
      
      std::sort(estimated_contributions.begin(), estimated_contributions.end(), 
                std::greater<std::pair<double, int>>());
      
      double upper_bound_contribution = 0;
      for (int i = 0; i < elements_to_select - number_of_selected && i < estimated_contributions.size(); i++) {
        upper_bound_contribution += estimated_contributions[i].first;
      }
      
      double upper_bound = sum_distances_within_selected + upper_bound_contribution;
      
      if (upper_bound < this->best_known_solution_value_) {
        continue; // Poda por cota superior
      }
      
      // Solución heurística: seleccionar los mejores elementos por contribución estimada
      std::vector<int> top_candidates;
      for (int i = 0; i < elements_to_select - number_of_selected && i < estimated_contributions.size(); i++) {
        top_candidates.push_back(estimated_contributions[i].second);
      }
      
      std::set<int> heuristic_solution = current_selected_elements;
      for (int v : top_candidates) {
        heuristic_solution.insert(v);
      }
      
      double heuristic_value = this->calculateObjectiveValue(heuristic_solution);
      this->updateBestSolution(heuristic_solution, heuristic_value);
      
      // Ramificación: generar nodos hijos añadiendo cada elemento no seleccionado
      // Ordenamos por contribución estimada para explorar primero los más prometedores
      for (auto& p : estimated_contributions) {
        int v = p.second;
        std::set<int> new_selected_elements = current_selected_elements;
        new_selected_elements.insert(v);
        exploration_stack.push({new_selected_elements, number_of_selected + 1});
      }
    }
  }
  
  // Construir la solución final a partir de best_solution_
  this->solucion_ = EspacioVectorial();
  for (int idx : this->best_solution_) {
    this->solucion_.addPunto(this->espacio_[idx]);
  }
  
  return this;
}
