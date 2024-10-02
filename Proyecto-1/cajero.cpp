#include "cajero.h"
#include <limits>

Cajero::Cajero() : primero(NULL), ultimo(NULL), totalCajeros(0) {}

Cajero::~Cajero() {
    while (primero != NULL) {
        NodoCajero* temp = primero;
        primero = primero->siguiente;
        delete temp;
    }
}

bool Cajero::existeCajero(int id) const {
    NodoCajero* actual = primero;
    while (actual != NULL) {
        if (actual->id == id) return true;
        actual = actual->siguiente;
    }
    return false;
}

bool Cajero::existeNumeroCaja(int numeroCaja) const {
    NodoCajero* actual = primero;
    while (actual != NULL) {
        if (actual->numeroCaja == numeroCaja) return true;
        actual = actual->siguiente;
    }
    return false;
}

bool Cajero::ingresar(int id, int numeroCaja, const string& nombre, const string& apellido, const string& correo) {
    if (totalCajeros >= MAX_CAJEROS) {
        cout << "Error: No se pueden agregar más cajeros. Límite alcanzado.\n";
        return false;
    }
    if (existeCajero(id)) {
        cout << "Error: Ya existe un cajero con ese ID.\n";
        return false;
    }
    if (existeNumeroCaja(numeroCaja)) {
        cout << "Error: Ya existe un cajero con ese número de caja.\n";
        return false;
    }

    NodoCajero* nuevo = new NodoCajero(id, numeroCaja, nombre, apellido, correo);

    if (primero == NULL) {
        primero = ultimo = nuevo;
    }
    else {
        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;
        ultimo = nuevo;
    }

    totalCajeros++;
    cout << "Cajero ingresado exitosamente.\n";
    return true;
}

void Cajero::mostrarListaCajero() {
    if (estaVacia()) {
        cout << "La lista de cajeros está vacía.\n";
        return;
    }

    cout << "------------------------------------ Lista de Cajeros ------------------------------------\n";
    cout << left
        << setw(5) << "ID" << "| "
        << setw(10) << "CAJA" << "| "
        << setw(15) << "NOMBRE" << "| "
        << setw(15) << "APELLIDO" << "| "
        << setw(25) << "CORREO" << "| "
        << setw(10) << "CLIENTES" << endl;
    cout << "----------------------------------------------------------------------------------------\n";

    NodoCajero* actual = primero;
    while (actual != NULL) {
        cout << left
            << setw(5) << actual->id << "| "
            << setw(10) << actual->numeroCaja << "| "
            << setw(15) << actual->nombre << "| "
            << setw(15) << actual->apellido << "| "
            << setw(25) << actual->correo << "| "
            << setw(10) << actual->clientesEnCola << endl;
        actual = actual->siguiente;
    }
    cout << "----------------------------------------------------------------------------------------\n";
    cout << "Cantidad total de cajeros: " << totalCajeros << endl;
}

void Cajero::mostrar(int id) const {
    if (estaVacia()) {
        cout << "La lista de cajeros está vacía.\n";
        return;
    }

    NodoCajero* actual = primero;
    while (actual != NULL) {
        if (actual->id == id) {
            cout << "ID: " << actual->id << "\n";
            cout << "Número de Caja: " << actual->numeroCaja << "\n";
            cout << "Nombre: " << actual->nombre << "\n";
            cout << "Apellido: " << actual->apellido << "\n";
            cout << "Correo: " << actual->correo << "\n";
            cout << "Clientes en cola: " << actual->clientesEnCola << "\n";
            return;
        }
        actual = actual->siguiente;
    }
    cout << "Cajero no encontrado.\n";
}

bool Cajero::modificar(int id, const string& nuevoNombre, const string& nuevoApellido, const string& nuevoCorreo) {
    if (estaVacia()) {
        cout << "La lista de cajeros está vacía.\n";
        return false;
    }

    NodoCajero* actual = primero;
    while (actual != NULL) {
        if (actual->id == id) {
            actual->nombre = nuevoNombre;
            actual->apellido = nuevoApellido;
            actual->correo = nuevoCorreo;
            cout << "Datos del cajero modificados exitosamente.\n";
            return true;
        }
        actual = actual->siguiente;
    }
    cout << "Cajero no encontrado.\n";
    return false;
}

bool Cajero::eliminar(int id) {
    if (estaVacia()) {
        cout << "La lista de cajeros está vacía.\n";
        return false;
    }

    NodoCajero* actual = primero;
    while (actual != NULL) {
        if (actual->id == id) {
            if (actual->clientesEnCola > 0) {
                cout << "No se puede eliminar el cajero. Tiene clientes pendientes.\n";
                return false;
            }

            if (actual == primero) {
                primero = actual->siguiente;
                if (primero != NULL) primero->anterior = NULL;
            }
            else if (actual == ultimo) {
                ultimo = actual->anterior;
                ultimo->siguiente = NULL;
            }
            else {
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
            }

            delete actual;
            totalCajeros--;
            cout << "Cajero eliminado exitosamente.\n";
            return true;
        }
        actual = actual->siguiente;
    }
    cout << "Cajero no encontrado.\n";
    return false;
}

void Cajero::mostrarTodos() const {
    if (estaVacia()) {
        cout << "La lista de cajeros está vacía.\n";
        return;
    }

    NodoCajero* actual = primero;
    while (actual != NULL) {
        cout << "ID: " << actual->id << ", Caja: " << actual->numeroCaja
            << ", Nombre: " << actual->nombre << ", Clientes: " << actual->clientesEnCola << "\n";
        actual = actual->siguiente;
    }
}


NodoCajero* Cajero::buscarCajeroParaAdultoMayor() {
    NodoCajero* cajeroElegido = NULL;
    int menorCantidadClientes = INT_MAX;

    NodoCajero* actual = primero;
    while (actual != NULL) {
        if (actual->clientesEnCola < menorCantidadClientes) {
            menorCantidadClientes = actual->clientesEnCola;
            cajeroElegido = actual;
        }
        actual = actual->siguiente;
    }

    return cajeroElegido;
}

NodoCajero* Cajero::buscarCajeroMenosClientes() {
    if (estaVacia()) return NULL;

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
    NodoCajero* actual = primero;
    while (actual != NULL) {
        if (actual->clientesEnCola < 5) { // Asumimos que un cajero está disponible si tiene menos de 5 clientes
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL; // No hay cajeros disponibles
}

NodoCajero* Cajero::buscarCajeroAleatorioDisponible() {
    int cajerosDisponibles = 0;
    NodoCajero* actual = primero;
    while (actual != NULL) {
        if (actual->clientesEnCola < 5) {
            cajerosDisponibles++;
        }
        actual = actual->siguiente;
    }

    if (cajerosDisponibles == 0) {
        return NULL; // No hay cajeros disponibles
    }

    int cajeroSeleccionado = rand() % cajerosDisponibles + 1;
    actual = primero;
    int contador = 0;

    while (actual != NULL) {
        if (actual->clientesEnCola < 5) {
            contador++;
            if (contador == cajeroSeleccionado) {
                return actual;
            }
        }
        actual = actual->siguiente;
    }

    return NULL; // No debería llegar aquí, pero por si acaso
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