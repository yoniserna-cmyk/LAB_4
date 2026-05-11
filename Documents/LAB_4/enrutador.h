#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <string>
#include <iostream>
#include <map>

using namespace std;



// Clase para modelar un Enrutador
class Enrutador
{
private:
    string nombre;
    // Elegir contenedor adecuado para guardar
    // enlaces directos a otros enrutadores y su costo
    map<string, int> Enlaces;

public:
    // Constructores y destructor
    Enrutador(string n) : nombre(n) {}     // Constructor por defecto
    ~Enrutador() {}                 // Destructor

    // Getters
    const string &getNombre() const {
        return nombre;
    }  // Getter para el nombre
    const map<string, int> &getEnlaces() const {
        return Enlaces;
    }   // Getter para los enlaces

    // Métodos de funcionamiento para gestionar los enlaces
    void agregarEnlace(const string &destino, int costo){
        Enlaces[destino] = costo;
    }
    void eliminarEnlace(const string &destino){
        Enlaces.erase(destino);
    }
    void actualizarCosto(const string &destino, int nuevoCosto) {
        auto it = Enlaces.find(destino);

        if (it != Enlaces.end()) {
            it->second = nuevoCosto; // it->second es el valor (el costo)
        } else {
            cout << "Error: La red '" << destino << "' no existe." << endl;
        }
    }

};// FALTA HACER TABLACOSTOS


#endif // ENRUTADOR_H






