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
                for (const Mesa& m : mesas) {
                    m.mostrarEstado();
                }
                break;
            case RESERVAR: {
                int num;
                string nombre;
                cout << "Ingrese número de mesa (1-10): ";
                cin >> num;
                if (num < 1 || num > 10) {
                    cout << "Número de mesa inválido." << endl;
                    break;
                }
                cout << "Ingrese su nombre: ";
                cin.ignore();
                getline(cin, nombre);
                mesas[num - 1].reservar(nombre);
                break;
            }
            case CANCELAR: {
                int num;
                cout << "Ingrese número de mesa para cancelar (1-10): ";
                cin >> num;
                if (num < 1 || num > 10) {
                    cout << "Número de mesa inválido." << endl;
                    break;
                }
                mesas[num - 1].cancelarReserva();
                break;
            }
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
