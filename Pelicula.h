/*
Autor: Alma Teresa Carpio Revilla
Matrícula: A01798523
Definición de clase hijo "Pelicula" la cual representa una película.
*/

//Verificar que la clase no esté definida y definirla
#ifndef PELICULA_H
#define PELICULA_H

#include "Video.h"

class Pelicula : public Video {
public:
  //Sobreescribimos para devolver falso, indicando que no es una serie
  bool esSerie() const {
      return false;
  }
};

#endif //PELICULA_H
