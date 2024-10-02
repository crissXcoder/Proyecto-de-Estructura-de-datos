#pragma once
#ifndef CAJERO_H
#define CAJERO_H
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class NodoCajero {
public:
    int id;
    int numeroCaja;
    string nombre;
    string apellido;
    string correo;
    int clientesEnCola;
    NodoCajero* siguiente;
    NodoCajero* anterior;
    NodoCajero(int _id, int _numeroCaja, const string& _nombre, const string& _apellido, const string& _correo) :
        id(_id), numeroCaja(_numeroCaja), nombre(_nombre), apellido(_apellido), correo(_correo), clientesEnCola(0), siguiente(NULL), anterior(NULL) {}
};

class Cajero {
private:
    NodoCajero* primero;
    NodoCajero* ultimo;
    int totalCajeros;
    const int MAX_CAJEROS = 6;
public:
    bool existeCajero(int id) const;
    bool existeNumeroCaja(int numeroCaja) const;
    Cajero();
    ~Cajero();
    bool ingresar(int id, int numeroCaja, const string& nombre, const string& apellido, const string& correo);
    void mostrarListaCajero();
    void mostrar(int id) const;
    bool modificar(int id, const string& nuevoNombre, const string& nuevoApellido, const string& nuevoCorreo);
    bool eliminar(int id);
    void mostrarTodos() const;
    NodoCajero* buscarCajeroMenosClientes();
    NodoCajero* buscarPrimerCajeroDisponible();
    NodoCajero* buscarCajeroAleatorioDisponible();
    NodoCajero* buscarCajeroParaAdultoMayor();
    NodoCajero* obtenerPrimerCajero() { return primero; }
    void incrementarClientes(int numeroCaja);
    void decrementarClientes(int numeroCaja);
    bool estaVacia() const { return primero == NULL; }
    
};
#endif