#include "cliente.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <cstdlib>

Cliente::Cliente() : primero(NULL), consecutivoC(1), consecutivoA(1) {}

Cliente::~Cliente() {
    while (primero != NULL) {
        NodoCliente* temp = primero;
        primero = primero->siguiente;
        delete temp;
    }
}

bool Cliente::ingresar(int edad, Cajero& cajeros, const string& nombre, const string& apellido, const string& telefono, const string& correo, const string& direccion) {
    string ficha;
    int cajeroAsignado;

    // Validación de datos
    if (edad <= 0 || nombre.empty() || apellido.empty() || telefono.empty() || correo.empty() || direccion.empty()) {
        cout << "Error: Todos los campos son obligatorios y la edad debe ser un número positivo.\n";
        return false;
    }

    if (edad >= 65) {
        ficha = "A" + to_string(consecutivoA++);
        NodoCajero* cajeroElegido = cajeros.buscarCajeroParaAdultoMayor();
        if (cajeroElegido == NULL) {
            cout << "No hay cajeros disponibles.\n";
            return false;
        }
        cajeroAsignado = cajeroElegido->numeroCaja;
    }
    else {
        ficha = "C" + to_string(consecutivoC++);
        NodoCajero* cajero = cajeros.buscarCajeroMenosClientes();
        if (cajero == NULL) {
            cout << "No hay cajeros disponibles.\n";
            return false;
        }
        cajeroAsignado = cajero->numeroCaja;
    }

    NodoCliente* nuevo = new NodoCliente(ficha, edad, cajeroAsignado, nombre, apellido, telefono, correo, direccion);

    if (primero == NULL || (ficha[0] == 'A' && (primero->ficha[0] != 'A' || primero->cajeroAsignado != cajeroAsignado))) {
        nuevo->siguiente = primero;
        primero = nuevo;
    } else {
        NodoCliente* actual = primero;
        while (actual->siguiente != NULL && 
               (actual->siguiente->ficha[0] == 'A' || actual->siguiente->cajeroAsignado != cajeroAsignado)) {
            actual = actual->siguiente;
        }
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }

    cajeros.incrementarClientes(cajeroAsignado);
    cout << "Cliente ingresado con ficha: " << ficha << " y asignado al cajero: " << cajeroAsignado << "\n";
    return true;
}

bool Cliente::eliminar(const string& ficha) {
    if (estaVacia()) {
        cout << "No hay clientes en la cola.\n";
        return false;
    }

    if (primero->ficha == ficha) {
        NodoCliente* temp = primero;
        primero = primero->siguiente;
        delete temp;
        cout << "Cliente con ficha " << ficha << " eliminado.\n";
        return true;
    }

    NodoCliente* actual = primero;
    while (actual->siguiente != NULL && actual->siguiente->ficha != ficha) {
        actual = actual->siguiente;
    }

    if (actual->siguiente != NULL) {
        NodoCliente* temp = actual->siguiente;
        actual->siguiente = temp->siguiente;
        delete temp;
        cout << "Cliente con ficha " << ficha << " eliminado.\n";
        return true;
    }
    else {
        cout << "Cliente con ficha " << ficha << " no encontrado.\n";
        return false;
    }
}

void Cliente::atenderClientes(Cajero& cajeros) {
    if (estaVacia()) {
        cout << "No hay clientes para atender.\n";
        return;
    }

    cout << "Estado antes de atender:\n";
    mostrarTodos();
    cajeros.mostrarTodos();

    NodoCajero* cajeroActual = cajeros.obtenerPrimerCajero();
    while (cajeroActual != NULL) {
        NodoCliente* clienteAtendido = NULL;
        NodoCliente* anterior = NULL;
        NodoCliente* actual = primero;

        while (actual != NULL) {
            if (actual->cajeroAsignado == cajeroActual->numeroCaja) {
                clienteAtendido = actual;
                break;
            }
            anterior = actual;
            actual = actual->siguiente;
        }

        if (clienteAtendido != NULL) {
            cout << "Atendiendo cliente con ficha: " << clienteAtendido->ficha
                << " en caja: " << clienteAtendido->cajeroAsignado << "\n";

            if (anterior == NULL) {
                primero = clienteAtendido->siguiente;
            }
            else {
                anterior->siguiente = clienteAtendido->siguiente;
            }

            cajeros.decrementarClientes(clienteAtendido->cajeroAsignado);
            delete clienteAtendido;
        }

        cajeroActual = cajeroActual->siguiente;
    }

    cout << "Estado después de atender:\n";
    mostrarTodos();
    cajeros.mostrarTodos();
}

void Cliente::mostrarTodos() const {
    if (estaVacia()) {
        cout << "No hay clientes en la cola.\n";
        return;
    }

    cout << "------------------------------------ Lista de Clientes ------------------------------------\n";
    cout << left
        << setw(10) << "FICHA" << "| "
        << setw(15) << "NOMBRE" << "| "
        << setw(15) << "APELLIDO" << "| "
        << setw(10) << "TELÉFONO" << "| "
        << setw(25) << "CORREO" << "| "
        << setw(10) << "CAJERO" << "| "
        << setw(20) << "DIRECCIÓN" << endl;
    cout << "------------------------------------------------------------------------------------------\n";

    NodoCliente* actual = primero;
    int totalClientes = 0;
    while (actual != NULL) {
        cout << left
            << setw(10) << actual->ficha << "| "
            << setw(15) << actual->nombre << "| "
            << setw(15) << actual->apellido << "| "
            << setw(10) << actual->telefono << "| "
            << setw(25) << actual->correo << "| "
            << setw(10) << actual->cajeroAsignado << "| "
            << setw(20) << actual->direccion << endl;
        actual = actual->siguiente;
        totalClientes++;
    }
    cout << "------------------------------------------------------------------------------------------\n";
    cout << "Cantidad total de clientes: " << totalClientes << endl;
}