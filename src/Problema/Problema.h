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
#include"../Algoritmo/BusquedaLocal/BusquedaLocal.h"
#include<algorithm>
#include<chrono>

struct Resultado {
  string fichero;
  int num_puntos;
  int dimensiones;
  int tam_sol;
  int tam_lista;
  int iter;  // preguntar que es
  double z;
  long double tiempo;
  EspacioVectorial espacio;
  int type; // 0: Voraz, 1: Grasp
};


class Problema {
 public:
  Problema();
  Problema(EspacioVectorial espacio_vectorial);
  vector<Resultado>& get_resultados();
  Problema* grasp(int tam_sol ,int candidatos_grasp, int iteraciones);
  Problema* voraz(int tam_sol);
  Problema* set_espacio(EspacioVectorial espacio_vectorial);
  Problema* set_fichero(string fichero);
  Problema* mostrar_resultados();
  Problema* resultados_clear();
 private: 
  void mostrar_resultados_voraz(vector<Resultado>& resultados);
  void mostrar_resultados_grasp(vector<Resultado>& resultados);
  EspacioVectorial espacio_;
  vector<Algoritmo*> algoritmos_; // 0: voraz, 1: grasp, 2: busqueda local
  vector<Resultado> resultados_;
  string fichero_;
};


#endif