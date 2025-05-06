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
  this->nodes_generated_ = 0;  // Inicializar contador de nodos
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

/** RamificacionPoda::setVorazSolution()
  * @brief Establece la solución Voraz inicial.
  * @param voraz_solution Solución Voraz
  * @return this
  */
RamificacionPoda* RamificacionPoda::setVorazSolution(const EspacioVectorial& voraz_solution) {
  this->voraz_solution_ = voraz_solution;
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
  this->distance_matrix_.clear();  // Limpiar primero para evitar problemas de memoria
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
  this->total_distance_to_others_.clear();  // Limpiar para evitar problemas de memoria
  this->total_distance_to_others_.resize(number_of_elements, 0.0);
  
  // Inicialización segura del vector de índices ordenados
  this->sorted_indices_by_distance_.clear();  // Limpiar primero
  this->sorted_indices_by_distance_ = std::vector<std::vector<int>>(number_of_elements);
  
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
    // No es necesario hacer clear() aquí ya que inicializamos el vector vacío arriba
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

/** RamificacionPoda::calculateUpperBound()
  * @brief Calcula una cota superior para un estado parcial de la solución.
  * @param selected_elements Conjunto de elementos seleccionados
  * @param unselected_elements Conjunto de elementos no seleccionados
  * @param elements_to_select Número total de elementos a seleccionar
  * @return Valor de la cota superior
  */
double RamificacionPoda::calculateUpperBound(const std::set<int>& selected_elements, 
                                            const std::set<int>& unselected_elements, 
                                            int elements_to_select) {
  // Calcular la suma de distancias entre los elementos ya seleccionados
  double sum_distances_selected = this->calculateObjectiveValue(selected_elements);
  
  // Calcular una cota superior para las distancias adicionales que se pueden obtener
  // seleccionando los elementos restantes de unselected_elements
  
  // Para cada par de elementos no seleccionados, calculamos su distancia
  std::vector<double> all_remaining_distances;
  for (int i : unselected_elements) {
    // Distancias entre elementos seleccionados y no seleccionados
    for (int j : selected_elements) {
      all_remaining_distances.push_back(this->distance_matrix_[i][j]);
    }
    
    // Distancias entre elementos no seleccionados
    for (int j : unselected_elements) {
      if (i < j) { // Evitar contar dos veces el mismo par
        all_remaining_distances.push_back(this->distance_matrix_[i][j]);
      }
    }
  }
  
  // Ordenar las distancias en orden descendente
  std::sort(all_remaining_distances.begin(), all_remaining_distances.end(), std::greater<double>());
  
  // Calcular cuántas aristas adicionales necesitamos
  int selected_size = selected_elements.size();
  int total_edges_needed = (elements_to_select * (elements_to_select - 1)) / 2;
  int current_edges = (selected_size * (selected_size - 1)) / 2;
  int additional_edges_needed = total_edges_needed - current_edges;
  
  // Sumar las mayores distancias restantes (cota superior optimista)
  double additional_distance = 0.0;
  for (int i = 0; i < additional_edges_needed && i < all_remaining_distances.size(); i++) {
    additional_distance += all_remaining_distances[i];
  }
  
  // La cota superior es la suma de las distancias ya seleccionadas más la estimación adicional
  return sum_distances_selected + additional_distance;
}

/** RamificacionPoda::solve()
  * @brief Resuelve el problema utilizando el algoritmo de Ramificación y Poda.
  * @return this
  */
RamificacionPoda* RamificacionPoda::solve() {
  // Precomputar distancias para agilizar cálculos
  this->precomputeDistances();
  
  int number_of_elements = this->espacio_.getSize();
  int elements_to_select = this->tam_sol;
  
  // Inicializar la mejor solución conocida y su valor
  this->best_solution_.clear();
  this->best_known_solution_value_ = 0.0;
  this->nodes_generated_ = 0; // Reiniciar contador de nodos
  
  // Usar la solución voraz como cota inferior inicial (LB)
  double LB = 0.0;
  if (this->voraz_solution_.getSize() > 0) {
    // Crear un conjunto con los índices de los puntos de la solución voraz
    std::set<int> voraz_indices;
    for (int i = 0; i < this->voraz_solution_.getSize(); ++i) {
      const Punto& voraz_point = this->voraz_solution_[i];
      for (int j = 0; j < number_of_elements; ++j) {
        if (this->espacio_[j] == voraz_point) {
          voraz_indices.insert(j);
          break;
        }
      }
    }
    
    // Calcular el valor objetivo de la solución voraz y usarlo como LB inicial
    LB = this->calculateObjectiveValue(voraz_indices);
    this->best_solution_ = voraz_indices;
    this->best_known_solution_value_ = LB;
  }
  
  // Inicializar la cola de prioridad para los nodos (ordenada por UB descendente)
  std::priority_queue<NodeWithBound> exploration_queue;
  
  // Crear el conjunto inicial de elementos no seleccionados
  std::set<int> all_elements;
  for (int i = 0; i < number_of_elements; i++) {
    all_elements.insert(i);
  }
  
  // Calcular la cota superior del nodo raíz
  double root_UB = this->calculateUpperBound(std::set<int>(), all_elements, elements_to_select);
  
  // Añadir el nodo raíz a la cola de prioridad
  exploration_queue.push({std::set<int>(), all_elements, 0, root_UB});
  this->nodes_generated_++; // Contar el nodo raíz
  
  // Bucle principal de ramificación y poda
  while (!exploration_queue.empty()) {
    // Extraer el nodo actual con mayor cota superior (UB)
    NodeWithBound best_node = exploration_queue.top();
    exploration_queue.pop();
    // Si hay más de un nodo en la cola, seleccionamos el segundo mejor
    // Si solo hay uno, usamos ese
    NodeWithBound current_node;
    if (!exploration_queue.empty()) {
      current_node = exploration_queue.top();
      exploration_queue.pop();
      exploration_queue.push(best_node);
    } else {
      current_node = best_node;
    }
    
    std::set<int> selected = current_node.selected;
    std::set<int> unselected = current_node.unselected;
    int level = current_node.level;
    double current_UB = current_node.upper_bound;
    if (current_UB < LB) {
      continue; // poda
    }
    // Caso 1: Tenemos una solución completa
    if (level == elements_to_select) {
      double objective_value = this->calculateObjectiveValue(selected);
      // Actualizar la cota inferior (LB) si encontramos una mejor solución
      if (objective_value > LB) {
        LB = objective_value;
        this->best_solution_ = selected;
        this->best_known_solution_value_ = objective_value;
      }
    } 
    // Caso 2: Solución parcial, ramificar
    else {
      // Ordenar los elementos no seleccionados por su contribución potencial a la función objetivo
      std::vector<int> unselected_ordered(unselected.begin(), unselected.end());
      // Para cada elemento no seleccionado, calculamos el UB del nodo hijo resultante
      std::vector<std::pair<double, int>> node_values;
      for (int v : unselected_ordered) {
        // Crear nuevos conjuntos para el nodo hijo
        std::set<int> new_selected = selected;
        std::set<int> new_unselected = unselected;
        // Mover el elemento v de unselected a selected
        new_selected.insert(v);
        new_unselected.erase(v);
        // Calcular la cota superior para este nodo hijo
        double child_UB = this->calculateUpperBound(new_selected, new_unselected, elements_to_select);
        // Añadir a la lista para ordenar después
        node_values.push_back({child_UB, v});
      }
      // Ordenar los nodos por cota superior descendente
      std::sort(node_values.begin(), node_values.end(), std::greater<std::pair<double, int>>());
      // Añadir todos los nodos que tengan UB ≥ LB a la cola de prioridad
      for (const auto& [child_UB, v] : node_values) {
        if (child_UB >= LB) {
          // Crear nuevos conjuntos para el nodo hijo
          std::set<int> new_selected = selected;
          std::set<int> new_unselected = unselected;
          // Mover el elemento v de unselected a selected
          new_selected.insert(v);
          new_unselected.erase(v);
          // Añadir el nodo a la cola de prioridad
          exploration_queue.push({new_selected, new_unselected, level + 1, child_UB});
          this->nodes_generated_++; // Incrementar contador de nodos
        }
      }
    }
  }
  
  // Construir la solución final a partir de best_solution_
  this->solucion_ = EspacioVectorial();
  if (!this->best_solution_.empty()) { // Verificar que best_solution_ no está vacía
    for (int idx : this->best_solution_) {
      if (idx >= 0 && idx < number_of_elements) { // Validar índices
        this->solucion_.addPunto(this->espacio_[idx]);
      }
    }
  }
  
  return this;
}

// Añadir método para obtener el número de nodos generados
int RamificacionPoda::getNodesGenerated() const {
  return this->nodes_generated_;
}
