/*
Autor: Alma Teresa Carpio Revilla
Matrícula: A01798523
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Video.h"
#include "Serie.h"
#include "Pelicula.h"

std::vector<Video*> cargarDatosDesdeCSV(const std::string& archivoCSV) {
    std::vector<Video*> videos;
    std::ifstream archivo(archivoCSV);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo " << archivoCSV << std::endl;
        return videos;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);
        std::string campo;
        std::vector<std::string> campos;
        while (std::getline(iss, campo, ',')) {
            campos.push_back(campo);
        }

        Video* video;
        if (!campos[7].empty()) { // Si el campo "ID del episodio" no está vacío, es una serie
            Serie* serie = new Serie();
            serie->setIdEpisodio(campos[6]);
            serie->setNombreEpisodio(campos[7]);
            serie->setTemporada(campos[8]);
            serie->setNumEpisodio(campos[9]);
            video = serie;
        } else {
            video = new Pelicula();
        }

        video->setId(campos[0]);
        video->setNombre(campos[1]);
        video->setDuracion(campos[2]);
        video->setGenero(campos[3]);
        video->setCalificacion(campos[4]);
        video->setFechaEstreno(campos[5]);

        videos.push_back(video);
    }

    archivo.close();
    return videos;
}

std::vector<Pelicula*> filtrarPeliculas(const std::vector<Video*>& videos) {
    std::vector<Pelicula*> peliculas;
    for (const auto& video : videos) {
        if (!video->esSerie()) {
            Pelicula* pelicula = dynamic_cast<Pelicula*>(video);
            if (pelicula)
                peliculas.push_back(pelicula);
        }
    }
    return peliculas;
}

std::vector<Serie*> filtrarSeries(const std::vector<Video*>& videos) {
    std::vector<Serie*> series;
    for (const auto& video : videos) {
        if (video->esSerie()) {
            Serie* serie = dynamic_cast<Serie*>(video);
            if (serie)
                series.push_back(serie);
        }
    }
    return series;
}

void mostrarVideosConCalificacionMayorOIgual(const std::vector<Video*>& videos, const std::string& calificacion) {
    std::cout << "Videos con calificación mayor o igual a " << calificacion << ":\n";
    for (const auto& video : videos) {
        if (video->getCalificacion() >= calificacion) {
            std::cout << "\nID: " << video->getId() << "\nNombre: " << video->getNombre()  << "\nCalificación: " << video->getCalificacion() << "\nGénero: " << video->getGenero() << "\n\n-----------------------------" <<std::endl;
        }
    }
    std::cout << std::endl;
}

void mostrarVideosConGenero(const std::vector<Video*>& videos, const std::string& genero) {
    std::cout << "Videos con género " << genero << ":\n";
    for (const auto& video : videos) {
        if (video->getGenero().find(genero) != std::string::npos) {
            std::cout << "\nID: " << video->getId() << "\nNombre: " << video->getNombre() << "\nGénero: " << video->getGenero() << "\n\n-----------------------------" << std::endl;
        }
    }
    std::cout << std::endl;
}


void mostrarEpisodiosDeSerie(const std::vector<Serie*>& series, const std::string& nombreSerie) {
    std::cout << "\nEpisodios de la serie " << nombreSerie << ":\n";
    for (const auto& serie : series) {
        if (serie->getNombre() == nombreSerie) {
            std::cout << "\nID Episodio: " << serie->getIdEpisodio() << "\nNombre Episodio: " << serie->getNombreEpisodio() << "\nTemporada: " << serie->getTemporada() << "\nNumero de Episodio: " << serie->getNumEpisodio() << "\n\n-----------------------------" <<std::endl;
        }
    }
    std::cout << std::endl;
}

void mostrarPeliculasConCalificacionMayor(const std::vector<Pelicula*>& peliculas, const std::string& calificacion) {
    std::cout << "\nPelículas con calificación mayor a " << calificacion << ":\n";
    for (const auto& pelicula : peliculas) {
        if (pelicula->getCalificacion() > calificacion) {
            std::cout << "\nID: " << pelicula->getId() << "\nNombre: " << pelicula->getNombre() << "\nDuración: " << pelicula->getDuracion() << " min" << "\nGénero: " << pelicula->getGenero() << "\nCalificacion: " << pelicula->getCalificacion()<< "\n\n-----------------------------" <<std::endl;
        }
    }
    std::cout << std::endl;
}

void calificarVideo(std::vector<Video*>& videos) {
    std::string nombreVideo;
    std::cout << "Ingrese el nombre de la película o episodio de la serie a calificar: ";
    std::cin.ignore();
    std::getline(std::cin, nombreVideo);

    std::string nuevaCalificacion;
    std::cout << "Ingrese la nueva calificación: ";
    std::cin >> nuevaCalificacion;

    for (auto& video : videos) {
        if (video->getNombre() == nombreVideo) {
            video->getCalificacion() = nuevaCalificacion;
            std::cout << "Calificación asignada correctamente.\n";
            return;
        }
    }

    std::cout << "No se encontró el video especificado.\n";
}

void calcularPromedioCalificacionSerie(const std::vector<Serie*>& series, const std::string& nombreSerie) {
    int totalEpisodios = 0;
    float totalCalificaciones = 0;

    for (const auto& serie : series) {
        if (serie->getNombre() == nombreSerie) {
            totalEpisodios++;
            totalCalificaciones += std::stof(serie->getCalificacion());
        }
    }

    if (totalEpisodios > 0) {
        float promedio = static_cast<float>(totalCalificaciones) / totalEpisodios;
        std::cout << "El promedio de calificación de la serie " << nombreSerie << " es: " << promedio << std::endl;
    } else {
        std::cout << "No se encontró la serie especificada.\n";
    }
}

void mostrarMenu() {
    std::cout << "\n===== Menú =====\n"
              << "1. Mostrar los videos en general con una calificación mayor o igual a un valor tecleado por el usuario\n"
              << "2. Mostrar los videos en general con un género tecleado por el usuario\n"
              << "3. Mostrar todos los episodios de una determinada Serie que teclea el usuario\n"
              << "4. Mostrar las Peliculas con una calificación mayor a un número tecleado por el usuario\n"
              << "5. Calificar un video\n"
              << "6. Calcular el promedio de la calificación de una Serie\n"
              << "7. Salir\n"
              << "------------------------------------------\n" 
              << "Ingrese su opción: ";
  
}

int main() {
    std::cout << "Autor: Alma Teresa Carpio Revilla, A01798523, ITC\n" << std::endl;
    std::cout << "Bienvenido al sistema de gestión de videos" << std::endl;
    std::cout << "------------------------------------------" << std::endl;
  
    std::string archivoCSV;
    std::cout << "Ingrese el nombre del archivo CSV: ";
    std::cin >> archivoCSV;

    std::vector<Video*> videos = cargarDatosDesdeCSV(archivoCSV);
    std::vector<Pelicula*> peliculas = filtrarPeliculas(videos);
    std::vector<Serie*> series = filtrarSeries(videos);

    int opcion;
    std::string valor;
    std::string genero;
    std::string nombreSerie;

    do {
        mostrarMenu();
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                std::cout << "Ingrese el valor de calificación: ";
                std::cin >> valor;
                mostrarVideosConCalificacionMayorOIgual(videos, valor);
                break;
            case 2:
                std::cout << "Ingrese el género: ";
                std::cin >> genero;
                mostrarVideosConGenero(videos, genero);
                break;
            case 3:
                std::cout << "Ingrese el nombre de la serie: ";
                std::cin.ignore();
                std::getline(std::cin, nombreSerie);
                mostrarEpisodiosDeSerie(series, nombreSerie);
                break;
            case 4:
                std::cout << "Ingrese el valor de calificación: ";
                std::cin >> valor;
                mostrarPeliculasConCalificacionMayor(peliculas, valor);
                break;
            case 5:
                calificarVideo(videos);
                break;
            case 6:
                std::cout << "Ingrese el nombre de la serie: ";
                std::cin.ignore();
                std::getline(std::cin, nombreSerie);
                calcularPromedioCalificacionSerie(series, nombreSerie);
                break;
            case 7:
                std::cout << "\n¡Hasta luego!\n";
                break;
            default:
                std::cout << "Opción inválida. Intente nuevamente.\n";
                break;
        }

        std::cout << std::endl;
    } while (opcion != 7);
  
    return 0;
}
