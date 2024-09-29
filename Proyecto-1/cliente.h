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
    NodoCliente* siguiente;

    NodoCliente(string _ficha, int _edad, int _cajeroAsignado) :
        ficha(_ficha), edad(_edad), cajeroAsignado(_cajeroAsignado), siguiente(NULL) {
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

    void ingresar(int edad, Cajero& cajeros);
    void eliminar(string ficha);
    void atenderClientes(Cajero& cajeros);
    void mostrarTodos();
};

#endif