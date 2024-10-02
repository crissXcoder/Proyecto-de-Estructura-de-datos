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
    system("cls");
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
        system("cls");
        gestionarCajeros(cajeros);
        system("pause");
        break;
    case 2:
        system("cls");
        gestionarClientes(clientes, cajeros);
        system("pause");
        break;
    case 3:
        system("cls");
        clientes.atenderClientes(cajeros);
        system("pause");
        break;
    case 4:
        system("cls");
        cout << "\n--- Estado Actual ---\n";
        cout << "Cajeros:\n";
        cajeros.mostrarTodos();
        cout << "\nClientes:\n";
        clientes.mostrarTodos();
        system("pause");
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
        system("cls");
        cout << "\n--- Gestión de Cajeros ---\n";
        cout << "1. Ingresar nuevo cajero\n";
        cout << "2. Mostrar cajero por ID\n";
        cout << "3. Mostrar lista de cajeros\n";
        cout << "4. Modificar cajero\n";
        cout << "5. Eliminar cajero\n";
        cout << "6. Volver al menú principal\n";
        cout << "Seleccione una opción: ";
        cin >> subOpcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (subOpcion) {
        case 1: {
            system("cls");
            int id, numeroCaja;
            string nombre, apellido, correo;
            cout << "Ingrese ID del cajero: ";
            cin >> id;
            cout << "Ingrese número de caja: ";
            cin >> numeroCaja;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ingrese nombre del cajero: ";
            getline(cin, nombre);
            cout << "Ingrese apellido del cajero: ";
            getline(cin, apellido);
            cout << "Ingrese correo electrónico del cajero: ";
            getline(cin, correo);
            cajeros.ingresar(id, numeroCaja, nombre, apellido, correo);
            system("pause");
            break;
        }
        case 2: {
            system("cls");
            int id;
            cout << "Ingrese ID del cajero a mostrar: ";
            cin >> id;
            cajeros.mostrar(id);
            system("pause");
            break;
        }
        case 3: {
            system("cls");
            cajeros.mostrarListaCajero();
            system("pause");
            break;
        }
        case 4: {
            system("cls");
            int id;
            string nuevoNombre, nuevoApellido, nuevoCorreo;
            cout << "Ingrese ID del cajero a modificar: ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ingrese nuevo nombre del cajero: ";
            getline(cin, nuevoNombre);
            cout << "Ingrese nuevo apellido del cajero: ";
            getline(cin, nuevoApellido);
            cout << "Ingrese nuevo correo electrónico del cajero: ";
            getline(cin, nuevoCorreo);
            cajeros.modificar(id, nuevoNombre, nuevoApellido, nuevoCorreo);
            system("pause");
            break;
        }
        case 5: {
            system("cls");
            int id;
            cout << "Ingrese ID del cajero a eliminar: ";
            cin >> id;
            cajeros.eliminar(id);
            system("pause");
            break;
        }
        case 6:
            cout << "Volviendo al menú principal...\n";
            break;
        default:
            cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (subOpcion != 6);
}

void gestionarClientes(Cliente& clientes, Cajero& cajeros) {
    int subOpcion;
    do {
        system("cls");
        cout << "\n--- Gestión de Clientes ---\n";
        cout << "1. Ingresar nuevo cliente\n";
        cout << "2. Eliminar cliente\n";
        cout << "3. Mostrar lista de clientes\n";
        cout << "4. Volver al menú principal\n";
        cout << "Seleccione una opción: ";
        cin >> subOpcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (subOpcion) {
        case 1: {
            system("cls");
            int edad;
            string nombre, apellido, telefono, correo, direccion;
            cout << "Ingrese edad del cliente: ";
            cin >> edad;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ingrese nombre del cliente: ";
            getline(cin, nombre);
            cout << "Ingrese apellido del cliente: ";
            getline(cin, apellido);
            cout << "Ingrese teléfono del cliente: ";
            getline(cin, telefono);
            cout << "Ingrese correo electrónico del cliente: ";
            getline(cin, correo);
            cout << "Ingrese dirección del cliente: ";
            getline(cin, direccion);
            clientes.ingresar(edad, cajeros, nombre, apellido, telefono, correo, direccion);
            system("pause");
            break;
        }
        case 2: {
            system("cls");
            string ficha;
            cout << "Ingrese ficha del cliente a eliminar: ";
            getline(cin, ficha);
            clientes.eliminar(ficha);
            system("pause");
            break;
        }
        case 3: {
            system("cls");
            clientes.mostrarTodos();
            system("pause");
            break;
        }
        case 4:
            cout << "Volviendo al menú principal...\n";
            break;
        default:
            cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (subOpcion != 4);
}