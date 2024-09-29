#pragma once
#ifndef CAJERO_H
#define CAJERO_H

#include <string>
#include <iostream>

using namespace std;

class NodoCajero {
public:
    int id;
    int numeroCaja;
    string nombre;
    int clientesEnCola;
    NodoCajero* siguiente;
    NodoCajero* anterior;

    NodoCajero(int _id, int _numeroCaja, string _nombre) :
        id(_id), numeroCaja(_numeroCaja), nombre(_nombre), clientesEnCola(0), siguiente(NULL), anterior(NULL) {}
};

class Cajero {
private:
    NodoCajero* primero;
    NodoCajero* ultimo;
    int totalCajeros;

public:
    Cajero();
    ~Cajero();

    void ingresar(int id, int numeroCaja, string nombre);
    void mostrar(int id);
    void modificar(int id, string nuevoNombre);
    void eliminar(int id);
    void mostrarTodos();
    NodoCajero* buscarCajeroMenosClientes();
    NodoCajero* buscarPrimerCajeroDisponible();
    void incrementarClientes(int numeroCaja);
    void decrementarClientes(int numeroCaja);
};

#endif