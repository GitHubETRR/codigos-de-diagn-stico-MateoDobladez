#include <iostream>
using namespace std;

int main() {
    float num1, num2, suma, promedio;

    cout << "Ingrese el primer número: ";
    cin >> num1;
    cout << "Ingrese el segundo número: ";
    cin >> num2;

    suma = num1 + num2;
    promedio = suma / 2.0;

    cout << "La suma es: " << suma << endl;
    cout << "El promedio es: " << promedio << endl;

    return 0;
}