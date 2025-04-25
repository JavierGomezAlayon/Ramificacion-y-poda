// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: DAA
// Curso: 3º
// Práctica 06 : Ramificación_y_poda
// Autor: javier Gómez Alayón
// Correo: alu0101562445@ull.edu.es
// Fecha: 04/25/25
// Archivo funciones_main.h: Declaración de las funciones del main
//        En este fichero se declara las funciones que se utilizan en el main.cc
//
// Historial de revisiones
//        04/25/25 - Creación (primera versión) del código
#ifndef C_funciones_main_H
#define C_funciones_main_H

#include<iostream>
#include<string>


struct Dato {
  bool correcto;
  std::string fichero;
};

Dato recoger_parametro(int argc, char *argv[]);
void mostrar_ayuda();
void mostrar_ayuda_resumida();
void menu();
void mostrar_ayuda_menu();

#endif