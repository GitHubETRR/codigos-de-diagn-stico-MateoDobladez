#include <iostream>

using namespace std;

// Clases con un solo bloque public y herencia simple
class Operacion {
public:
    virtual double aplicar(double a, double b) const = 0;
};

class Suma : public Operacion {
public:
    double aplicar(double a, double b) const override { return a + b; }
};

class Resta : public Operacion {
public:
    double aplicar(double a, double b) const override { return a - b; }
};

class Multiplicacion : public Operacion {
public:
    double aplicar(double a, double b) const override { return a * b; }
};

class Division : public Operacion {
public:
    double aplicar(double a, double b) const override { return a / b; }
};

// Prototipos de funciones
void mostrarMenu();
void sumar();
void restar();
void multiplicar();
void dividir();

void mostrarMenu() {
    cout << "\nCalculadora básica" << endl;
    cout << "1. Sumar" << endl;
    cout << "2. Restar" << endl;
    cout << "3. Multiplicar" << endl;
    cout << "4. Dividir" << endl;
    cout << "5. Salir" << endl;
    cout << "Seleccione una opción: ";
}

void sumar() {
    double a = 0.0, b = 0.0;
    cout << "Ingrese el primer número: ";
    cin >> a;
    cout << "Ingrese el segundo número: ";
    cin >> b;
    Suma op;
    cout << "Resultado: " << op.aplicar(a, b) << endl;
}

void restar() {
    double a = 0.0, b = 0.0;
    cout << "Ingrese el primer número: ";
    cin >> a;
    cout << "Ingrese el segundo número: ";
    cin >> b;
    Resta op;
    cout << "Resultado: " << op.aplicar(a, b) << endl;
}

void multiplicar() {
    double a = 0.0, b = 0.0;
    cout << "Ingrese el primer número: ";
    cin >> a;
    cout << "Ingrese el segundo número: ";
    cin >> b;
    Multiplicacion op;
    cout << "Resultado: " << op.aplicar(a, b) << endl;
}

void dividir() {
    double a = 0.0, b = 0.0;
    cout << "Ingrese el dividendo: ";
    cin >> a;
    cout << "Ingrese el divisor: ";
    cin >> b;
    if (b == 0.0) {
        cout << "Error: división por cero no permitida." << endl;
        return;
    }
    Division op;
    cout << "Resultado: " << op.aplicar(a, b) << endl;
}

int main() {
    const int SUMAR = 1;
    const int RESTAR = 2;
    const int MULTIPLICAR = 3;
    const int DIVIDIR = 4;
    const int SALIR = 5;

    int opcion = 0;
    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case SUMAR:
                sumar();
                break;
            case RESTAR:
                restar();
                break;
            case MULTIPLICAR:
                multiplicar();
                break;
            case DIVIDIR:
                dividir();
                break;
            case SALIR:
                cout << "Saliendo de la calculadora." << endl;
                break;
            default:
                cout << "Opción no válida. Intente nuevamente." << endl;
                break;
        }
    } while (opcion != SALIR);

    return 0;
}

#include <iostream>

using namespace std;

// Clases con herencia para representar operaciones básicas
class Operacion {
public:
    virtual double aplicar(double a, double b) const = 0;
};

class Suma : public Operacion {
public:
    double aplicar(double a, double b) const override { return a + b; }
};

class Resta : public Operacion {
public:
    double aplicar(double a, double b) const override { return a - b; }
};

class Multiplicacion : public Operacion {
public:
    double aplicar(double a, double b) const override { return a * b; }
};

class Division : public Operacion {
public:
    double aplicar(double a, double b) const override { return a / b; }
};

// Prototipos de funciones
void mostrarMenu();
void sumar();
void restar();
void multiplicar();
void dividir();

void mostrarMenu() {
    cout << "\nCalculadora básica" << endl;
    cout << "1. Sumar" << endl;
    cout << "2. Restar" << endl;
    cout << "3. Multiplicar" << endl;
    cout << "4. Dividir" << endl;
    cout << "5. Salir" << endl;
    cout << "Seleccione una opción: ";
}

void sumar() {
    double a = 0.0, b = 0.0;
    cout << "Ingrese el primer número: ";
    cin >> a;
    cout << "Ingrese el segundo número: ";
    cin >> b;
    Suma op;
    cout << "Resultado: " << op.aplicar(a, b) << endl;
}

void restar() {
    double a = 0.0, b = 0.0;
    cout << "Ingrese el primer número: ";
    cin >> a;
    cout << "Ingrese el segundo número: ";
    cin >> b;
    Resta op;
    cout << "Resultado: " << op.aplicar(a, b) << endl;
}

void multiplicar() {
    double a = 0.0, b = 0.0;
    cout << "Ingrese el primer número: ";
    cin >> a;
    cout << "Ingrese el segundo número: ";
    cin >> b;
    Multiplicacion op;
    cout << "Resultado: " << op.aplicar(a, b) << endl;
}

void dividir() {
    double a = 0.0, b = 0.0;
    cout << "Ingrese el dividendo: ";
    cin >> a;
    cout << "Ingrese el divisor: ";
    cin >> b;
    if (b == 0.0) {
        cout << "Error: división por cero no permitida." << endl;
        return;
    }
    Division op;
    cout << "Resultado: " << op.aplicar(a, b) << endl;
}

int main() {
    const int SUMAR = 1;
    const int RESTAR = 2;
    const int MULTIPLICAR = 3;
    const int DIVIDIR = 4;
    const int SALIR = 5;

    int opcion = 0;
    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case SUMAR:
                sumar();
                break;
            case RESTAR:
                restar();
                break;
            case MULTIPLICAR:
                multiplicar();
                break;
            case DIVIDIR:
                dividir();
                break;
            case SALIR:
                cout << "Saliendo de la calculadora." << endl;
                break;
            default:
                cout << "Opción no válida. Intente nuevamente." << endl;
                break;
        }
    } while (opcion != SALIR);

    return 0;
}


