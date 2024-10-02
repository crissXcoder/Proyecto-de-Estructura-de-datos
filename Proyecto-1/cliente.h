#pragma once
#ifndef CLIENTE_H
#define CLIENTE_H
#include "cajero.h"
#include <string>
#include <ctime>
using namespace std;

class NodoCliente {
public:
    string ficha;
    time_t fecha;
    int edad;
    int cajeroAsignado;
    string nombre;
    string apellido;
    string telefono;
    string correo;
    string direccion;
    NodoCliente* siguiente;
    NodoCliente(const string& _ficha, int _edad, int _cajeroAsignado, const string& _nombre, const string& _apellido, const string& _telefono, const string& _correo, const string& _direccion) :
        ficha(_ficha), edad(_edad), cajeroAsignado(_cajeroAsignado), nombre(_nombre), apellido(_apellido), telefono(_telefono), correo(_correo), direccion(_direccion), siguiente(NULL) {
        fecha = time(0);
    }
};

class Cliente {
private:
    NodoCliente* primero;
    int consecutivoC;
    int consecutivoA;
public:
    Cliente();
    ~Cliente();
    bool ingresar(int edad, Cajero& cajeros, const string& nombre, const string& apellido, const string& telefono, const string& correo, const string& direccion);
    bool eliminar(const string& ficha);
    void atenderClientes(Cajero& cajeros);
    void mostrarTodos() const;
    bool estaVacia() const { return primero == NULL; }
};
#endif