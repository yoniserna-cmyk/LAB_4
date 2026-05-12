#ifndef RED_H
#define RED_H

#include "enrutador.h"
#include <iostream>
#include <fstream>
#include <map>
// agregar librerias faltantes...


// Clase para modelar la Red
class Red
{
private:
    // elegir contenedor adecuado para guardar los enrutadores de la red
    map<string, Enrutador> enrutadores;
    // elegir contenedor adecuado para guardar las tablas de enrutamiento de cada enrutador
    map<string, map<string, int>> tablasEnrutamiento;

public:
    // Constructores y destructor
    Red() {}  // Constructor por defecto
    ~Red() {} // Destructor

    // Agregar un enrutador a la red
    void agregarEnrutador(const string &nombre){
        if(enrutadores.find(nombre) == enrutadores.end()){
            enrutadores[nombre] = Enrutador(nombre);
            cout << "enrrutador" << nombre << "agregado" << endl;
        }else{
            cout << "el enrrutador ya existe " << endl;
        }
    }
    // Remover un enrutador de la red
    void removerEnrutador(const string &nombre){
        enrutadores.erase(nombre);// posible error
    }

    // Agregar un enlace entre dos enrutadores
    void agregarEnlace(const string &origen, const string &destino, int costo){
        if(enrutadores.find(origen) != enrutadores.end() && enrutadores.find(destino) != enrutadores.end()){
            for(const auto& par : enrutadores){
                cout << par.first;
            }
            enrutadores[origen].agregarEnlace(destino,costo);
            enrutadores[destino].agregarEnlace(origen,costo);
        }else{
            cout << "el error no se encotro un enrutador"<< endl;
        }
    }


    // Eliminar un enlace entre dos enrutadores
    void eliminarEnlace(const string &destino, string &origen){
        if (enrutadores.find(destino) != enrutadores.end()) {
            enrutadores[origen].eliminarEnlace(destino);
            enrutadores[destino].eliminarEnlace(origen);
            cout << "enlaces " << origen << "y" << destino << "eliminados" << endl;
        }else
        {
            cout << "algun enrutador no existe " << endl;

        }

    }

    // Actualizar el costo de un enlace
    void actualizarCosto(const string &origen, const string &destino, int nuevoCosto){
        if(enrutadores.find(origen) != enrutadores.end() && enrutadores.find(destino) != enrutadores.end())
        {
            enrutadores[origen].actualizarCosto(destino, nuevoCosto);
            enrutadores[destino].actualizarCosto(origen, nuevoCosto);
        }
        else
        {
            cout << "un enrutador buscado no existe " << endl;
        }
    }

    // Cargar la topología desde un archivo
    void cargarDesdeArchivo(const string &nombreArchivo){
        string enlace1, enlace2;
        int costo;
        ifstream file(nombreArchivo);
        if(! file.is_open())
        {
            cout << "error a la hora de abrir el archivo " << endl;
            return;
        }

        while(file >> enlace1 >> enlace2 >> costo){
            agregarEnrutador(enlace1);
            agregarEnrutador(enlace2);

            agregarEnlace(enlace1, enlace2, costo);
        }
        cout << "archivo leido correctamente "<< endl;
        file.close();
    }

    // Algoritmo de Dijkstra para calcular rutas y costos
    void dijkstra(const string &origen);

    // Actualizar todas las tablas de enrutamiento
    void actualizarTablas();

    // Obtener el costo entre dos enrutadores
    int obtenerCosto(const string &origen, const string &destino){
        int suma;
        auto enrutador1 = enrutadores.find(origen);
        auto enrutador2 = enrutadores.find(destino);

        if(enrutador1 != enrutadores.end())
        {
            enrutador1->second;
        }

        if(enrutador2 != enrutadores.end())
        {
            enrutador2->second;
        }

        suma = enrutador1 + enrutador2; // estoy travajando con punteros no se puede sumar asi

        return suma;
    }

    // Obtener el camino eficiente entre dos enrutadores
    // debe aoperar con el mismo tipo de dato que se usó para guardar las rutas en las tablas de enrutamiento
    //... obtenerCamino(const string &origen, const string &destino);

    // Mostrar la tabla de enrutamiento para un enrutador específico
    void mostrarTablaEnrutamiento(const string &nombre);
};

#endif // RED_H
