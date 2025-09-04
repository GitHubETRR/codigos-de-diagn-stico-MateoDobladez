#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Mesa {
private:
    int numero;
    bool reservada;
    string nombreCliente;

public:
    Mesa(int num) {
        numero = num;
        reservada = false;
        nombreCliente = "";
    }

    int getNumero() const {
        return numero;
    }

    bool estaReservada() const {
        return reservada;
    }

    string getNombreCliente() const {
        return nombreCliente;
    }

    void reservar(string nombre) {
        if (!reservada) {
            reservada = true;
            nombreCliente = nombre;
            cout << "Mesa " << numero << " reservada exitosamente por " << nombre << "." << endl;
        } else {
            cout << "La mesa " << numero << " ya está reservada por " << nombreCliente << "." << endl;
        }
    }

    void cancelarReserva() {
        if (reservada) {
            cout << "Reserva de la mesa " << numero << " cancelada (era de " << nombreCliente << ")." << endl;
            reservada = false;
            nombreCliente = "";
        } else {
            cout << "La mesa " << numero << " no está reservada." << endl;
        }
    }

    void mostrarEstado() const {
        cout << "Mesa " << numero << " - ";
        if (reservada)
            cout << "Reservada por: " << nombreCliente << endl;
        else
            cout << "Disponible" << endl;
    }
};

// Funciones auxiliares para manejar las opciones del menú
void mostrarEstados(const vector<Mesa>& mesas) {
    for (const Mesa& mesa : mesas) {
        mesa.mostrarEstado();
    }
}

void manejarReservarMesa(vector<Mesa>& mesas) {
    int numeroMesa;
    string nombreCliente;
    cout << "Ingrese número de mesa (1-10): ";
    cin >> numeroMesa;
    if (numeroMesa < 1 || numeroMesa > 10) {
        cout << "Número de mesa inválido." << endl;
        return;
    }
    cout << "Ingrese su nombre: ";
    cin.ignore();
    getline(cin, nombreCliente);
    mesas[numeroMesa - 1].reservar(nombreCliente);
}

void manejarCancelarReserva(vector<Mesa>& mesas) {
    int numeroMesa;
    cout << "Ingrese número de mesa para cancelar (1-10): ";
    cin >> numeroMesa;
    if (numeroMesa < 1 || numeroMesa > 10) {
        cout << "Número de mesa inválido." << endl;
        return;
    }
    mesas[numeroMesa - 1].cancelarReserva();
}

int main() {
    vector<Mesa> mesas;

    for (int i = 1; i <= 10; i++) {
        mesas.push_back(Mesa(i));
    }

    const int ESTADO = 1;
    const int RESERVAR = 2;
    const int CANCELAR = 3;
    const int SALIR = 4;
    int opcion;
    do {
        cout << "  Reservas de mesas - Restaurante\n";
        cout << ESTADO << ". Ver estado de las mesas\n";
        cout << RESERVAR << ". Reservar una mesa\n";
        cout << CANCELAR << ". Cancelar una reserva\n";
        cout << SALIR << ". Salir\n";
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
            case ESTADO:
                mostrarEstados(mesas);
                break;
            case RESERVAR:
                manejarReservarMesa(mesas);
                break;
            case CANCELAR:
                manejarCancelarReserva(mesas);
                break;
            case SALIR:
                cout << "Cerrando el sistema." << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
                break;
        }
    } while (opcion != SALIR);

    return 0;
}
