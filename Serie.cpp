/*
Autor: Alma Teresa Carpio Revilla
Matrícula: A01798523
Definición de clase hijo "Serie" la cual representa una serie de TV.
*/

#include "Video.h"
#include "Serie.h"

//Devueve true, para indicar que es una serie
bool Serie::esSerie() const {
    return true;
}
//Implementación del método getIdEpisodio() para obtener el id del episodio
std::string Serie::getIdEpisodio() const {
    return idEpisodio;
}
//Implementación del método getNombreEpisodio() para obtener el nombre del episodio
std::string Serie::getNombreEpisodio() const {
    return nombreEpisodio;
}
//Implementación del método getTemporada() para obtener la temporada a la que pertenece el episodio
std::string Serie::getTemporada() const {
    return temporada;
}
//Implementación del método getNumEpisodio() para obtener el número del episodio
std::string Serie::getNumEpisodio() const {
    return numEpisodio;
}
//Implementación del método setIdEpisodio() para establecer el id del episodio
void Serie::setIdEpisodio(const std::string& newIdEpisodio) {
    idEpisodio = newIdEpisodio;
}
//Implementación del método setNombreEpisodio() para establecer el nombre del episodio
void Serie::setNombreEpisodio(const std::string& newNombreEpisodio) {
    nombreEpisodio = newNombreEpisodio;
}
//Implementación del método setTemporada() para establecer la temporada a la que pertenece el episodio
void Serie::setTemporada(const std::string& newTemporada) {
    temporada = newTemporada;
}
//Implementación del método setNumEpisodio() para establecer el número del episodio
void Serie::setNumEpisodio(const std::string& newNumEpisodio) {
    numEpisodio = newNumEpisodio;
}
