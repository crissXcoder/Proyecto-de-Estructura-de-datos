#include "cajero.h"
#include "cliente.h"
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

void mostrarMenu();
void procesarOpcion(int opcion, Cajero& cajeros, Cliente& clientes);

int main() {
    srand(time(0));
    
    Cajero cajeros;
    Cliente clientes;
    
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        procesarOpcion(opcion, cajeros, clientes);
    } while (opcion != 7);
    
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
    switch(opcion) {
        case 1:
            // Implementar gestión de cajeros
            break;
        case 2:
            // Implementar gestión de clientes
            break;
        case 3:
            clientes.atenderClientes(cajeros);
            break;
        case 4:
            cajeros.mostrarTodos();
            clientes.mostrarTodos();
            break;
        case 5:
            cout << "Gracias por usar el sistema. Hasta luego!\n";
            exit(0);
        default:
            cout << "Opción no válida. Intente de nuevo.\n";
    }
}