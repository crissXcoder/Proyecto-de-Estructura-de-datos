#include "cliente.h"
#include <iostream>
#include <iomanip>
#include <ctime>

Cliente::Cliente() : primero(NULL), consecutivoC(1), consecutivoA(1) {}

Cliente::~Cliente() {
    NodoCliente* actual = primero;
    while (actual != NULL) {
        NodoCliente* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void Cliente::ingresar(int edad, Cajero& cajeros) {
    string ficha;
    int cajeroAsignado;
    
    if (edad >= 65) {
        ficha = "A" + to_string(consecutivoA++);
        NodoCajero* cajero = cajeros.buscarPrimerCajeroDisponible();
        if (cajero == NULL) {
            cout << "No hay cajeros disponibles.\n";
            return;
        }
        cajeroAsignado = cajero->numeroCaja;
    } else {
        ficha = "C" + to_string(consecutivoC++);
        NodoCajero* cajero = cajeros.buscarCajeroMenosClientes();
        if (cajero == NULL) {
            cout << "No hay cajeros disponibles.\n";
            return;
        }
        cajeroAsignado = cajero->numeroCaja;
    }
    
    NodoCliente* nuevo = new NodoCliente(ficha, edad, cajeroAsignado);
    
    if (primero == NULL || ficha[0] == 'A') {
        nuevo->siguiente = primero;
        primero = nuevo;
    } else {
        NodoCliente* actual = primero;
        while (actual->siguiente != NULL && actual->siguiente->ficha[0] != 'A') {
            actual = actual->siguiente;
        }
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }
    
    cajeros.incrementarClientes(cajeroAsignado);
    cout << "Cliente ingresado con ficha: " << ficha << " y asignado al cajero: " << cajeroAsignado << "\n";
}

void Cliente::eliminar(string ficha) {
    if (primero == NULL) {
        cout << "No hay clientes en la cola.\n";
        return;
    }
    
    if (primero->ficha == ficha) {
        NodoCliente* temp = primero;
        primero = primero->siguiente;
        delete temp;
        cout << "Cliente con ficha " << ficha << " eliminado.\n";
        return;
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
    } else {
        cout << "Cliente con ficha " << ficha << " no encontrado.\n";
    }
}

void Cliente::atenderClientes(Cajero& cajeros) {
    cout << "Estado antes de atender:\n";
    mostrarTodos();
    cajeros.mostrarTodos();
    
    NodoCliente* actual = primero;
    NodoCliente* anterior = NULL;
    
    while (actual != NULL) {
        cout << "Atendiendo cliente con ficha: " << actual->ficha << " en caja: " << actual->cajeroAsignado << "\n";
        cajeros.decrementarClientes(actual->cajeroAsignado);
        
        if (anterior == NULL) {
            primero = actual->siguiente;
        } else {
            anterior->siguiente = actual->siguiente;
        }
        
        NodoCliente* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
    
    cout << "Estado después de atender:\n";
    mostrarTodos();
    cajeros.mostrarTodos();
}

void Cliente::mostrarTodos() {
    NodoCliente* actual = primero;
    while (actual != NULL) {
        cout << "Ficha: " << actual->ficha 
             << ", Edad: " << actual->edad
             << ", Fecha: " << &actual->fecha
             << ", Cajero: " << actual->cajeroAsignado << "\n";
        actual = actual->siguiente;
    }
}