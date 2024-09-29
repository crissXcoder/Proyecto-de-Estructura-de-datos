#include "cajero.h"
#include "cliente.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <locale>
#include <locale.h>
#include <limits>

using namespace std;

void mostrarMenu();
void procesarOpcion(int opcion, Cajero& cajeros, Cliente& clientes);
void gestionarCajeros(Cajero& cajeros);
void gestionarClientes(Cliente& clientes, Cajero& cajeros);

int main() {

    setlocale(LC_ALL, "");

    srand(time(0));

    Cajero cajeros;
    Cliente clientes;

    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        procesarOpcion(opcion, cajeros, clientes);
    } while (opcion != 5);

    return 0;
}

void mostrarMenu() {
    cout << "\n--- Banco Quiebra-Segura RL ---\n";
    cout << "1. Gestionar Cajeros\n";
    cout << "2. Gestionar Clientes\n";
    cout << "3. Atender Clientes\n";
    cout << "4. Mostrar Estado Actual\n";
    cout << "5. Salir\n";
    cout << "Seleccione una opción: ";
}

void procesarOpcion(int opcion, Cajero& cajeros, Cliente& clientes) {
    switch (opcion) {
    case 1:
        gestionarCajeros(cajeros);
        break;
    case 2:
        gestionarClientes(clientes, cajeros);
        break;
    case 3:
        clientes.atenderClientes(cajeros);
        break;
    case 4:
        cout << "\n--- Estado Actual ---\n";
        cout << "Cajeros:\n";
        cajeros.mostrarTodos();
        cout << "\nClientes:\n";
        clientes.mostrarTodos();
        break;
    case 5:
        cout << "Gracias por usar el sistema. Hasta luego!\n";
        break;
    default:
        cout << "Opción no válida. Intente de nuevo.\n";
    }
}

void gestionarCajeros(Cajero& cajeros) {
    int subOpcion;
    do {
        cout << "\n--- Gestión de Cajeros ---\n";
        cout << "1. Ingresar nuevo cajero\n";
        cout << "2. Mostrar cajero\n";
        cout << "3. Modificar cajero\n";
        cout << "4. Eliminar cajero\n";
        cout << "5. Volver al menú principal\n";
        cout << "Seleccione una opción: ";
        cin >> subOpcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (subOpcion) {
        case 1: {
            int id, numeroCaja;
            string nombre;
            cout << "Ingrese ID del cajero: ";
            cin >> id;
            cout << "Ingrese número de caja: ";
            cin >> numeroCaja;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ingrese nombre del cajero: ";
            getline(cin, nombre);
            cajeros.ingresar(id, numeroCaja, nombre);
            break;
        }
        case 2: {
            int id;
            cout << "Ingrese ID del cajero a mostrar: ";
            cin >> id;
            cajeros.mostrar(id);
            break;
        }
        case 3: {
            int id;
            string nuevoNombre;
            cout << "Ingrese ID del cajero a modificar: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ingrese nuevo nombre del cajero: ";
            getline(cin, nuevoNombre);
            cajeros.modificar(id, nuevoNombre);
            break;
        }
        case 4: {
            int id;
            cout << "Ingrese ID del cajero a eliminar: ";
            cin >> id;
            cajeros.eliminar(id);
            break;
        }
        case 5:
            cout << "Volviendo al menú principal...\n";
            break;
        default:
            cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (subOpcion != 5);
}

void gestionarClientes(Cliente& clientes, Cajero& cajeros) {
    int subOpcion;
    do {
        cout << "\n--- Gestión de Clientes ---\n";
        cout << "1. Ingresar nuevo cliente\n";
        cout << "2. Eliminar cliente\n";
        cout << "3. Volver al menú principal\n";
        cout << "Seleccione una opción: ";
        cin >> subOpcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (subOpcion) {
        case 1: {
            int edad;
            cout << "Ingrese edad del cliente: ";
            cin >> edad;
            clientes.ingresar(edad, cajeros);
            break;
        }
        case 2: {
            string ficha;
            cout << "Ingrese ficha del cliente a eliminar: ";
            getline(cin, ficha);
            clientes.eliminar(ficha);
            break;
        }
        case 3:
            cout << "Volviendo al menú principal...\n";
            break;
        default:
            cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (subOpcion != 3);
}