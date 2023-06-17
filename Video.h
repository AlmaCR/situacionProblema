/*
Autor: Alma Teresa Carpio Revilla
Matrícula: A01798523
Definición de clase base abstracta "Video" la cual representa un vídeo genérico.
*/

//Verificar que la clase no esté definida y definirla
#ifndef VIDEO_H
#define VIDEO_H

#include <string>

class Video {
//Atributos
private:
    std::string id;
    std::string nombre;
    std::string duracion;
    std::string genero;
    std::string calificacion;
    std::string fechaEstreno;
//Métodos
public:
    //Getters
    std::string getId() const;
    std::string getNombre() const;
    std::string getDuracion() const;
    std::string getGenero() const;
    std::string getCalificacion() const;
    std::string getFechaEstreno() const;
    //Setters
    void setId(const std::string& newId);
    void setNombre(const std::string& newNombre);
    void setDuracion(const std::string& newDuracion);
    void setGenero(const std::string& newGenero);
    void setCalificacion(const std::string& newCalificacion);
    void setFechaEstreno(const std::string& newFechaEstreno);
    //Método virtual para determinar si el video es una serie
    virtual bool esSerie() const = 0;
};

#endif //VIDEO_H
