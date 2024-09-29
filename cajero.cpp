#include "cajero.h"

Cajero::Cajero() : primero(NULL), ultimo(NULL), totalCajeros(0) {}

Cajero::~Cajero() {
    NodoCajero* actual = primero;
    while (actual != NULL) {
        NodoCajero* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

void Cajero::ingresar(int id, int numeroCaja, string nombre) {
    if (totalCajeros >= 6) {
        cout << "Error: No se pueden agregar más cajeros. Límite alcanzado.\n";
        return;
    }
    
    NodoCajero* nuevo = new NodoCajero(id, numeroCaja, nombre);
    
    if (primero == NULL) {
        primero = ultimo = nuevo;
    } else {
        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;
        ultimo = nuevo;
    }
    
    totalCajeros++;
    cout << "Cajero ingresado exitosamente.\n";
}

void Cajero::mostrar(int id) {
    NodoCajero* actual = primero;
    while (actual != NULL) {
        if (actual->id == id) {
            cout << "ID: " << actual->id << "\n";
            cout << "Número de Caja: " << actual->numeroCaja << "\n";
            cout << "Nombre: " << actual->nombre << "\n";
            cout << "Clientes en cola: " << actual->clientesEnCola << "\n";
            return;
        }
        actual = actual->siguiente;
    }
    cout << "Cajero no encontrado.\n";
}

void Cajero::modificar(int id, string nuevoNombre) {
    NodoCajero* actual = primero;
    while (actual != NULL) {
        if (actual->id == id) {
            actual->nombre = nuevoNombre;
            cout << "Datos del cajero modificados exitosamente.\n";
            return;
        }
        actual = actual->siguiente;
    }
    cout << "Cajero no encontrado.\n";
}

void Cajero::eliminar(int id) {
    NodoCajero* actual = primero;
    while (actual != NULL) {
        if (actual->id == id) {
            if (actual->clientesEnCola > 0) {
                cout << "No se puede eliminar el cajero. Tiene clientes pendientes.\n";
                return;
            }
            
            if (actual == primero) {
                primero = actual->siguiente;
                if (primero != NULL) primero->anterior = NULL;
            } else if (actual == ultimo) {
                ultimo = actual->anterior;
                ultimo->siguiente = NULL;
            } else {
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
            }
            
            delete actual;
            totalCajeros--;
            cout << "Cajero eliminado exitosamente.\n";
            return;
        }
        actual = actual->siguiente;
    }
    cout << "Cajero no encontrado.\n";
}

void Cajero::mostrarTodos() {
    NodoCajero* actual = primero;
    while (actual != NULL) {
        cout << "ID: " << actual->id << ", Caja: " << actual->numeroCaja 
             << ", Nombre: " << actual->nombre << ", Clientes: " << actual->clientesEnCola << "\n";
        actual = actual->siguiente;
    }
}

NodoCajero* Cajero::buscarCajeroMenosClientes() {
    if (primero == NULL) return NULL;
    
    NodoCajero* menorCola = primero;
    NodoCajero* actual = primero->siguiente;
    
    while (actual != NULL) {
        if (actual->clientesEnCola < menorCola->clientesEnCola) {
            menorCola = actual;
        }
        actual = actual->siguiente;
    }
    
    return menorCola;
}

NodoCajero* Cajero::buscarPrimerCajeroDisponible() {
    return primero;  // Simplemente retorna el primer cajero
}

void Cajero::incrementarClientes(int numeroCaja) {
    NodoCajero* actual = primero;
    while (actual != NULL) {
        if (actual->numeroCaja == numeroCaja) {
            actual->clientesEnCola++;
            return;
        }
        actual = actual->siguiente;
    }
}

void Cajero::decrementarClientes(int numeroCaja) {
    NodoCajero* actual = primero;
    while (actual != NULL) {
        if (actual->numeroCaja == numeroCaja && actual->clientesEnCola > 0) {
            actual->clientesEnCola--;
            return;
        }
        actual = actual->siguiente;
    }
}