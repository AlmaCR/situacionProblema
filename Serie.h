/*
Autor: Alma Teresa Carpio Revilla
Matrícula: A01798523
Definición de clase hijo "Serie" la cual representa una serie de TV.
*/

//Verificar que la clase no esté definida y definirla
#ifndef SERIE_H
#define SERIE_H

#include "Video.h"

class Serie : public Video {
//Atributos
private:
  std::string idEpisodio;
  std::string nombreEpisodio;
  std::string temporada;
  std::string numEpisodio;
//Métodos
public:
  //Sobrescribimos para devolver true, indicando que si es una serie
  bool esSerie() const; 
  //Getters
  std::string getIdEpisodio() const;
  std::string getNombreEpisodio() const;
  std::string getTemporada() const;
  std::string getNumEpisodio() const;
  //Setters
  void setIdEpisodio(const std::string& newIdEpisodio);
  void setNombreEpisodio(const std::string& newNombreEpisodio);
  void setTemporada(const std::string& newTemporada);
  void setNumEpisodio(const std::string& newNumEpisodio);
};

#endif // SERIE_H
