#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

enum MENU {
    AGREGAR = 1,
    LISTA,
    BUSCAR,
    EDITAR,
    GUARDAR_SALIR
};

struct Perfume {
    std::string nombre;
    std::string marca;
    float precio;
    int stock;
    Perfume* siguiente;
    
    Perfume(const std::string& n, const std::string& m, float p, int s)
        : nombre(n), marca(m), precio(p), stock(s), siguiente(nullptr) {}
};

class StockPerfumes {
private:
    Perfume* lista;

    Perfume* crearPerfume(const std::string& nombre, const std::string& marca, float precio, int stock);
    void agregarPerfume(const std::string& nombre, const std::string& marca, float precio, int stock);
    void listaDePerfumes();
    void buscarPerfume(const std::string& nombreBuscado);
    void editarPerfume(const std::string& nombre);
    void guardarPerfumes(const std::string& archivo);
    void cargarPerfumes(const std::string& archivo);
    void liberarPerfumes();

public:
    StockPerfumes() : lista(nullptr) {}
    ~StockPerfumes() {
        liberarPerfumes();
    }
    
    void ejecutar();
};

Perfume* StockPerfumes::crearPerfume(const std::string& nombre, const std::string& marca, float precio, int stock) {
    return new Perfume(nombre, marca, precio, stock);
}

void StockPerfumes::agregarPerfume(const std::string& nombre, const std::string& marca, float precio, int stock) {
    Perfume* nuevo = crearPerfume(nombre, marca, precio, stock);
    nuevo->siguiente = lista;
    lista = nuevo;
}

void StockPerfumes::listaDePerfumes() {
    Perfume* actual = lista;
    int num = 1;

    std::cout << "\n\033[1;34m--- Lista de perfumes ---\033[0m\n";
    while (actual != nullptr) {
        std::cout << "\nPerfume " << num << ":\n";
        std::cout << "Nombre: " << actual->nombre << "\n";
        std::cout << "Marca: " << actual->marca << "\n";
        std::cout << "Precio: $" << std::fixed << std::setprecision(2) << actual->precio << "\n";
        std::cout << "Stock: " << actual->stock << " unidades\n";
        actual = actual->siguiente;
        num++;
    }
}

void StockPerfumes::buscarPerfume(const std::string& nombreBuscado) {
    Perfume* actual = lista;
    while (actual != nullptr) {
        if (actual->nombre == nombreBuscado) {
            std::cout << "\n\033[1;35mPerfume encontrado:\033[0m\n";
            std::cout << "Nombre: " << actual->nombre << "\n";
            std::cout << "Marca: " << actual->marca << "\n";
            std::cout << "Precio: $" << std::fixed << std::setprecision(2) << actual->precio << "\n";
            std::cout << "Stock: " << actual->stock << " unidades\n";
            return;
        }
        actual = actual->siguiente;
    }
    std::cout << "\033[1;31mPerfume no encontrado.\033[0m\n";
}

void StockPerfumes::editarPerfume(const std::string& nombre) {
    Perfume* actual = lista;
    while (actual != nullptr) {
        if (actual->nombre == nombre) {
            std::cout << "\n\033[1;36mEditando " << actual->nombre << "\033[0m\n";
            std::cout << "Nuevo precio: ";
            std::cin >> actual->precio;
            std::cout << "Nuevo stock: ";
            std::cin >> actual->stock;
            std::cin.ignore();
            std::cout << "\033[1;32mActualización completada.\033[0m\n";
            return;
        }
        actual = actual->siguiente;
    }
    std::cout << "\033[1;31mPerfume no encontrado para editar.\033[0m\n";
}

void StockPerfumes::guardarPerfumes(const std::string& archivo) {
    std::ofstream f(archivo);
    if (!f.is_open()) {
        std::cout << "\033[1;31mNo se pudo abrir el archivo para guardar.\033[0m\n";
        return;
    }

    Perfume* actual = lista;
    while (actual != nullptr) {
        f << actual->nombre << ";" << actual->marca << ";" 
          << std::fixed << std::setprecision(2) << actual->precio 
          << ";" << actual->stock << "\n";
        actual = actual->siguiente;
    }
    f.close();
}

void StockPerfumes::cargarPerfumes(const std::string& archivo) {
    std::ifstream f(archivo);
    if (!f.is_open()) return;

    std::string linea;
    while (std::getline(f, linea)) {
        if (linea.empty()) continue;
        
        size_t pos1 = linea.find(';');
        size_t pos2 = linea.find(';', pos1 + 1);
        size_t pos3 = linea.find(';', pos2 + 1);
        
        if (pos1 != std::string::npos && pos2 != std::string::npos && pos3 != std::string::npos) {
            std::string nombre = linea.substr(0, pos1);
            std::string marca = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            float precio = std::stof(linea.substr(pos2 + 1, pos3 - pos2 - 1));
            int stock = std::stoi(linea.substr(pos3 + 1));
            
            agregarPerfume(nombre, marca, precio, stock);
        }
    }
    f.close();
}

void StockPerfumes::liberarPerfumes() {
    Perfume* actual = lista;
    while (actual != nullptr) {
        Perfume* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
    lista = nullptr;
}

void StockPerfumes::ejecutar() {
    int eleccion;
    std::string nombre, marca;
    float precio;
    int stock;
    const std::string archivo = "perfumes.txt";

    cargarPerfumes(archivo);

    do {
        std::cout << "\n\033[1;32m--- MENU STOCK PERFUMES ---\033[0m\n";
        std::cout << AGREGAR << ". Agregar perfume\n";
        std::cout << LISTA << ". Lista de perfumes\n";
        std::cout << BUSCAR << ". Buscar perfume\n";
        std::cout << EDITAR << ". Editar perfume\n";
        std::cout << GUARDAR_SALIR << ". Guardar y salir\n";
        std::cout << "Elige una opción: ";
        std::cin >> eleccion;
        std::cin.ignore();

        switch (eleccion) {
            case AGREGAR:
                std::cout << "\nNombre: ";
                std::getline(std::cin, nombre);

                std::cout << "Marca: ";
                std::getline(std::cin, marca);

                std::cout << "Precio: ";
                std::cin >> precio;
                std::cout << "Stock: ";
                std::cin >> stock;
                std::cin.ignore();

                agregarPerfume(nombre, marca, precio, stock);
                break;

            case LISTA:
                listaDePerfumes();
                break;

            case BUSCAR:
                std::cout << "\nNombre a buscar: ";
                std::getline(std::cin, nombre);
                buscarPerfume(nombre);
                break;

            case EDITAR:
                std::cout << "\nNombre del perfume a editar: ";
                std::getline(std::cin, nombre);
                editarPerfume(nombre);
                break;

            case GUARDAR_SALIR:
                guardarPerfumes(archivo);
                liberarPerfumes();
                std::cout << "\n\033[1;36mDatos guardados correctamente. Hasta luego!\033[0m\n";
                break;

            default:
                std::cout << "\033[1;31mOpción no válida.\033[0m\n";
        }
    } while (eleccion != GUARDAR_SALIR);
}

int main() {
    StockPerfumes stock;
    stock.ejecutar();
    return 0;
}

