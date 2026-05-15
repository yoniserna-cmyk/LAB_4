#include <iostream>
#include "red.h"
#include "enrutador.h"
#include <string>

using namespace std;

// Función para limpiar la pantalla y pausar
void clearScreen()
{
    cout << "\nPresione Enter para continuar...";
    cin.ignore(1000, '\n'); // Limpia el buffer
    cin.get();
#ifdef _WIN32
    system("cls");
#else
    cout << "\033[2J\033[1;1H";
#endif
}

int main()
{
    Red red;
    int opcion;

    // Variables de apoyo para el switch
    string nombre, origen, destino;
    int costo;
    // Sugerencia: Usa el nombre del archivo directamente si esta en la misma carpeta
    string archivo = "C:\\Users\\Yudy2\\Documents\\LAB_4\\topologia.txt";

    do
    {
        cout << "\n--- MENU RED DE ENRUTADORES ---\n";
        cout << "1. Agregar enrutador\n";
        cout << "2. Remover enrutador\n";
        cout << "3. Agregar enlace\n";
        cout << "4. Eliminar enlace\n";
        cout << "5. Actualizar costo de enlace\n";
        cout << "6. Cargar topologia desde archivo\n";
        cout << "7. Mostrar tabla de enrutamiento\n";
        cout << "8. Obtener costo entre dos enrutadores\n";
        cout << "9. Obtener camino eficiente entre dos enrutadores\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) { // Evita bucle infinito si se ingresa una letra
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (opcion)
        {
        case 1:
            cout << "Ingresa el nombre del enrutador: ";
            cin >> nombre;
            red.agregarEnrutador(nombre);
            clearScreen();
            break;

        case 2:
            cout << "Ingresa el nombre del enrutador a eliminar: ";
            cin >> nombre;
            red.removerEnrutador(nombre);
            clearScreen();
            break;

        case 3:
            cout << "Origen: "; cin >> origen;
            cout << "Destino: "; cin >> destino;
            cout << "Costo: "; cin >> costo;
            red.agregarEnlace(origen, destino, costo);
            clearScreen();
            break;

        case 4:
            cout << "Primer nodo del enlace: "; cin >> origen;
            cout << "Segundo nodo del enlace: "; cin >> destino;
            red.eliminarEnlace(origen, destino);
            clearScreen();
            break;

        case 5:
            cout << "Origen: "; cin >> origen;
            cout << "Destino: "; cin >> destino;
            cout << "Nuevo costo: "; cin >> costo;
            red.actualizarCosto(origen, destino, costo);
            clearScreen();
            break;

        case 6:
            red.cargarDesdeArchivo(archivo);
            clearScreen();
            break;

        case 7:
            cout << "Ingresa el nombre del enrutador para ver su tabla: ";
            cin >> nombre;
            // Primero calculamos rutas desde ese nodo
            red.dijkstra(nombre);
            red.mostrarTablaEnrutamiento(nombre);
            clearScreen();
            break;

        case 8:
            cout << "Origen: "; cin >> origen;
            cout << "Destino: "; cin >> destino;
            // Ejecutamos Dijkstra para hallar el costo minimo
            red.dijkstra(origen);
            costo = red.obtenerCosto(origen, destino);
            if(costo != -1) // Suponiendo que devuelves -1 si no hay ruta
                cout << "El costo minimo de " << origen << " a " << destino << " es: " << costo << endl;
            clearScreen();
            break;

        case 9:
            cout << "Origen: "; cin >> origen;
            cout << "Destino: "; cin >> destino;
            // El camino eficiente se calcula y guarda en las tablas con Dijkstra
            red.dijkstra(origen);
            // Reutilizamos mostrarTabla para ver la ruta especifica
            red.mostrarTablaEnrutamiento(origen);
            // Nota: Aquí podrías crear una función 'red.mostrarRutaEspecifica(origen, destino)'
            clearScreen();
            break;

        case 0:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opcion invalida.\n";
            clearScreen();
        }
    } while (opcion != 0);

    return 0;
}

