#ifndef RED_H
#define RED_H

#include "enrutador.h"
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <vector>
// agregar librerias faltantes...

struct inforuta
{
    int costo;
    string camino;
};


// Clase para modelar la Red
class Red
{
private:
    // elegir contenedor adecuado para guardar los enrutadores de la red
    map<string, Enrutador> enrutadores;
    // elegir contenedor adecuado para guardar las tablas de enrutamiento de cada enrutador
    map<string, map<string, inforuta>> tablasEnrutamiento;

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
    void removerEnrutador(const string &nombre) {
        auto it = enrutadores.find(nombre);

        if (it != enrutadores.end()) { // Si el enrutador existe...

            // 1. Limpiamos las referencias en los demás enrutadores
            for (auto &par : enrutadores) {
                par.second.eliminarEnlace(nombre);
            }

            // 2. Lo borramos del mapa principal (ahora sí, dentro del if)
            enrutadores.erase(it);

            cout << "El enrutador: " << nombre << " fue eliminado exitosamente." << endl;
        } else {
            cout << "Error: El enrutador " << nombre << " no existe en la red." << endl;
        }
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
    void eliminarEnlace(const string &origen, string &destino){
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
    void dijkstra(const string &origen){
        map <string, int> distancias;
        map < string, bool> visitados;
        map <string , string > caminos;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> cola;

        for(auto const& [nombre, objeto] : enrutadores){
            distancias[nombre] = 9999;
            visitados[nombre] = false;
        }
        caminos[origen] = origen;
        distancias[origen] = 0;
        cola.push({0, origen});

        while(!cola.empty()){
            string u = cola.top().second;
            cola.pop();

            if(visitados[u]) continue;
            visitados[u] = true;

            auto vecinos = enrutadores[u].getEnlaces();

            for(auto const& [v, costoEnlace] : vecinos){
                if(!visitados[v] && distancias[u] + costoEnlace < distancias[v]){
                    distancias[v] = distancias[u] + costoEnlace; // distancia[v] es el costo total

                    caminos[v] = caminos[u] + "->" + v;

                    actualizarTablas(origen, v, distancias[v], caminos[v]);
                    cola.push({distancias[v], v});
                }
            }

        }
    }

    // Actualizar todas las tablas de enrutamiento
    void actualizarTablas(string origen, string destino, int costotal, string rutatexto){
        tablasEnrutamiento[origen][destino] = {costotal, rutatexto};
    }

    // Obtener el costo entre dos enrutadores
    int obtenerCosto(const string &origen, const string &destino){
        int s = -1;
        auto enrutador1 = enrutadores.find(origen);

        if(enrutador1 != enrutadores.end())
        {
            auto& enlace = enrutador1->second.getEnlaces();

            auto enlacedestino = enlace.find(destino) ;
            if(enlacedestino != enlace.end()){
                s = enlacedestino->second;

            }
        }

        return s;
    }

    // Obtener el camino eficiente entre dos enrutadores
    // debe aoperar con el mismo tipo de dato que se usó para guardar las rutas en las tablas de enrutamiento
    //... obtenerCamino(const string &origen, const string &destino);

    // Mostrar la tabla de enrutamiento para un enrutador específico
    void mostrarTablaEnrutamiento(const string &nombre){
        for(auto const& [destino, info] : tablasEnrutamiento[nombre]){
            cout << "Hacia: " << destino
                 << " | Costo: " << info.costo
                 << " | Ruta: " << info.camino << endl;
        }
    }
};


#endif // RED_H
