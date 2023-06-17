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

// Función para cargar datos desde un archivo CSV y devolver un vector de punteros a objetos Video
std::vector<Video*> cargarDatosDesdeCSV(const std::string& archivoCSV) {
    std::vector<Video*> videos; // Vector para almacenar los videos cargados
    std::ifstream archivo(archivoCSV); // Abrir el archivo CSV
    if (!archivo) {
        std::cerr << "Error al abrir el archivo " << archivoCSV << std::endl;
        return videos;
    }
    std::string linea;
    while (std::getline(archivo, linea)) {
        // Leer una línea del archivo CSV
        std::istringstream iss(linea);
        std::string campo;
        std::vector<std::string> campos;
        while (std::getline(iss, campo, ',')) {
        // Separar los campos de cada línea por comas y almacenarlos en un vector
            campos.push_back(campo);
        }
        Video* video;
        if (!campos[7].empty()) { // Si el campo "Id del episodio" no está vacío, es una serie
            Serie* serie = new Serie();
            serie->setIdEpisodio(campos[6]);
            serie->setNombreEpisodio(campos[7]);
            serie->setTemporada(campos[8]);
            serie->setNumEpisodio(campos[9]);
            video = serie;
        } else {
            video = new Pelicula();
        }
        // Establecer los atributos del video
        video->setId(campos[0]);
        video->setNombre(campos[1]);
        video->setDuracion(campos[2]);
        video->setGenero(campos[3]);
        video->setCalificacion(campos[4]);
        video->setFechaEstreno(campos[5]);

        videos.push_back(video); // Agregar el video al vector
    }
    archivo.close();
    return videos;  // Devolver el vector de videos cargados
}

// Función para filtrar y devolver un vector de punteros a objetos Pelicula
std::vector<Pelicula*> filtrarPeliculas(const std::vector<Video*>& videos) {
    std::vector<Pelicula*> peliculas;  // Vector para almacenar las películas
    for (const auto& video : videos) {
        if (!video->esSerie()) { // Verificar si el video no es una serie
            Pelicula* pelicula = dynamic_cast<Pelicula*>(video);
            if (pelicula)
                peliculas.push_back(pelicula); // Agregar la película al vector 
        }
    }
    return peliculas; // Devolver el vector de películas
}
// Función para filtrar y devolver un vector de punteros a objetos Serie
std::vector<Serie*> filtrarSeries(const std::vector<Video*>& videos) {
    std::vector<Serie*> series; // Crear un vector para almacenar las series filtradas
    for (const auto& video : videos) {
        if (video->esSerie()) { // Verificamos si el video es una serie
            Serie* serie = dynamic_cast<Serie*>(video); // Realizamos un dynamic_cast para convertir el puntero de Video a Serie
            if (serie)
                series.push_back(serie); // Agregar la serie al vector 
        }
    }
    return series;
}

//Implementación de la función mostrarVideosConCalificacionMayorOIgual(), opción 1 del menú
void mostrarVideosConCalificacionMayorOIgual(const std::vector<Video*>& videos, const std::string& calificacion) {
    std::cout << "Videos con calificación mayor o igual a " << calificacion << ":\n";
    float calificacionNumerica;
    try {
        calificacionNumerica = std::stof(calificacion); // Convertir la calificación ingresada de string a float
    } catch (const std::exception& e) {
        std::cout << "\nLa calificación ingresada no es un valor numérico válido por lo que será redirigido al menu principal.\n";
        return;
    }
    if (calificacionNumerica < 0 || calificacionNumerica > 7) {
        std::cout << "\nLa calificación ingresada no está dentro del rango válido (0-7) por lo que será redirigido al menu principal.\n";
        return;
    }
    bool encontrados = false; // Variable para realizar el seguimiento de si se encontraron videos
    for (const auto& video : videos) {
        float calificacionVideo;
        try {
            calificacionVideo = std::stof(video->getCalificacion()); // Obtener la calificación del video y convertirla de string a float
        } catch (const std::exception& e) {
            std::cout << "\nError al procesar la calificación de un video por lo que será redirigido al menu principal.\n";
            continue; // Pasar al siguiente video en caso de error en la conversión
        } 
        if (calificacionVideo >= calificacionNumerica) {
            encontrados = true;
            std::cout << "\nID: " << video->getId() << "\nNombre: " << video->getNombre() << "\nCalificación: " << video->getCalificacion() << "\nGénero: " << video->getGenero() << "\n\n-----------------------------" << std::endl;
        }
    }
    if (!encontrados) {
        std::cout << "\nNo se encontraron videos con la calificación ingresada por lo que será redirigido al menu principal.\n";
    }
    std::cout << std::endl;
}

//Implementación de la función mostrarVideosConGenero(), opción 2 del menú
void mostrarVideosConGenero(const std::vector<Video*>& videos, const std::string& genero) {
    bool videosEncontrados = false; // Variable para verificar si se encontraron videos
    std::cout << "Videos con género " << genero << ":\n";
    for (const auto& video : videos) {
        if (video->getGenero().find(genero) != std::string::npos) { //Utilizar find para que el usuario pueda escribir un género y no todos los géneros de una serie
            videosEncontrados = true;
            std::cout << "\nID: " << video->getId() << "\nNombre: " << video->getNombre() << "\nGénero: " << video->getGenero() << "\n\n-----------------------------" << std::endl;
        }
    }
    if (!videosEncontrados) {
        std::cout << "\n¡Ups! No se encontraron videos con el género especificado. El género es inválido por lo que será redirigido al menu principal.\n";
    }
    std::cout << std::endl;
}

//Implementación de la función mostrarEpisodiosDeSerie(), opción 3 del menú
void mostrarEpisodiosDeSerie(const std::vector<Serie*>& series, const std::string& nombreSerie) {
    bool serieEncontrada = false; // Variable para verificar si se encontró la serie
    std::cout << "\nEpisodios de la serie " << nombreSerie << ":\n";
    // Iterar a través de todas las series en el vector de series
    for (const auto& serie : series) {
        if (serie->getNombre() == nombreSerie) { // Verificar si el nombre de la serie coincide con el nombre ingresado
            serieEncontrada = true;
            std::cout << "\nID Episodio: " << serie->getIdEpisodio() << "\nNombre Episodio: " << serie->getNombreEpisodio() << "\nTemporada: " << serie->getTemporada() << "\nNumero de Episodio: " << serie->getNumEpisodio() << "\n\n-----------------------------" <<std::endl;
        }
    }
    if (!serieEncontrada) {
        std::cout << "\nNo se encontró la serie especificada. El nombre es inválido por lo que será redirigido al menu principal.\n";
    }
    std::cout << std::endl;
}

//Implementación de la función mostrarPeliculasConCalificacionMayor(), opción 4 del menú
void mostrarPeliculasConCalificacionMayor(const std::vector<Pelicula*>& peliculas, const std::string& calificacion) {
    float calificacionNumerica;
    try {
        calificacionNumerica = std::stof(calificacion); // Convertir la calificación ingresada de string a float
    } catch (const std::exception& e) {
        std::cout << "\nLa calificación ingresada no es un valor numérico válido por lo que será redirigido al menu principal.\n";
        return;
    }
    std::cout << "\nPelículas con calificación mayor a " << calificacion << ":\n";
    bool encontradas = false; // Variable para realizar el seguimiento de si se encontraron películas
    // Iterar a través de todas las películas en el vector de peliculas
    for (const auto& pelicula : peliculas) {
        float calificacionPelicula;
        try {
            calificacionPelicula = std::stof(pelicula->getCalificacion()); // Obtener la calificación de la película y convertirla de string a float
        } catch (const std::exception& e) {
            std::cout << "\nError al procesar la calificación de una película por lo que será redirigido al menú principal.\n";
            continue; // Pasar a la siguiente película en caso de error en la conversión
        }   
        if (calificacionPelicula > calificacionNumerica) {
            encontradas = true;
            std::cout << "\nID: " << pelicula->getId() << "\nNombre: " << pelicula->getNombre() << "\nDuración: " << pelicula->getDuracion() << " min" << "\nGénero: " << pelicula->getGenero() << "\nCalificacion: " << pelicula->getCalificacion() << "\n\n-----------------------------" << std::endl;
        }
    }
    if (!encontradas) {
        std::cout << "\nNo se encontraron películas con calificación mayor a " << calificacion << " por lo que será redirigido al menu principal.\n";
    }
    std::cout << std::endl;
}

//Implementación de la función calificarVideo(), opción 5 del menú
void calificarVideo(std::vector<Video*>& videos) {
    std::string nombreVideo;
    std::cout << "Ingrese el nombre de la película o episodio de la serie a calificar: ";
    std::cin.ignore(); //Asegurar que no hay caractéres adicionales
    std::getline(std::cin, nombreVideo); // Leer el nombre del video

    std::string nuevaCalificacion;
    std::cout << "Ingrese la nueva calificación: ";
    std::cin >> nuevaCalificacion; // Leer la nueva calificación

    for (auto& video : videos) {
        if (video->getNombre() == nombreVideo) { // Verificar si el nombre del video coincide con el nombre ingresado
            video->getCalificacion() = nuevaCalificacion;  // Asignar la nueva calificación al video
            std::cout << "\nCalificación asignada correctamente.\n";
            return;
        }
    }
    std::cout << "\nNo se encontró el video especificado por lo que se redirigirá al menú principal.\n";
}

//Implementación de la función calcularPromedioCalificacionSerie(), opción 6 del menú
void calcularPromedioCalificacionSerie(const std::vector<Serie*>& series, const std::string& nombreSerie) {
    int totalEpisodios = 0;
    float totalCalificaciones = 0;
    // Recorrer todas las series
    for (const auto& serie : series) {
        if (serie->getNombre() == nombreSerie) { // Verificar si el nombre de la serie coincide con el nombre ingresado
            totalEpisodios++; // Incrementar el contador de episodios de la serie
            totalCalificaciones += std::stof(serie->getCalificacion());
        }
    }
    if (totalEpisodios > 0) { // Verificar si se encontraron episodios de la serie
        float promedio = static_cast<float>(totalCalificaciones) / totalEpisodios; // Calcular el promedio de calificación
        std::cout << "El promedio de calificación de la serie " << nombreSerie << " es: " << promedio << std::endl;
    } else {
        std::cout << "No se encontró la serie especificada por lo que se redirigirá al menú principal.\n";
    }
}

//Diseñar nuestro menú
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

    bool opcionValida = false; // Variable para verificar si se ingresó una opción válida

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
                opcionValida = true; // La opción 7 es válida, el usuario puede salir del bucle
                break;
            default:
                std::cout << "Opción inválida. Intente nuevamente.\n";
                break;
        }
        std::cout << std::endl;
    } while (!opcionValida); // Continuar el bucle hasta que se ingrese una opción válida o se seleccione la opción 7

    return 0;
}
