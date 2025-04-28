// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: DAA
// Curso: 3º
// Práctica 06 : Ramificación_y_poda
// Autor: javier Gómez Alayón
// Correo: alu0101562445@ull.edu.es
// Fecha: 04/27/25
// Archivo Problema.cc: Implementación de Problema
//        En este fichero se implementa las funciones de la clase Problema
//
// Historial de revisiones
//        04/27/25 - Creación (primera versión) del código

#include"Problema.h"

/** Problema::Problema()
  * @brief Crea el objeto de la clase Problema.
  * @return objeto de la clase Problema
  */
 Problema::Problema() {
  Algoritmo* voraz = new Voraz();
  Algoritmo* grasp = new Grasp();
  Algoritmo* busqueda = new BusquedaLocal();
  this->algoritmos_ = {voraz, grasp, busqueda};
}

/** Problema::Problema()
  * @brief Crea el objeto de la clase Problema.
  * @param espacio_vectorial: Espacio vectorial
  * @return objeto de la clase Problema
  */
 Problema::Problema(EspacioVectorial espacio_vectorial) {
  Algoritmo* voraz = new Voraz();
  Algoritmo* grasp = new Grasp();
  Algoritmo* busqueda = new BusquedaLocal();
  this->algoritmos_ = {voraz, grasp, busqueda};
  this->espacio_ = espacio_vectorial;
}

/** Problema::set_espacio()
  * @brief Establece el espacio vectorial.
  * @param espacio_vectorial: Espacio vectorial
  * @return this
  */
Problema* Problema::set_espacio(EspacioVectorial espacio_vectorial) {
  this->espacio_ = espacio_vectorial;
  return this;
}

/** Problema::get_resultados()
  * @brief Devuelve los results obtenidos.
  * @return vector<EspacioVectorial>&: Resultados
  */
vector<Resultado>& Problema::get_resultados() {
  return this->resultados_;
}

/** Problema::grasp()
  * @brief Resuelve el problema con el algoritmo GRASP.
  * @param tam_sol: Tamaño de la solución
  * @param candidatos_grasp: Número de candidatos para el algoritmo GRASP
  * @return Problema*
  * @exception invalid_argument: Si el número de candidatos es menor que 1
  * @exception invalid_argument: Si el tamaño de la solución es menor que 1
  */
 Problema* Problema::grasp(int tam_sol ,int candidatos_grasp) {
  if (candidatos_grasp < 1) {
    throw std::invalid_argument("El número de candidatos para el algoritmo GRASP debe ser mayor que 0");
  }
  if (tam_sol < 1) {
    throw std::invalid_argument("El tamaño de la solución debe ser mayor que 0");
  }
  dynamic_cast<Grasp*>(this->algoritmos_[1]->setEspacio(this->espacio_))->setTamLista(candidatos_grasp)->setTamSol(tam_sol);
  auto start = chrono::high_resolution_clock::now();
  EspacioVectorial solucion = this->algoritmos_[1]->solve()->getSolucion();

  dynamic_cast<BusquedaLocal*>(this->algoritmos_[2]->setEspacio(this->espacio_))->setSolucion(solucion)->solve();
  EspacioVectorial solucion_busqueda = this->algoritmos_[2]->getSolucion();
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double> tiempo = end - start;
  this->algoritmos_[2]->reset();
  this->algoritmos_[1]->reset();
  
  // Hago los results
  Resultado resultado;
  resultado.fichero = this->fichero_;
  resultado.espacio = solucion_busqueda;
  resultado.dimensiones = solucion_busqueda[0].getNumeroDimensiones();
  resultado.z = solucion_busqueda.getZ();
  resultado.tiempo = tiempo.count();
  resultado.num_puntos = this->espacio_.getSize();
  resultado.tam_lista = candidatos_grasp;
  resultado.type = 1;
  resultado.tam_sol = tam_sol;
  this->resultados_.push_back(resultado);
  return this;
}

/** Problema::voraz()
  * @brief Resuelve el problema con el algoritmo voraz.
  * @return Problema*
  */
 Problema* Problema::voraz(int tam_sol) {
  if (tam_sol < 1) {
    throw std::invalid_argument("El tamaño de la solución debe ser mayor que 0");
  }
  this->algoritmos_[0]->setEspacio(this->espacio_)->setTamSol(tam_sol);
  auto start = chrono::high_resolution_clock::now();
  EspacioVectorial solucion = this->algoritmos_[0]->solve()->getSolucion();
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double> tiempo = end - start;
  this->algoritmos_[0]->reset();
  
  // Hago los results
  Resultado resultado;
  resultado.fichero = this->fichero_;
  resultado.espacio = solucion;
  resultado.dimensiones = solucion[0].getNumeroDimensiones();
  resultado.z = solucion.getZ();
  resultado.tiempo = tiempo.count();
  resultado.num_puntos = this->espacio_.getSize();
  resultado.tam_lista = -1;
  resultado.tam_sol = tam_sol;
  resultado.type = 0;
  this->resultados_.push_back(resultado);
  return this;
}

/** Problema::mostrar_resultados()
  * @brief Muestra los results.
  * @return Problema*
  */
 Problema* Problema::mostrar_resultados() {
  cout << "Resultados:" << endl;
  // ordeno el vector de results por el tipo de algoritmo
  sort(this->resultados_.begin(), this->resultados_.end(), [](const Resultado& a, const Resultado& b) {
    return a.type < b.type;
  });
  // diferencio los results por el tipo de algoritmo
  vector<int> counts(2, 0); // Para contar la cantidad de cada tipo (0: voraz, 1: grasp)
  for (const auto& resultado : this->resultados_) {
    counts[resultado.type]++;
  }
  // divido el vector de results en 3 partes
  vector<Resultado> resultados_voraz(this->resultados_.begin(), this->resultados_.begin() + counts[0]);
  vector<Resultado> resultados_grasp(this->resultados_.begin() + counts[0], this->resultados_.begin() + counts[0] + counts[1]);
  // muestro los results de cada algoritmo
  if (resultados_voraz.size() > 0) {
    // ordeno los results
    sort(resultados_voraz.begin(), resultados_voraz.end(), [](const Resultado& a, const Resultado& b) {
      if (a.num_puntos == b.num_puntos) {
        if (a.dimensiones == b.dimensiones) {
          if (a.tam_sol == b.tam_sol) {
            return a.z < b.z;
          }
          return a.tam_sol < b.tam_sol;
        }
        return a.dimensiones < b.dimensiones;
      }
      return a.num_puntos < b.num_puntos;
    });
    this->mostrar_resultados_voraz(resultados_voraz);
  }
  if (resultados_grasp.size() > 0) {
    sort(resultados_grasp.begin(), resultados_grasp.end(), [](const Resultado& a, const Resultado& b) {
      if (a.num_puntos == b.num_puntos) {
        if (a.dimensiones == b.dimensiones) {
          if (a.tam_sol == b.tam_sol) {
            if (a.tam_lista == b.tam_lista) {
              return a.z < b.z;
            }
            return a.tam_lista < b.tam_lista;
          }
          return a.tam_sol < b.tam_sol;
        }
        return a.dimensiones < b.dimensiones;
      }
      return a.num_puntos < b.num_puntos;
    });
    this->mostrar_resultados_grasp(resultados_grasp);
  }
  return this;
}

/** Problema::mostrar_resultados_voraz()
  * @brief Muestra los results del algoritmo voraz.
  * @return void
  */
void Problema::mostrar_resultados_voraz(vector<Resultado>& results) {
  int resultados_size = results.size();
  const string separador = "-----------------------------------------------------------------------------------------------------------";
  // Cabecera
  cout << endl;
  cout << separador << endl;
  cout << "Resultados del algoritmo voraz:" << endl;
  cout << separador << endl;
  cout << fixed << setprecision(4);
  cout << left 
  << setw(18) << "Problema" 
  << setw(5) << "n" 
  << setw(5) << "K" 
  << setw(5) << "m" 
  << setw(12) << "z" 
  << setw(24) << "S"
  << setw(12) << "CPU"
  << endl;
  cout << separador << endl;

  // double mediaZonas = 0.0, mediaCV = 0.0, mediaTV = 0.0, mediaCPU = 0.0, mediaCoste = 0.0;
  // Itero sobre los datos
  for (int i = 0; i < resultados_size; i++) {
    cout << fixed << setprecision(4);
    cout << left 
    << setw(18) << results[i].fichero
    << setw(5) << results[i].num_puntos
    << setw(5) << results[i].dimensiones
    << setw(5) << results[i].tam_sol
    << setw(12) << results[i].z
    << setw(24) << results[i].espacio.ids()
    << setw(12) << setprecision(8) << results[i].tiempo << setprecision(4)
    << endl;
    // mediaZonas += results[i].num_zonas_;
    // mediaCV += results[i].rutas_recoleccion_.size();
    // mediaTV += results[i].rutas_transporte_.size();
    // mediaCPU += results[i].tiempo_ejecucion_;
    // mediaCoste += results[i].coste_total_;
  }
  // Medias
  // cout << separador << endl;
  // mediaZonas /= results.size();
  // mediaCV /= results.size();
  // mediaTV /= results.size();
  // mediaCPU /= results.size();
  // mediaCoste /= results.size();
  // cout << fixed << setprecision(2);
  // cout << left 
  // << setw(15) << "Averages" 
  // << setw(8) << mediaZonas
  // << setw(6) << mediaCV
  // << setw(6) << mediaTV
  // << setw(12) << mediaCPU
  // << setw(12) << mediaCoste
  // << endl;
  cout << separador << endl;
  cout << "Fin de la tabla voraz" << endl;
}

/** Problema::mostrar_resultados_grasp()
  * @brief Muestra los results del algoritmo GRASP.
  * @return void
  */
void Problema::mostrar_resultados_grasp(vector<Resultado>& results) {
  int resultados_size = results.size();
  const string separador = "-----------------------------------------------------------------------------------------------------------";
  // Cabecera
  cout << endl;
  cout << separador << endl;
  cout << "Resultados del algoritmo GRASP:" << endl;
  cout << separador << endl;
  cout << fixed << setprecision(4);
  cout << left 
  << setw(18) << "Problema" 
  << setw(5) << "n" 
  << setw(5) << "K" 
  << setw(5) << "m" 
  << setw(5) << "Iter"
  << setw(6) << "|LRC|"
  << setw(12) << "z" 
  << setw(24) << "S"
  << setw(12) << "CPU"
  << endl;
  cout << separador << endl;

  // double mediaZonas = 0.0, mediaCV = 0.0, mediaTV = 0.0, mediaCPU = 0.0, mediaLRC = 0.0, mediaCoste = 0.0;
  // Itero sobre los datos
  for (int i = 0; i < resultados_size; i++) {
    cout << fixed << setprecision(4);
    cout << left 
    << setw(18) << results[i].fichero
    << setw(5) << results[i].num_puntos
    << setw(5) << results[i].dimensiones
    << setw(5) << results[i].tam_sol
    // << setw(5) << results[i].iter
    << setw(5) << 10
    << setw(6) << results[i].tam_lista
    << setw(12) << results[i].z
    << setw(24) << results[i].espacio.ids()
    << setw(12) << setprecision(8) << results[i].tiempo << setprecision(4)
    << endl;
    // mediaZonas += results[i].num_zonas_;
    // mediaLRC += results[i].num_candidatos_grasp_;
    // mediaCV += results[i].rutas_recoleccion_.size();
    // mediaTV += results[i].rutas_transporte_.size();
    // mediaCPU += results[i].tiempo_ejecucion_;
    // mediaCoste += results[i].coste_total_;
  }
  // Medias
  // cout << separador << endl;
  // mediaZonas /= results.size();
  // mediaLRC /= results.size();
  // mediaCV /= results.size();
  // mediaTV /= results.size();
  // mediaCPU /= results.size();
  // mediaCoste /= results.size();
  // cout << fixed << setprecision(2);
  // cout << left 
  // << setw(15) << "Averages" 
  // << setw(8) << int(mediaZonas)
  // << setw(6) << int(mediaLRC)
  // << setw(6) << mediaCV
  // << setw(6) << mediaTV
  // << setw(12) << mediaCPU
  // << setw(12) << mediaCoste
  // << endl;
  cout << separador << endl;
  cout << "Fin de la tabla GRASP" << endl;
}


/** Problema::resultados_clear()
  * @brief Limpia los results.
  * @return this
  */
Problema* Problema::resultados_clear() {
  this->resultados_.clear();
  return this;
}

/** Problema::set_fichero()
  * @brief Establece el fichero que quiere el usuario
  * @return this
  */
Problema* Problema::set_fichero(string fichero) {
  this->fichero_ = fichero;
  return this;
}