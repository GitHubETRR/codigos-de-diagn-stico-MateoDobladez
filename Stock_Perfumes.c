#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

enum MENU {
    AGREGAR = 1,
    LISTA,
    BUSCAR,
    EDITAR,
    GUARDAR_SALIR
};

typedef struct perfume {
    char nombre[MAX];
    char marca[MAX];
    float precio;
    int stock;
    struct perfume* siguiente;
} perfume;

perfume* lista = NULL;

perfume* CrearPerfume(const char* nombre, const char* marca, float precio, int stock);
void AgregarPerfume(const char* nombre, const char* marca, float precio, int stock);
void ListaDePerfumes();
void BuscarPerfume(const char* nombreBuscado);
void EditarPerfume(const char* nombre);
void GuardarPerfumes(const char* archivo);
void CargarPerfumes(const char* archivo);
void LiberarPerfumes();

int main() {
    int eleccion;
    char nombre[MAX], marca[MAX];
    float precio;
    int stock;
    const char* archivo = "perfumes.txt";

    CargarPerfumes(archivo);

    do {
        printf("\n\033[1;32m--- MENU STOCK PERFUMES ---\033[0m\n");
        printf("%d. Agregar perfume\n", AGREGAR);
        printf("%d. Lista de perfumes\n", LISTA);
        printf("%d. Buscar perfume\n", BUSCAR);
        printf("%d. Editar perfume\n", EDITAR);
        printf("%d. Guardar y salir\n", GUARDAR_SALIR);
        printf("Elige una opción: ");
        scanf("%d", &eleccion);
        getchar();

        switch (eleccion) {
            case AGREGAR:
                printf("\nNombre: ");
                fgets(nombre, MAX, stdin);
                nombre[strcspn(nombre, "\n")] = '\0';

                printf("Marca: ");
                fgets(marca, MAX, stdin);
                marca[strcspn(marca, "\n")] = '\0';

                printf("Precio: ");
                scanf("%f", &precio);
                printf("Stock: ");
                scanf("%d", &stock);
                getchar();

                AgregarPerfume(nombre, marca, precio, stock);
                break;

            case LISTA:
                ListaDePerfumes();
                break;

            case BUSCAR:
                printf("\nNombre a buscar: ");
                fgets(nombre, MAX, stdin);
                nombre[strcspn(nombre, "\n")] = '\0';
                BuscarPerfume(nombre);
                break;

            case EDITAR:
                printf("\nNombre del perfume a editar: ");
                fgets(nombre, MAX, stdin);
                nombre[strcspn(nombre, "\n")] = '\0';
                EditarPerfume(nombre);
                break;

            case GUARDAR_SALIR:
                GuardarPerfumes(archivo);
                LiberarPerfumes();
                printf("\n\033[1;36mDatos guardados correctamente. Hasta luego!\033[0m\n");
                break;

            default:
                printf("\033[1;31mOpción no válida.\033[0m\n");
        }
    } while (eleccion != GUARDAR_SALIR);

    return 0;
}

perfume* CrearPerfume(const char* nombre, const char* marca, float precio, int stock) {
    perfume* nuevo = (perfume*)malloc(sizeof(perfume));
    if (!nuevo) {
        printf("\033[1;31mError de memoria.\033[0m\n");
        exit(1);
    }
    strcpy(nuevo->nombre, nombre);
    strcpy(nuevo->marca, marca);
    nuevo->precio = precio;
    nuevo->stock = stock;
    nuevo->siguiente = NULL;
    return nuevo;
}

void AgregarPerfume(const char* nombre, const char* marca, float precio, int stock) {
    perfume* nuevo = CrearPerfume(nombre, marca, precio, stock);
    nuevo->siguiente = lista;
    lista = nuevo;
}

void ListaDePerfumes() {
    perfume* actual = lista;
    int num = 1;

    printf("\n\033[1;34m--- Lista de perfumes ---\033[0m\n");
    while (actual != NULL) {
        printf("\nPerfume %d:\n", num);
        printf("Nombre: %s\n", actual->nombre);
        printf("Marca: %s\n", actual->marca);
        printf("Precio: $%.2f\n", actual->precio);
        printf("Stock: %d unidades\n", actual->stock);
        actual = actual->siguiente;
        num++;
    }
}

void BuscarPerfume(const char* nombreBuscado) {
    perfume* actual = lista;
    while (actual != NULL) {
        if (strcmp(actual->nombre, nombreBuscado) == 0) {
            printf("\n\033[1;35mPerfume encontrado:\033[0m\n");
            printf("Nombre: %s\n", actual->nombre);
            printf("Marca: %s\n", actual->marca);
            printf("Precio: $%.2f\n", actual->precio);
            printf("Stock: %d unidades\n", actual->stock);
            return;
        }
        actual = actual->siguiente;
    }
    printf("\033[1;31mPerfume no encontrado.\033[0m\n");
}

void EditarPerfume(const char* nombre) {
    perfume* actual = lista;
    while (actual != NULL) {
        if (strcmp(actual->nombre, nombre) == 0) {
            printf("\n\033[1;36mEditando %s\033[0m\n", actual->nombre);
            printf("Nuevo precio: ");
            scanf("%f", &actual->precio);
            printf("Nuevo stock: ");
            scanf("%d", &actual->stock);
            getchar();
            printf("\033[1;32mActualización completada.\033[0m\n");
            return;
        }
        actual = actual->siguiente;
    }
    printf("\033[1;31mPerfume no encontrado para editar.\033[0m\n");
}

void GuardarPerfumes(const char* archivo) {
    FILE* f = fopen(archivo, "w");
    if (!f) {
        printf("\033[1;31mNo se pudo abrir el archivo para guardar.\033[0m\n");
        return;
    }

    perfume* actual = lista;
    while (actual != NULL) {
        fprintf(f, "%s;%s;%.2f;%d\n", actual->nombre, actual->marca, actual->precio, actual->stock);
        actual = actual->siguiente;
    }
    fclose(f);
}

void CargarPerfumes(const char* archivo) {
    FILE* f = fopen(archivo, "r");
    if (!f) return;

    char linea[4 * MAX];
    char nombre[MAX], marca[MAX];
    float precio;
    int stock;

    while (fgets(linea, sizeof(linea), f)) {
        if (sscanf(linea, "%99[^;];%99[^;];%f;%d", nombre, marca, &precio, &stock) == 4) {
            AgregarPerfume(nombre, marca, precio, stock);
        }
    }
    fclose(f);
}

void LiberarPerfumes() {
    perfume* actual = lista;
    while (actual != NULL) {
        perfume* temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
}
