#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAM_TXT 50

typedef struct Alumno {
    char nombre[TAM_TXT];
    bool asistencia;
    struct Alumno* siguiente;
} Alumno_t;

Alumno_t* agregarAlumno(Alumno_t* lista);
void mostrarLista(Alumno_t* lista);
void tomarAsistencia(Alumno_t* lista);
void liberarMemoria(Alumno_t* lista);

int main() {
    Alumno_t* lista = NULL;
    int opcion;

    do {
        printf("\nMenu de opciones:\n");
        printf("1. Agregar alumno\n");
        printf("2. Mostrar lista de alumnos\n");
        printf("3. Tomar asistencia\n");
        printf("4. Salir\n");
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion);
        getchar(); 

        switch(opcion) {
            case 1:
                lista = agregarAlumno(lista);
                break;
            case 2:
                mostrarLista(lista);
                break;
            case 3:
                tomarAsistencia(lista);
                break;
            case 4:
                liberarMemoria(lista);
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida. Por favor ingrese una opcion valida.\n");
        }
    } while(opcion != 4);

    return 0;
}

Alumno_t* agregarAlumno(Alumno_t* lista) {
    Alumno_t* nuevo = (Alumno_t*) malloc(sizeof(Alumno_t));
    if (!nuevo) {
        printf("Memoria insuficiente\n");
        return lista;
    }
    printf("Ingrese el nombre del alumno: ");
    fgets(nuevo->nombre, sizeof(nuevo->nombre), stdin);
    nuevo->asistencia = false;
    if (lista == NULL) {
        nuevo->siguiente = NULL;
        lista = nuevo;
    } else {
        Alumno_t* actual = lista;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
        nuevo->siguiente = NULL;
    }

    printf("Alumno agregado exitosamente!\n");
    return lista;
}

void mostrarLista(Alumno_t* lista) {
    if (lista == NULL) {
        printf("La lista esta vacia\n");
        return;
    }
    Alumno_t* actual = lista;
    while (actual != NULL) {
        printf("Nombre: %s\n", actual->nombre);
        printf("Asistencia: %s\n", actual->asistencia ? "Presente" : "Ausente");
        printf("------------------------\n");
        actual = actual->siguiente;
    }
}

void tomarAsistencia(Alumno_t* lista) {
    if (lista == NULL) {
        printf("La lista esta vacia\n");
        return;
    }

    Alumno_t* actual = lista;
    while (actual != NULL) {
        printf("Alumno: %s\n", actual->nombre);
        printf("Ingrese 1 si esta presente o 0 si esta ausente: ");
        int respuesta;
        scanf("%d", &respuesta);
        getchar();
        if (respuesta == 1) {
            actual->asistencia = true;
        } else {
            actual->asistencia = false;
        }
        actual = actual->siguiente;
    }
    printf("Asistencia registrada exitosamente!\n");
}

void liberarMemoria(Alumno_t* lista) {
    Alumno_t* actual = lista;
    while (actual != NULL) {
        Alumno_t* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    lista = NULL;
}
