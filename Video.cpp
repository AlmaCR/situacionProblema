/*
Autor: Alma Teresa Carpio Revilla
Matrícula: A01798523
Implementación de los métodos de la clase base abstracta "Video" la cual representa un vídeo genérico.
*/

#include "Video.h"

//Implementación del método getId() para obtener el id
std::string Video::getId() const {
    return id;
}
//Implementación del método getNombre() para obtener el nombre
std::string Video::getNombre() const {
    return nombre;
}
//Implementación del método getDuracion() para obtener la duracion
std::string Video::getDuracion() const {
    return duracion;
}
//Implementación del método getGenero() para obtener el genero
std::string Video::getGenero() const {
    return genero;
}
//Implementación del método getCalificacion() para obtener la calificacion
std::string Video::getCalificacion() const {
    return calificacion;
}
//Implementación del método getFechaEstreno() para obtener la fecha de estreno
std::string Video::getFechaEstreno() const {
    return fechaEstreno;
}
//Implementación del método setId() para establecer el id
void Video::setId(const std::string& newId) {
    id = newId;
}
//Implementación del método setNombre() para establecer el nombre
void Video::setNombre(const std::string& newNombre) {
    nombre = newNombre;
}
//Implementación del método setId() para establecer la duracion
void Video::setDuracion(const std::string& newDuracion) {
    duracion = newDuracion;
}
//Implementación del método setGenero() para establecer el genero
void Video::setGenero(const std::string& newGenero) {
    genero = newGenero;
}
//Implementación del método setCalificacion() para establecer la calificacion
void Video::setCalificacion(const std::string& newCalificacion) {
    calificacion = newCalificacion;
}
//Implementación del método setFechaEstreno() para establecer la fecha de estreno
void Video::setFechaEstreno(const std::string& newFechaEstreno) {
    fechaEstreno = newFechaEstreno;
}
